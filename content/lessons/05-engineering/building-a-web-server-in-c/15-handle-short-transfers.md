<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-web-server-in-c/15-handle-short-transfers.md

PURPOSE:
Explain the lesson: Handle short reads and writes.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Handle short reads and writes

A read operation may return fewer bytes than requested. A write may accept only part of an output buffer. Neither event automatically means the complete exchange failed.

## Prepare

Open exchange.c in the HTTP contract lab. It uses memory callbacks rather than a real socket. Read supplies one byte per call; Write accepts at most three.

This deliberate fragmentation makes transport behavior visible and repeatable without depending on a network.

## Follow the state

MemoryWire contains input length, current offset, output length and a handler count.

1. Read copies one available byte and advances offset.
2. Framework collects enough bytes to frame the request.
3. Routing invokes Handle once.
4. Framework repeatedly calls Write for the remaining response.
5. The result records total received and sent counts.

Expected: all input bytes are consumed, the handler runs once and the response completes even though no callback transfers the entire message.

## Exercise

Change the successful read adapter to return at most two bytes. Keep its count bounded by both available input and destination capacity. Predict why the application's final response should remain the same.

Do not return OK with an invented byte count. The count describes bytes actually transferred, not bytes the callback intended to transfer.

## Recovery

If the process appears stuck, look for a callback reporting success without progress. Real callbacks also need bounded waits so cancellation can be observed.

The memory adapter demonstrates the contract. It does not simulate network latency, authentication or operating-system socket ownership.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-http-contracts/exchange.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](14-register-a-route-and-context.md) · [Next lesson](16-distinguish-dispatch-from-delivery.md)

