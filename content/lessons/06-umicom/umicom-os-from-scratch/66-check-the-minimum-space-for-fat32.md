<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-os-from-scratch/66-check-the-minimum-space-for-fat32.md

PURPOSE:
Check the minimum space for a FAT32 volume

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Check the minimum space for a FAT32 volume

A **receipt** can record information inspected earlier. The saved version-4 disk review in Umicom OS checks whether its claims agree with known geometry. A label saying FAT32 needs enough room for a FAT32 layout. A claimed 512-byte volume has room for only one sector and cannot hold that layout.

## Before you begin

Have paper and a calculator ready. Copy the sample block size, sectors per cluster and volume size into separate columns so you can follow the arithmetic. If you want to inspect the saved test inputs, open the `tools/persistent-receipt-review` directory in an Umicom OS checkout.

## Count the required pieces

The supported receipt grammar in this exercise uses 512-byte sectors. A **cluster** groups one or more sectors into an allocation unit. The Framework filesystem inspector classifies FAT32 using at least 65,525 data clusters. The file allocation table also needs a four-byte entry for each of those clusters and two reserved entries. There must be space for at least one reserved sector and one table before the data area.

1. Add two reserved entries to the minimum data cluster count. This gives 65,527 table entries.
2. Multiply by four bytes per entry. The result is 262,108 bytes.
3. Round up after dividing by 512 bytes per sector. The table needs at least 512 sectors.
4. Add the one reserved sector and the sectors needed by all the data clusters.

| Sectors per cluster | Minimum data sectors | Minimum total sectors | Minimum bytes |
| --- | --- | --- | --- |
| 1 | 65,525 | 66,038 | 33,811,456 |
| 2 | 131,050 | 131,563 | 67,360,256 |

These are lower bounds. A particular filesystem may use a larger reserved area or two copies of its table. A receipt that meets a lower bound can still fail other checks. [Microsoft FAT32 File System Specification, pages 14–15](https://www.cs.uni.edu/~diesburg/courses/cs3430_sp15/recitations/r07/fatspec.pdf)

## Recheck a boundary with C arithmetic

Find the saved receipt fixtures under `umicomOS/tools/persistent-receipt-review`. Start with one sector per cluster and subtract one sector from the exact minimum. The remaining byte count is still a multiple of 512, but it falls below the minimum FAT32 layout.

~~~c
/* Use the receipt's fixed sector size and the minimum FAT32 cluster count. */
const uint64_t sector_bytes = 512U;
const uint64_t min_clusters = 65525U;
const uint64_t table_bytes = (min_clusters + 2U) * 4U;
const uint64_t table_sectors = (table_bytes + sector_bytes - 1U) / sector_bytes;
const uint64_t min_total_sectors = 1U + table_sectors + min_clusters;
~~~

In a copy of the exercise, change the data area to two sectors per cluster. Multiply the count of data clusters by two before adding the metadata sectors. Verify both exact bounds from the table. Use these ordinary values as data. They are calculations, so the exercise needs no allocation of a disk-sized buffer.

## Keep geometry and live checks separate

A disk inspector still needs the original evidence and its layout rules. A saved receipt check can refuse an impossible claim before referring to another review or installation step. It cannot establish the condition of a drive from arithmetic alone. Keep the partition identity, measured filesystem details and review result together when using the evidence in Umicom OS or its installer.

[Course contents](index.md) · [Previous: Read a filesystem header within its partition](65-read-a-filesystem-header-within-its-partition.md) · [Next: Keep boot option text in its argument](67-keep-boot-option-text-in-its-argument.md) · [HTML edition](../../../courses/umicom-os-from-scratch/lessons/66-check-the-minimum-space-for-fat32.html)
