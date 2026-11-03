# Keep firmware-owned pages out of the allocator

A physical allocator manages pages, while firmware reservations describe byte ranges. Translating between those units must protect every touched byte. A one-byte reservation in the middle of a page makes that entire page unavailable to ordinary allocations.

## Trace the normal bootstrap

1. Read `kernel/boot_memory.c`. Notice that metadata validation and plan construction precede allocator initialization.
2. Read `kernel/boot_reservations.c`. It clips firmware entries to the declared RAM, rounds outward to page boundaries and merges overlapping or adjacent page ranges.
3. Find the existing allocator's `UmicomKernelPhysicalMemoryReserveRange`. It refuses overlap, so the caller must not submit the same page twice.
4. Read the `memory-firmware-reserved` startup regression. It uses the real allocator with synthetic aligned RAM and checks that the firmware page never appears among allocated frames.

## Read the lab plan

The preceding lesson builds `btb-kernel-boot-metadata`. Run it with `plan`. The synthetic layout reserves low memory through the Kernel, a separate device-tree page and a page containing a one-byte firmware reservation. Expected plan count: three ranges.

```text
& ".\build\kernel-boot-metadata\btb-kernel-boot-metadata.exe" plan
```

The executable only constructs a plan. It does not allocate physical memory, run a guest or modify your machine's memory map. A host result establishes arithmetic and ownership behavior for the supplied fixture.

## Exercise

Change the firmware address to a byte already inside the Kernel reservation. Predict why the merged plan should have two ranges, then update the local expected result. Add a second byte-disjoint reservation in the same page and explain why it must not be reserved twice.

## Know what remains outside this feature

The current normal bootstrap applies the firmware reservation table. Parsing every `/reserved-memory` binding, discovering a new RAM layout and qualifying other machines are separate tasks. Independent recovery must still remain available when normal boot rejects metadata.

## Need an earlier explanation?

[Review the foundation concepts](../../00-getting-started/04-memory-storage-and-information.md), then use the [connected learning map](../../../courses/learning-paths.html#kernel) for the longer written chapters. For C syntax or compiler commands, use the map's first-programming route before running this lab.

---

[Read this lesson in HTML](../../../courses/umicom-kernel-from-scratch/lessons/06-reserved-pages.html) · [Learning sequence](../../../start/learning-sequence.md)
