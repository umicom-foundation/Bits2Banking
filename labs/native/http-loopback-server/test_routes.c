/*-----------------------------------------------------------------------------
 * Bits2Banking | Umicom Foundation
 * File: labs/native/http-loopback-server/test_routes.c
 * PURPOSE: Reject invalid routes and verify owned, bounded GET/HEAD replies.
 * AUTHOR: Sammy Hegab | LICENCE: MIT
 *---------------------------------------------------------------------------*/
#include "learning_routes.h"
#include "route_service.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CHECK(condition) do { if (!(condition)) { \
    fprintf(stderr, "FAIL %s:%d: %s\n", __FILE__, __LINE__, #condition); return 1; \
} } while (0)

static int Contains(const char *bytes, size_t count, const char *needle)
{
    const size_t length = strlen(needle);
    if (length > count) return 0;
    for (size_t i = 0U; i <= count - length; ++i)
        if (memcmp(bytes + i, needle, length) == 0) return 1;
    return 0;
}
static BtbRouteResult Echo(const BtbHttpRequest *request,
                           BtbRouteResponse *out, void *context)
{
    (void)request;
    const char *text = context;
    return BtbRouteResponseSet(out, 200U, BTB_ROUTE_PLAIN_TEXT,
                               text, strlen(text));
}
static BtbRouteResult Deny(const BtbHttpRequest *request,
                           BtbRouteResponse *out, void *context)
{
    (void)request; (void)out; (void)context;
    return BTB_ROUTE_INVALID;
}
static BtbRouteResult TryStop(const BtbHttpRequest *request,
                              BtbRouteResponse *out, void *context)
{
    (void)request;
    BtbRouteService *service = context;
    if (BtbRouteServiceStop(service) != BTB_ROUTE_BUSY) return BTB_ROUTE_BAD_STATE;
    const char reply[] = "still-running";
    return BtbRouteResponseSet(out, 200U, BTB_ROUTE_PLAIN_TEXT,
                               reply, sizeof reply - 1U);
}
static int Routes(void)
{
    BtbRouteService owner = {0};
    CHECK(BtbRouteServiceInit(&owner) == BTB_ROUTE_OK);
    CHECK(BtbLearningRoutesInstall(&owner) == BTB_ROUTE_OK);
    CHECK(owner.count == 3U);
    CHECK(BtbRouteServiceRegister(&owner, "/api/status", Echo, "x") == BTB_ROUTE_DUPLICATE);
    CHECK(BtbRouteServiceRegister(&owner, "/bad/../path", Echo, "x") == BTB_ROUTE_INVALID);
    CHECK(BtbRouteServiceStart(&owner) == BTB_ROUTE_OK);
    CHECK(BtbRouteServiceRegister(&owner, "/late", Echo, "x") == BTB_ROUTE_BAD_STATE);
    BtbHttpRequest request = {.method = BTB_HTTP_GET};
    memcpy(request.path, "/api/courses", sizeof "/api/courses");
    BtbRouteResponse response = {0};
    CHECK(BtbRouteServiceDispatch(&owner, &request, &response) == BTB_ROUTE_OK);
    CHECK(response.statusCode == 200U && response.media == BTB_ROUTE_JSON);
    /* Verify JSON content without relying on a nonstandard substring parser. */
    const char name[] = "C23";
    int found = 0;
    for (size_t i = 0U; i + sizeof name - 1U <= response.bodyLength; ++i)
        if (memcmp(response.body + i, name, sizeof name - 1U) == 0) found = 1;
    CHECK(found);
    char buffer[4096];
    size_t written = 0U, headers = 0U;
    CHECK(BtbRouteEncode(&request, &response, buffer, sizeof buffer,
                          &written, &headers) == BTB_ROUTE_OK);
    CHECK(written == headers + response.bodyLength);
    CHECK(memcmp(buffer, "HTTP/1.1 200 OK", sizeof "HTTP/1.1 200 OK" - 1U) == 0);
    CHECK(Contains(buffer, written, "Content-Length:"));
    BtbHttpRequest head = request;
    head.method = BTB_HTTP_HEAD;
    CHECK(BtbRouteEncode(&head, &response, buffer, sizeof buffer,
                          &written, &headers) == BTB_ROUTE_OK);
    CHECK(written == headers);
    CHECK(Contains(buffer, written, "Content-Length:"));
    CHECK(BtbRouteEncode(&request, &response, buffer, 10U,
                          &written, &headers) == BTB_ROUTE_CAPACITY);
    CHECK(written == headers);
    /* A site file with an extension must be a normal fallback, not 503. */
    memcpy(request.path, "/assets/site.css", sizeof "/assets/site.css");
    CHECK(BtbRouteServiceDispatch(&owner, &request, &response) == BTB_ROUTE_NOT_FOUND);
    return 0;
}

