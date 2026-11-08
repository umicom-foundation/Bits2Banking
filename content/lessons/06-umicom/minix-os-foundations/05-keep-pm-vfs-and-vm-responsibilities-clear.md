# Keep process, filesystem and memory responsibilities clear

## Separate the questions

A process needs an identity and lifecycle, access to named files, and memory mappings. These concerns interact, but they are not the same owner. The MINIX architecture uses distinct services to coordinate them.

The [VM internals guide](https://wiki.minix3.org/doku.php?id=developersguide:vminternals) explains the separation of process management and memory management. VM maintains memory-region information and page-table state; operations can involve PM, VFS and the kernel. Read the release source before assuming the current wiki's implementation details match 3.3.0 exactly.

## Draw two address spaces

Draw virtual addresses 0x1000–0x1fff for process A and the same numeric range for process B. The numbers can map to different physical frames. This is why equality of pointer values across processes does not imply shared storage.

Now draw two adjacent virtual pages in A backed by nonadjacent physical frames. A contiguous virtual range is not necessarily a contiguous physical range. Device DMA may impose additional constraints that ordinary CPU copying does not.

## Worked source-reading task

1. Locate the receive loop in the VM server.
2. Select one memory operation.
3. Trace its call-specific handling into region or page-table management.
4. Identify where another service supplies information.
5. Mark which errors leave ownership unchanged and which require cleanup.

Record file names and your release identity. Do not treat a conceptual diagram as proof that you have traced every asynchronous path.

## Exercise and answer

A driver asks for a buffer suitable for hardware DMA by calling an ordinary allocation function. Is that enough? Answer: not without the device's addressing, contiguity and lifetime requirements being satisfied. An available virtual pointer alone does not establish those properties.

## Connection to Umicom

Return to Umicom Kernel's earlier lessons on user-memory spans and backing owners. Compare the invariant—every accessed byte belongs to valid storage—while keeping the two systems' implementation and public APIs separate. Neither system is qualified by the other's tests.

[Course contents](index.md)
