/*-----------------------------------------------------------------------------
 * Bits2Banking | Umicom Foundation
 * File: labs/native/http-loopback-server/route_service.c
 * PURPOSE: Single-owner route registration, dispatch and bounded HTTP output.
 * AUTHOR: Sammy Hegab | LICENCE: MIT
 *---------------------------------------------------------------------------*/
#include "route_service.h"
#include <stdio.h>
#include <string.h>
#include <limits.h>

static int BtbRouteStatusSupported(unsigned code)
{
    return code == 200U || code == 400U || code == 403U || code == 404U ||
           code == 409U || code == 500U || code == 503U;
}
static int BtbRouteMediaSupported(BtbRouteMedia media)
{
    return media == BTB_ROUTE_PLAIN_TEXT || media == BTB_ROUTE_JSON ||
           media == BTB_ROUTE_HTML;
}
static int BtbRoutePathValid(const char *path)
{
    if (path == NULL || path[0] != '/') return 0;
    size_t size = 0U;
    while (size < BTB_ROUTE_PATH_LIMIT && path[size] != '\0') {
        const unsigned char c = (unsigned char)path[size];
        if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') ||
              (c >= '0' && c <= '9') || c == '-' || c == '_' ||
              c == '/')) return 0;
        ++size;
    }
    return size != 0U && size < BTB_ROUTE_PATH_LIMIT;
}
static int BtbRouteOwnerValid(const BtbRouteService *service)
{
    return service != NULL && service->self == service &&
           service->state >= BTB_ROUTE_CONFIGURING &&
           service->state <= BTB_ROUTE_STOPPED && service->count <= BTB_ROUTE_LIMIT;
}
BtbRouteResult BtbRouteServiceInit(BtbRouteService *service)
{
    if (service == NULL || service->self != NULL ||
        service->state != BTB_ROUTE_UNINITIALISED || service->count != 0U ||
        service->busy != 0U) return BTB_ROUTE_BAD_STATE;
    /* Existing route descriptors must not survive a new lifetime. */
    *service = (BtbRouteService){0};
    service->self = service;
    service->state = BTB_ROUTE_CONFIGURING;
    return BTB_ROUTE_OK;
}
BtbRouteResult BtbRouteServiceRegister(BtbRouteService *service,
                                       const char *path, BtbRouteHandler handler,
                                       void *context)
{
    if (!BtbRouteOwnerValid(service) || service->state != BTB_ROUTE_CONFIGURING)
        return BTB_ROUTE_BAD_STATE;
    if (!BtbRoutePathValid(path) || handler == NULL) return BTB_ROUTE_INVALID;
    for (size_t i = 0U; i < service->count; ++i)
        if (strcmp(service->routes[i].path, path) == 0) return BTB_ROUTE_DUPLICATE;
    if (service->count == BTB_ROUTE_LIMIT) return BTB_ROUTE_CAPACITY;
    const size_t length = strlen(path);
    BtbRouteEntry *entry = &service->routes[service->count];
    memcpy(entry->path, path, length + 1U);
    entry->handler = handler;
    entry->context = context;
    ++service->count;
    return BTB_ROUTE_OK;
}
BtbRouteResult BtbRouteServiceStart(BtbRouteService *service)
{
    if (!BtbRouteOwnerValid(service) ||
        (service->state != BTB_ROUTE_CONFIGURING && service->state != BTB_ROUTE_STOPPED))
        return BTB_ROUTE_BAD_STATE;
    if (service->busy != 0U) return BTB_ROUTE_BUSY;
    service->state = BTB_ROUTE_READY;
    return BTB_ROUTE_OK;
}
BtbRouteResult BtbRouteServiceStop(BtbRouteService *service)
{
    if (!BtbRouteOwnerValid(service) || service->state != BTB_ROUTE_READY)
        return BTB_ROUTE_BAD_STATE;
    if (service->busy != 0U) return BTB_ROUTE_BUSY;
    service->state = BTB_ROUTE_STOPPED;
    return BTB_ROUTE_OK;
}
BtbRouteResult BtbRouteResponseSet(BtbRouteResponse *out, unsigned status,
                                   BtbRouteMedia media, const void *body,
                                   size_t length)
{
    if (out == NULL || !BtbRouteStatusSupported(status) ||
        !BtbRouteMediaSupported(media) || length > BTB_ROUTE_BODY_LIMIT ||
        (length != 0U && body == NULL)) return BTB_ROUTE_INVALID;
    BtbRouteResponse candidate = {0};
    candidate.statusCode = status;
    candidate.media = media;
    candidate.bodyLength = length;
    if (length != 0U) memcpy(candidate.body, body, length);
    *out = candidate;
    return BTB_ROUTE_OK;
}
BtbRouteResult BtbRouteServiceDispatch(BtbRouteService *service,
                                        const BtbHttpRequest *request,
                                        BtbRouteResponse *out)
{
    if (!BtbRouteOwnerValid(service) || service->state != BTB_ROUTE_READY)
        return BTB_ROUTE_BAD_STATE;
    if (service->busy != 0U) return BTB_ROUTE_BUSY;
    if (request == NULL || out == NULL ||
        (request->method != BTB_HTTP_GET && request->method != BTB_HTTP_HEAD) ||
        request->path[0] != '/' ||
        memchr(request->path, '\0', sizeof(request->path)) == NULL)
        return BTB_ROUTE_INVALID;
    /* Static filenames may contain dots. Routing recognises only registered
     * exact paths; other parsed targets are NOT_FOUND for filesystem fallback,
     * not 503 Service Unavailable. Only registration has the narrower grammar. */
    for (size_t i = 0U; i < service->count; ++i) {
        BtbRouteEntry *entry = &service->routes[i];
        if (strcmp(entry->path, request->path) != 0) continue;
        BtbRouteResponse candidate = {0};
        service->busy = 1U;
        BtbRouteResult result = entry->handler(request, &candidate, entry->context);
        service->busy = 0U;
        if (result != BTB_ROUTE_OK) return result;
        if (!BtbRouteStatusSupported(candidate.statusCode) ||
            !BtbRouteMediaSupported(candidate.media) ||
            candidate.bodyLength > sizeof(candidate.body)) return BTB_ROUTE_INVALID;
        *out = candidate;
        if (service->dispatched < UINT64_MAX) ++service->dispatched;
        return BTB_ROUTE_OK;
    }
    return BTB_ROUTE_NOT_FOUND;
}
static const char *BtbRouteReason(unsigned status)
{
    switch (status) {
        case 200U: return "OK";
        case 400U: return "Bad Request";
        case 403U: return "Forbidden";
        case 404U: return "Not Found";
        case 409U: return "Conflict";
        case 500U: return "Internal Server Error";
        case 503U: return "Service Unavailable";
        default: return NULL;
    }
}
static const char *BtbRouteMediaText(BtbRouteMedia media)
{
    switch (media) {
        case BTB_ROUTE_PLAIN_TEXT: return "text/plain; charset=utf-8";
        case BTB_ROUTE_JSON: return "application/json; charset=utf-8";
        case BTB_ROUTE_HTML: return "text/html; charset=utf-8";
        default: return NULL;
    }
}
BtbRouteResult BtbRouteEncode(const BtbHttpRequest *request,
                              const BtbRouteResponse *response,
                              char *buffer, size_t capacity,
                              size_t *outBytes, size_t *outHeaderBytes)
{
    if (request == NULL || response == NULL || buffer == NULL ||
        outBytes == NULL || outHeaderBytes == NULL ||
        (request->method != BTB_HTTP_GET && request->method != BTB_HTTP_HEAD) ||
        !BtbRouteStatusSupported(response->statusCode) ||
        !BtbRouteMediaSupported(response->media) ||
        response->bodyLength > sizeof(response->body)) return BTB_ROUTE_INVALID;
    const char *reason = BtbRouteReason(response->statusCode);
    const char *media = BtbRouteMediaText(response->media);
    char headers[1024];
    const int count = snprintf(headers, sizeof headers,
        "HTTP/1.1 %u %s\r\n"
        "Content-Type: %s\r\nContent-Length: %zu\r\n"
        "Connection: close\r\nCache-Control: no-store\r\n"
        "X-Content-Type-Options: nosniff\r\n"
        "Content-Security-Policy: default-src 'none'; base-uri 'none'; "
        "frame-ancestors 'none'\r\n\r\n",
        response->statusCode, reason, media, response->bodyLength);
    if (count <= 0 || (size_t)count >= sizeof headers) return BTB_ROUTE_CAPACITY;
    const size_t headerBytes = (size_t)count;
    const size_t wireBody = request->method == BTB_HTTP_HEAD ? 0U : response->bodyLength;
    if (headerBytes > capacity || wireBody > capacity - headerBytes)
        return BTB_ROUTE_CAPACITY;
    memcpy(buffer, headers, headerBytes);
    if (wireBody != 0U) memcpy(buffer + headerBytes, response->body, wireBody);
    *outHeaderBytes = headerBytes;
    *outBytes = headerBytes + wireBody;
    return BTB_ROUTE_OK;
}
const char *BtbRouteResultText(BtbRouteResult result)
{
    switch (result) {
        case BTB_ROUTE_OK: return "ok";
        case BTB_ROUTE_INVALID: return "invalid input";
        case BTB_ROUTE_CAPACITY: return "capacity exceeded";
        case BTB_ROUTE_DUPLICATE: return "duplicate route";
        case BTB_ROUTE_NOT_FOUND: return "not found";
        case BTB_ROUTE_BAD_STATE: return "invalid service state";
        case BTB_ROUTE_BUSY: return "request in progress";
    }
    return "unknown";
}
