<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-web-server-in-c/35-finish-headers-and-partial-body-writes.md

PURPOSE:
Finish headers and partial body writes

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->


# Finish headers and partial body writes

## A response is more than one successful write

The connection first formats validated status and headers, then writes the selected representation. The transport can accept fewer bytes than requested. A successful partial write advances the offset; it does not finish the response. A later failure can leave a peer with complete headers and only a prefix of the body. Preserve that distinction in result reporting.

UmiWebResponseFormatClosedHeaders receives the external length and formats framing without copying the external bytes into the inline array. The response metadata must have zero inline body_length. The serializer owns Content-Length and Connection, and rejects competing framing fields. Handlers should provide semantic metadata such as Content-Type through the supported response helpers.

## Read the connection in two phases

Find UmiWebConnectionProcess in src/web/connection.c. After header delivery, the body path clears response_complete before starting the second write loop. Every accepted byte contributes to bytes_sent. Only successful completion of all required output marks the response complete. Cleanup destroys the owner on success, cancellation and transport failure.

A cancelled exchange may already have sent bytes. Retrying the entire response on that connection would append another status line to an incomplete message. The current closed-response transport does not retry a request. The host decides how to report the failed exchange and whether to accept a later connection. This is separate from whether the request handler itself succeeded.

## HEAD describes the representation

A HEAD response describes the representation that a corresponding GET would return, but carries no message body. The preview still admits and reads the selected file to determine its bounded representation. Content-Length can therefore describe nonzero bytes even though the transport sends only headers. An empty file and a HEAD request for a large file are different cases.

The existing serializer also suppresses bodies for 204 and 304 responses. Read those branches separately from the HEAD branch. Do not infer that every status code uses the same framing rules. RFC 9110 defines the semantics; Framework tests establish only the implementation scenarios actually executed.

## Exercise: predict the result fields

Study partial-failure and cancel-body in tests/web/test_response_body.c. The test transport accepts a controlled prefix after headers, then fails or requests cancellation. Record expected bytes_sent, response_complete, dispatch_status and returned operation status before running the check. Use the exact fixture behavior; do not invent a socket result from a headless callback.

Then inspect the head, no-content and not-modified cases. Explain why an allocated body can be destroyed without sending its bytes. If a regression reports success after only headers, investigate the completion flag before changing HTTP status. If bytes_sent is wrong, inspect the transport callback count contract and offset accounting. Keep the original failed output so the correction can be compared against the same source and fixture.

[Installed-SDK lab setup](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-static-preview/README.md) · [Body ownership contract](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/web/response_body.h) · [Authored regression scenarios](https://github.com/umicom-foundation/umicom-framework/blob/main/tests/web/test_response_body.c) · [HTTP HEAD semantics](https://www.rfc-editor.org/rfc/rfc9110.html#section-9.3.2)

[Course contents](index.md) · [Previous lesson](34-own-static-response-bytes-until-consumed.md) · [Next lesson](36-qualify-approved-assets-through-each-layer.md)
