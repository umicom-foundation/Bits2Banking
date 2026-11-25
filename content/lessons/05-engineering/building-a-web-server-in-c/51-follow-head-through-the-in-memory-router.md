<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-web-server-in-c/51-follow-head-through-the-in-memory-router.md

PURPOSE:
Follow a HEAD request through the in-memory router

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Follow a HEAD request through the in-memory router

Lesson 50 started with a response that already contained three bytes. This time, start with the request. The Framework runtime can process a complete HTTP request stored in memory, choose the route and format the response into a second buffer. A test can check this sequence without opening a listening socket.

## Match the method and path

Read `HEAD /report` as two pieces of information. `HEAD` is the method, and `/report` is the path. A route associates both with a handler, the function that prepares a response.

The in-memory fixture registers these routes. The two report routes use the same handler. The handler prepares status `202 Accepted`, `X-Report: summary`, and the three bytes `41 00 42` in hexadecimal. The middle byte has value zero.

| Method | Path | Handler prepares |
| --- | --- | --- |
| GET | `/report` | The counted report |
| HEAD | `/report` | The counted report |
| GET | `/hello` | The text `hello` |

The compatibility runtime looks for a route with the requested method and path. In this fixture, a `HEAD /hello` request has no matching HEAD route. Its GET route remains available for `GET /hello`.

~~~text
READ the method and path from the complete request
FIND the exact method and path in the route table
PREPARE the route response or the not-found response
FORMAT the response headers
IF the request is HEAD
    END the response after its headers
END IF
~~~

## Trace one request into a C buffer

The following fragment assumes `service` has the listed routes. `sizeof request - 1U` counts the request bytes and leaves out the zero that ends the C string. The `\r\n` escapes write HTTP's line ending. The empty line completes this request.

~~~c
static const char request[] = "HEAD /report HTTP/1.1\r\nHost: localhost\r\n\r\n";
char reply[256];
size_t used = 0U;

// Run the counted request through routing and formatting in memory.
UmiStatus result = umi_web_runtime_process(service, request, sizeof request - 1U,
                                           reply, sizeof reply, &used);
// Read reply[0] through reply[used - 1] only when result is UMI_STATUS_OK.
~~~

The `Host` value is text in the test input. This operation reads the bytes passed by the caller and returns a result in the caller's buffer. Its declaration is in `include/umicom/web/runtime.h` in Framework.

## Predict the four results

Write the API result, HTTP status, declared length and body bytes for each request before uncovering the answer.

| Request | API result | HTTP status | Declared length | Body bytes |
| --- | --- | --- | --- | --- |
| `GET /report` | `UMI_STATUS_OK` | 202 | 3 | `41 00 42` |
| `HEAD /report` | `UMI_STATUS_OK` | 202 | 3 | 0 bytes |
| `GET /hello` | `UMI_STATUS_OK` | 200 | 5 | `hello` |
| `HEAD /hello` | `UMI_STATUS_OK` | 404 | 9 | 0 bytes |

The report HEAD reply keeps `X-Report: summary`. Both `/report` replies declare length 3 for the shared representation, the form the handler prepared. HTTP requires a supplied HEAD `Content-Length` to equal the content length of the corresponding GET. Check that rule with the two `/report` rows. [HTTP Semantics on Content-Length](https://www.rfc-editor.org/rfc/rfc9110.html#section-8.6)

The two `/hello` rows show how this compatibility runtime handles an exact route match. Its GET route returns five bytes. With no HEAD route, the runtime selects a 404 and declares the nine-byte not-found representation, a different length from that GET. The 404 row is still a successful API call because the runtime produced a complete response. Keep the API result and the HTTP status in separate columns when reviewing a synthetic Umicom TMS report route.

The stored Framework routing fixture checks these complete byte buffers. Actual HTTP delivery requires separate evidence. [HTTP HEAD semantics](https://www.rfc-editor.org/rfc/rfc9110.html#section-9.3.2)

[Course contents](index.md) · [Previous lesson · Count every response body byte](50-count-every-response-body-byte.md) · [Next lesson · Keep a saved representation after a 304 response](52-keep-a-saved-representation-after-304.md) · [Register a route and its context](14-register-a-route-and-context.md) · [Separate an HTTP refusal from an operation failure](28-separate-http-status-from-operation-status.md) · [Check native routes before listening](43-check-native-routes-before-listening.md) · [HTML edition](../../../courses/building-a-web-server-in-c/lessons/51-follow-head-through-the-in-memory-router.html)
