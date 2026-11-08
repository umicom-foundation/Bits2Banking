<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-web-server-in-c/18-scan-only-new-header-bytes.md

PURPOSE:
Scan new header bytes and reuse strict rules

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Scan new header bytes and reuse strict rules

## Prepare

Open request_stream.c beside request_frame.c in the same Framework revision. Locate received, scanned and frame in the private stream structure. Read the strict framing lesson first: the supported subset still requires one Host header and rejects ambiguous length fields.

## Understand repeated work

The former connection loop called the stateless frame reader on the entire accumulated prefix after each read. With one-byte reads, that revisits earlier request and header lines many times. The stream keeps a scan position, examines new header bytes and detects the header terminator. It then asks the existing Frame implementation to validate header semantics and report the expected message size.

## Keep recognition and policy separate

Recognizing the four-byte header boundary is not enough to accept a request. Host, method, field syntax, Content-Length and supported-feature rules still belong to the strict parser. The incremental layer calls the shared private header-admission function instead of inventing a second interpretation.

~~~text
new bytes -> CR/LF and header-boundary scan
complete header -> existing strict field rules
known body length -> bounded completion comparison
complete message -> existing owned strict parse
~~~

## Notice the timing contract

Stream semantic rejection waits for the complete header. The stateless reader may reject an unsupported request line sooner when explicitly called on that prefix. CR/LF errors can still fail during the incremental scan. The delayed-semantic regression documents this difference. The transport deadline and maximum size remain necessary even when parsing does less repeated work.

## Exercise and worked answer

A body contains CR, LF, CR, LF. Should the stream treat it as another header terminator? No. Once the header is admitted, its declared body length controls completion. Scanning body bytes as header syntax would reject valid binary content or split the message incorrectly.

## Recover without competing rules

If a fragmented request differs from the same complete input, compare the shared parser result and the stream state at each feed. Repair the boundary handling or shared rule once. Do not add a special exception in the transport adapter that silently accepts input rejected by strict parsing. No throughput measurement is implied by reading this algorithm.

## Read the source

[Umicom-Applications/framework/src/web/request_stream.c](https://github.com/umicom-foundation/umicom-framework/blob/main/src/web/request_stream.c). Use the matching local revision when working offline.

## Continue learning

[Course contents](index.md) · [Previous: Own an incomplete request across reads](17-own-an-incomplete-request.md) · [Next: Keep binary body length explicit](19-keep-binary-body-length-explicit.md)
