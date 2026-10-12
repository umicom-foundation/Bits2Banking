# 158. Build HTTP response headers and support HEAD

When a C23 handler produces a course list, the web server must turn that result into a byte sequence that a browser can interpret. This sequence contains a status line, headers, a blank line and, for many responses, a body.

A browser cannot infer the correct response size merely from the number of characters displayed on screen. HTTP uses byte lengths, and different characters may occupy different numbers of bytes in UTF-8.

![A response has headers and a counted body; HEAD omits the body without changing the announced length.](../../assets/diagrams/c23-response-byte-lifecycle.svg)

## 1. Examine a complete response

A request to `/api/status` produces an HTTP/1.1 result with a structure similar to:

```http
HTTP/1.1 200 OK
Content-Type: application/json; charset=utf-8
Content-Length: 69
Connection: close

{"service":"bits2banking-routes","state":"ready","scope":"loopback"}
```

The actual network bytes use a carriage return and line feed (`\r\n`) after each header line. The blank line is `\r\n\r\n`. Here the JSON body contains 69 bytes, including its final newline. You can confirm the length with a network client instead of trusting what it looks like in a console.

## 2. Construct a response in two stages

The C23 implementation uses `BtbRouteResponseSet()` to copy a handler's body into caller-owned storage. That copy is deliberate: a response cannot safely borrow a pointer to a local array after its handler returns.

```c
const char message[] = "Notes saved\n";
BtbRouteResponse response = {0};
BtbRouteResult result = BtbRouteResponseSet(
    &response, 200U, BTB_ROUTE_PLAIN_TEXT,
    message, sizeof message - 1U);
```

Check that `result == BTB_ROUTE_OK` before encoding or sending it. If the supplied byte count exceeds the fixed 2,048-byte teaching limit, the operation refuses the request without publishing a partial result.

`BtbRouteEncode()` then adds the HTTP status line and headers. The handler may select only the supported status codes and media types. It cannot inject arbitrary header text through a media-type string.

## 3. Understand GET and HEAD

`GET /api/courses` requests the complete representation: **headers and body**. `HEAD /api/courses` requests the headers that a corresponding GET would produce, but the network response must contain **no body bytes**.

This does not make the `Content-Length` header zero. It still announces the length of the representation that GET would send.

The encoder returns two measurements:

```c
size_t wireBytes = 0U;
size_t headerBytes = 0U;
char packet[4096];
BtbRouteResult result = BtbRouteEncode(
    &request, &response, packet, sizeof packet,
    &wireBytes, &headerBytes);
```

For GET, `wireBytes` includes `headerBytes + response.bodyLength`. For HEAD, `wireBytes == headerBytes`. The declared body length remains `response.bodyLength` in both cases.

## 4. Make one request of each kind

Start the C23 server with `--routes` as shown in [Chapter 157](157-route-http-requests-to-c23-handlers.md). In a second PowerShell window:

```powershell
Invoke-WebRequest "http://127.0.0.1:8765/api/courses" -Method Get
Invoke-WebRequest "http://127.0.0.1:8765/api/courses" -Method Head
```

Compare the status and headers. GET supplies JSON data; HEAD supplies no response body. Some PowerShell versions display a summary rather than raw headers; inspect `.Headers` on the returned response object if necessary.

## 5. Check response-buffer failures

Every output buffer has a real capacity. If the headers and body will not fit, `BtbRouteEncode()` returns `BTB_ROUTE_CAPACITY`. It must not write half a response and then pretend success.

The tests use both a normal 4,096-byte buffer and a deliberately tiny 10-byte buffer:

```powershell
ctest --test-dir ".\output\learning-build\http-loopback-server" `
    -R "bits2banking.http.(routing|response_completion)" --output-on-failure
```

### Questions

1. What separates HTTP headers from the body?
2. Why can `Content-Length` be non-zero in a HEAD response?
3. Why must a handler copy response bytes before returning?

Next, we will distinguish a response that has been *prepared* from a response that has been *fully sent*.
