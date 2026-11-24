<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-web-server-in-c/16-distinguish-dispatch-from-delivery.md

PURPOSE:
Explain the lesson: Distinguish dispatch from delivery.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Distinguish dispatch from delivery

A server can finish an operation and still fail to deliver its reply. The caller then has an uncertain outcome, not proof that nothing happened.

## Prepare

Read the second Exchange call in exchange.c. It enables fail_write while leaving reading and routing unchanged.

The handler increments calls and prepares ready. The first attempted write then returns IO_ERROR.

## Predict the result

| Observation | Expected value |
| --- | --- |
| Handler calls | 1 |
| dispatched | true |
| response_complete | false |
| bytes sent | 0 |
| Overall result | IO_ERROR |

The two booleans answer different questions. Routing occurred; complete response delivery did not.

## Compare dispatch counters with accepted bytes

The service counts the requests it handles and the bytes of the application body it selects. The counters for 2xx, 4xx and 5xx group successful replies, request refusals and server failures. The exchange separately reports `bytes_sent`, which counts all bytes accepted by its writer, including response headers.

The three cases below use the same request and a fresh service each time. The numbers in the counters column appear in the order 2xx/4xx/5xx. The HTTP status is the one Framework prepares for the writer.

| Case | HTTP status | Counters | Selected body bytes | Accepted bytes |
| --- | --- | --- | --- | --- |
| Writer refuses a ready reply | 200 | 1/0/0 | 5 | Zero |
| Gate supplies an intentional refusal | 403 | 0/1/0 | 6 | Nonzero |
| Gate returns an operational error | 500 | 0/0/1 | 0 | Nonzero |

When the writer refuses the successful response, the five selected bytes stay in the service counter and the exchange reports zero accepted bytes. An intentional 403 selects its six-byte explanation. If dispatch itself fails, Framework counts a 500 with zero selected application bytes. The writer can still accept the separate generic error reply.

### Try the three cases in memory

The C23 example supplies its request and writer in memory. Its writer makes the acceptance decision visible to the learner.

~~~c
#include "umicom/web/connection.h"
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum Mode { WRITE_ERROR, REFUSE, DISPATCH_ERROR } Mode;
typedef struct Memory { Mode mode; size_t offset; } Memory;
typedef struct Example {
    const char *name;
    Mode mode;
    int http;
    uint64_t selected;
    UmiStatus outcome;
} Example;

static UmiStatus ReadRequest(void *context, void *bytes, size_t capacity, size_t *count)
{
    /* Feed the same complete request in as many reads as the caller needs. */
    static const char request[] = "GET /demo HTTP/1.1\r\nHost: localhost\r\n\r\n";
    Memory *memory = context;
    size_t remaining = sizeof(request) - 1U - memory->offset;
    *count = remaining < capacity ? remaining : capacity;
    memcpy(bytes, request + memory->offset, *count);
    memory->offset += *count;
    return *count == 0U ? UMI_STATUS_UNAVAILABLE : UMI_STATUS_OK;
}

static UmiStatus AcceptReply(void *context, const void *bytes, size_t length, size_t *count)
{
    /* Model acceptance by a writer without sending the bytes anywhere. */
    const Memory *memory = context;
    (void)bytes;
    *count = memory->mode == WRITE_ERROR ? 0U : length;
    return memory->mode == WRITE_ERROR ? UMI_STATUS_IO_ERROR : UMI_STATUS_OK;
}

static UmiStatus Gate(const UmiWebRequest *request, UmiWebResponse *response,
    bool *accepted, void *context)
{
    const Memory *memory = context;
    (void)request;
    /* A completed 403 response is a different decision from a gate error. */
    *accepted = memory->mode == WRITE_ERROR;
    if (memory->mode == DISPATCH_ERROR) return UMI_STATUS_IO_ERROR;
    if (*accepted) return UMI_STATUS_OK;
    return umi_web_response_set_text(response, 403, "text/plain", "denied");
}

static UmiStatus Reply(const UmiWebRequest *request, UmiWebResponse *response, void *context)
{
    (void)request;
    (void)context;
    return umi_web_response_set_text(response, 200, "text/plain", "ready");
}

