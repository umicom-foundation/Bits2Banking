<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/46-build-targets-and-platform-evidence.md

PURPOSE:
Explain the lesson: Keep platform builds and evidence separate.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Keep platform builds and evidence separate

## Before you begin

A source file contains instructions for a compiler. An object file contains compiled machine-specific code. A library groups compiled code. A target describes an output and its dependencies. These are different stages of the same build.

Read the activity adapter CMake file and each platform README. You need no installation to draw the dependency map.

## Same source, different output

The same C source can be compiled for a Windows desktop, Android ABI, iPhone simulator or WebAssembly environment. That does not make the resulting binaries interchangeable. The compiler, platform SDK, architecture and linking conventions must match the destination.

~~~text
activity.c + bridge.c
  -> desktop toolchain -> host library
  -> Android NDK       -> Android shared library
  -> Xcode iOS SDK     -> iPhone target objects
  -> Emscripten        -> WebAssembly module
~~~

## Make a build record

For each target, record the source revision, compiler version, SDK, architecture, configuration and commands. Then record whether the stage configured, compiled, linked and executed. A successful compile can still leave a missing symbol at link time.

## Lab

1. Find which adapter target compiles `activity.c`.
2. Find where Framework headers are made available.
3. Explain why an include directory supplies declarations rather than an implementation library.
4. Compare the desktop `Umicom::base` dependency with the mobile labs' status-header-only use.
5. Draw which output belongs to each platform build directory.

## Incremental work

An existing build system normally reuses outputs whose inputs have not changed. Keeping independent build directories prevents one platform's cache from being mistaken for another's. Do not copy a desktop build cache into a mobile project.

## Evaluate a claim

“Works on my desktop” is useful evidence for that desktop configuration. It is not evidence for Android or iPhone. For each additional platform, run the documented smoke workflow and failure cases and save its own result.

## Troubleshooting

If a linker reports an incompatible format, inspect the library's target architecture and platform. Rebuilding the relevant source with the correct toolchain is different from changing a filename extension.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/activity-adapters/CMakeLists.txt). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](45-sampled-buttons-on-small-devices.md) · [Next lesson](47-test-adapters-and-user-journeys.md)

