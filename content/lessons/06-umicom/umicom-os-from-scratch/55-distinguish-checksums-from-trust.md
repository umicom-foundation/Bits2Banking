<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-os-from-scratch/55-distinguish-checksums-from-trust.md

PURPOSE:
Teach distinguish checksums from trust through the installed Framework GPT service.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-logo.svg)

# Distinguish checksums from trust

[Course contents](index.md) · [Previous lesson](54-preserve-an-observation-on-refusal.md) · [Next lesson](56-qualify-an-installed-image-client.md)

[Complete source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-gpt-inspection/image.c) · [Build and run the lab](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-gpt-inspection/README.md) · [Qualification guide](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-gpt-inspection/QUALIFICATION.md)

The lab can produce a malformed table and then compute perfectly matching checksums for it. That is intentional. A checksum answers a narrow consistency question; it does not decide whether the bytes describe a useful operating system or came from a trusted publisher.

## Before you begin

Read the GPT lab checksum helper and keep a known-valid synthetic image for comparison. Identify which bytes belong to the header checksum and which belong to the table checksum. No signing key or trusted distribution channel is part of this exercise; prepare a table separating corruption detection from provenance.

## Follow the encoder

Crc processes each byte of a synthetic record and returns a 32-bit result. Seal stores that value for the declared array, copies the array to its backup position, and recomputes each header’s CRC. These are producer operations. Framework independently interprets the resulting bytes and decides whether they fit its structural profile.

~~~c
uint32_t crc = Crc(entries, length);
memcpy(backup_entries, entries, length);
Put32(header + 88U, crc);
Put32(header + 16U, 0U);
Put32(header + 16U, Crc(header, 92U));
~~~

This abbreviated fragment names the existing array and header pointers for clarity. The complete Seal function repeats header work for both copies. The CRC field is zero while the header checksum is calculated, so the calculation does not depend on its previous stored value.

## Compare kinds of evidence

| Observation | What it can support |
| --- | --- |
| CRC agrees | The observed bytes agree with the recorded consistency value. |
| Both arrays agree | The two observed array copies contain the same declared bytes. |
| Parser returns OK | The source satisfies this bounded structural profile. |
| Whole-file copy agrees | The observed destination bytes match the source. |
| Firmware boots a guest | A particular boot attempt worked in its recorded environment. |

None of the first four observations establishes publisher identity. The final observation also needs its own machine or emulator configuration, source digest and captured result. A familiar filename, a green status label or a lesson screenshot cannot substitute for those records.

## Understand the overlap case

The overlap scenario creates a second active entry with a distinct identifier. Its first block is the final block of the first partition. Because partition intervals include both endpoints, the entries share one block. Seal gives the changed arrays matching checksums, but Framework must still reject their overlap.

## Exercise

Change the second partition’s first address from first plus 10 to first plus 11 in a scratch fixture. Predict which observation changes and which remain the same. Do not alter the expected result in the supplied refusal scenario merely to force its test to pass.

## Worked explanation

The intervals become adjacent instead of overlapping. Their encoded bytes and checksum values change, while the general fact that the two copies agree can remain true after resealing. A separate positive scenario should now expect two partitions. The Framework suite contains such an adjacency case, keeping it separate from the negative overlap assertion.

## Apply this to distribution

An image distribution workflow needs provenance, artifact identity and appropriate verification in addition to structural parsing. Preserve the original image while investigating a mismatch. Do not “repair” a published checksum to match unexplained changes. Likewise, duplicating an image’s bytes is not a general disk-identity provisioning service; the current inspector neither regenerates identifiers nor installs boot loaders.

## Expected result and limits

Run overlap and backup. Both deliberately recompute checksums but require a structural refusal and unchanged output. These are teaching observations to execute after building. The lab has no network trust service, signing key, credential store or firmware connection. Its purpose is to make the boundary between consistency and trust visible in real C code.

[Primary GPT format reference](https://uefi.org/specs/UEFI/2.11/05_GUID_Partition_Table_Format.html)

[Standalone lesson](../../../courses/umicom-os-from-scratch/lessons/55-distinguish-checksums-from-trust.html)
