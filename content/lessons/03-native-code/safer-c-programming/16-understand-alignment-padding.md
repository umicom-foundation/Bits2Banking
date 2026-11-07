<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/safer-c-programming/16-understand-alignment-padding.md

PURPOSE:
Explain the lesson: Understand alignment and padding.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Understand alignment and padding

## Prepare
Read BtbArenaAllocate in arena.c and the alignment assertions in test_arena.c. Alignment means that an address meets a spacing requirement, such as being divisible by eight.

The test requests a region with uint64_t alignment but only inspects its address. It does not write a uint64_t object through that pointer.

## Trace a boundary
Imagine the current address is 101 and the required alignment is eight. The next divisible address is 104. Three bytes are padding before the requested region.

The implementation accepts nonzero powers of two. For these values, a mask can round an address upwards after checking that the addition is representable.

## Lab
Make a paper table for current addresses 100 through 108 with alignment four. Record the next aligned address and padding.

Expected padding ranges from zero to three. An already aligned address needs no padding.

## Exercise and explanation
Does a request for eight bytes always consume eight bytes? No. It may also consume alignment padding. Capacity calculations must include both.

Does alignment establish C object lifetime and access rules? No. Those are separate requirements. Use this arena's text example as the initial supported exercise.

## Troubleshoot
An alignment of three is refused because it does not meet this API's power-of-two contract. Do not silently round the requested alignment. Explain the refusal to the caller, and use the required alignment of the intended data representation.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/arena-allocator/arena.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](15-request-space-for-a-terminator.md) · [Next lesson](17-subtract-only-after-checking.md)

