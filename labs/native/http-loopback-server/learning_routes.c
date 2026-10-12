/*-----------------------------------------------------------------------------
 * Bits2Banking | Umicom Foundation
 * File: labs/native/http-loopback-server/learning_routes.c
 * PURPOSE: Compose real teaching endpoints from the shared route contract.
 * AUTHOR: Sammy Hegab | LICENCE: MIT
 *---------------------------------------------------------------------------*/
#include "learning_routes.h"
#include <string.h>

/* Application callbacks supply content; they do not manage HTTP framing,
 * sockets, routing tables or response-completion state. */
static BtbRouteResult Courses(const BtbHttpRequest *request,
                               BtbRouteResponse *out, void *context)
{
    (void)request;
    (void)context;
    static const char contents[] =
        "{\"courses\":[\"Computer Architecture\",\"C23\",\"Assembly\",\"Umicom Kernel\"]}\n";
    return BtbRouteResponseSet(out, 200U, BTB_ROUTE_JSON,
                               contents, sizeof contents - 1U);
}
static BtbRouteResult Status(const BtbHttpRequest *request,
                              BtbRouteResponse *out, void *context)
{
    (void)request;
    (void)context;
    static const char contents[] =
        "{\"service\":\"bits2banking-routes\",\"state\":\"ready\",\"scope\":\"loopback\"}\n";
    return BtbRouteResponseSet(out, 200U, BTB_ROUTE_JSON,
                               contents, sizeof contents - 1U);
}
static BtbRouteResult Workshop(const BtbHttpRequest *request,
                                BtbRouteResponse *out, void *context)
{
    (void)request;
    (void)context;
    static const char contents[] =
        "<!doctype html><html lang=\"en\"><meta charset=\"utf-8\">"
        "<title>Bits2Banking Routes</title><main><h1>C23 routing workshop</h1>"
        "<p>Read <a href=\"/api/courses\">our course list</a>.</p>"
        "</main></html>\n";
    return BtbRouteResponseSet(out, 200U, BTB_ROUTE_HTML,
                               contents, sizeof contents - 1U);
}
BtbRouteResult BtbLearningRoutesInstall(BtbRouteService *service)
{
    if (service == NULL) return BTB_ROUTE_INVALID;
    BtbRouteResult result = BtbRouteServiceRegister(service, "/api/courses", Courses, NULL);
    if (result == BTB_ROUTE_OK)
        result = BtbRouteServiceRegister(service, "/api/status", Status, NULL);
    if (result == BTB_ROUTE_OK)
        result = BtbRouteServiceRegister(service, "/workshop", Workshop, NULL);
    return result;
}
