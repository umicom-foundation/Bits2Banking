<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-web-server-in-c/42-turn-a-worker-document-into-http.md

PURPOSE:
Teach conversion of a complete FastCGI document into an owned HTTP response.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Turn a worker document into HTTP

[Course contents](index.md) · [Previous lesson](41-read-a-fastcgi-reply-before-forwarding.md)

A FastCGI worker sends its document as bytes in the standard output stream. A successful exchange tells you those bytes arrived in full. The document still needs to be read as headers followed by a blank line and content. Framework's `UmiWebFastCgiResponseDecode` handles that step before the HTTP server writes anything.

## Trace a complete response

1. Read the document head using one line-ending convention, either CRLF or LF. A blank line ends the head and the next byte belongs to the body. An ordinary document needs a `Content-Type` field so the browser knows how to interpret its bytes.
2. Convert a worker field such as `Status: 201 Created` to the numeric HTTP status. The Framework formatter writes the HTTP status line and its own reason phrase. An optional worker `Content-Length` must match the available body. The formatter writes its own length after checking that match. Connection and transfer framing belong to the server.
3. Pass the verified body length to `UmiWebResponseFormatClosedHeaders`. The body uses an independent allocation, so it remains valid after the exchange result is destroyed. Send its exact length and release it with `UmiWebResponseBodyDestroy` after delivery. On denial, return a server-generated failure through your route's policy.

## Observe the boundary in the compiler tests

Use the configured directory from the FastCGI encoding lesson. Rebuild after opening the current Framework source so the new cases are registered.

```powershell
$wireBuild = Join-Path $PWD 'build/fastcgi-wire'
cmake --build $wireBuild
ctest --test-dir $wireBuild --no-tests=error -R '^framework[.]web[.]fastcgi_response[.](actual-exchange|binary|status-and-length|wrong-length)$'
```

Expect four passing tests. The exchange fixture splits a header between two worker records and delivers the records one byte at a time. The binary fixture includes a zero byte in the body. The length fixtures accept the exact byte count and refuse a mismatch before either output changes. If the exchange fixture fails, first check whether `END_REQUEST` was accepted, then inspect the blank line and count the bytes after it. These fixtures exercise the shared C adapter. A deployed worker and browser delivery need their own checks.
