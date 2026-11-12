<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/96-read-linker-boundaries-as-addresses.md

PURPOSE:
Teach read linker boundaries as addresses through the native Kernel coordinator.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
![Umicom](../../../assets/branding/umicom-logo.svg)

# Read linker boundaries as addresses

## Separate a C object from a linker symbol

An ordinary C array has elements whose relationship the language defines. A linker boundary symbol identifies a location chosen when sections are laid out. The Kernel declares symbols so C can refer to those locations, but two boundary declarations do not describe two elements of a single ordinary array. This distinction matters when computing an embedded executable size.

## Use the existing address contract

The Kernel already provides UMICOM_KERNEL_LINKER_ADDRESS for deliberate conversion through its pointer-sized integer type. Normal startup uses that conversion for the executable boundaries, requires the end to follow the start, and only then subtracts. The resulting number is a byte count; it is not evidence that the bytes form an acceptable ELF.

~~~c
const UmicomAddress imageStart =
    UMICOM_KERNEL_LINKER_ADDRESS(UmicomLaunchExecutableStart);
const UmicomAddress imageEnd =
    UMICOM_KERNEL_LINKER_ADDRESS(UmicomLaunchExecutableEnd);
if (imageEnd <= imageStart)
    UmicomStartupRecovery("startup-image-range", UMICOM_FALSE);
const UmicomSize imageBytes = (UmicomSize)(imageEnd - imageStart);
~~~

## Check each layer for its own reason

An ordered range allows the coordinator to describe the embedded buffer. The existing executable loader still checks the image format and target rules. The boot-memory reservation still protects the linked Kernel image. None of those checks replaces the others. Treat a conversion macro as a platform contract, not a portable way for arbitrary application code to subtract unrelated pointers.

## Construct useful negative cases

The hosted fixture maps the symbol identities to explicit synthetic target addresses. One case gives equal endpoints and another reverses them. Both must select startup-image-range before controller admission. The ordinary case supplies a 64-byte fixture span and checks that the job description receives that exact count. It does not pretend those bytes are a runnable guest program.

## Exercise and recovery

For start 0x80300000 and end 0x80300040, calculate the size: 0x40, or 64 bytes. For an end below the start, do not interpret unsigned wraparound as a very large valid image. Inspect the linker script, symbol map and image identity before changing the guard. A range failure is evidence to preserve, not an invitation to bypass admission.

Companion source: umicom-kernel/kernel/normal_boot.c and tests/boot_services/normal_boot_tests.c. Read docs/NORMAL_BOOT_COORDINATOR.md in the same Kernel checkout. Match source revisions before running the exercises.

[Course contents](index.md) · [Previous lesson](95-follow-startup-owner-transitions.md) · [Next lesson](97-preserve-startup-stream-identity.md)
