<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-os-from-scratch/32-distinguish-build-host-and-target-identities.md

PURPOSE:
Distinguish build, host and target identities

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Distinguish build, host and target identities

## Prepare the exercise

Install a matching native Framework SDK with the recipe API, then build this C23 consumer using the same compiler and architecture. Run each command separately and stop on unexpected errors. The recipe stages themselves are never executed by this exercise.

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S .\labs\native\framework-recipes -B .\build\framework-recipes -G Ninja -DCMAKE_C_COMPILER=C:/msys64/ucrt64/bin/gcc.exe -DCMAKE_PREFIX_PATH=C:/umicom/installed/framework -DBUILD_TESTING=ON
cmake --build .\build\framework-recipes --parallel 2
ctest --test-dir .\build\framework-recipes --output-on-failure --no-tests=error
& .\build\framework-recipes\btb-framework-recipes.exe inspect C:/umicom/Umicom-Bits2Banking/labs/native/framework-recipes/recipe.json
```

The inspect scenario should report recipe-lab with one input and one stage. CTest registers inspect, owned, identity and refuse. These are expected observations; the commands must be run to establish results in your environment.

## Name three different machines

Build is the machine on which a tool is built. Host is the machine on which that resulting tool runs. Target is the machine for which a compiler produces code. A compiler built on Windows to run on Windows and emit RISC-V code therefore has equal build and host identities but a different target. An ordinary program may not itself generate code; still record the intended environment explicitly when documenting a toolchain rather than guessing from the filename.

## Read what the parser actually checks

The recipe checks lowercase triple spelling, nonempty components and bounded length. It does not interrogate gcc, load a binary, inspect an ABI or confirm that a target backend exists. Change target from riscv64-unknown-elf to a structurally invalid value with an empty component and inspect the refusal. Then choose another syntactically valid triple and observe that acceptance is only a metadata result. Keep the original file and use a separate exercise copy.

## Prepare a real qualification record

Before using a compiler, collect its version output and artifact identity in the environment where it will run. Keep the compiler, assembler, linker, libraries and sysroot identities together. For an OS image, distinguish a host-side utility passing its tests from code executing in the target guest. A successful host recipe inspection cannot establish boot support. Write a small table assigning each proposed artifact to its build, host and target before selecting commands.

## Review and recover

Keep the selected JSON, diagnostic and executable identity when a check fails. Reconcile SDK headers and libraries before changing source. Correct malformed metadata without weakening the validator, and preserve unexecuted build, target and provenance checks separately from inspection results.

[Read the C exercise](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-recipes/main.c) · [Full setup and native commands](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-recipes/README.md) · [Shared contract](https://github.com/umicom-foundation/umicom-framework/blob/main/docs/learning/source-build-recipes.md)

[Course contents](index.md) · [Previous lesson](31-describe-a-source-build-before-running-it.md) · [Next lesson](33-admit-portable-source-and-output-paths.md)
