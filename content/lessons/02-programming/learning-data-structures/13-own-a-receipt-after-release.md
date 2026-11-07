<!--
Umicom Bits2Banking
File: content/lessons/02-programming/learning-data-structures/13-own-a-receipt-after-release.md

PURPOSE:
Explain the lesson: Keep a delivered receipt independent of queue storage.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Keep a delivered receipt independent of queue storage

## Prepare
Open dispatch.h and BtbDispatchReceive. The lab's README contains setup and build commands. A borrowed pointer refers to storage another component owns. An owned value is copied into storage whose lifetime the caller controls.

BtbDispatchReceipt contains identity, connection ID, request length, digest and result. It contains no borrowed payload pointer.

## Follow the delivery order
Receive inspects the next notice, locates its record and constructs a local receipt value. It then consumes the notice and releases the original work slot. Finally it clears the record, increments delivered and writes the receipt to the caller.

The caller can retain the receipt after another request reuses that slot. The old request bytes themselves are not part of the receipt.

## Exercise
Receive a completed request into receiptA. Save its request ID, length and digest. Submit and complete enough later work to reuse slots, then inspect receiptA again.

Expected: those saved fields remain unchanged. A new receipt should be stored separately if the caller needs both histories.

## Failure boundary
An EMPTY receive leaves the output unchanged. Initialize a receipt with recognizable values, call Receive on an empty dispatcher, and check both EMPTY and preservation.

Do not use uninitialized values as your expected result. The sentinel must be deliberately written before the call.

## Product connection
A user interface may need to display a completed job after the worker queue has moved on. Copy stable result data into a suitable model rather than keeping pointers into temporary queue slots. Durable history requires an additional storage service; this receipt alone is an in-memory value, not an audit database.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/work-dispatch/dispatch.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](12-cancellation-is-a-result.md) · [Next lesson](14-budget-a-dispatch-turn.md)

