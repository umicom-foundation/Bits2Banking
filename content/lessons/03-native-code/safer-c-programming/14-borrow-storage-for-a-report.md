<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/safer-c-programming/14-borrow-storage-for-a-report.md

PURPOSE:
Explain the lesson: Borrow storage for a temporary report.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Borrow storage for a temporary report

## Prepare
Open labs/native/arena-allocator/main.c and arena.h in the Bits2Banking checkout. The laboratory README contains the independent CMake commands. Begin by reading; no allocator knowledge is required.

A byte is a small unit of storage. The array named workspace contains 512 bytes owned by main. BtbArena records which part is already used. It borrows the array instead of creating another allocation.

## Trace ownership
Draw three boxes: main owns workspace; arena points to workspace; title points into workspace. A pointer records a location. It does not automatically keep that location alive.

The report has a heading and body. Both fit inside the same array. Returning from main ends the array's lifetime.

## Lab
Locate the initialise call. Write down the address, capacity and used count immediately after success. Then locate the two allocation calls and explain which values change.

Expected: capacity stays 512; used grows after each successful allocation. The original array remains the owner.

## Exercise and explanation
Could a function return title when workspace was its own local array? No. The pointer would refer to storage whose lifetime ended on return. Move the owner to the caller or copy the result into longer-lived storage.

## Troubleshoot
Do not treat a successful allocation as proof that every future access is valid. Check the owner's lifetime and the arena checkpoint. This laboratory stores text bytes; alignment alone is not permission to place arbitrary typed C objects in a declared byte array.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/arena-allocator/main.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](13-review-before-sharing-a-model.md) · [Next lesson](15-request-space-for-a-terminator.md)

