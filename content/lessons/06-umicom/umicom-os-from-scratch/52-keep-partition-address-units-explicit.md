<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-os-from-scratch/52-keep-partition-address-units-explicit.md

PURPOSE:
Teach keep partition address units explicit through the installed Framework GPT service.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-logo.svg)

# Keep partition address units explicit

[Course contents](index.md) · [Previous lesson](51-connect-an-owned-image-read-port.md) · [Next lesson](53-reserve-table-space-before-partitions.md)

[Complete source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-gpt-inspection/image.c) · [Build and run the lab](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-gpt-inspection/README.md) · [Qualification guide](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-gpt-inspection/QUALIFICATION.md)

A partition record contains addresses, while a read callback consumes byte offsets. Confusing those units can point a correct-looking reader at the wrong part of an image. This lesson keeps logical blocks, entry widths and byte lengths visible in names and calculations.

## Before you begin

Keep the GPT inspection lab from the preceding chapter. Read the valid-512 and valid-4096 scenarios and write down the logical-block size used by each before calculating byte offsets. Use the same installed SDK for both runs so the unit comparison is meaningful.

## Identify each quantity

| Quantity | Meaning in this lab |
| --- | --- |
| image.length | Number of allocated source bytes. |
| image.block | Bytes per logical block: 512 or 4096. |
| sectors | image.length divided by image.block. |
| first | First usable logical block address. |
| width | Byte width of one partition entry. |

The synthetic allocation has 524,288 bytes. At 512 bytes per block it contains 1,024 blocks; at 4096 it contains 128 blocks. Neither representation changes the allocation size. The header locations and usable addresses do change because they describe positions in the chosen logical-block coordinate system.

## Follow construction

~~~c
uint64_t sectors = candidate.length / block;
uint64_t reserve = 16384U / block;
uint64_t first = 2U + reserve;
uint64_t last = sectors - 2U - reserve;
~~~

The lab accepts only two block sizes, each of which divides the reservation exactly. Its first usable address is 34 for the 512-byte fixture and 6 for the 4096-byte fixture. Those become byte offsets 17,408 and 24,576 respectively. The larger logical-block fixture needs fewer address units but not fewer allocated source bytes.

## Keep encoding separate from host layout

Put32 and Put64 write individual little-endian bytes. They do not cast the image buffer to a C structure. A structure cast would depend on alignment, padding and the host representation. Explicit encoding also makes it possible to alter one field in a teaching fixture without accidentally modifying a neighboring field.

~~~c
static void Put64(unsigned char *p, uint64_t value)
{
    for (unsigned i = 0U; i < 8U; ++i)
        p[i] = (unsigned char)(value >> (8U * i));
}
~~~

## Run two coordinate systems

Run valid-512 and valid-4096 separately. Each should report one partition. The expected usable intervals are 34..990 and 6..122. The program compares the first usable address with the fixture calculation and checks the reported logical-block size. Keep both command results; passing one case does not qualify the other geometry.

## Exercise

Calculate the byte address of the backup header for each fixture before running it. Then explain why multiplying a partition count by the block size would not locate that header.

## Worked explanation

The backup header occupies the final logical block. Its byte address is source length minus one logical block: 523,776 for 512-byte blocks and 520,192 for 4096-byte blocks. A partition count describes how many regions are active, not where the final block begins. Using it as an address confuses a count with a coordinate.

## Transfer the lesson to an application

Carry observed logical-block geometry alongside the source identity. Do not substitute a filesystem cluster size, a physical-sector size or an assumed universal value. The read-only Framework service supports both teaching geometries, while the existing Boot Media transfer workflow retains its separate 512-byte image policy. Inspection support alone does not authorize or qualify a new device-writing format.

## Check a plan using whole blocks

A disk plan can require one partition of a given type and a minimum number of bytes. For this example, the plan asks for an EFI System partition and an x86-64 Linux root partition. A type GUID is the identifier for a declared use. A unique partition GUID identifies one particular partition. Framework checks the exact stored type and reports the matching partition. [Discoverable Partitions Specification](https://uapi-group.org/specifications/specs/discoverable_partitions_specification/)

Suppose a paper observation records 512 bytes per logical block and these three occupied ranges. Both endpoints are included. The minimum sizes are small on purpose so the arithmetic is easy to follow.

| GPT slot | Declared type | First block | Last block | Required minimum bytes |
| --- | --- | ---: | ---: | ---: |
| 2 | EFI System | 60 | 61 | 513 |
| 9 | x86-64 Linux root | 80 | 85 | 3073 |
| 12 | Other data | 100 | 103 | None in this plan |

Count the blocks in each partition as last minus first plus one. Divide the minimum byte count by the block size, then add one block if there is a remainder. Dividing first also avoids adding extra bytes to a very large integer before the division. Framework's `UmiGptImageMatchRequirements` applies this rule after it checks the supplied geometry.

~~~c
/* Round a reviewed byte minimum up to whole logical blocks. */
uint64_t requiredBlocks = minimumBytes / blockBytes;
if (minimumBytes % blockBytes != 0U) {
    ++requiredBlocks;
}
~~~

1. Work out the observed and required block counts for EFI and root. Decide if the complete plan passes.
2. On paper, extend the root range to end at block 86. Keep the other ranges and minimum sizes. Decide if the complete plan now passes.
3. From the passing paper layout, consider two separate variations. In one, remove the root row. In the other, keep the root row and give slot 12 the same root type. Predict each outcome.

## Check your answers

EFI has two blocks and needs two. Root has six blocks and needs seven because 3073 is one byte more than six 512-byte blocks. The original plan is refused as undersized, and the output receives no partial match. Ending the root at 86 gives it seven blocks, so the revised paper plan passes. Removing the root gives a missing-type refusal. Giving slot 12 the same root type gives an ambiguous-type refusal even though slot 9 is still large enough. Matching two alternatives leaves the planned root unresolved.

The Umicom OS owner's disk reviewer has a separate `--check-plan` option with `--esp-min-bytes` and `--root-min-bytes`. After building it with the matching Framework SDK, the owner supplies the reviewed raw image and its independently recorded SHA-256 as well as both byte counts from the real plan. A completed version-3 receipt records both matched slots, their unique GUIDs and the observed whole blocks. Find the owner commands in `docs/foundation/persistent-disk-layout-review.md` in the Umicom OS checkout. This paper exercise uses no image. Filesystem content, the bootloader and boot with persistent data each need separate evidence.

[Primary GPT format reference](https://uefi.org/specs/UEFI/2.11/05_GUID_Partition_Table_Format.html)

[Standalone lesson](../../../courses/umicom-os-from-scratch/lessons/52-keep-partition-address-units-explicit.html)
