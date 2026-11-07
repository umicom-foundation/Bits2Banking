<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-web-server-in-c/09-observe-a-complete-http-message.md

PURPOSE:
Explain the lesson: Observe a complete HTTP message.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Observe a complete HTTP message

A browser sends a sequence of bytes. The server needs a rule for deciding when one request has arrived. That rule is called framing.

## Prepare

Open labs/native/framework-http-contracts/README.md in Bits2Banking and follow its SDK setup. Start with framing.c. Reading the example needs no network connection.

The request is a POST to /echo. Its header declares Content-Length: 3. After the blank line, its three body bytes are A, zero and B.

## Count the bytes

1. Find the C string literal named wire.
2. Notice that C adds one final zero byte after the literal.
3. sizeof(wire) includes that final terminator; subtracting one excludes it.
4. The zero deliberately placed between A and B remains part of the request.
5. Predict the result when length minus one is passed to the framing function.

Expected: BUSY, because the last B has not arrived. BUSY asks the caller for more input; it does not authorize a handler to process the partial body.

## Use the Framework contract

UmiWebRequestFrameRead returns header_bytes, body_bytes and message_bytes on success. The lab expects body_bytes to be three and message_bytes to equal the supplied complete length.

This is a local-development HTTP subset. Its public header lists refused features; a successful example does not imply support for every HTTP transfer mode.

## Exercise

Write a byte table for A, zero and B. Explain why strlen would count only one body byte. Then replace the length with the complete size and predict the observed status before running the exercise.

If the incomplete case reports success, retain the exact SDK and source versions. Do not remove the expectation: processing truncated input would change the contract.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-http-contracts/framing.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Next lesson](10-parse-into-owned-storage.md)


[Previous: Reject an invalid port before starting a server](08-reject-an-invalid-port-before-launch.md)
