# 65. Parse incoming bytes without assuming they form a string

A web server receives bytes from a network connection. Those bytes might contain a valid request, an incomplete request, a zero byte or something entirely unrelated to HTTP. A C program must not assume that data read from a socket ends with the `\0` byte used to terminate a C string.

This exercise begins with a single HTTP request line. It does **not** open a network socket. Once we understand how to examine the bytes, we can follow the complete Umicom Framework web server, which owns real connections, routing, deadlines and access policy.

## 1. Recognise one request line

A browser may send the beginning of a request such as:

```text
GET /lessons/ HTTP/1.1\r\n
```

The line has a method (`GET`), a path (`/lessons/`), and a protocol version (`HTTP/1.1`). The final two bytes are called **CRLF**: carriage return (`13`) followed by line feed (`10`). They end this line. They are not an instruction to print the two characters `\` and `n`.

Actual HTTP requests contain headers after the first line. This introductory exercise intentionally parses only that first line. It does not handle HTTP/2, chunked messages, TLS, cookies, request bodies or general URL decoding.

## 2. Use a pointer and an explicit length

In `labs/native/http-byte-parser/request_line.h` you will find:

```c
BtbHttpResult BtbParseRequestLine(
    const uint8_t *bytes,
    size_t byteCount,
    BtbHttpRequestLine *out);
```

The input is a **byte span**. `bytes` points to the first byte. `byteCount` says exactly how many bytes may be examined. The parser never calls `strlen(bytes)` because a network message may have no terminating zero byte.

The output pointer refers to caller-owned storage. A rejected request must leave that storage unchanged.

## 3. Check bounds before reading

Open `request_line.c` and find the first conditions:

```c
if (bytes == NULL || out == NULL || byteCount < 16U)
    return BTB_HTTP_INVALID;
if (byteCount > BTB_HTTP_LINE_MAX_BYTES)
    return BTB_HTTP_TOO_LONG;
```

The minimum size is checked before the parser examines the last two bytes. This order matters: without it, `bytes[byteCount - 2U]` would be invalid when `byteCount` is zero or one.

The example also checks that the only carriage return and line feed bytes occur at the expected end. It refuses embedded zero bytes and rejects unsafe or ambiguous paths. For simplicity, it accepts only GET and HEAD, HTTP/1.0 or HTTP/1.1, and restricted ASCII paths without percent escapes or queries.

These choices are **exercise limitations**, not the rules for every HTTP server.

## 4. Publish the result only after validation

The parser fills a local structure:

```c
BtbHttpRequestLine staged = {0};
```

It copies the accepted method and path into fixed-capacity arrays and adds the terminating zero bytes. Only after every field is validated does it execute:

```c
*out = staged;
return BTB_HTTP_OK;
```

A malformed request cannot leave half a method or half a path in the caller's output structure. This uses the same failure-atomic thinking as the Notes replacement from the previous lesson.

## 5. Build and run

Open PowerShell:

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"

cmake -S ".\labs\native\http-byte-parser" `
    -B ".\output\learning-build\http-byte-parser" `
    -G Ninja `
    -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe"

cmake --build ".\output\learning-build\http-byte-parser" --parallel 2
ctest --test-dir ".\output\learning-build\http-byte-parser" --output-on-failure
& ".\output\learning-build\http-byte-parser\bits2banking-http-parser.exe"
```

The demonstration prints:

```text
Method: GET
Path: /lessons/
Version: HTTP/1.1
```

CTest should run two tests: ordinary request-line cases and a deterministic malformed-input experiment.

## 6. Investigate one rejected message

Open `test_request_line.c`. The test includes a request whose path contains `..`, a request with no carriage return, an unsupported method and an embedded zero byte. For each rejected request, `RefusedUnchanged` fills the output with a known pattern and confirms that it remains unchanged.

Try adding another case with a query string, for example `GET /lessons/?page=2 HTTP/1.1`. This laboratory should reject it because query handling has not been implemented. The correct response from a teaching parser is to refuse unsupported input, not to guess.

## 7. Connect the exercise to a real server

The production-grade network boundary is different. Umicom Framework already provides an [HTTP server and routing interface](https://github.com/umicom-foundation/umicom-framework/tree/main/include/umicom/web). Its existing [local service example](https://github.com/umicom-foundation/umicom-framework/blob/main/examples/web/local_service.c) demonstrates how the transport, request handler and static-file service fit together.

A parser accepting a request line does **not** prove that a service is safe to expose publicly. Authentication, timeouts, request framing, path confinement, concurrency and deployment policy are additional responsibilities.

**Check your understanding:** Why can't we use `strlen` on a socket buffer? What happens when a packet is shorter than the parser expects? Why does the parser stage its output before writing to the caller? Which responsibilities remain with the real Framework web server?

Continue with [Lesson 66: Reproduce parser failures with deterministic tests](../05-engineering/66-fuzz-bytes-and-check-contracts.md).
