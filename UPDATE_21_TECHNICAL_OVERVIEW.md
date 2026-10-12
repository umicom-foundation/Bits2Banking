# Bits2Banking — Update 21: Filesystems, storage and recoverable Notes

## What this update changes

This is a **Bits2Banking-only** educational update. Its five new learner chapters (132–136) explain sectors, cached writes, durability boundaries, filesystem paths, write-ahead logging and the Umicom Kernel storage stack. It introduces two independent C23/CMake laboratories and two complete educational-video scripts. The site navigation, lesson indexes and development roadmap are extended without removing previous content, including the original *Islam: Blueprint for Life* volume.

The learning sequence is: understand the layers → stage and flush a sector → interrupt an accepted Notes save → replay a journal → examine actual Umicom Kernel VFS, FAT16 and VirtIO source.

## Working source

`labs/native/writeback-sector-store/` provides four fixed 512-byte sectors with distinct staged and simulated stable representations. Its C23 tests verify invalid sector refusal, partial flushing, restart behavior, exact 2048-byte image export/import and failure-atomic import.

`labs/native/journalled-notes/` composes that same source file as a CMake library. A one-note, one-writer redo record in sector zero is flushed before the applied snapshot in sector one. The journal retains bounded UTF-8-like bytes as an opaque text string with a NUL terminator; the laboratory does not validate full Unicode. Record layout and CRC32 are encoded bytewise, not by writing compiler-dependent C structures. Three deliberate interruption points let a learner inspect the stable result and practise explicit replay. The decoder refuses corrupted records, stale revisions and conflicting state.

**Durability boundary:** Both laboratory arrays are ordinary process RAM. The designation *stable* is a simulation invariant, not evidence of actual flash or disk power-loss behaviour. `fflush()` in the example transfers C-library output buffers, but is not a portable hardware persistence guarantee. Physical-sector tear protection, concurrency, authenticated ownership, atomic cross-file transactions and real device-driver safety are not implemented.

## Authoritative source references

- [Umicom Kernel — VFS](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/vfs.c)
- [Umicom Kernel — RAM filesystem](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/ramfs.c)
- [Umicom Kernel — Read-only filesystem provider](https://github.com/umicom-foundation/umicom-kernel/blob/main/docs/READ_ONLY_FILESYSTEM_PROVIDER.md)
- [Umicom Kernel — Writable VirtIO block contract](https://github.com/umicom-foundation/umicom-kernel/blob/main/docs/WRITABLE_VIRTIO_BLOCK.md)
- [Umicom Kernel — FAT16 ordered commits](https://github.com/umicom-foundation/umicom-kernel/blob/main/docs/FAT16_ORDERED_COMMITS.md)
- [Umicom Kernel — Persistent FAT16 file lifecycle](https://github.com/umicom-foundation/umicom-kernel/blob/main/docs/FAT16_FILE_LIFECYCLE.md)

The research kernel's ordered FAT16 dirty-marker protocol and this classroom Notes redo-journal protocol are **different** designs. Neither is a basis for advertising production financial durability or broad power-loss tolerance.

## Integration and publication

Review the full-file `mkdocs.yml` replacement against the current local repository using Beyond Compare. It is based on the delivered Update 20 configuration and appends seven navigation links. Keep newer local entries and chapter changes if they exist. The earlier source lines in the full-file replacements have been preserved.

Build/test instructions are in [UPDATE_21_BUILD_TEST_AND_GIT.md](UPDATE_21_BUILD_TEST_AND_GIT.md). No Framework submodule or parent repository commit is required; only `C:\umicom\Umicom-Bits2Banking` is in scope.