static bool CheckExample(const Example *example)
{
    Memory memory = {example->mode, 0U};
    UmiWebService *service = NULL;
    if (umi_web_service_create(&service) != UMI_STATUS_OK) return false;
    if (UmiWebServiceSetRequestGate(service, Gate, &memory) != UMI_STATUS_OK ||
        UmiWebRouterSetFallback(umi_web_service_router(service), Reply, NULL) != UMI_STATUS_OK) {
        umi_web_service_destroy(service);
        return false;
    }

    /* The service owns the counters and the exchange reports writer progress. */
    const UmiWebConnectionIo io = {&memory, ReadRequest, AcceptReply};
    UmiWebExchangeResult exchange;
    UmiStatus status = UmiWebConnectionProcess(service, &io, 1024U, NULL, &exchange);
    const UmiWebMetrics *metrics = umi_web_service_metrics(service);
    const bool complete = example->mode != WRITE_ERROR;
    const UmiStatus dispatch = example->mode == DISPATCH_ERROR ? UMI_STATUS_IO_ERROR : UMI_STATUS_OK;
    const bool counters_agree = metrics->requests == 1U &&
        metrics->responses_2xx == (example->http == 200 ? 1U : 0U) &&
        metrics->responses_4xx == (example->http == 403 ? 1U : 0U) &&
        metrics->responses_5xx == (example->http == 500 ? 1U : 0U) &&
        metrics->bytes_out == example->selected;
    const bool writer_agrees = complete
        ? exchange.bytes_sent > example->selected
        : exchange.bytes_sent == 0U;
    const bool passed = counters_agree && writer_agrees && exchange.dispatched &&
        exchange.dispatch_status == dispatch && exchange.response_complete == complete &&
        exchange.response_status == example->http && status == example->outcome;

    if (passed) {
        printf("%s: HTTP %d, counters %" PRIu64 "/%" PRIu64 "/%" PRIu64
               ", selected %" PRIu64 ", accepted %s\n",
               example->name, exchange.response_status, metrics->responses_2xx,
               metrics->responses_4xx, metrics->responses_5xx, metrics->bytes_out,
               exchange.bytes_sent == 0U ? "zero" : "nonzero");
    }
    umi_web_service_destroy(service);
    return passed;
}

int main(void)
{
    const Example examples[] = {
        {"Writer refused", WRITE_ERROR, 200, 5U, UMI_STATUS_IO_ERROR},
        {"Intentional refusal", REFUSE, 403, 6U, UMI_STATUS_OK},
        {"Dispatch failed", DISPATCH_ERROR, 500, 0U, UMI_STATUS_IO_ERROR}
    };
    for (size_t i = 0U; i < sizeof(examples) / sizeof(examples[0]); ++i) {
        if (!CheckExample(&examples[i])) {
            fprintf(stderr, "%s: observation differed from the prediction\n", examples[i].name);
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
}
~~~

### Build and compare the result

Save the C example as `observe-dispatch.c` in a new practice folder. Save the build file below as `CMakeLists.txt` in the same folder. Use a C23-capable compiler and a matching Framework SDK with the web component and current dispatch accounting.

~~~cmake
cmake_minimum_required(VERSION 3.24)
project(ObserveDispatch LANGUAGES C)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
find_package(UmicomFramework CONFIG REQUIRED COMPONENTS web)
add_executable(observe-dispatch observe-dispatch.c)
target_link_libraries(observe-dispatch PRIVATE Umicom::web)
~~~

Open PowerShell in the practice folder. Replace the SDK path with your actual prefix. Run each command in order and stop on errors.

~~~powershell
$sdk = 'C:\umicom\installed\applications'
cmake -S . -B build -G Ninja "-DCMAKE_PREFIX_PATH=$sdk"
cmake --build build --target observe-dispatch
.\build\observe-dispatch.exe
~~~

Compare the three lines with this output.

~~~text
Writer refused: HTTP 200, counters 1/0/0, selected 5, accepted zero
Intentional refusal: HTTP 403, counters 0/1/0, selected 6, accepted nonzero
Dispatch failed: HTTP 500, counters 0/0/1, selected 0, accepted nonzero
~~~

If a counter differs, check the dispatch status and the writer's accepted bytes separately. If CMake reports that the package is missing, check the SDK prefix for `UmicomFrameworkConfig.cmake`.

To compare the related cases in a configured Framework build, substitute its build path and run this selection.

~~~powershell
ctest --test-dir 'C:\path\to\framework-build' --no-tests=error -R '^framework[.]web[.](request_gate[.]gate-(accept|refuse|failure)|response_body[.](body-failure|body-conflict|invalid-header))$' --output-on-failure
~~~

[Service metrics API](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/web/service.h) · [Connection exchange API](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/web/connection.h) · [Read response status and body length](45-read-response-status-and-body.md)

## Apply the idea

Imagine a handler that records a payment or adds a media job. Blindly repeating it after a lost reply could duplicate the operation. A production design needs an explicit duplicate-request policy and a way to inspect an operation's outcome.

This lab intentionally uses a counter so no external side effect occurs. It teaches the uncertainty before adding durable state.

## Exercise

Draw a timeline with request completion, handler entry, handler exit, write failure and cleanup. Mark the point after which automatic retry becomes an application policy decision.

## Recovery

Preserve the exchange result along with the status. Logging only IO_ERROR loses the useful distinction between a request that was never dispatched and one whose reply was lost.

For a real connection, the host must close the transport after either outcome. Framework borrows it; ownership remains with the host.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-http-contracts/exchange.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](15-handle-short-transfers.md) · [Next: Own an incomplete request](17-own-an-incomplete-request.md)

