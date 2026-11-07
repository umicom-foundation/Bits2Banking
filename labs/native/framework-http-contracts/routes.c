/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/framework-http-contracts/routes.c
 *
 * PURPOSE:
 *   Register an exact route with a borrowed context and observe a missing route.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include "check.h"
#include "umicom/web/connection.h"
#include <stdlib.h>
static UmiStatus Health(const UmiWebRequest *request, UmiWebResponse *response, void *context)
{
    (void)request;
    size_t *calls = context;
    ++*calls;
    return umi_web_response_set_text(response, 200, "text/plain", "ready");
}
int main(void)
{
    UmiWebService *service = NULL;
    REQUIRE(umi_web_service_create(&service) == UMI_STATUS_OK);
    UmiWebRequest *request = calloc(1U, sizeof(*request));
    UmiWebResponse *response = calloc(1U, sizeof(*response));
    if (!request || !response) {
        free(request); free(response); umi_web_service_destroy(service); return 1;
    }
    size_t calls = 0U;
    UmiWebRoute route;
    UmiStatus status = umi_web_route_init(&route, UMI_HTTP_METHOD_GET, "/health", Health, &calls);
    if (status == UMI_STATUS_OK)
        status = umi_web_router_add(umi_web_service_router(service), &route);
    const char found[] = "GET /health HTTP/1.1\r\nHost: localhost\r\n\r\n";
    const char missing[] = "GET /missing HTTP/1.1\r\nHost: localhost\r\n\r\n";
    int success = status == UMI_STATUS_OK;
    /* Read complete messages through the canonical parser, then route them. */
    if (success) {
        status = UmiWebRequestParseStrict(found, sizeof(found) - 1U, 1024U, request);
        if (status == UMI_STATUS_OK) status = umi_web_service_handle(service, request, response);
        success = status == UMI_STATUS_OK && response->status == 200 && calls == 1U;
    }
    if (success) {
        status = UmiWebRequestParseStrict(missing, sizeof(missing) - 1U, 1024U, request);
        if (status == UMI_STATUS_OK) status = umi_web_service_handle(service, request, response);
        success = status == UMI_STATUS_OK && response->status == 404 && calls == 1U;
    }
    /* Destroy the borrower before the local context leaves scope. */
    umi_web_service_destroy(service);
    free(request); free(response);
    REQUIRE(success);
    puts("Exact and missing-route expectations satisfied.");
    return 0;
}
