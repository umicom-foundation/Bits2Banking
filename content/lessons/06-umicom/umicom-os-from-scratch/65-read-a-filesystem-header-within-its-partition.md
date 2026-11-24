<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-os-from-scratch/65-read-a-filesystem-header-within-its-partition.md

PURPOSE:
Teach what a bounded filesystem header can establish about a selected partition.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg)

# Read a filesystem header within its partition

[Course contents](index.md) · [Previous lesson](64-recognise-truncation-before-format-fallback.md) · [HTML edition](../../../courses/umicom-os-from-scratch/lessons/65-read-a-filesystem-header-within-its-partition.html)

A partition table describes where a part of a disk begins and ends. An ext-family superblock records details such as how many filesystem blocks the volume contains. In this exercise you give Framework a simulated partition and one real byte window in memory. You will predict when the C program may request the header. [Linux kernel superblock format](https://docs.kernel.org/filesystems/ext4/super.html)

## Draw the byte window

1. The partition starts at logical block 2048. Each logical block has 512 bytes, so the partition starts at byte 1,048,576.
2. The superblock begins 1024 bytes into the partition. Add 1024 to get the absolute read position, 1,049,600.
3. The superblock occupies 1024 bytes. The partition needs at least 2048 bytes from its beginning to cover its first complete superblock.

The short scenario ends at logical block 2050. In this table the final block is included, so the partition contains three blocks, or 1536 bytes. The header needs four 512-byte logical blocks. Framework refuses that read before the callback runs. The underlying C array still contains the full header.

## Follow the C program

The callback is the function that supplies bytes to Framework. It accepts a request only at byte 1,049,600 and only for a 1024-byte copy. This makes the observable test independent of other memory on the machine.

~~~c
UmiStatus status = UmiGptPartitionProbeFilesystem(ReadHeader, &fixture,
    UINT64_C(307200000), &image, &partition,
    UMI_GPT_FILESYSTEM_EXT_SUPERBLOCK, &observed);
~~~

The fixture reports a 4096-byte **filesystem block** even though its disk **logical block** is 512 bytes. The number 4096 also appears as the filesystem block count. Multiply 4096 filesystem blocks by 4096 bytes per filesystem block to get the reported volume length of 16,777,216 bytes.

## Run, predict and explain

1. Use the [lab guide](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-filesystem-header/README.md) to build the C23 client.
2. Run `present`, `partition-too-short` and `unknown-signature`. Compare their expected read counts: 1, 0 and 1.
3. Explain why the unchanged result after a refusal still belongs to the previous inspection. If a test disagrees, check the supplied last block, requested offset and byte count before editing the expected outcome.

For a final experiment, use a last block of 2051 and keep the original superblock. Predict how many reads occur, then run `volume-too-large`. Four logical blocks cover the complete header, so one read can occur. Its claimed 16,777,216-byte volume exceeds the 2048-byte partition, so Framework still refuses the observation. Header bounds, volume bounds and a boot test answer three separate questions.

[Next: Check the minimum space for a FAT32 volume](66-check-the-minimum-space-for-fat32.md)
