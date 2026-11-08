<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-web-server-in-c/23-connect-stream-state-to-transport-ownership.md

PURPOSE:
Connect parser state to the transport owner

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Connect parser state to the transport owner

## Prepare

Read the active UmiWebConnectionProcess implementation and the preserved earlier loop. Locate the private Writable/Commit interface in request_stream_internal.h. Public lab callers use Feed; only the connection owner fills the private buffer tail directly.

## Avoid a second staging allocation

Writable returns the unused tail and its capacity while the stream is incomplete. The transport callback must write at most that capacity. Commit admits the reported bytes and advances the incremental state. The connection checks an overreported count before committing, retaining the existing invalid-state refusal.

## Keep callback outcomes distinct

A read can fail after reporting some received bytes. The exchange records the observed count but does not dispatch an unadmitted request. Cancellation is checked before more work and before dispatch. A completed strict parse still does not mean that a handler has run or that any response reached a client.

## Leave deadlines with the socket adapter

The native adapter uses a monotonic deadline for the exchange and bounded waits. The parser has no clock and does not interrupt a synchronous handler. Smaller parsing work does not justify removing accept limits, exchange limits or cancellation. Those constraints protect different resources.

## Exercise and worked answer

A callback reports capacity + 1 bytes. Should the connection ask the parser to truncate the count? No. The callback violated its writable-span contract. The connection refuses the invalid count before advancing the parser. Truncation would hide an ownership error and could make the recorded request differ from what was read.

## Recover with phase information

Record whether the failure happened during reading, parsing, dispatch or writing. Preserve bytes_received, bytes_sent, dispatched and response_complete alongside the final status. The stream replaces repeated prefix scans; it does not replace the exchange result or the rule that an accepted socket must be closed after return.

## Read the source

[Umicom-Applications/framework/src/web/connection.c](https://github.com/umicom-foundation/umicom-framework/blob/main/src/web/connection.c). Use the matching local revision when working offline.

## Continue learning

[Course contents](index.md) · [Previous: Test message decisions across fragment boundaries](22-test-every-fragment-boundary.md) · [Next: Qualify the parser, exchange and local host separately](24-qualify-a-local-c-web-workflow.md)
