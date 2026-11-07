<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/safer-c-programming/07-allocator-context-and-test-doubles.md

PURPOSE:
Explain the lesson: Make memory allocation observable through a callback.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Make memory allocation observable through a callback

## Prepare
Use the existing fault-injection lab. Open `note.h` beside `test_note.c`. A callback is a function passed to another piece of code. The receiving code calls it when an event occurs. Here that event is “allocate or release memory.”

The `BtbAllocator` structure holds two function pointers and a `context` pointer. Context carries the state that those functions need without using a global variable.

## Read the test state
`Faults` contains:
- `attempts`: how many allocation calls have been made;
- `failOn`: which numbered attempt should return null;
- `live`: how many successful allocations have not yet been released.

`TryAllocate` converts the context pointer back to `Faults *`. That conversion is valid because the caller originally supplied the address of a live `Faults` object. It increments attempts, applies the chosen failure, then calls `malloc`.

A successful allocation increases live. A failed allocation does not.

## Trace a deterministic failure
Suppose attempts is 4. Setting failOn to 6 makes the second allocation of the next two-allocation replacement fail. This is more repeatable than trying to exhaust the computer's memory.

The test double still uses real allocated storage on successful calls. It changes when allocation is refused, not the representation of the strings.

## Exercise
Draw a table with columns Call, attempts, failOn, result and live. Start at attempts 0, failOn 2, live 0. Trace title allocation, body allocation and temporary-title release.

Expected final values are attempts 2 and live 0. Release does not increase attempts. The returned status should be `BTB_NO_MEMORY`.

## Lifetime and recovery
The context object must outlive every call through the allocator. In this lab it is local to `main` and remains alive until the note is destroyed. Returning a note whose allocator points to an expired local context would be invalid.

If a test hangs or crashes, inspect context identity and callback signatures before changing allocation policy. A function-pointer cast cannot repair incompatible parameters. Run the lab's ordinary checks only after configuring the intended target; a clean compile alone does not establish correct ownership.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/fault-injection/test_note.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](06-two-fields-one-commit.md) · [Next lesson](08-spans-terminators-and-text-policy.md)

