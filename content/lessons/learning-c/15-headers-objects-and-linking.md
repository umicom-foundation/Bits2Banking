# Connect declarations, source files and the linker

A program can be correct in one file and still fail to build when another file calls it. Follow one real Kernel function from its public declaration to its implementation and final executable.

## 1. Give each build stage a job

A **source file** contains the C you write. A **header**, usually ending in `.h`, describes types and function contracts shared by callers. The **preprocessor** handles directives such as `#include`. The compiler translates each resulting **translation unit** into an object file. The **linker** combines object files and resolves references to functions and data.

 <svg viewbox="0 0 700 110" role="img" aria-label="Preprocessing and compilation produce an object file; linking combines object files into the executable." style="width:100%;max-width:700px"><title>Preprocessing and compilation produce an object file; linking combines object files into the executable.</title><rect x="10" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="115" y="53" text-anchor="middle" fill="white" font-size="17">Header + C source</text><path d="M220 47h18l-7 -6m7 6l-7 6" fill="none" stroke="#287b78" stroke-width="3"></path><rect x="240" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="345" y="53" text-anchor="middle" fill="white" font-size="17">Object file</text><path d="M450 47h18l-7 -6m7 6l-7 6" fill="none" stroke="#287b78" stroke-width="3"></path><rect x="470" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="575" y="53" text-anchor="middle" fill="white" font-size="17">Linked executable</text></svg>

Preprocessing and compilation produce an object file; linking combines object files into the executable.

Successful compilation of one source file does not establish that the final executable can be linked. Conversely, having a function somewhere in the repository does not automatically put its object code into every executable.

## 2. A declaration describes a call

Open [`include/umicom/kernel/fat16_space.h`](https://github.com/umicom-foundation/umicom-kernel/blob/main/include/umicom/kernel/fat16_space.h). Its public function has this shape:

```text
UmicomKernelDiskStatus UmicomKernelFat16SpaceRead(
    UmicomKernelFat16Volume *volume,
    UmicomKernelFat16Space *outSpace);
```

The first name is the result type. The function name identifies the operation. The names in parentheses describe two pointer arguments. The final semicolon ends a **declaration**; there is no function body here. The compiler uses this declaration to check a caller's argument count and types.

The header also defines the result structure and explains the ownership contract. Types answer “what is the value's shape?” Comments and tests also answer “who owns it, when is it valid, and what happens on error?” Both matter.

## 3. Include the declaration before the call

A caller uses `#include "umicom/kernel/fat16_space.h"`. The build's include directories tell the compiler where to look. Do not add an absolute path belonging to one developer's computer.

If a C23 compiler reports an implicit function declaration, it has reached a call without a suitable earlier declaration. Check spelling and the correct public header. Do not silence the error by guessing a return type or copying a mismatched declaration into the caller.

A header guard keeps the header's declarations and type definitions from being processed repeatedly within one translation unit. It does not arrange the linker's input and does not provide a missing function implementation.

## 4. A definition supplies the implementation

Find `UmicomKernelFat16SpaceRead` in [`kernel/fat16_space.inc`](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/fat16_space.inc). The definition has braces containing the actual work: admit a scan, read mirrored allocation tables, count clusters and publish a complete result.

In this implementation, [`kernel/fat16_inspector.c`](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/fat16_inspector.c) includes that fragment at its end. The extension `.inc` is a project convention for included implementation text. It has no special linking behavior. The fragment is part of the inspector's translation unit, where it can reuse private parser helpers.

Private helpers declared `static` at file scope have internal linkage: their names are local to the translation unit. The public function has external linkage so a linked caller can refer to it. Do not expose a private helper just to bypass a missing public contract.

## 5. Put the correct object into the target

Read [`cmake/DiskInspection.cmake`](https://github.com/umicom-foundation/umicom-kernel/blob/main/cmake/DiskInspection.cmake). Its `target_sources` call adds `kernel/fat16_inspector.c` to the Kernel target. A **target** is a named build result, such as an executable or a library, with its own sources and dependencies.

The included fragment is not separately compiled. Adding the same implementation twice can create duplicate definitions. Omitting the inspector object can leave a call unresolved. The host tests also list their own required sources; a target's dependencies are not inherited merely because its files are nearby.

## 6. Identify the stage from the diagnostic

| Message | What to inspect first |
| --- | --- |
| Implicit declaration | The caller's earlier declarations, header inclusion and spelling. |
| Conflicting types | Whether the header, definition and caller agree on the result and argument types. |
| Undefined reference or unresolved symbol | Whether the required definition was compiled and its object or library is linked into this target. |
| Multiple definition | Whether the same external definition is compiled or included more than once. |

These are starting points, not automatic diagnoses. Conditional compilation, stale build rules and toolchain differences can affect what was actually built. Preserve the complete diagnostic and command.

## 7. Follow the exact function yourself

1. Find the public declaration in the header and count its two arguments.
2. Find the definition and its required include.
3. Find the `#include "fat16_space.inc"` at the end of the inspector source.
4. Find the inspector source in the CMake target.
5. Read `tests/fat16_space/CMakeLists.txt` and compare the host test target's sources.

The [allocation guide](https://github.com/umicom-foundation/umicom-kernel/blob/main/docs/FAT16_SPACE_GUIDE.md) supplies focused configure, build and test commands. Configure updates the build rules. Build translates and links. Test exercises the resulting executable. Stop on errors so an older executable is not mistaken for a successful new build.

## Exercise

You add the correct declaration to a caller. Its source now compiles, but linking still reports the function as missing. Should you add another declaration?

<details>

<summary>Explanation</summary>

No. The compiler now knows the call's type, but the linker still needs the actual definition. Trace the definition to its translation unit, then check that this target links the corresponding object or library. A second declaration does not create machine code.

</details>

Use the same investigation when reading Umicom Framework and application targets. Keeping reusable behavior in Framework still requires each caller to use its public headers and declared build dependencies.

## Read the source

Open [umicom-kernel/cmake/DiskInspection.cmake](https://github.com/umicom-foundation/umicom-kernel/blob/main/cmake/DiskInspection.cmake) to compare the explanation with the current source. Repository contents can change; use the commit shown by GitHub when recording your observations.

[Words explained](../../courses/learning-c/glossary.html) · [Practical lab guide](../../courses/learning-c/practical-guide.html) · [Connected learning routes](../../courses/learning-paths.html)

---

[Read this lesson in HTML](../../courses/learning-c/lessons/15-headers-objects-and-linking.html) · [Learning sequence](../../start/learning-sequence.md)

## Continue this module

Working with more information · Lesson 4 of 4.

[Previous: Let a function read memory you still own](10-pointers-and-borrowing.md) · [Module complete: return to course contents](index.md)
