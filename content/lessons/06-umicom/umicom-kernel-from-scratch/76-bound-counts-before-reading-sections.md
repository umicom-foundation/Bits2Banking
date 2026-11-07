<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/76-bound-counts-before-reading-sections.md

PURPOSE:
Bound counts before reading sections

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Bound counts before reading sections

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


## A count is input too

A record can describe several RAM and reserved ranges. The header stores their counts. A count tells a loop how many times to run; an unchecked count can make it walk past an array. Even calculating the required space can overflow if large counts are multiplied first.

Umicom bounds RAM entries to 32 and reservations to 64 before computing section positions. It then requires the exact total length. The current format has one section order and no offsets chosen by the sender.

## Work through the size

1. Begin with the 64-byte header.
2. Add one 16-byte RAM span and one 16-byte reservation: 96 bytes so far.
3. Add the 16-byte firmware descriptor and 32-byte framebuffer descriptor: 144 bytes.
4. Add the command text length, zero in the lab.
5. Compare both the advertised total and the accessible buffer size to this result.

The formula is 64 + 16 × (RAM count + reservation count) + 48 + command length. It is evaluated only after the counts have passed their limits.

## Exercise and expected result

In a scratch fixture, advertise two RAM entries without adding another span or increasing the buffer. The input must be refused for length. It must not read a second span from unrelated memory. Review the counts and truncation regression cases for larger and shorter variants.

## Recovery habit

Do not change a test's expected result simply to make it pass. First compare the fixture's intended fields with its length equation. A malformed fixture is useful when the test explicitly expects refusal. A fixture intended to be valid must have every required byte present, including zero-filled absent optional sections.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/boot_handoff.c).

## Continue learning

[Course contents](../../../courses/umicom-kernel-from-scratch/index.html) · [Previous: Read little-endian fields without alignment assumptions](75-read-little-endian-fields.md) · [Next: Check physical-memory spans without integer wrap](77-check-physical-memory-spans.md)
