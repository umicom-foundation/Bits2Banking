<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/81-qualify-host-and-freestanding-boundaries.md

PURPOSE:
Qualify host and freestanding boot boundaries

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Qualify host and freestanding boot boundaries

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


## Two different questions

Host tests ask whether the reader accepts and refuses the right byte sequences. A freestanding link check asks whether the compiled code can exist without the usual operating-system C library. Neither alone proves that a machine boots.

A compiler may turn a structure copy or clearing loop into a call to memcpy or memset. That can work in a host test and fail during a kernel link. Umicom reuses its explicit boot-memory helpers and includes the reader in debug and optimised link checks.

## Review the qualification path

1. Build and run the isolated host tests described in the Kernel BOOT_HANDOFF guide.
2. Read tests/boot_handoff/handoff_tests.c and find valid, malformed-length, overlap and unchanged-output checks.
3. Read cmake/BootMemoryContracts.cmake. The link targets include the reader even though a test entry may not call it.
4. Configure the existing RISC-V preset using its documented toolchain, then build the umicom-boot-memory-contracts target.
5. Keep the actual command output and compiler identity with the result. A prepared test is not a passing test until run.

## What remains to integrate

A platform adapter must construct the record from admitted firmware data, preserve startup ownership and connect the result to memory management. The existing RISC-V entry remains the current boot path. Architecture tags for x86-64 and AArch64 describe a record format; they do not create boot entries or USB images.

## Exercise

Create an evidence checklist with three rows: host malformed-input tests, freestanding link checks, and emulator boot integration. Mark a row completed only when its actual command and result are available. When a link fails with an undefined C-library symbol, inspect the generated dependency and the boot-memory helper use; do not suppress the check or label it an emulator failure.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/boot_handoff.c).

## Continue learning

[Course contents](../../../courses/umicom-kernel-from-scratch/index.html) · [Previous: Publish one owned boot observation](80-publish-one-owned-boot-observation.md)
