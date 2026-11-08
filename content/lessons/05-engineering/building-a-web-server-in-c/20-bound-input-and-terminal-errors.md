<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-web-server-in-c/20-bound-input-and-terminal-errors.md

PURPOSE:
Bound input and keep terminal errors visible

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Bound input and keep terminal errors visible

## Prepare

Read the stream header and the capacity, full-incomplete and declared-overlimit regression scenarios. Create uses a maximum of 1 through 65,536 bytes. The existing request body capacity remains smaller; increasing the stream maximum does not remove that separate limit.

## Distinguish refusal states

A null nonempty input is an invalid call and preserves the stream. A chunk larger than the remaining capacity is refused without copying and puts the stream into a terminal capacity error. A full buffer without a complete header cannot keep waiting for more bytes. An admitted header whose declared total cannot fit is also refused.

## Inspect without advancing

Inspect copies received bytes, maximum, known framing and current status. Its own OK result means the snapshot was copied successfully; snapshot.status may still be BUSY or an error. Treat those two statuses as answers to different questions.

~~~c
UmiWebRequestStreamSnapshot snapshot;
UmiStatus copied = UmiWebRequestStreamInspect(stream, &snapshot);
/* Check copied first, then interpret snapshot.status. */
~~~

## Do not conceal the first error

After a framing or capacity error, later feeds report that error until Reset. The stream does not search ahead for a convenient next request or discard an arbitrary prefix. A caller handling a real connection must follow its close/error policy; reset alone does not make ambiguous input safe to continue.

## Exercise and worked answer

A 1024-byte stream receives a header declaring a 1024-byte body. Why can it fail before the body arrives? The maximum covers the entire wire message, including the header, and the declared total already exceeds it. Raising the limit may be a policy decision, but it is not a correction to the length arithmetic.

## Recover deliberately

Check whether the intended request fits the documented total and body bounds. Keep the failed snapshot and original configuration. If the application chooses a larger supported maximum, repeat boundary checks and retain the new environment identity. Do not turn capacity errors into empty successful requests.

## Read the source

[Umicom-Applications/framework/include/umicom/web/request_stream.h](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/web/request_stream.h). Use the matching local revision when working offline.

## Continue learning

[Course contents](index.md) · [Previous: Keep binary body length explicit](19-keep-binary-body-length-explicit.md) · [Next: Reset parser state without claiming keep-alive](21-reset-state-without-keeping-a-connection.md)
