<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-web-server-in-c/12-format-get-and-head-responses.md

PURPOSE:
Explain the lesson: Format GET and HEAD responses.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Format GET and HEAD responses

A response consists of headers and sometimes a body. GET normally asks for the representation. HEAD asks for its metadata without transferring the body.

## Prepare

Build the HTTP contract lab using its README and open response.c. The response body is the five-byte text ready.

The program asks the same Framework formatter to produce a normal response and a HEAD response. The boolean argument selects whether body bytes are omitted.

## Inspect the expectations

1. Both responses declare Content-Length: 5.
2. Both announce Connection: close.
3. The GET output ends with ready.
4. The HEAD output contains five fewer bytes.
5. The test checks the declared size independently of the transmitted size.

A length in a header describes a protocol value. It is not automatically the number of bytes transmitted in every response mode.

## Understand the spare byte

The output arrays begin filled with zero. The formatter receives capacity minus one. This leaves a zero after its bounded output so this particular lab can safely use strstr to inspect headers.

The formatter's length remains the authoritative count. In a socket adapter, write exactly that count; do not send the spare zero.

## Exercise

Change ready to waiting in a personal copy. Predict the new declared length and the difference between GET and HEAD. Update every expectation that depends on the body length.

If the HEAD test fails, examine the length and body rules before altering the route. A request method, response content and transmission format have related but separate responsibilities.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-http-contracts/response.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](11-reject-ambiguous-framing.md) · [Next lesson](13-preserve-output-on-small-buffers.md)

