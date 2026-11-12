<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/90-align-a-physical-frame-run.md

PURPOSE:
Teach align a physical frame run through the real Kernel allocator.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Align a physical frame run

![Umicom](../../../assets/branding/umicom-wordmark-on-dark.svg)

## Start with pages, not pointers

A physical frame is one fixed-size part of RAM. Umicom Kernel uses 4096-byte frames. Earlier lessons allocated one frame at a time; some future consumers need several adjacent frames whose first address also obeys a larger alignment. A contiguous run is such a consecutive group. It is an ownership allocation, not a virtual mapping or a device operation.

Prepare labs/native/physical-frame-runs using its README. It compiles the real kernel/physical_memory.c and kernel/address.c files. The addresses in this host exercise are invented numbers; the program never dereferences them. Read lessons 22–29 first if the difference between reserved, allocated and free frames is unfamiliar.

## Express the request in frames

The following call requests three consecutive pages with a four-page alignment. The count and alignment have different meanings: the run contains 12288 bytes, but its first address must be divisible by 16384. Count need not be a power of two. Alignment must be a nonzero power of two.

~~~c
UmicomAddress first = 0;
UmicomKernelMemoryStatus status =
    UmicomKernelPhysicalMemoryAllocateFrames(3U, 4U, &first);
if (status == UMICOM_KERNEL_MEMORY_OK) {
    /* Own three frames beginning at first. Do not dereference it here. */
}
~~~

Check the result before using first. A failed call preserves the previous output value. A physical address of zero can be a valid successful result when the managed RAM range includes it; testing first != 0 is not a replacement for checking status.

## Align absolute addresses

Our example initializes sixteen pages beginning at 0x1000. Their physical page numbers are 1 through 16. Four-page alignment admits page numbers 4, 8, 12 and 16. The lowest three-page run therefore starts at 0x4000, not at the beginning of RAM.

An implementation that aligns an array index relative to ramBase would call index zero aligned and return 0x1000. That is a different contract. The production implementation divides the physical address by the page size, then checks the low bits of that absolute page number. It avoids multiplying a possibly enormous alignment by 4096.

## Follow the ownership transition

The allocator scans for the lowest eligible complete run. It changes no bits during that search. Only after finding every required free page does it mark ownership and publish the first address. Single-page calls delegate to this same service with count and alignment equal to one.

1. Initialize the isolated lab inventory and confirm that it contains sixteen free pages.
2. Run the alignment scenario. Expect first=0x4000, three allocated frames and thirteen free frames.
3. Release exactly those three owned frames. Expect allocated=0 and free=16.
4. Change the requested count to five while keeping alignment four. Predict the same first address and eleven free frames before running your changed example.

## Exercise and answer

RAM begins at 0x3000 and has eight pages. What is the first two-page run aligned to four pages? Answer: 0x4000 followed by 0x5000. The initial RAM page is skipped because its absolute page number is three. If 0x5000 is reserved, the next eligible start is 0x8000, provided both it and 0x9000 are managed and free.

The source and examples are authored. Obtain compiler and execution results before claiming the expected observations occurred. This exercise does not qualify DMA, cache behaviour, an IOMMU, page-table mappings or a bootable image.

[Hosted laboratory](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/physical-frame-runs/README.md) · [Complete C example](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/physical-frame-runs/main.c)

[Course contents](index.md) · [Previous lesson](89-qualify-a-boot-producer-independently.md) · [Next lesson](91-explain-fragmentation-before-retrying.md)
