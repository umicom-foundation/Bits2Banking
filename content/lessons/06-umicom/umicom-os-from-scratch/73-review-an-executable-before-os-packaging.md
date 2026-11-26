<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-os-from-scratch/73-review-an-executable-before-os-packaging.md

PURPOSE:
Review an executable before OS packaging

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Review an executable before OS packaging

Your team has received a standalone executable named `umicom-cvm-probe`. It is a small program that checks part of Umicom’s C runtime when somebody runs it. Before discussing whether it belongs in an OS image, compare the file you received with the one the team reviewed. Start by writing down the file’s target processor, exact length in bytes and SHA-256 digest. A digest is a fixed-length value calculated from the file’s bytes.

## Before you begin

Start with the sample values and write down the expected processor type and the independently recorded file identity. The optional command uses an existing Framework image tool and a reviewed executable file it can inspect without running it.

## 1. Separate the compiler target from the file

The optional Umicom OS setting `UMICOM_OS_CVM_STATIC` first checks CMake’s configured system name. The C source then checks the compiler’s `__linux__` and `_WIN32` definitions. If the configuration says Linux and the compiler targets Windows, the source check stops the build. A Linux-target compiler can reach the static link, which still needs a static C library for that target.

An ELF file holds machine code and directions for loading it. Umicom’s file check expects a selected static ELF executable profile. It compares the requested processor with the file header and rejects an ELF that declares a program interpreter or a dynamic program header. Keep a separate review for the intended Linux application binary interface (ABI), the rules the executable uses to interact with its system, and for its actual dependency and link requirements.

## 2. Compare the file with an independent review

1. Use an existing build of Umicom Framework’s `umicom-os-image` that supports both identity arguments. In a shell, set `BUILD` to its absolute build directory and `CVM_PROBE` to the absolute file path. This example expects `x86_64`. Use `riscv64` only when the reviewed file targets that processor.
2. Copy the full SHA-256 and exact byte count from the reviewed record into `EXPECTED_SHA256` and `EXPECTED_BYTES`. Computing both values from a newly received file would only compare it with itself.
3. Ask the tool to inspect the file. Supply the digest and count together so the command checks identity as well as structure.

~~~sh
"$BUILD/bin/umicom-os-image" elf --file "$CVM_PROBE" --arch x86_64 \
  --sha256 "$EXPECTED_SHA256" --bytes "$EXPECTED_BYTES"
~~~

A match reports `ELF structure and reviewed bytes agree` with exit status `0`. Look for `process-launched=0` in the report. The tool reads the file without starting it. If a comparison fails, record the failure and check the selected file, processor and review record. With both identity options omitted, the command checks the structure alone. With only one supplied, it refuses the request.

Think of the tool holding one copy of the bytes in memory. All three checks use that same copy, so the hash describes the bytes whose structure was inspected.

~~~text
read one bounded buffer from the existing file
require the buffer to match the requested static ELF profile
require the byte count to match the reviewed count
require the SHA-256 of that buffer to match the reviewed digest
record a reviewed file match
~~~

## 3. Trace a handoff on paper

Start with a review card for `x86_64`, `4096` bytes and digest `A`. In this exercise, `A` and `B` stand for different full SHA-256 values. Cover the last column, predict the earliest stopping point, then uncover it.

| Artifact observation | Expected result |
| --- | --- |
| `x86_64`, 4096 bytes, digest `A` | The reviewed file matches. |
| `x86_64`, 4096 bytes, digest `B` after changing the last byte | The digest check refuses it. The unchanged count and parsed headers cannot establish identity. |
| `riscv64` requested for the original `x86_64` file | The selected ELF profile rejects the processor before the digest comparison. |
| Original file, expected count mistyped as `4095` | The byte-count check refuses it before hashing. |

The source includes a small inert ELF fixture for these comparisons. The exercise uses paper predictions. After a file match, review image enrollment and runtime behaviour separately. The current OS image inventory and first Linux process do not enroll this probe. Record package membership, normal boot and recovery boot as separate observations.

[Course contents](index.md) · [Previous lesson · Keep a complete report through replacement](72-keep-a-complete-report-through-replacement.md) · [Inspect an image without booting it](39-inspect-an-image-without-booting-it.md) · [Plan boot and distribution evidence](44-plan-boot-and-distribution-evidence.md) · [Read a captured boot observation](19-read-a-captured-boot-observation.md) · [Match ELF files to a finished Kernel build](../umicom-kernel-from-scratch/138-match-elf-files-to-a-finished-kernel-build.md) · [HTML edition](../../../courses/umicom-os-from-scratch/lessons/73-review-an-executable-before-os-packaging.html)
