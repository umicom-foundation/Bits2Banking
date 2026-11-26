<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-os-from-scratch/72-keep-a-complete-report-through-replacement.md

PURPOSE:
Keep a complete report through replacement

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Keep a complete report through replacement

The previous lesson stopped when the report writer acquired a temporary name. Continue from that point. The existing `report` contains the last finished boot record. The writer has acquired `report.tmp.1`. The occupied `report.tmp` belongs to someone else and stays outside this save.

## Before you begin

Draw two columns for the existing report name and the temporary name. In each example, record which name still points to a complete report after the next operation.

## Follow the save after the open

1. The writer sends the version 1 report bytes to the temporary file. A write can accept fewer bytes than requested and return that smaller count. The code advances by the count it received and attempts to write the rest. An interrupted write can be retried. Other write errors end the write loop.
2. The writer closes the file descriptor, the integer handle it received when it opened the file. It attempts that close even if writing failed. A close error makes the save fail.
3. After all bytes are written and the close succeeds, the writer calls `rename` to put the finished file at `report`. On failure it attempts to remove only the temporary name it acquired. The writer never deletes an occupied name to make room for its next attempt.

Start each row with a complete old `report` and with `report.tmp` occupied. Count what happens after the writer acquires `report.tmp.1`. Assume no other writer changes `report` during your trace.

| Paper case | Operations after the open | State of the named report |
| --- | --- | --- |
| All operations succeed | Write, close, rename | The new complete report has the name `report`. |
| The write returns `EIO`, an input/output error | Attempt write, close, attempt to remove `report.tmp.1` | The old report stays in place. The writer skips rename. |
| The rename returns `EIO` | Write, close, attempt rename, attempt to remove `report.tmp.1` | The old report stays in place. The save reports failure. |

The saved unit test substitutes controlled functions for file operations. It checks the written bytes, call order and exact names. Its write either accepts the entire report or returns an error, and its close always succeeds. The short-write loop and close-error branch can be read in the source. Native Linux filesystem behavior, a guest boot and power-loss behavior on a device still need separate verification.

## Separate replacement from durability

On a successful Linux rename over an existing file, a reader opening the destination name can find the old or new file around the switch, with no gap in which the destination name is absent. This is **atomic name replacement**. Keeping data after a crash is **durability**. On persistent storage, saving the file's contents and saving the containing directory's entry are separate synchronization steps. [Linux rename(2)](https://man7.org/linux/man-pages/man2/rename.2.html) · [Linux fsync(2)](https://man7.org/linux/man-pages/man2/fsync.2.html)

Umicom OS writes `/run/umicom/boot.report` on the temporary `tmpfs` it mounts at `/run`. The current writer has no `fsync` step, and a fresh boot starts with a new mount. Read the report as evidence for the current boot. [Linux kernel documentation on tmpfs](https://docs.kernel.org/filesystems/tmpfs.html)

On paper, suppose the first write accepts five of twelve bytes. Mark the next offset and the number of bytes still due. Then suppose the remainder is written and close fails. The next write starts at offset five with seven bytes due. A failed close prevents rename and the writer attempts to remove its own temporary name.

[Course contents](index.md) · [Previous lesson · Claim a temporary name for a boot report](71-claim-a-temporary-boot-report-name.md) · [Keep the first boot failure when a report cannot be saved](70-keep-the-first-boot-failure.md) · [Read a captured boot observation](19-read-a-captured-boot-observation.md) · [Check native release without retrying handles](61-check-native-release-without-retrying-handles.md) · [Next lesson · Review an executable before OS packaging](73-review-an-executable-before-os-packaging.md) · [HTML edition](../../../courses/umicom-os-from-scratch/lessons/72-keep-a-complete-report-through-replacement.html)
