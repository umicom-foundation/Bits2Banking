<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/safer-c-programming/09-revisions-and-stale-writers.md

PURPOSE:
Explain the lesson: Reject an edit based on an older revision.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Reject an edit based on an older revision

## Prepare
Open the fault-injection lab's header and replacement function. A caller supplies `expectedRevision` when replacing a note. This is the revision it read before preparing its edit.

A stale writer is a caller whose expectation no longer matches the current record. It might be an old window, a delayed operation or an outdated draft.

## Trace two edits
Start with revision 1. Two views both read that revision.
1. View A prepares an updated title and body.
2. View B prepares a different update.
3. A calls Replace with expected revision 1. It succeeds and creates revision 2.
4. B calls Replace with expected revision 1. It receives `BTB_CONFLICT`.

B's text is not silently applied over A's work. The caller can retain its draft, show the current version and ask for a reviewed resolution.

## Read the ordering
The source checks the expected revision before attempting new allocations. A known conflict therefore does not need temporary strings. It also refuses replacement at `UINT64_MAX`, preventing the revision counter from wrapping to a previously used value.

This local check does not make the object thread-safe. Concurrent access still needs a shared synchronization policy. Do not infer a distributed transaction protocol from a single in-memory function.

## Exercise
Write a sequence with three calls: successful A, stale B, then B retried with the current revision after review. Record the input revision, status and final stored text each time.

Expected revisions are 2 after A, still 2 after rejected B, then 3 after an explicitly reviewed retry. A blind automatic retry may discard the user's intent and is not the lesson's policy.

## Recover from a conflict
Keep the caller's proposed content separate from the stored note. Read the current record, compare changes and decide whether to revise or discard the draft. The test should assert that a refused edit preserves both fields and the revision, not just the returned status. Production applications should reuse Framework conflict handling and audit services rather than copying this lab into each screen.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/fault-injection/note.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](08-spans-terminators-and-text-policy.md) · [Next lesson](10-borrowed-pointers-after-replacement.md)

