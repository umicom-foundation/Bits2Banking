<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-os-from-scratch/44-plan-boot-and-distribution-evidence.md

PURPOSE:
Plan boot and distribution evidence

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Plan boot and distribution evidence

## Prepare the acceptance review

Collect the source revision, executable identity and output from your completed file-only exercises. Keep the failed-review experiments separately. Revisit the course lessons on host, target and image identity and the Kernel course on the first boot. This chapter produces a review plan, not a command that boots or writes a drive.

## Build a chain of specific observations

Start with the source and toolchain used to produce the kernel and userland. Add the packaging inputs, producer version and image digest. Then identify the exact image presented to a virtual machine or physical medium. Finally capture the startup and service behavior that matters to the intended product. Each observation answers a narrower question than the phrase build passed.

The current C23 laboratory covers regular-file admission and byte verification. Its synthetic image cannot satisfy an OS startup check. Kernel hosted tests also answer different questions from a guest boot. Connect the evidence instead of adding unrelated test counts and treating the sum as a release claim.

- Source: record revisions and changed-file state for Framework, OS, Kernel and any required userland.
- Artifact: record image length, digest, format observations and producer diagnostics.
- Guest: identify architecture, machine model, firmware and the selected image; capture actual startup and shutdown results.
- Physical medium: independently record target identity, transfer result and readback where supported before a hardware boot.
- Product workflow: exercise required services and applications after startup, including recovery and failure paths.

## Keep architecture and media assumptions visible

The x86-64 Linux staging path does not establish RISC-V support for the same ISO workflow. A firmware expecting one boot contract cannot be assumed to accept another merely because both artifacts are images. Keep architecture-specific acceptance checks with the artifact that was actually produced.

Physical USB writing in Framework remains an explicit build-gated capability, disabled by default. The gate does not confer qualification, and enabling it is not a lesson prerequisite. This course provides no optical burning adapter. Record those gaps as missing or unexecuted capabilities rather than inserting a fabricated green status into a distribution screen.

## Design the next thin application step

Extend the existing approved Boot Media UI by composing Framework inspection, review and progress contracts. Display the selected source and target identity, distinguish review from execution, and retain the report after completion. A Cancel control needs a worker and callback lifetime design; it is not a call to destroy the active plan. Preserve the existing layout and use shared Umicom SVG and ICO resources rather than drawing another brand.

Write acceptance criteria before implementation: changed source refuses, unavailable device capabilities remain visible, an existing output survives rejection, and a successful file copy is labeled as byte-verified rather than boot-tested. When execution evidence becomes available, attach it to the relevant criterion without changing the meaning of earlier observations.

## Review and recover

For every failed criterion, retain the selected inputs and diagnostics and state what remains unknown. Reproduce in the appropriate owner-controlled environment, then connect a focused regression to the source repair. Do not discard skipped device or firmware checks from the report. You now have a real Framework client and a precise boundary between its implemented behavior and the remaining OS distribution work.

[Lab setup and complete commands](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-boot-media/README.md) · [Read the C23 application](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-boot-media/main.c) · [Framework media contract](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/boot_media/media.h)

[Course contents](index.md) · [Previous lesson](43-prepare-an-iso-through-native-services.md)

[Continue: share a read-only image inspector](45-share-a-read-only-image-inspector.md)
