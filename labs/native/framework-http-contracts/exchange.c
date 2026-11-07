/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/framework-http-contracts/exchange.c
 *
 * PURPOSE:
 *   Drive Framework with short memory transfers and observe a failed response after dispatch.
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
#include <string.h>
typedef struct MemoryWire {
    const unsigned char *input;
    size_t length, offset, output_length, calls;
    unsigned char output[1024];
    bool fail_write;
} MemoryWire;
static UmiStatus Read(void *context, void *bytes, size_t capacity, size_t *out)
{
    MemoryWire *wire = context;
    *out = 0U;
    if (wire->offset == wire->length) return UMI_STATUS_UNAVAILABLE;
    if (capacity == 0U) return UMI_STATUS_INVALID_ARGUMENT;
    /* One byte at a time proves that request boundaries are not read boundaries. */
    ((unsigned char *)bytes)[0] = wire->input[wire->offset++];
    *out = 1U;
    return UMI_STATUS_OK;
}
static UmiStatus Write(void *context, const void *bytes, size_t length, size_t *out)
{
    MemoryWire *wire = context;
    *out = 0U;
    if (wire->fail_write) return UMI_STATUS_IO_ERROR;
    const size_t count = length < 3U ? length : 3U;
    if (count == 0U || count > sizeof(wire->output) - wire->output_length)
        return UMI_STATUS_CAPACITY_EXCEEDED;
    memcpy(wire->output + wire->output_length, bytes, count);
    wire->output_length += count;
    *out = count;
    return UMI_STATUS_OK;
}
static UmiStatus Handle(const UmiWebRequest *request, UmiWebResponse *response, void *context)
{
    (void)request;
    MemoryWire *wire = context;
    ++wire->calls;
    return umi_web_response_set_text(response, 200, "text/plain", "ready");
}
static int Exchange(bool fail)
{
    static const unsigned char request[] = "GET /health HTTP/1.1\r\nHost: localhost\r\n\r\n";
    MemoryWire wire = {.input = request, .length = sizeof(request) - 1U, .fail_write = fail};
    UmiWebService *service = NULL;
    REQUIRE(umi_web_service_create(&service) == UMI_STATUS_OK);
    UmiWebRoute route;
    UmiStatus status = umi_web_route_init(&route, UMI_HTTP_METHOD_GET, "/health", Handle, &wire);
    if (status == UMI_STATUS_OK) status = umi_web_router_add(umi_web_service_router(service), &route);
    UmiWebExchangeResult result = {0};
    const UmiWebConnectionIo io = {&wire, Read, Write};
    if (status == UMI_STATUS_OK)
        status = UmiWebConnectionProcess(service, &io, 1024U, NULL, &result);
    umi_web_service_destroy(service);
    REQUIRE(status == (fail ? UMI_STATUS_IO_ERROR : UMI_STATUS_OK));
    REQUIRE(wire.calls == 1U && result.dispatched);
    REQUIRE(result.response_complete == !fail);
    REQUIRE(result.bytes_received == wire.length);
    REQUIRE(result.bytes_sent == wire.output_length);
    REQUIRE(fail ? wire.output_length == 0U : wire.output_length > 5U);
    return 0;
}
int main(void)
{
    REQUIRE(Exchange(false) == 0);
    REQUIRE(Exchange(true) == 0);
    puts("Fragmented transport and post-dispatch failure expectations satisfied.");
    return 0;
}
