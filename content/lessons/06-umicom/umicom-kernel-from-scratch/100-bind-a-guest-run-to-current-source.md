<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/100-bind-a-guest-run-to-current-source.md

PURPOSE:
Bind a guest run to current source and images

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Bind a guest run to current source and images

## Before you begin
Read the course's separate host, cross-build and guest boundaries. Use a disposable practice build directory, the documented RISC-V Clang toolchain and QEMU. Keep the Kernel checkout and optional canonical Umicom C runtime identity together.

## A successful boot can still be stale
An old ELF file can remain after a failed compilation. Launching it may produce a familiar ready marker even though the new source never linked. The Kernel qualification fixture rebuilds current targets and records source/image identities before dependent guest tests.

~~~text
Source tree + toolchain
    -> current build
    -> source and ELF receipt
    -> receipt verification
    -> guest observation
~~~

1. Inspect cmake/Qualification.cmake.
2. Follow the current-image fixture relationship in the root CMake file.
3. Open the receipt in your build directory.
4. Distinguish source identity from the runtime marker printed by a guest.

## Optional external runtime
The CVM user program links the canonical Umicom C runtime. Its additional receipt includes selected runtime sources, public headers, build recipe and both O0/O2 images. A Kernel-only revision cannot identify that external code by itself.

## Exercise and expected result
After a successful practice build, change a copied source input and run the identity verification against the old receipt. Expect refusal, not an automatic claim that the old image represents the edit. Restore through your normal reviewed source workflow and rebuild before rerunning the guest.

The regression fixtures perform controlled source, image and receipt mutations in test-owned storage. Do not perform this exercise on your only working tree or an important disk image.

## Recovery
If identity verification fails, preserve the receipt and compare its listed inputs with current files. A missing header, edited source and corrupted receipt are different causes. Rebuild only after resolving the mismatch; do not hand-edit hashes to make verification succeed.

A receipt documents what was observed. It is not a code signature, a proof of authenticity or a replacement for reproducible toolchain qualification.


[Course contents](index.md) · [Previous lesson](99-qualify-normal-boot-at-separate-boundaries.md) · [Next lesson](101-qualify-kernel-storage-on-disposable-media.md)
