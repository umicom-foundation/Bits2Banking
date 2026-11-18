<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/learning-gtk4/25-diagnose-an-unexpected-full-rebuild.md

PURPOSE:
Diagnose an unexpected full rebuild

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Diagnose an unexpected full rebuild

[Course contents](index.md)
An incremental build reuses outputs whose inputs have not changed. It still must rebuild the dependencies of the selected target. A small command can therefore trigger substantial work if that target depends on many libraries. Measure the actual reason before deleting the build directory: deleting it also removes the reusable outputs.


## Inspect the build plan first

Use the source-study build from lesson 22. The following PowerShell commands inspect a configured Ninja build. The -n option requests a dry run; -d explain asks Ninja why work is considered necessary. These commands do not execute compile or link commands.

~~~powershell
ninja -C build/preview-study -n -d explain btb-preview-revisions
ninja -C build/preview-study -t targets
~~~

1. Run the dry plan immediately after a successful build and save its output.
2. Edit a comment in the lab's main.c and save it. A source timestamp can trigger recompilation even when the resulting machine code would be identical.
3. Run the dry plan again. Expect main.c's object and the executable link to be affected; inspect the actual explanation.
4. Build only btb-preview-revisions, then run its CTest check.
5. Repeat with an unchanged file. If a generator rewrites a header every time, inspect that generator rather than assuming the compiler is ignoring dependencies.


## Understand the dependency chain

~~~text
main.c -------------------+
hot_reload.h -> main.c.o --+-> btb-preview-revisions
hot_reload.c -> service.o -+
dev_types.c -> text.o -----+

Changing a shared header may affect more than one object.
~~~

A compilation database records commands used to compile translation units. Enable CMAKE_EXPORT_COMPILE_COMMANDS during configuration when the chosen generator supports it. Read compile_commands.json to compare include directories, definitions and language options. Running gcc on one file with different flags is not an equivalent project check.

~~~powershell
cmake -S labs/native/framework-preview-revisions -B build/preview-study -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
cmake --build build/preview-study --target btb-preview-revisions --parallel 2
~~~

Keep a short table of edit type, planned object count, build elapsed time and observed result. An empty plan is different from a fast compile. A successful compile is different from a passing behavioural check. A cache can reduce repeated compilation but cannot fix a missing dependency or a wrong target.


## Recovery

If Ninja cannot find its build file, confirm that CMake successfully configured the exact directory passed to -C. If the compiler path changed, inspect the cache and use a separate build directory for the different toolchain. Avoid mixing UCRT64 objects with an unrelated compiler environment. Do not delete evidence before understanding a failure.

Exercise: a header shared by fifty targets changes. Is recompiling all affected users necessarily a defect? No. The useful question is whether those targets are required by the selected output and whether the dependency is accurate.


[Previous lesson](24-preserve-edits-during-a-preview-build.md) · [Next lesson](26-qualify-a-current-interactive-preview.md)
