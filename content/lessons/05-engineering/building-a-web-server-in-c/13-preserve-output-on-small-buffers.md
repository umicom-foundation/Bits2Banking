<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-web-server-in-c/13-preserve-output-on-small-buffers.md

PURPOSE:
Explain the lesson: Preserve output when a buffer is too small.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Preserve output when a buffer is too small

A buffer is a region of memory with a fixed capacity. A formatter must not write beyond that capacity, even when the desired output is much larger.

## Prepare

Open response.c in the HTTP contract lab. Find the four-byte array named tiny. Every byte initially contains 0x55, a recognizable hexadecimal value.

The HTTP response cannot fit in four bytes. The example expects CAPACITY_EXCEEDED, an output length of zero and all four bytes unchanged.

## Why check all three?

An error code alone does not prove the buffer was preserved. A zero length alone does not prove there was no partial write. Comparing the bytes checks the promised failure behavior.

1. Record tiny before the call.
2. Record tiny_length before the call: it is deliberately 99.
3. Inspect the status after the call.
4. Compare the entire array with before.
5. Confirm that the reported length was reset.

This pattern is useful for file names, serialized records and generated messages as well as HTTP.

## Exercise

Try capacities of one, four and a comfortably large value in separate cases. Predict which should succeed. Never increase the capacity argument beyond the actual array size; that would lie to the function about available memory.

## Recovery

If a case fails only in an optimized build, inspect undefined behavior and lifetime mistakes rather than assuming the optimizer is wrong. The lab's REQUIRE macro remains active regardless of NDEBUG.

Framework owns the formatting rule. The consumer owns the storage and must supply an honest capacity.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-http-contracts/response.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](12-format-get-and-head-responses.md) · [Next lesson](14-register-a-route-and-context.md)

