<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-os-from-scratch/46-decode-optical-records-and-byte-order.md

PURPOSE:
Decode optical records and byte order

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->



# Decode optical records and byte order

## Prepare the byte-layout exercise

Use the bios scenario from the installed ISO lab. The memory allocation contains 24 optical blocks, each 2048 bytes long. The primary volume descriptor begins at block 16, so its byte offset is 16 multiplied by 2048. That arithmetic locates a record; it does not create a filesystem.

An LBA is a logical block address. Its byte meaning depends on the structure that contains it. This ISO profile uses 2048-byte blocks for descriptor and catalogue locations, while the El Torito load count uses 512-byte units. Name units in comments and variables so a plausible integer does not conceal a fourfold error.

## Read integers without casting byte buffers

Do not cast a pointer into an input buffer to uint32_t and dereference it. The address may be unaligned, the host may use another byte order, and a typed access may violate the object rules. Combine unsigned bytes with shifts instead. The Framework reader uses explicit little-endian and big-endian helpers.

~~~c
uint32_t little = (uint32_t)p[0] | ((uint32_t)p[1] << 8U) |
                  ((uint32_t)p[2] << 16U) | ((uint32_t)p[3] << 24U);
uint32_t big = (uint32_t)p[3] | ((uint32_t)p[2] << 8U) |
               ((uint32_t)p[1] << 16U) | ((uint32_t)p[0] << 24U);
~~~

## Two encodings must describe the same value

ISO9660 represents selected numeric fields in both byte orders. The primary descriptor stores the volume-space size at offsets 80 and 84. For 24 blocks, the little-endian bytes are 18 00 00 00 in hexadecimal; the big-endian bytes are 00 00 00 18. These are two representations of one value, not two independent size claims.

The endian scenario changes the second representation to 23 while leaving the first at 24. The expected outcome is a parse error and no published flags. Keeping only the value that happens to match your host would accept contradictory input.

~~~text
volume blocks: 24
volume bytes: 24 * 2048 = 49152
boot start:   20 * 2048 = 40960
BIOS load:     4 * 512  = 2048
end of load:  40960 + 2048 = 43008
~~~

## Bound the work as well as each read

A parser can stay inside the file and still spend excessive time scanning it. This service reads at most 64 volume descriptors and one 2048-byte catalogue. A terminator beyond the accepted descriptor window is not silently treated as valid. The profile also rejects duplicate primary descriptors and duplicate El Torito boot records.

One catalogue block is a deliberate support limit. An unsupported extension can return unavailable even when another ISO tool understands it. That status should lead to a profile review, not an automatic instruction to delete records or relax every bound.

## Exercise and reference

Write the hexadecimal bytes for a 32-block volume in both orders. Next, move the synthetic boot start to block 24 without enlarging the 24-block source. Predict why the range check fails before any load can be accepted. Keep the positive BIOS fixture and add a separate negative case.

Read the numeric-field and volume-descriptor definitions in ECMA-119. The service checks a bounded structural subset; it does not validate every directory record, path table or file extent. If a test fails, compare the expected unit, field offset and complete encoded bytes before changing an acceptance rule.

[ECMA-119 standard and editions](https://ecma-international.org/publications-and-standards/standards/ecma-119/)

[Installed SDK lab and commands](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-iso-inspection/README.md) · [Course contents](../../../courses/umicom-os-from-scratch/index.html)

[Written contents](index.md) · [Previous lesson](45-share-a-read-only-image-inspector.md) · [Next lesson](47-interpret-uefi-boot-catalogue-counts.md)

<!-- Repository laboratory sources live outside the published content root.
Public repository links replace the former local-only routes, retained here for review:
../../../../labs/native/framework-iso-inspection/README.md
Offline source files remain available in their listed repository/learning-pack locations. -->
