<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/49-understand-a-cross-compiled-build.md

PURPOSE:
Explain the lesson: Understand a cross-compiled build.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Understand a cross-compiled build

A compiler usually produces programs for the computer on which it runs. A cross-compiler produces programs for a different target. The Pico exercise builds Arm firmware while the development computer may run Windows, Linux or macOS.

## Setup recap

Read labs/microdevices/pico-activity/README.md. It lists the SDK, compiler and Framework header requirements, plus complete PowerShell and Bash commands. Use a separate build directory called build/pico-activity.

## 1. Read the configuration order

The SDK import appears before the project declaration. It prepares the toolchain information that CMake needs while detecting languages.

The SDK project enables C, C++ and Assembly because SDK support code can require them. The exercise's own application and model are written in C. Enabling a language is different from rewriting application behavior in it.

## 2. Inspect the source list

The target includes main.c, the shared button adapter and the shared activity model. The include directory points to the chosen Framework headers. pico_stdlib supplies the board-facing functions.

The explicit PICO_BOARD check accepts pico for this exercise. A wireless Pico uses a different route to control its LED. Removing the check does not implement that route.

## 3. Distinguish the outputs

An ELF file contains executable code plus information useful to tools such as debuggers. The UF2 output packages firmware for the board's documented copy-based loading mechanism. These are not interchangeable file extensions.

The native Windows executable produced by the host model exercise cannot be copied to the Pico as firmware.

## Exercise and troubleshooting

Before compiling, record the compiler version, SDK revision, board name and Framework revision. Predict which source file supplies each of BtbActivityAdvance, BtbActivityButtonSample and gpio_put.

If C23 is rejected, check the cross-compiler version instead of deleting the language requirement. If the SDK import is missing, check PICO_SDK_PATH. If status.h is missing, check the Framework source root. Resolve the first configuration error before interpreting later missing outputs.

A successful host check establishes model behavior on that host. A successful firmware build establishes a different result; neither alone proves the physical wiring or button behavior.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/microdevices/pico-activity/CMakeLists.txt). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](48-share-a-model-with-a-microdevice.md) · [Next lesson](50-read-a-button-as-a-sampled-signal.md)

