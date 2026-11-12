<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-os-from-scratch/53-reserve-table-space-before-partitions.md

PURPOSE:
Teach reserve table space before partitions through the installed Framework GPT service.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-logo.svg)

# Reserve table space before partitions

[Course contents](index.md) · [Previous lesson](52-keep-partition-address-units-explicit.md) · [Next lesson](54-preserve-an-observation-on-refusal.md)

[Complete source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-gpt-inspection/image.c) · [Build and run the lab](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-gpt-inspection/README.md) · [Qualification guide](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-gpt-inspection/QUALIFICATION.md)

A small data structure can still require a larger reserved region around it. The synthetic image in this lab declares four partition slots. At 128 bytes per slot, their encoded contents occupy only 512 bytes. The layout deliberately reserves more room, so later partitions do not begin inside space assigned to table metadata.

## Distinguish occupied bytes from reserved space

Seal calculates a CRC over the declared array contents and copies those bytes into the backup array. LabImageCreate separately calculates the reservation used to choose usable addresses. These calculations answer different questions: which bytes participate in this checksum, and where may partition data begin?

~~~c
size_t length = (size_t)4U * width;
uint32_t crc = Crc(entries, length);
memcpy(image->bytes + backup_table * image->block,
    entries, length);
~~~

This teaching fragment names the backup-table address explicitly; the complete source calculates it from the source extent and reservation. Copying only the declared bytes is correct for the fixture. Treating the unused reserved area as partition space is a different decision and is refused by the inspection profile.

## Create a meaningful negative fixture

The reservation scenario changes the first usable address to 3 in both headers, then recomputes their checksums. The first partition itself still begins later. This isolates the reservation rule: a parser checking only partition overlap and checksum consistency would miss the problem.

~~~c
Put64(primary + 40U, 3U);
Put64(backup + 40U, 3U);
Seal(image, 128U);
~~~

The stride scenario keeps a four-slot table but changes the entry width to 384 bytes. The generator recomputes the array and header checksums. Framework must reject the unsupported width even though all the encoded CRC values agree. Updating a checksum should never be a way to bypass a semantic format check.

## Run and interpret

Run gpt-inspection.exe reservation and gpt-inspection.exe stride after the ordinary build. Both scenarios first inspect a valid fixture successfully, then require a parse error for the controlled mutation. Each also checks that the previously accepted output remains unchanged. A zero exit code means those assertions were observed, not that the mutated image was accepted.

## Exercise

Explain why changing only the primary header without recomputing its checksum would make a weaker regression case for the reservation rule. Propose what you should compare in the test output to confirm the intended path.

## Worked explanation

A stale header CRC gives the parser an earlier reason to stop. The test might pass because checksum validation works while the reservation defect remains. Keeping both copies and checksums consistent removes those incidental failures. The remaining expected refusal must arise from the declared geometry. The Framework suite additionally checks individual metadata rules with separate fixtures.

## Extend carefully

Do not broaden an image profile just because one producer creates different metadata. First distinguish a valid but unsupported format from malformed bytes. Compare the format reference, current service contract and actual producer output. Keep the original artifact unchanged and record its identity. The lab constructs only teaching metadata; it supplies neither a filesystem nor executable boot code.

[Primary GPT format reference](https://uefi.org/specs/UEFI/2.11/05_GUID_Partition_Table_Format.html)

[Standalone lesson](../../../courses/umicom-os-from-scratch/lessons/53-reserve-table-space-before-partitions.html)
