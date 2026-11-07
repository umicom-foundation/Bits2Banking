<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-rust/04-review-a-c-language-boundary.md

PURPOSE:
Explain the lesson: Review a C language boundary.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Review a C language boundary

An interface between languages is often called a foreign function interface, or FFI. Both sides must agree on the function name, argument types, result type and calling convention.

## Setup recap

Open labs/languages/rust-activity/activity.rs and labs/native/activity-adapters/bridge.h. No broker, network service or device is involved. This example passes one integer by value and receives one integer.

The lab uses Rust edition 2024. See the [Rust edition guide](https://doc.rust-lang.org/edition-guide/rust-2024/unsafe-extern.html) for external declarations.

## 1. Compare the declarations

The C declaration takes int and returns int. The Rust declaration uses c_int for each. The external block names the C calling convention.

Do not replace c_int with a type merely because it is the same size on your computer. Interface compatibility is a contract between the two compilers.

A correct-looking declaration cannot prove that the library linked later contains the expected implementation.

## 2. Locate the unsafe operation

Rust cannot inspect the C implementation through this declaration. Calling it therefore requires an unsafe block. The nearby safety comment explains this particular call: the signature agrees, there are no borrowed pointers, and the C bridge checks every integer input.

The public advance function then provides a Result-based interface.

Unsafe does not mean that an error is known to occur. It identifies obligations the programmer must justify. Moving the call into a wrapper concentrates that review in one place.

## 3. Follow the actual rule

Open bridge.c and then framework-activity/activity.c. The bridge rejects negative input before converting to unsigned. The model checks its limit and writes the next value only on success.

This is a shared educational model using Framework status conventions. A production feature should call the relevant Framework service rather than recreate its policy in each language.

## Exercise and recovery

Write the interface contract in four lines: symbol, parameter, result and refusal encoding. Then explain why adding a pointer parameter would introduce new lifetime and length questions.

If linking fails, check the library and target architecture. Changing unsafe annotations cannot repair a missing or incompatible library.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/languages/rust-activity/activity.rs). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](03-represent-success-and-refusal.md) · [Next lesson](05-link-a-rust-client-to-c.md)

