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

[Primary GPT format reference](https://uefi.org/specs/UEFI/2.11/05_GUID_Partition_Table_Format.html)

[Standalone lesson](../../../courses/umicom-os-from-scratch/lessons/52-keep-partition-address-units-explicit.html)
