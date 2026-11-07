<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/75-read-little-endian-fields.md

PURPOSE:
Read little-endian fields without alignment assumptions

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Read little-endian fields without alignment assumptions

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


## Bytes and numbers

A byte has eight bits and can represent a value from 0 through 255. A larger integer uses several bytes. Endianness describes their order. Little endian stores the least significant byte first. The two bytes 0x40 and 0x00 represent 64 in this format.

The wire format is a sequence of specified bytes. A C structure has a layout chosen by the compiler, including possible padding between members. Directly casting incoming bytes to a structure would assume its layout and alignment match the producer. Alignment is a requirement that some objects begin at particular address multiples.

## Follow the reader

1. Find Read16 in kernel/boot_handoff.c.
2. It reads p[0] and p[1] separately, shifts the second byte left eight bits and combines them with bitwise OR.
3. Read32 repeats the idea for four bytes. Read64 combines two four-byte values after widening the upper half to 64 bits.
4. The laboratory Put helper reverses the process when creating a fixture.
5. In the regression file, find the unaligned case. It moves a complete record one byte into a larger array and still expects acceptance.

## Exercise

Calculate the bytes representing version 1 and header size 64. They are 01 00 and 40 00. Change only the version bytes to 02 00 in a scratch copy of the lab and rebuild. The reader must refuse the unsupported version. Restore 1 afterwards.

## Why this matters

A byte-wise reader is usable even when a record begins at an address unsuitable for a multi-byte integer load. This does not make an arbitrary address accessible: the caller still supplies a real buffer. If a test crashes before reporting refusal, inspect buffer allocation and the supplied length first. Endianness handling cannot repair an invalid pointer.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/boot_handoff.c).

## Continue learning

[Course contents](../../../courses/umicom-kernel-from-scratch/index.html) · [Previous: Describe the startup handoff](74-describe-the-startup-handoff.md) · [Next: Bound counts before reading sections](76-bound-counts-before-reading-sections.md)
