<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/native-language-interoperability/04-call-c-from-rust.md

PURPOSE:
Teach use a narrow rust foreign-function boundary.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Use a narrow Rust foreign-function boundary

[Course contents](index.md) · [Previous](03-call-c-from-cpp.md) · [Next](05-call-c-from-zig.md)

## Start with the existing Rust course
Rust distinguishes owned values from borrowed references and checks many rules during compilation. That checking cannot prove the behaviour of an arbitrary C library. A foreign-function declaration is therefore a promise the author must verify.

## Follow the existing client
1. Open activity.rs and main.rs in labs/languages/rust-activity.
2. Read the external declaration and its C-compatible integer type. Match it to bridge.h rather than choosing Rust's default integer by habit.
3. Find the narrow unsafe call. Its argument is a value, the C function keeps no pointer, and the linked library must export the declared function.
4. Observe how the wrapper translates rejection into a Result. The application can then handle refusal without repeating the counting rule.
5. Use the complete Windows GNU or Linux commands in that directory's README. Check rustc --version first; the example uses edition 2024.

On Windows the documented Rust target is x86_64-pc-windows-gnu with the matching GNU linker. Do not mix it accidentally with an MSVC-targeted archive or a 32-bit object. Installing a target is a separate setup step; opening the source does not install one.

## Expected result and verification
The client prints 0 -> 1, 41 -> 42, 999 -> 1000 and 1000 -> refused. Its separate test build checks invalid input and independent calls. Run both commands from the README. If the compiler or target is missing, record the example as not run rather than passed.

## Exercise and answer
Would a Rust reference guarantee that C never keeps its address? No. A reference does not rewrite the C implementation or its lifetime contract. This example avoids that issue by passing only one integer value. For a buffer API, review length, lifetime, mutability and whether the callee stores the address before writing the unsafe wrapper.

[Read the Rust foreign-function guide](https://doc.rust-lang.org/nomicon/ffi.html) for the language boundary. Continue Learning Rust for values, borrowing and Result before adding callbacks or owned buffers.

## Read the complete source

[labs/languages/rust-activity/activity.rs](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/languages/rust-activity/activity.rs)
