<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-web-server-in-c/10-parse-into-owned-storage.md

PURPOSE:
Explain the lesson: Parse into owned storage.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Parse into owned storage

Parsing gives meaning to received bytes: a method, path, headers and body. The parser needs somewhere to put those results.

## Prepare

Complete the HTTP contract lab setup in its README. Open framing.c beside Framework's include/umicom/web/connection.h. Locate UmiWebRequestParseStrict.

The destination belongs to the caller. The parser promises to leave it unchanged if parsing fails. That promise helps an application keep a previously valid value instead of exposing a half-written replacement.

## Follow the allocation

1. malloc requests enough storage for one UmiWebRequest.
2. A null result means storage was not obtained.
3. Only after checking the pointer does the example call the parser.
4. The example compares body_length and all three body bytes.
5. free releases the allocation after the last inspection.

The value can be large because it contains bounded arrays. Heap allocation avoids placing that entire value on a small thread stack. Allocation is still fallible, so its result must be checked.

## Read bytes with a length

memcmp compares a stated number of bytes. It is appropriate here because a body may contain zero. A C text function that stops at zero would describe a different value.

Expected: the parsed body length is three and memcmp finds A, zero, B unchanged.

## Exercise

On paper, move free before the comparison. Identify the resulting lifetime error: the pointer value may remain, but its allocation no longer belongs to the program.

Keep parsing inside Framework. A platform adapter should supply bytes and manage ownership, rather than introducing a different HTTP parser for each application.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-http-contracts/framing.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](09-observe-a-complete-http-message.md) · [Next lesson](11-reject-ambiguous-framing.md)

