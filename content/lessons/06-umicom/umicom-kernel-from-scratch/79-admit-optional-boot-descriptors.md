<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/79-admit-optional-boot-descriptors.md

PURPOSE:
Admit firmware and framebuffer descriptions

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Admit firmware and framebuffer descriptions

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


## Optional information still has a contract

Firmware is startup software provided by a machine or emulator. A firmware table describes hardware. A framebuffer is a region where pixel values represent an image. The boot record may describe either, but this reader does not access their contents.

Absent information is explicit: the kind is zero and its descriptor fields are zero. This avoids an ambiguous stale address being mistaken for usable data.

## Firmware descriptor

Find the tableKind checks. An FDT descriptor needs eight-byte alignment and at least 40 bytes. An ACPI RSDP descriptor needs sixteen-byte alignment and at least 20 bytes. These are preliminary descriptor checks; table parsing and checksums belong to separate validators. Any descriptor intersecting RAM must be wholly covered by one reservation.

## Framebuffer descriptor

1. Width counts pixels per row; height counts rows.
2. The admitted formats use four bytes per pixel.
3. Stride is the byte distance between consecutive row starts. It can exceed width times four because a row may include padding.
4. The reader widens width before multiplying by four.
5. It checks stride times height against storage length and requires four-byte alignment.

For a width of 16, height of 4 and stride of 64, the minimum storage is 256 bytes. The framebuffer-refusal test tries 255.

## Exercise

Explain why accepting that descriptor does not authorise writing pixels. Physical mapping, device ownership, cache policy and platform support still need proof. Change no real framebuffer memory in this host lab. If rendering later fails, separate descriptor admission from the platform's mapping and display code instead of weakening the size check.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/boot_handoff.c).

## Continue learning

[Course contents](../../../courses/umicom-kernel-from-scratch/index.html) · [Previous: Reserve what startup already owns](78-reserve-what-startup-already-owns.md) · [Next: Publish one owned boot observation](80-publish-one-owned-boot-observation.md)
