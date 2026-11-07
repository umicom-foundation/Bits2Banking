<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/80-publish-one-owned-boot-observation.md

PURPOSE:
Publish one owned boot observation

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Publish one owned boot observation

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


## Staging before publication

A function can discover an error near the end of an input. If it has already overwritten caller state, the caller may be left with a mixture of old and new fields. Staging means building a complete candidate separately and publishing only after all checks succeed.

UmicomKernelBootHandoffRead clears a local candidate, fills it, validates every section and copies it to the output once. Every earlier return leaves the output untouched. Unused array entries and the remainder of the command buffer stay zero.

## Ownership and lifetime

The successful result owns its arrays and text. It contains no pointer into the input. The producer may release the input after the call, while the result remains usable. The result still contains numeric physical addresses whose later use requires platform validation.

1. Find the staged local variable in the reader.
2. Follow all return statements before UmicomBootMemoryCopy.
3. Confirm none writes through out.
4. Inspect Refused in the test source: it fills output with a known byte, calls the reader and compares all bytes afterwards.
5. Inspect overlap: it refuses output storage that overlaps the input because publication could otherwise corrupt data still being read.

## Exercise

Add a printable three-character command to a scratch record, adjusting its length and header. Predict what happens if its second byte becomes a newline. The reader returns UMICOM_BOOT_HANDOFF_TEXT and preserves output. The output command is terminated because the candidate was cleared before copying the printable bytes.

## Limit

Atomic publication here describes a single call's failure behaviour. It does not provide thread synchronisation. The caller must prevent simultaneous mutation of either buffer.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/boot_handoff.c).

## Continue learning

[Course contents](../../../courses/umicom-kernel-from-scratch/index.html) · [Previous: Admit firmware and framebuffer descriptions](79-admit-optional-boot-descriptors.md) · [Next: Qualify host and freestanding boot boundaries](81-qualify-host-and-freestanding-boundaries.md)
