<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/native-language-interoperability/05-call-c-from-zig.md

PURPOSE:
Teach keep zig errors separate from c status values.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Keep Zig errors separate from C status values

[Course contents](index.md) · [Previous](04-call-c-from-rust.md) · [Next](06-call-c-from-fortran.md)

## Read a boundary before building it
Zig can call a C ABI function. In the existing example, c_int describes the platform's C int, while a Zig error union represents the wrapper's success-or-failure result. These are different contracts connected by a small translation function.

## Follow the files in order
1. Read bridge.h to learn the C function name and rejection sentinel.
2. Open labs/languages/zig-activity/activity.zig. Locate the external function declaration and the advance wrapper.
3. Open main.zig. The catch branch prints refused and continues to the next input; it does not pretend that the count advanced.
4. Check zig version and read the lab README before running its build-exe and test commands. Zig compiler interfaces can change between releases; use the source and flags for the version you actually installed.
5. Link the same archive created in lesson 1, with a target matching that archive. Keep runtime checks enabled while learning.

## Expected behaviour
The four demonstration inputs have the same answers as the Rust and C++ clients. Debug output can appear on standard error; a terminal displaying it does not by itself indicate a failed process. Check the process exit status and the separate Zig test results.

## Memory and ABI responsibilities
A Zig allocator is not automatically interchangeable with C malloc. If a later Framework API creates an object, release it with the function specified by that API. Do not free it through a different language allocator. Never retain a temporary slice or return an address into a function's local storage.

## Exercise and answer
Why does the wrapper translate -1 instead of adding one itself? Because the C model owns validation and the upper bound. Why should the lab not declare every language as equally fast? This tiny example measures neither realistic workload nor memory behaviour, and foreign-call overhead may dominate it.

[Zig documentation](https://ziglang.org/documentation/) explains C interoperability. The existing Learning Zig sequence gives the complete example and build commands without replacing the Framework boundary.

## Read the complete source

[labs/languages/zig-activity/activity.zig](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/languages/zig-activity/activity.zig)
