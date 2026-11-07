<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-rust/05-link-a-rust-client-to-c.md

PURPOSE:
Explain the lesson: Link a Rust client to C.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Link a Rust client to C

Compilation translates a source file into machine-level instructions and references. Linking joins those references to the implementations they name. A Rust client can compile successfully yet fail to link when its C bridge is absent.

## Setup recap

Use the exact PowerShell or Bash sequence in labs/languages/rust-activity/README.md. It first builds the existing C activity-adapters library with CMake and then links the Rust program.

On Windows, the example selects the GNU Rust target to match the UCRT64 GCC toolchain. A default MSVC Rust installation and a GNU archive are not automatically an interchangeable pair.

## 1. Build the dependency

The CMake project finds the Framework base package and compiles bridge.c with the activity model. Its output is a static library: an archive of compiled object files.

The README's SDK path is an example. Replace it with your actual installed Framework location. Stop if configuration or compilation fails.

## 2. Read the Rust command

The command's native-library search directory points at the CMake build output. Its static-library option names btb-activity-adapters. The final output option names the executable.

These options tell the linker where to resolve BtbActivityNext. They do not copy the C algorithm into the Rust source.

For this small model, the objects use a Framework status type without calling additional Framework functions. Larger services can require further libraries and runtime dependencies.

## 3. Run only after linking succeeds

The expected output includes three successful counts and one refusal. It is a prediction to compare with your own run, not evidence of a run on your machine.

Record the Rust version, C compiler version and source revision beside the output. Keep build logs separate from the source files.

## Troubleshooting exercise

Match each symptom to its first check:

- Unknown external symbol: confirm the bridge library is included.
- Incompatible object format: compare the Rust target and C compiler target.
- Package not found: inspect the Framework SDK location.
- Executable missing: inspect the preceding build result.

Changing the current count cannot solve any of those toolchain problems. Diagnose the failing stage before editing application behavior.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/languages/rust-activity/README.md). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](04-review-a-c-language-boundary.md) · [Next lesson](06-test-boundaries-and-independent-calls.md)

