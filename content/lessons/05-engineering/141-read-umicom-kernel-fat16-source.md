# Read the Umicom Kernel filesystem implementation

Umicom Kernel develops the real native storage stack in a separate repository. Bits2Banking teaches the ideas without changing the Kernel.

## 1. Begin at the interface

Read [Umicom Kernel's VFS implementation](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/vfs.c). A descriptor grants operations on an already-open object; authority to change a directory name is separate. Read [RAMFS](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/ramfs.c) to understand in-memory file ownership and why an unlinked open file may remain alive.

## 2. Follow FAT16 and block I/O

Read [FAT16 lifecycle](https://github.com/umicom-foundation/umicom-kernel/blob/main/docs/FAT16_FILE_LIFECYCLE.md), [ordered FAT16 commits](https://github.com/umicom-foundation/umicom-kernel/blob/main/docs/FAT16_ORDERED_COMMITS.md) and [writable VirtIO block leases](https://github.com/umicom-foundation/umicom-kernel/blob/main/docs/WRITABLE_VIRTIO_BLOCK.md).

Trace one conceptual file write: VFS client → filesystem provider → block request → write completion → flush → validated filesystem finalisation. Write down which component owns each handle, buffer and revision.

## 3. Keep release claims precise

The native Kernel research code and the Linux-libre-based Umicom OS distribution are different tracks. Neither this FAT16 classroom inspector nor a successful QEMU test establishes that a physical computer can safely mount a writable production filesystem.

## 4. Continue

Compare the [Umicom Kernel storage sources](https://github.com/umicom-foundation/umicom-kernel) with the educational `fat16.c` parser. Identify which validations are absent from the classroom exercise and explain why their omission is acceptable only within its stated limits.
