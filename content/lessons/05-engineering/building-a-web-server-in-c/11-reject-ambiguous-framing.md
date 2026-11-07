<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-web-server-in-c/11-reject-ambiguous-framing.md

PURPOSE:
Explain the lesson: Reject ambiguous request framing.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Reject ambiguous request framing

Two pieces of software must agree on where a request ends. An ambiguous length can cause one component to process bytes that another considers a separate message.

## Prepare

Read the final case in framing.c after setting up the HTTP contract lab. It contains two Content-Length headers, both with value zero.

The example deliberately refuses even matching duplicate lengths. The public Framework contract permits at most one length header. This gives the small server one clear admission rule.

## Trace the refusal

1. Identify the request line.
2. Find Host, which identifies the requested host.
3. Count the two length headers.
4. Locate the expected PARSE_ERROR.
5. Confirm that this example never calls an application handler.

A parser error is different from a missing route. A missing route is a valid request for a path the application does not provide. A framing error prevents the request from reaching routing at all.

## Extend the case carefully

Create one experimental request without Host. Keep all other bytes unchanged. Predict its refusal using connection.h, then add a separate expectation.

Do not combine five malformed changes into one input. If it fails, you would not know which rule rejected it.

## Recover and explain

If your added case accidentally lacks the final blank line, the result may be BUSY rather than the refusal you intended to study. Count the CR and LF bytes first.

This lesson studies admission at a byte boundary. Authentication and permission checks are later layers; correct framing does not establish who a user is.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-http-contracts/framing.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](10-parse-into-owned-storage.md) · [Next lesson](12-format-get-and-head-responses.md)

