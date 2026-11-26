<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-os-from-scratch/68-count-the-slots-both-gpt-tables-need.md

PURPOSE:
Count the slots both GPT tables need

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Count the slots both GPT tables need

An Umicom OS saved disk receipt describes where a disk image could hold partitions. Sometimes the receipt leaves too little room for the disk's own table. In this lesson you will spot that mistake using numbers on paper, with no disk image or special equipment.

If you are new to disk layouts, start with the lesson that explains why even a small GPT table needs reserved space. The FAT32 lesson shows another calculation that uses a lower bound.

## Before you begin

Have paper and a calculator ready. Write down the logical block size and leave space for two tables, one at each end of the image. Use the sample values from this lesson for the exercise.

## 1. Tell a slot from a partition

GPT stands for GUID Partition Table. A partition is an area set aside for a purpose, such as holding startup files. A GPT slot is a row in the table where that partition can be described. The row numbers start at zero. Slot `128` is the 129th row. Empty rows still occupy space in the table.

The saved receipt gives the number of occupied slots and identifies two selected slots. The EFI System Partition is the role for firmware startup files. The root partition is the role for the main operating-system filesystem. If the EFI slot is `0`, the root slot is `128`, and the receipt counts three occupied slots, the table needs space for at least 129 rows. If both selected slots are near the start and the receipt counts 129 occupied slots, the table still needs at least 129 rows. Use the larger of the occupied count and the highest selected slot plus one.

## 2. Count blocks at both ends

This saved receipt format uses logical blocks of 512 bytes. GPT reserves at least 16 KiB, or 16,384 bytes, for each entry array. The saved text does not give the actual entry size. Use the minimum entry size of 128 bytes to calculate the smallest possible table. Round any partially used block up to a whole block. [UEFI Specification, GUID Partition Table Format](https://uefi.org/specs/UEFI/2.11/05_GUID_Partition_Table_Format.html)

Take an image with 800,000 blocks, numbered `0` through `799999`. Use EFI slot `0`, root slot `128` and three occupied slots.

1. The highest selected slot requires `128 + 1 = 129` slots. That exceeds the occupied count of three.
2. At 128 bytes per entry, 129 slots need `129 × 128 = 16512` bytes. This exceeds 16,384 bytes. The remainder after 32 blocks needs one more block, so each entry array needs at least 33 blocks.
3. At the start, block `0` holds the protective master boot record, which marks the disk for older tools. Block `1` holds the primary GPT header. With 33 blocks for the entry array, the earliest usable block is `2 + 33 = 35`.
4. At the end, the backup GPT header occupies block `799999`. Reserving 33 blocks before it for the backup array leaves `799965` as the latest usable block.

The two reservations leave `35` through `799965`, inclusive, as the widest possible usable interval for these claims. An actual image can reserve more space. In the Umicom OS C reviewer, the byte-to-block rounding uses integer arithmetic after bounding the inputs. With 16,512 bytes, `(16512 + 511) / 512` gives `33` when the remainder is discarded.

## 3. Decide which claims fit

Use the same 800,000-block image size on paper. In each case, assume the EFI slot is `0` and the other receipt fields are valid. Write down the minimum blocks per array, then decide whether the claimed endpoint is possible.

| Root slot | Occupied slots | Claim to check |
| --- | --- | --- |
| `127` | 3 | First usable block `34` |
| `128` | 3 | First usable block `34` |
| `128` | 3 | Last usable block `799966` |
| `1` | 129 | First usable block `35` |
| `255` | 3 | Last usable block `799934` |

1. Slot `127` requires 128 slots and a 32-block array. Block `34` can be the first usable block.
2. Slot `128` requires a 33-block array. Block `34` would be inside the minimum primary reservation.
3. The same claim requires 33 blocks for the backup array. Block `799966` would be inside that reservation.
4. With 129 occupied entries, each array still needs 33 blocks. Block `35` can be the first usable block.
5. Slot `255` requires 256 slots. Each array needs `32768 / 512 = 64` blocks. Block `799934` can be the last usable block.

## 4. Follow up on a rejected receipt

The Umicom OS saved-receipt reviewer refuses an interval that reaches into either minimum reservation. Keep the original receipt and its recorded image checksum. Check the 512-byte units, the zero-based slot numbers, the occupied count and the arithmetic at both ends. If the original image needs inspection, ask for a fresh receipt through the project's read-only inspection workflow for an ordinary image file. Keep the old receipt alongside the new one so the claims can be compared.

In Umicom Framework, the separate GPT image reader examines the actual table locations, entry size and both copies. A satisfactory saved-text calculation establishes only that the reported interval fits the minimum reservation. Actual table contents, filesystem condition and the result of starting the operating system each need their own evidence.

## Where to find the implementation

In the Umicom OS checkout, the C implementation is in `tools/persistent-receipt-review/receipt.c`. The companion `tools/persistent-receipt-review/test_receipt.c` covers saved text with too little space at the primary end, too little space at the backup end and nearby values that fit.

[Course contents](index.md) · [Previous lesson · Keep boot option text in its argument](67-keep-boot-option-text-in-its-argument.md) · [Reserve table space before partitions](53-reserve-table-space-before-partitions.md) · [Check the minimum space for a FAT32 volume](66-check-the-minimum-space-for-fat32.md) · [HTML edition](../../../courses/umicom-os-from-scratch/lessons/68-count-the-slots-both-gpt-tables-need.html)

[Next lesson · Follow the first blocked boot service](69-follow-the-first-blocked-boot-service.md)
