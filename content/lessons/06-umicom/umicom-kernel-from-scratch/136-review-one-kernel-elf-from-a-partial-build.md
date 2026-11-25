<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/136-review-one-kernel-elf-from-a-partial-build.md

PURPOSE:
Review one Kernel ELF from a partial build record

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Review one Kernel ELF from a partial build record

A build can produce one image while other steps are still pending. In this saved Umicom Kernel example, you can read an image header and a build transcript on paper. Put one question beside each observation.

## 1. Follow the named link step

CMake finished configuration and generation for a Debug build with Clang targeting 64-bit RISC-V. Those steps wrote the build plan. Ninja then worked through that plan. The saved transcript shows this step for the interactive console image:

```text
[305/6173] Linking C executable bin\umicom-console.elf
```

The CMake target `umicom-console-image` produces this file. The last retained line at `[1558/6173]` records compilation of one object for a different image. The saved prefix has no final process result for the full build command. Record that result as unconfirmed for this snapshot.

## 2. Read the saved ELF header

An ELF is an Executable and Linkable Format file. A tool can read its header to identify the file format and machine. The saved `llvm-readobj` output for `umicom-console.elf` includes these fields:

```text
Format: elf64-littleriscv
Arch: riscv64
AddressSize: 64bit
Type: Executable (0x2)
Machine: EM_RISCV (0xF3)
Entry: 0x80200000
```

The header describes a little-endian 64-bit RISC-V executable. Little-endian describes the order of bytes in numbers stored in the file. The entry address is where a suitable loader would hand control to the program. Reading that address tells you what the file declares.

## 3. Match each claim to its evidence

CTest listed 244 registered checks. The list includes `kernel.qualification.identity`. That check requires `kernel_current_image`, a setup step that first builds the wider `umicom-kernel-evidence` target. A setup step that prepares inputs for other checks is called a fixture. In this snapshot the setup fixture and QEMU guest were unexecuted.

Cover the right column and fill it from the observations above. Then check your answers.

| Question | Answer from this snapshot |
| --- | --- |
| Did CMake write a build plan? | Yes. The configure transcript records configuration and generation. |
| Which ELF was inspected? | The interactive console image, with RISC-V entry address `0x80200000`. |
| Did the full build complete? | Unconfirmed in the saved prefix. Its last retained progress line describes another image. |
| Did the identity check run? | The registry lists the check. The artifact fixture was unexecuted and there is no verification result in this record. |
| What did the running guest do? | Guest behavior is unobserved in this snapshot. |

When someone asks whether the full build succeeded, ask for the final exit status of the same build command. A zero exit answers that question for the targets the command requested. Keep the identity check result and any guest transcript with their matching build evidence.

[Course contents](index.md) · [Previous lesson · Check boot mode and process exit separately](135-check-boot-mode-and-process-exit.md) · [Check the configured Kernel platform](133-check-the-configured-kernel-platform.md) · [Read a Ninja progress record](../../05-engineering/learning-build-systems/28-read-a-ninja-progress-record.md) · [Read ELF and PE/COFF headers](../../05-engineering/74-read-elf-pe-coff-with-c23.md) · [HTML edition](../../../courses/umicom-kernel-from-scratch/lessons/136-review-one-kernel-elf-from-a-partial-build.html)

[Next lesson · Run Kernel evidence checks on the host](137-run-kernel-evidence-checks-on-the-host.md)