static int RouteMutations(void)
{
    /* Every candidate contains an invalid dot, even when all surrounding
     * bytes are otherwise plausible. No refused candidate may mutate routes. */
    BtbRouteService service = {0};
    CHECK(BtbRouteServiceInit(&service) == BTB_ROUTE_OK);
    const BtbRouteEntry original = service.routes[0];
    unsigned state = 0x9e3779b9U;
    for (size_t round = 0U; round < 4096U; ++round) {
        char path[BTB_ROUTE_PATH_LIMIT + 12U] = {'/', 'a', 0};
        state = state * 1664525U + 1013904223U;
        size_t count = 3U + (size_t)(state % (BTB_ROUTE_PATH_LIMIT + 8U));
        for (size_t i = 1U; i < count; ++i) path[i] = 'a';
        path[count] = '\0';
        path[1U + (size_t)(state % (unsigned)(count - 1U))] = '.';
        CHECK(BtbRouteServiceRegister(&service, path, Echo, "sample") == BTB_ROUTE_INVALID);
        CHECK(service.count == 0U);
        CHECK(memcmp(&service.routes[0], &original, sizeof original) == 0);
    }
    const char ok[] = "/notes";
    CHECK(BtbRouteServiceRegister(&service, ok, Echo, "notes") == BTB_ROUTE_OK);
    CHECK(BtbRouteServiceStop(&service) == BTB_ROUTE_BAD_STATE);
    CHECK(BtbRouteServiceStart(&service) == BTB_ROUTE_OK);
    CHECK(BtbRouteServiceStop(&service) == BTB_ROUTE_OK);
    return 0;
}

static int Lifetime(void)
{
    BtbRouteService owner = {0};
    CHECK(BtbRouteServiceInit(&owner) == BTB_ROUTE_OK);
    CHECK(BtbRouteServiceRegister(&owner, "/busy", TryStop, &owner) == BTB_ROUTE_OK);
    CHECK(BtbRouteServiceRegister(&owner, "/deny", Deny, NULL) == BTB_ROUTE_OK);
    CHECK(BtbRouteServiceStart(&owner) == BTB_ROUTE_OK);
    BtbHttpRequest request = {.method = BTB_HTTP_GET};
    memcpy(request.path, "/busy", sizeof "/busy");
    BtbRouteResponse response = {0};
    CHECK(BtbRouteServiceDispatch(&owner, &request, &response) == BTB_ROUTE_OK);
    CHECK(owner.dispatched == 1U && owner.state == BTB_ROUTE_READY);
    memset(&response, 0xA5, sizeof response);
    BtbRouteResponse before = response;
    memcpy(request.path, "/deny", sizeof "/deny");
    CHECK(BtbRouteServiceDispatch(&owner, &request, &response) == BTB_ROUTE_INVALID);
    CHECK(memcmp(&response, &before, sizeof response) == 0);
    CHECK(owner.dispatched == 1U);
    memcpy(request.path, "/not-found", sizeof "/not-found");
    CHECK(BtbRouteServiceDispatch(&owner, &request, &response) == BTB_ROUTE_NOT_FOUND);
    CHECK(memcmp(&response, &before, sizeof response) == 0);
    CHECK(BtbRouteServiceStop(&owner) == BTB_ROUTE_OK);
    CHECK(BtbRouteServiceDispatch(&owner, &request, &response) == BTB_ROUTE_BAD_STATE);
    CHECK(BtbRouteServiceStart(&owner) == BTB_ROUTE_OK);
    CHECK(BtbRouteServiceStop(&owner) == BTB_ROUTE_OK);
    BtbRouteService copy = owner;
    CHECK(BtbRouteServiceStart(&copy) == BTB_ROUTE_BAD_STATE);
    return 0;
}
int main(int argc, char **argv)
{
    if (argc != 2) return 2;
    if (strcmp(argv[1], "routing") == 0) return Routes();
    if (strcmp(argv[1], "lifetime") == 0) return Lifetime();
    if (strcmp(argv[1], "mutations") == 0) return RouteMutations();
    return 2;
}
