# Write ordering, flush and recovery

Reading a filesystem safely is different from updating it safely. A filesystem mutation may involve a data sector, a FAT entry, a directory entry and a durable completion boundary.

## 1. Separate the events

1. **Stage**: prepare all intended changes and check capacity.
2. **Publish**: make a write request visible to the storage device.
3. **Complete**: the driver observes a validated completion for that request.
4. **Flush**: request a storage persistence boundary when supported by the negotiated protocol.
5. **Reopen**: inspect the filesystem again after the earlier owner is gone.

A timeout or cancellation does not prove that a device did nothing. Conversely, a successful write completion does not always prove persistence after power failure.

## 2. Recovery is not automatic

The FAT16 dirty indicator can announce an unfinished change, but it cannot reconstruct missing old bytes or invent the intended result. A journal or other recovery protocol must define the exact bytes retained and the ordering guarantees it relies on.

## 3. Explore the earlier exercises

Return to [Write-back Sector Storage](133-build-a-writeback-sector-store.md) and [Journalled Notes](134-write-ahead-journalling-and-recovery.md). Explain which state is volatile, which is stable in the classroom simulation, and what a true device flush would have to establish. Compare the answers with the Umicom Kernel material linked in Chapter 141.
