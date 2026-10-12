# Episode 47 — Why Writing a File Is More Than One Write

**Length:** approximately 14–19 minutes.

## Opening (0:00–2:00)

**Narrator:** A Notes file can involve several structures: data bytes, an allocation table, a directory record and a device write cache. An application that sees one successful callback still needs to understand what was actually completed.

## Demonstration (2:00–9:00)

**Screen:** Work through Chapter 140. Show the existing write-back sector store and journalled Notes laboratories.

**Narrator:** We distinguish staging, submission, completion, flushing and reopening. A cancelled request may still reach a device. An interrupted update may leave an on-disk warning without enough information to reconstruct old data.

## Read the Kernel source (9:00–15:00)

**Screen:** Open the authoritative `docs/FAT16_ORDERED_COMMITS.md` and `docs/WRITABLE_VIRTIO_BLOCK.md` in the Umicom Kernel repository.

**Narrator:** Observe how the Kernel separates a writable lease, a write's completion and a later flush. Compare that contract with the classroom model. They are related educational ideas, not identical implementations.

## Questions and next step (15:00–19:00)

**Narrator:** What does a timeout prove? What does an acknowledged flush prove only when the storage backend honours its persistence contract? Why must an open descriptor retain its owner? Continue learning through the written lessons and source references on the Bits2Banking website.
