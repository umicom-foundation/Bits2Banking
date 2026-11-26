<!--
Umicom Bits2Banking
File: content/wiki/toolchain.md

PURPOSE:
Guide a contributor from an Umicom C source change to a checked compiler or interpreter result.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Compiler and toolchain

![Umicom Foundation](../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A toolchain is the set of programs that turns source into something you can run. A compiler produces a new representation, such as a native object file. An interpreter runs the program through its own execution engine. The work of the language frontend starts before either action.

1. Open [Developing with Umicom C](../lessons/03-native-code/developing-with-umicom-c/index.md). Run the first source example with the tool you intend to change. Save the actual output beside its expected result.
2. When studying a diagnostic, change one token and keep the original source in a separate file. Run the same command on both. Compare the exit status, source location and wording. A result printed by the program and an error printed by the tool are different observations.
3. Add the smallest case that shows the defect to the existing test group. Include a valid neighboring case. A change that simply forbids the whole feature can pass a rejection check while breaking users' valid programs.
4. Run the targeted test from a fresh build directory. Keep the tool path, architecture and exact command with the result. Repeat a native build separately if the change also affects the object file or linker.

For a classroom example, change a brew timer from 4 minutes and 15 seconds to 3 minutes and 30 seconds. First predict 210 seconds. Then compare the interpreter result with the native executable result. Follow the workshop's build and link steps for the current platform.

[Tool installation and setup](../simple-steps/index.md) · [Contributor wiki](index.md)
