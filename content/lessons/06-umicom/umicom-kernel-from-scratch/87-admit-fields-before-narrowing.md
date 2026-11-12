<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/87-admit-fields-before-narrowing.md

PURPOSE:
Teach admit fields before narrowing through the production Kernel implementation.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Admit fields before narrowing

![Umicom](../../../assets/branding/umicom-wordmark-on-dark.svg)

## Prepare a boundary review

A wire format uses small fixed-width fields to keep messages predictable. The in-memory types may be wider. Converting first and validating second can turn an invalid caller value into a valid-looking message. Open kernel/boot_handoff_write.c and the pixel_tag, ram_count and text_termination cases in tests/boot_handoff/write_tests.c.

Use the host build described in the boot-handoff lab README. Read the code before executing any case. The supplied tests are acceptance checks awaiting qualification, not a record of passing results.

## Do not let a cast invent validity

The pixel format occupies 16 bits on the wire. The value 65537 has low 16 bits equal to 1. If a producer cast that value first, it could appear to be RGBX32. The writer instead compares the complete caller value against the three supported enum values.

~~~c
if (record->framebuffer.format != UMICOM_BOOT_PIXELS_NONE &&
    record->framebuffer.format != UMICOM_BOOT_PIXELS_RGBX32 &&
    record->framebuffer.format != UMICOM_BOOT_PIXELS_BGRX32) {
    return UMICOM_BOOT_HANDOFF_UNSUPPORTED;
}
~~~

Only after this admission may the value be narrowed for Put16. The same principle applies to architecture and firmware tags. A cast changes representation; it does not prove that a value belongs to the protocol.

## Bound counts before arithmetic

The input object has space for 32 RAM ranges and 64 reserved ranges. The writer rejects zero RAM ranges, excessive RAM counts and excessive reservation counts before indexing either array. It then computes 64 + 16 × (ramCount + reservedCount) + 48 + commandBytes.

With 32 RAM ranges, 64 reservations and 255 command bytes, that expression is 1903 bytes. This is below the 4096-byte API limit. The proof depends on the earlier limits; moving arithmetic before admission would invalidate that reasoning. Unused array slots are deliberately ignored. They do not become extra ranges because their bytes happen to look plausible.

## Find the terminator within the object

The command array contains 256 characters. The writer searches only inside that array for its first zero terminator. A fully nonzero array is refused with UMICOM_BOOT_HANDOFF_TEXT. The reader then applies printable-ASCII policy to the encoded prefix.

The zero terminator belongs to the C representation and is omitted from the wire. Bytes after the first zero are unused storage. An embedded newline before the zero is different: it is part of the proposed text and must be refused. The existing bad-text lab case exercises this distinction.

## Exercise and answer

1. Predict the result for ramCount equal to 65537. It is LIMIT before array access or narrowing.
2. Predict the result for a supported pixel tag with stride 63 and width 16. Tag admission succeeds, but reader validation refuses the framebuffer because a 64-byte row does not fit.
3. Predict the result for a 256-byte command array with no zero. It is TEXT; the writer must not read a 257th byte.
4. Find where the implementation checks destination capacity. A too-small destination can be refused before later semantic checks; callers must not rely on an invalid input producing every possible diagnostic at once.

## Use types accurately in diagnostics

UmicomSize is an unsigned long long in the Kernel type contract. It is not the host's size_t typedef. The lab's printf now casts its counters to unsigned long long and uses %llu. Keeping a printf conversion matched to its argument is necessary even when two types happen to occupy the same number of bytes on one computer.

[Hosted laboratory](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/boot-handoff/README.md) · [Complete producer example](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/boot-handoff/write.c)

[Course contents](index.md) · [Previous lesson](86-encode-a-boot-handoff-through-the-kernel.md) · [Next lesson](88-publish-encoded-bytes-only-after-admission.md)

<!-- Repository laboratory sources live outside the published content root.
Public repository links replace the former local-only routes, retained here for review:
../../../../labs/native/boot-handoff/README.md
../../../../labs/native/boot-handoff/write.c
Offline source files remain available in their listed repository/learning-pack locations. -->
