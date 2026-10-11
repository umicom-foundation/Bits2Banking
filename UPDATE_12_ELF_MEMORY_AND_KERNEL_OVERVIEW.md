# Update 12 — ELF programme headers and memory ownership

The native educational tools now inspect **ELF programme headers** in addition to the existing binary header, static-archive, symbol-table and relocation summaries. The new `load-plan` command reports bounded PT_LOAD file and memory ranges without executing or loading the input image. The parser supports ELF32/ELF64 in both byte orders, ordinary programme-header counts, explicit file size and segment-bound checks, executable-entry containment, non-overlapping virtual-memory regions and failure-atomic report updates. The file reader holds only a bounded header prefix (up to one MiB), not the complete binary.

The educational C23 laboratories address two separate questions. The physical-frame pool tracks free, reserved and caller-owned page frames. The Sv39 software model translates a 39-bit canonical virtual address through three nine-bit indices and one twelve-bit page offset. Neither performs real kernel allocation or privileged hardware operations. They intentionally remain small so learners can read and test the entire implementations.

Five new lessons and two video scripts connect those concepts to the actual Umicom Kernel boot, physical-memory, virtual-memory and hardware-translation source. Three SVG illustrations support the lessons. The current website navigation is extended without removing any earlier entries, and all existing books and *Islam: Blueprint for Life* chapters remain referenced.

The implementation language is C23. The kernel reference remains C23 and RISC-V64 Assembly. The website keeps its existing MkDocs/Python publishing dependency; no new Python or PowerShell application scripts have been created.

**Qualification boundary:** isolated GCC and Clang sanitizer builds passed; Windows UCRT64, a full real MkDocs build and real-kernel QEMU qualification remain to be performed in their respective environments.
