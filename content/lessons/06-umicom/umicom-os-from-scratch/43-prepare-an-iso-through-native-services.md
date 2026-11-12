<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-os-from-scratch/43-prepare-an-iso-through-native-services.md

PURPOSE:
Prepare an ISO through native services

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Prepare an ISO through native services

## Prepare the source reading

Read Framework src/setup_centre/media.c and the prepare-and-check-boot-media guide. This chapter is a source walkthrough unless you separately possess a qualified Linux kernel, matching gzip initrd, native Linux GRUB producer and an isolated output location. The synthetic MBR image from earlier lessons is not an input to media-stage. No ISO producer is bundled by this course.

## Staging and ISO production are separate operations

media-stage accepts a supported x86-64 Linux boot-protocol kernel and gzip initrd, creates a new staging directory and records the files it prepared. It is not a generic converter for any Umicom Kernel executable or a RISC-V disk image. Follow the format checks before assuming that a file called kernel is compatible.

media-iso consumes the prepared tree, checks its receipt and uses an explicitly selected native Linux GRUB program through the Framework process executor. It creates another new directory and writes UmicomOS.iso inside it. The output parameter therefore names a directory, not the final ISO filename. This distinction matters when preparing a path that must not already exist.

```text
umicom setup media-stage --kernel /absolute/linux-kernel --initrd /absolute/initrd.gz --output /absolute/new-prepared-tree
umicom setup media-iso --prepared /absolute/new-prepared-tree --grub /absolute/grub-mkrescue --output /absolute/new-iso-directory
```

## Understand the shared CLI boundary

The main umicom setup route and standalone umicom-setup delegate to the same service. UmiSetupNativeMain owns a process-result buffer for the synchronous call and uses the existing process adapter. The routing layer does not build a shell command string, duplicate ISO policy or silently elevate privileges. Reduced builds without the process adapter report unavailable for execution-dependent operations.

The ISO-producing implementation is native Linux functionality. Its Windows branch reports unavailable; a Windows build of the CLI is not evidence of Windows ISO-production support. Copying a Windows path into the Linux command example will not make the producer or payload compatible. Keep platform qualification separate.

## Inspect the result before considering distribution

After an owner-run production step succeeds, locate UmicomOS.iso inside the named output directory. Review its producer result, receipt, length and digest. The setup service performs structural checks on the produced artifact; boot-media inspect can provide a separate structural observation. An optical boot catalogue or a successful producer exit still does not establish that the image boots on your intended firmware.

The existing media interface has no optical burning or eject command. An ISO file and a CD written from it are different artifacts with different verification requirements. Do not describe a completed file-generation step as a tested USB or CD distribution.

## Review and recover

If a staging directory already exists, preserve it and select a new reviewed location. If receipt checks fail, identify the changed file rather than editing the receipt to bypass comparison. If the producer fails, retain its output and treat the new directory as incomplete. Continue to the final lesson to plan the evidence needed for an actual OS release.

[Lab setup and complete commands](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-boot-media/README.md) · [Read the C23 application](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-boot-media/main.c) · [Framework media contract](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/boot_media/media.h)

[Course contents](index.md) · [Previous lesson](42-copy-and-verify-regular-file-media.md) · [Next lesson](44-plan-boot-and-distribution-evidence.md)
