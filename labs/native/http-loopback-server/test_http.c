/* Bits2Banking | Sammy Hegab, Umicom Foundation | MIT */
#include "http.h"
#include <stdio.h>
#include <string.h>
#define CHECK(q) do {if (!(q)){fprintf(stderr,"%s:%d: %s\n",__FILE__,__LINE__,#q);return 1;}} while(0)

static int Parsing(void)
{
    static const unsigned char request[] =
        "GET /health HTTP/1.1\r\nHost: 127.0.0.1:8765\r\nConnection: close\r\n\r\n";
    BtbHttpRequest parsed = {.method = BTB_HTTP_HEAD, .path = "unchanged", .hostPort = 111U};
    CHECK(BtbHttpParse(request, sizeof request - 2U, &parsed) == BTB_HTTP_INCOMPLETE);
    CHECK(parsed.method == BTB_HTTP_HEAD && strcmp(parsed.path, "unchanged") == 0);
    CHECK(BtbHttpParse(request, sizeof request - 1U, &parsed) == BTB_HTTP_OK);
    CHECK(parsed.method == BTB_HTTP_GET && strcmp(parsed.path, "/health") == 0);
    CHECK(parsed.hostPort == 8765U);
    static const unsigned char head[] =
        "HEAD / HTTP/1.1\r\nHost: localhost\r\n\r\n";
    CHECK(BtbHttpParse(head, sizeof head - 1U, &parsed) == BTB_HTTP_OK);
    CHECK(parsed.method == BTB_HTTP_HEAD && parsed.hostPort == 0U);
    const unsigned char badHost[] = "GET / HTTP/1.1\r\nHost: example.org\r\n\r\n";
    CHECK(BtbHttpParse(badHost, sizeof badHost - 1U, &parsed) == BTB_HTTP_INVALID);
    const unsigned char duplicate[] = "GET / HTTP/1.1\r\nHost: localhost\r\nHost: localhost\r\n\r\n";
    CHECK(BtbHttpParse(duplicate, sizeof duplicate - 1U, &parsed) == BTB_HTTP_INVALID);
    const unsigned char badMethod[] = "POST / HTTP/1.1\r\nHost: localhost\r\n\r\n";
    CHECK(BtbHttpParse(badMethod, sizeof badMethod - 1U, &parsed) == BTB_HTTP_METHOD_NOT_ALLOWED);
    const unsigned char bareLine[] = "GET / HTTP/1.1\nHost: localhost\n\n";
    CHECK(BtbHttpParse(bareLine, sizeof bareLine - 1U, &parsed) == BTB_HTTP_INVALID);
    const unsigned char traversal[] = "GET /../a HTTP/1.1\r\nHost: localhost\r\n\r\n";
    CHECK(BtbHttpParse(traversal, sizeof traversal - 1U, &parsed) == BTB_HTTP_INVALID);
    const unsigned char body[] = "GET / HTTP/1.1\r\nHost: localhost\r\nContent-Length: 0\r\n\r\n";
    CHECK(BtbHttpParse(body, sizeof body - 1U, &parsed) == BTB_HTTP_INVALID);
    const unsigned char extra[] = "GET / HTTP/1.1\r\nHost: localhost\r\n\r\nx";
    CHECK(BtbHttpParse(extra, sizeof extra - 1U, &parsed) == BTB_HTTP_INVALID);
    const unsigned char nul[] = {'G','E','T',' ','/',' ','H','T','T','P','/','1','.','1','\r','\n','H','o','s','t',':',' ',0,'\r','\n','\r','\n'};
    CHECK(BtbHttpParse(nul, sizeof nul, &parsed) == BTB_HTTP_INVALID);
    unsigned char tooLarge[BTB_HTTP_MAX_HEADER + 1U];
    (void)memset(tooLarge, 'A', sizeof tooLarge);
    CHECK(BtbHttpParse(tooLarge, sizeof tooLarge, &parsed) == BTB_HTTP_TOO_LARGE);
    return 0;
}
static int Responses(void)
{
    BtbHttpRequest get = {.method = BTB_HTTP_GET, .path = "/health", .hostPort = 8765U};
    char response[2048];
    size_t size = 0U;
    CHECK(BtbHttpRespond(&get, BTB_HTTP_OK, 8765U, response, sizeof response, &size));
    CHECK(size > 100U);
    CHECK(strstr(response, "HTTP/1.1 200 OK") != NULL);
    CHECK(strstr(response, "bits2banking-http-lab") != NULL);
    CHECK(strstr(response, "application/json") != NULL);
    get.method = BTB_HTTP_HEAD;
    CHECK(BtbHttpRespond(&get, BTB_HTTP_OK, 8765U, response, sizeof response, &size));
    CHECK(strstr(response, "Content-Length:") != NULL);
    CHECK(size < 550U && strstr(response, "bits2banking-http-lab") == NULL);
    CHECK(strstr(response, "HTTP/1.1 200 OK") != NULL);
    get.hostPort = 8900U;
    CHECK(BtbHttpRespond(&get, BTB_HTTP_OK, 8765U, response, sizeof response, &size));
    CHECK(strstr(response, "HTTP/1.1 400 Bad Request") != NULL);
    get.hostPort = 8765U;
    (void)strcpy(get.path, "/missing");
    CHECK(BtbHttpRespond(&get, BTB_HTTP_OK, 8765U, response, sizeof response, &size));
    CHECK(strstr(response, "HTTP/1.1 404 Not Found") != NULL);
    CHECK(BtbHttpRespond(NULL, BTB_HTTP_METHOD_NOT_ALLOWED, 8765U,
                         response, sizeof response, &size));
    CHECK(strstr(response, "405 Method Not Allowed") != NULL);
    CHECK(strstr(response, "Allow: GET, HEAD") != NULL);
    size = 8877U;
    CHECK(!BtbHttpRespond(&get, BTB_HTTP_OK, 8765U,
                          response, 8U, &size));
    CHECK(size == 8877U);
    return 0;
}
static int Mutations(void)
{
    const unsigned char valid[] = "GET /health HTTP/1.1\r\nHost: localhost\r\n\r\n";
    unsigned char changed[sizeof valid - 1U];
    BtbHttpRequest parsed = {0};
    for (size_t i = 0U; i < 8192U; ++i) {
        (void)memcpy(changed, valid, sizeof changed);
        const size_t where = (i * 37U) % sizeof changed;
        changed[where] ^= (unsigned char)(1U << (i % 8U));
        const BtbHttpResult result = BtbHttpParse(changed, sizeof changed, &parsed);
        CHECK(result == BTB_HTTP_OK || result == BTB_HTTP_INVALID ||
              result == BTB_HTTP_INCOMPLETE || result == BTB_HTTP_METHOD_NOT_ALLOWED ||
              result == BTB_HTTP_TOO_LARGE);
    }
    return 0;
}
int main(int argc, char **argv)
{
    if (argc != 2) return 2;
    if (strcmp(argv[1], "parsing") == 0) return Parsing();
    if (strcmp(argv[1], "responses") == 0) return Responses();
    if (strcmp(argv[1], "mutations") == 0) return Mutations();
    return 2;
}
