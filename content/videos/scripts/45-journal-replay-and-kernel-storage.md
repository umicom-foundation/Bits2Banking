# Episode 45 — Recover an interrupted Notes save

**Duration:** approximately 14–18 minutes  
**Companion lessons:** [134](../../lessons/05-engineering/134-write-ahead-journalling-and-recovery.md), [135](../../lessons/05-engineering/135-filesystem-paths-and-metadata.md), [136](../../lessons/06-umicom/136-follow-kernel-filesystems-and-storage.md)  
**Demonstration:** `labs/native/journalled-notes`  
**Reference:** [Umicom Kernel FAT16 ordered commits](https://github.com/umicom-foundation/umicom-kernel/blob/main/docs/FAT16_ORDERED_COMMITS.md)

## Opening: the save that stopped halfway (0:00–1:45)

**On screen:** Notes window displays “Quarterly cash plan”. A Save bar moves halfway, then stops. The file icon remains, with a question mark above it.

**Narration:**

“Imagine that your computer stops while saving a note. When it starts again, should the program show the old text, the new text, or an error? The answer cannot depend on wishful thinking. It must depend on information that was actually stored and can be checked. In this episode we will give our C23 Notes laboratory a simple recovery record. We will stop the save at three different points and observe exactly what survives.”

“We will build a write-ahead journal. The idea is to record what we intend to apply before we change the primary saved copy. That way, a later recovery process has enough information to finish an accepted change. We will use a tiny fixed-size storage model, so that we can see the ordering clearly without touching a real disk controller.”

## Part 1: two sectors, two responsibilities (1:45–4:00)

**On screen:** [Journal and snapshot illustration](../../assets/diagrams/write-ahead-journal-recovery.svg). Emphasise sector zero and sector one.

**Narration:**

“Sector zero is our journal. It holds the latest accepted note revision. Sector one is our snapshot: the version normally used as the current saved note. Both contain a revision number and the note's text. They also contain a CRC32 value so we can detect some accidental changes. CRC32 is not a signature. It does not tell us who wrote the record, only whether its bytes match a simple integrity calculation.”

“Suppose the snapshot says revision one, while the journal says revision two. If the journal was written through the simulated flush boundary, recovery can apply revision two to the snapshot. But suppose the journal is damaged. We do not pretend the record is empty. We refuse to proceed because discarding a possibly accepted change would destroy evidence.”

**Demonstration:** In `journal.h`, show the 81-byte text capacity and the named statuses. In `journal.c`, show explicit byte encoding rather than `fwrite(&myStruct, sizeof myStruct, ...)`.

## Part 2: write ahead before applying (4:00–7:10)

**Narration:**

“Let's follow a Save request. First we check the caller's expected revision. If the note has changed since the caller last read it, we refuse the stale update. That avoids quietly overwriting someone else's newer work. Next we prepare a complete record with the new text. We stage it in the journal sector and flush that sector. Only then do we stage and flush the snapshot.”

“This order is the key. We do not update the snapshot first and hope the journal catches up later. The journal provides the recovery information, so it must reach the simulated stable boundary before the main update begins.”

**On screen:** Show three labelled stages: `stage journal → flush journal → stage snapshot → flush snapshot`. Pause over the first flush.

**Demonstration:** Locate `BtbJournalCommit()` and point to each operation. Highlight the call that refuses new commits while replay is needed.

## Part 3: test all three interruptions (7:10–10:50)

**Narration:**

“Now we make the program stop at three precise points. First, we stop before the journal flush. The journal only exists in volatile staged memory. A simulated crash discards it; the old note survives. Second, we stop just after the journal flush. The new revision is now in our stable journal, but the snapshot is still old. Recovery can replay the accepted change. Third, we stage the new snapshot but stop before flushing it. The stable journal still provides the newest accepted record. Once again, recovery can replay it.”

“Notice how much stronger this explanation is than simply saying 'the program recovers'. We know which bytes reached which boundary, and we can point to the exact reason for the recovered revision.”

**Demonstration:** Configure, build, test and run:

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\journalled-notes" -B ".\output\learning-build\journalled-notes" -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" -DBUILD_TESTING=ON
cmake --build ".\output\learning-build\journalled-notes" --parallel 2
ctest --test-dir ".\output\learning-build\journalled-notes" --output-on-failure
& ".\output\learning-build\journalled-notes\btb-journalled-notes-demo.exe"
```

**On screen:** Show the recovered revision and text. Open `test_journal.c` and identify the three named stop points. Ask viewers to predict which revision appears before reading each assertion.

## Part 4: recognise corruption and unsafe retries (10:50–13:20)

**Narration:**

“A recovery algorithm must not silently change the meaning of a failed operation. What if the journal checksum is wrong? Our decoder refuses the record. It does not manufacture a new note from a half-validated buffer. What if the expected revision is stale? The commit refuses that request before changing the sectors. And what if a previous update is still awaiting replay? A new commit must not erase the only journal record that could complete it.”

“Here is a useful rule for financial software as well: when the result of an operation is uncertain, inspect the accepted state before retrying. Repeating a payment or a settlement instruction without checking its identity could cause duplicate work. Our exercise uses fictional Notes revisions only, but the principle is important.”

## Part 5: connect the lesson to Umicom Kernel (13:20–16:00)

**On screen:** [Kernel VFS/storage diagram](../../assets/diagrams/kernel-vfs-to-virtio.svg) and then the Umicom Kernel repository files `kernel/vfs.c`, `kernel/ramfs.c`, `kernel/fat16_writable_provider.c` and `kernel/virtio_block.c`.

**Narration:**

“Our small journal has no directories, no path permissions and no real block device. Umicom Kernel has separate components for those concerns. The Virtual File System handles names and open descriptions. RAMFS stores data in owned memory pages. A disk provider maps filesystem operations onto an admitted block handle. The VirtIO driver owns the device queue and DMA memory until completion or verified reset.”

“The Kernel also has an ordered FAT16 update protocol. It records an on-disk dirty state so an unfinished change can be detected. But a dirty marker is not the same as our write-ahead log: it does not contain a complete redo record. A good engineer reads the exact implementation contract instead of describing two different mechanisms as though they guarantee the same recovery.”

## Closing: learn, test and teach (16:00–17:30)

**Narration:**

“Today we recovered an interrupted Notes save by checking what actually reached our stable-state boundary. We learned that a journal must precede the applied update, that a checksum can detect corruption but not prove authenticity, and that recovery must be explicit when the last result is uncertain. Our model assumes full atomic sectors and does not pretend to survive a real power interruption. The real hardware, filesystem and driver contracts need separate testing.”

“Your next exercise is to change one interruption point and predict the recovered revision. Then find the same concepts in the Umicom Kernel documentation. Share the explanation with another learner. Understanding grows when we can explain not only what the program did, but why it was safe to do it.”
