<!--
Umicom Bits2Banking
File: labs/languages/native-interoperability/README.md

PURPOSE:
Connect the native language course to its complete shared C ABI examples.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Native languages working together

![Umicom](../../../content/assets/branding/umicom-wordmark.svg)

Start with the [twelve-lesson course](../../../content/courses/native-language-interoperability/index.html). Its C boundary reuses activity.c and bridge.c; each client translates types and errors rather than copying the counting rule.

## Files to open

- C: [the checked model](../../native/framework-activity/activity.c) and [bridge](../../native/activity-adapters/bridge.c).
- C++: [client and build guide](../../native/cpp-activity-client/README.md).
- Rust: [client and commands](../rust-activity/README.md).
- Zig: [client and commands](../zig-activity/README.md).
- Fortran: [C interoperable client](../fortran-activity/main.f90), [first program](../fortran-activity/hello.f90).
- D: [BetterC client](../d-activity/main.d).
- Odin: [foreign client](../odin-activity/main.odin), [first program](../odin-activity/hello.odin).
- Nim: [C backend client](../nim-activity/main.nim), [first program](../nim-activity/hello.nim).
- Assembly: [GNU-style x86-64 forwarding function](../../native/assembly-activity/forward.S) and [checking C driver](../../native/assembly-activity/main.c).

The first lesson builds the common archive with an installed Framework SDK. Per-language lessons provide their command lines. Select one main source at a time: hello and the foreign client both have entry points. Match processor, object format and runtime across the compiled objects.

## Expected checks

The foreign clients check (-1,-1), (0,1), (41,42), (999,1000) and (1000,-1), where each pair is input and expected result. The assembly driver also compares INT_MIN and INT_MAX with explicit rejected results and the direct C call. Earlier C++, Rust and Zig labs retain their own tests and output formatting. No benchmark ranking follows from these examples.

A missing compiler is not a passing test. Keep source review, configuration, compilation, linking and execution results separate. The presence of these files does not mean the optional compilers are installed or their Windows/Linux linkers have been qualified.

## Read inside Studio

Studio's bundled Native languages and the C boundary guide explains language selection and the examples. For the complete course, choose the Bits2Banking repository as the library root and learning-packs/native-language-interoperability.json as the manifest path. The manifest names exact repository-relative resources. Load it through the existing catalogue as described in [the pack guide](../../../learning-packs/README.md). Keep the complete checkout available; copying only the manifest into an empty folder cannot supply its resources. External prerequisite links may require another pack or a browser.

Loading content never runs its code or installs a toolchain. Studio editing recognition is separate from syntax packages, compiler configuration, language servers and debuggers. Fixed-form Fortran and arbitrary assembly dialect comment rules are outside this course's automatic editing policy.
