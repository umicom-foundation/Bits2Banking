# Update 22 — FAT16 layout, inspection and storage safety

The update adds a standalone, read-only C23 FAT16 image inspector, five lessons and two video scripts. The inspector accepts a bounded regular file rather than a physical disk and demonstrates geometry checks, root-directory entry inspection, cluster-chain validation and malformed-input refusal.

Its scope is deliberately narrow: standard 512/1024/2048/4096-byte sectors, standard FAT16 classification based on cluster count, root 8.3 names, and a single chain walk. It does not mount, write, repair, authenticate or qualify full filesystems. It does not support FAT12/FAT32 or VFAT long names.

The accompanying source references explain the differences between the classroom model and Umicom Kernel's actual VFS, FAT16 and VirtIO components. No other repository is modified.
