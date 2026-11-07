<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/74-describe-the-startup-handoff.md

PURPOSE:
Describe the startup handoff

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Describe the startup handoff

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


## What a kernel needs to know

A kernel is the part of an operating system that manages processors, memory and devices. Before it can allocate memory, it needs a reliable description of what memory exists and which parts are already occupied. Startup code supplies that description. A handoff is the boundary where one component passes information and responsibility to another.

Our laboratory describes a synthetic machine with one RAM region. RAM means memory that can hold changing program data. The kernel image occupies part of that region, so an allocator must not offer those bytes to another user. A reservation records that restriction.

## Trace one complete example

1. Open the lab's main.c and find the record array. An array is a consecutive set of equally sized elements; each element here is one byte.
2. Find the RAM address 0x80000000 and length 0x100000. The prefix 0x means hexadecimal, a base-sixteen number notation.
3. Find the kernel address 0x80001000 and length 4096. The kernel starts 4096 bytes after the RAM start.
4. Find the reservation length 8192. It covers the initial 8192 bytes of RAM, including the kernel.
5. Run the lab. The first message describes accepted metadata. Nothing has been loaded at these numeric addresses.

## Draw the relationship

RAM: [startup space | kernel bytes | available remainder]
Reservation: [startup space | kernel bytes]

The picture explains why merely knowing RAM size is insufficient. Ownership matters too. The reader checks this relationship before publishing its result.

## Exercise and expected result

Write down who creates the input, who validates it and who may later allocate memory. The fixture creates the bytes; UmicomKernelBootHandoffRead validates them; a future platform integration will pass admitted information to memory management. The current reader itself allocates nothing and changes no boot path. If the lab exits before its first message, inspect the declared lengths before investigating emulator settings.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/boot_handoff.c).

## Continue learning

[Course contents](../../../courses/umicom-kernel-from-scratch/index.html) · [Next: Read little-endian fields without alignment assumptions](75-read-little-endian-fields.md)
