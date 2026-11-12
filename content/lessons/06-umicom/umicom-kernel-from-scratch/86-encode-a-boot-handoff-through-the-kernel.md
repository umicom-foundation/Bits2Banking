<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/86-encode-a-boot-handoff-through-the-kernel.md

PURPOSE:
Teach encode a boot handoff through the kernel through the production Kernel implementation.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Encode a boot handoff through the Kernel

![Umicom](../../../assets/branding/umicom-wordmark-on-dark.svg)

## Prepare the producer exercise

A producer creates a message; a consumer reads it. Earlier lessons built bytes by hand to explain the handoff format. A startup adapter needs a maintained producer so that it does not repeat field offsets and memory-admission rules. The Kernel now exposes UmicomKernelBootHandoffWrite beside the existing reader.

Read lessons 74–81 first, then open labs/native/boot-handoff/write.c and its README. Use the documented C23 host build with the Kernel source checkout. This lesson works with synthetic numbers in ordinary process memory. It needs no administrator rights, emulator, USB device or boot image. The source is authored; compiler and execution qualification must still be obtained.

## Describe a small machine

The following declarations are the beginning of a complete input object. The kernel occupies 4096 bytes starting at 0x80001000. Its containing RAM range begins at 0x80000000 and spans one mebibyte. The reserved range covers the first 8192 bytes, including the whole kernel. Zero initialization makes the optional firmware and framebuffer descriptions absent.

~~~c
UmicomKernelBootHandoff record = {0};
record.architecture = UMICOM_BOOT_RISCV64;
record.kernel.address = 0x80001000ULL;
record.kernel.bytes = 4096;
record.ramCount = 1;
record.ram[0].address = 0x80000000ULL;
record.ram[0].bytes = 0x100000;
record.reservedCount = 1;
record.reserved[0].address = 0x80000000ULL;
record.reserved[0].bytes = 8192;
~~~

These addresses are integers describing the fixture. Never convert them to pointers in a hosted exercise. An architecture tag describes the message; selecting x86-64 does not implement an x86 startup path.

## Ask the shared producer to encode

The caller owns all three storage areas: input object, destination bytes and written-length counter. Keep them separate and stable during the call.

~~~c
unsigned char bytes[UMICOM_BOOT_HANDOFF_MAX_BYTES];
UmicomSize written = 0;
UmicomBootHandoffStatus status =
    UmicomKernelBootHandoffWrite(&record, bytes, sizeof bytes, &written);
if (status != UMICOM_BOOT_HANDOFF_OK) {
    return 1;
}
~~~

This minimal record needs 144 bytes. The supplied lab adds the 14 characters console=serial and therefore expects 158 bytes. Pass written, not destination capacity, to the reader. Its exact-length contract rejects a valid record followed by unused tail bytes.

## Follow the real implementation

1. The writer checks pointer extents, array counts, enum values and bounded command termination before encoding.
2. It writes each little-endian field into private storage. C structure padding and native byte order never become part of the wire format.
3. It calls UmicomKernelBootHandoffRead to apply existing semantic rules, then copies the admitted bytes and updates written.
4. The original main.c exercise remains available for studying offsets. Production clients should use the shared writer instead of copying that fixture helper.

## Exercise and answer

Change the reserved length from 8192 to 4096, leaving the kernel unchanged. Predict the result before running the unreserved lab case. Answer: UMICOM_BOOT_HANDOFF_MEMORY, because the reservation ends exactly where the kernel begins. Increasing destination capacity cannot repair this ownership error. Restore the valid input and run the roundtrip case again.

A successful host exercise would show agreement with the contract on that host. It would not establish physical mapping, allocator reservation, firmware compatibility or a bootable operating system.

[Hosted laboratory](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/boot-handoff/README.md) · [Complete producer example](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/boot-handoff/write.c)

[Course contents](index.md) · [Previous lesson](85-copy-one-owned-service-observation.md) · [Next lesson](87-admit-fields-before-narrowing.md)

<!-- Repository laboratory sources live outside the published content root.
Public repository links replace the former local-only routes, retained here for review:
../../../../labs/native/boot-handoff/README.md
../../../../labs/native/boot-handoff/write.c
Offline source files remain available in their listed repository/learning-pack locations. -->
