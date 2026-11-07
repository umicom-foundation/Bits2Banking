<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/77-check-physical-memory-spans.md

PURPOSE:
Check physical-memory spans without integer wrap

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Check physical-memory spans without integer wrap

This lesson explains one boundary between startup software and a kernel. It begins with a small hosted C program, uses synthetic addresses, and links the real Umicom Kernel reader. No previous operating-system course is required.

## Prepare a small host laboratory

A terminal accepts commands as text. A compiler translates C into machine instructions. CMake describes which files form a program; Ninja executes the build steps. Use a C23-capable GCC, CMake 3.24 or later and Ninja. On Windows these commands use an existing MSYS2 UCRT64 installation. Open PowerShell, enter one command at a time, and stop if it fails. Replace the checkout paths if yours differ. No boot disk or administrator access is needed.

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S labs/native/boot-handoff -B build/boot-handoff -G Ninja -DUMICOM_KERNEL_SOURCE=C:/umicom/umicom-kernel
cmake --build build/boot-handoff --parallel 2
& .\build\boot-handoff\boot-handoff.exe
ctest --test-dir build/boot-handoff --output-on-failure --no-tests=error
```

On Linux, open a Bash terminal and use these equivalent paths:

```bash
cd ~/umicom/Umicom-Bits2Banking
cmake -S labs/native/boot-handoff -B build/boot-handoff -G Ninja -DUMICOM_KERNEL_SOURCE="$HOME/umicom/umicom-kernel"
cmake --build build/boot-handoff --parallel 2
./build/boot-handoff/boot-handoff
ctest --test-dir build/boot-handoff --output-on-failure --no-tests=error
```

The expected messages begin with `Accepted:` and `Refused:`. The latter confirms a deliberate invalid-input exercise. A nonzero exit code indicates the expected result was not obtained. If CMake cannot find the reader, check `UMICOM_KERNEL_SOURCE`; if a compiler option is unsupported, check the compiler version. These host checks do not establish that a kernel can boot.


## Start and length

A span describes an address and a number of bytes. A half-open interval includes its start and excludes its end. A span starting at 100 with length 20 covers addresses 100 through 119; its exclusive end is 120. This convention makes adjacent intervals easy to express.

An unsigned integer has a largest value. Adding beyond it wraps around, producing a small value. ValidSpan first checks that length is nonzero and that start is at most the largest value minus length. Only then can the exclusive end be formed safely.

## Follow containment

1. Open Contains in the reader.
2. It first checks that the inner start is not below the outer start.
3. It subtracts the outer start to get the distance into the outer span.
4. It checks that distance fits, then compares the inner length with the remaining space.
5. It relies on both spans already having passed ValidSpan.

These ordered checks prevent subtraction underflow and addition overflow. Ordering is part of the algorithm, not a formatting choice.

## RAM admission

RAM ranges must have starts and sizes divisible by 4096. This is the admission unit used by this format. Two RAM ranges may touch, but they cannot overlap. The reader compares a new range with all previously admitted ranges; at most 32 entries keeps that work bounded.

## Exercise

On paper, compare [100,120) with [120,140), then [119,140). The first pair is adjacent, the second overlaps. Locate ram-overlap in the regression source and identify the equivalent page-aligned examples. Keep addresses numeric; do not dereference the synthetic values in the laboratory.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/boot_handoff.c).

## Continue learning

[Course contents](../../../courses/umicom-kernel-from-scratch/index.html) · [Previous: Bound counts before reading sections](76-bound-counts-before-reading-sections.md) · [Next: Reserve what startup already owns](78-reserve-what-startup-already-owns.md)
