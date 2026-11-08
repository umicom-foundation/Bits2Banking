<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-web-server-in-c/21-reset-state-without-keeping-a-connection.md

PURPOSE:
Reset parser state without claiming keep-alive

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Reset parser state without claiming keep-alive

## Prepare

Trace the extra-byte and reset section near the end of stream.c. The lab has no socket and no handler. Its explicit Reset demonstrates object reuse, not a persistent HTTP connection protocol.

## Follow terminal completion

After a complete request, an empty feed reports OK. Supplying another byte changes the stream to PARSE_ERROR: the byte is not silently accepted as a second message. A parse attempted in that state refuses and leaves the previously owned UmiWebRequest unchanged.

## Begin a separate request explicitly

Reset discards received bytes, scan position and known framing while retaining the allocated maximum. Inspect should then show zero received bytes, no expected message and BUSY. The caller can feed a new independent request. The previously parsed owned value remains separate.

~~~text
complete -> extra input -> framing error
framing error -> explicit reset -> empty/incomplete
owned parsed request -> unchanged throughout
~~~

## Keep transport ownership visible

The native connection service handles one request and closes the accepted socket. Reset cannot extend that socket lifetime, reorder messages or create HTTP keep-alive support. A future persistent protocol would need explicit message consumption, connection state and error recovery rules. Those features are not supplied by this API.

## Exercise and worked answer

A developer catches every parse error, resets and keeps reading the same socket. What is missing? A defined resynchronization and connection policy. With ambiguous framing, remaining bytes may not begin at a safe message boundary. The current one-exchange service closes the transport instead of guessing.

## Recover from stale-state mistakes

If a new independent input starts with old counts, inspect whether Reset was called on the intended object and whether another owner is still using it. Keep one owner thread and do not feed, reset or destroy concurrently. A new allocation may help isolate a diagnosis, but it does not excuse an ownership defect.

## Read the source

[labs/native/framework-http-contracts/stream.c](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-http-contracts/stream.c). Use the matching local revision when working offline.

## Continue learning

[Course contents](index.md) · [Previous: Bound input and keep terminal errors visible](20-bound-input-and-terminal-errors.md) · [Next: Test message decisions across fragment boundaries](22-test-every-fragment-boundary.md)
