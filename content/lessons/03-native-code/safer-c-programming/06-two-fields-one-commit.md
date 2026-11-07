<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/safer-c-programming/06-two-fields-one-commit.md

PURPOSE:
Explain the lesson: Replace two fields as one complete change.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Replace two fields as one complete change

## Prepare the example
Open the repository's `labs/native/fault-injection` folder. Read `note.h`, then `note.c`. No execution is needed for the first trace. The [lab instructions](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/fault-injection/README.md) give PowerShell and Linux configure, build and test commands.

A note contains a title, a body and a revision number. A revision identifies which saved state a caller expects to replace. This teaching model illustrates an ownership rule used by larger Framework services; it is not another production document engine.

## Follow the replacement
Find `BtbNoteReplace`. It first checks the note and expected revision. It then asks `CopyPair` to prepare two new strings. Only after both copies exist does it release the old strings, assign the new pointers and increase the revision.

Draw three boxes:

```text
Old title/body remain owned
          |
Prepare new title and new body
          |
Publish both pointers and increment revision
```

“Atomic” here means the function preserves its logical state when preparation fails. It does not mean other threads may read this object without synchronization.

## Work through failure
Suppose the old values are Title A, Body A, revision 1. The title allocation succeeds but the body allocation fails.

1. `CopyPair` releases the temporary title.
2. It returns `BTB_NO_MEMORY`.
3. `BtbNoteReplace` returns before releasing either old field.
4. The caller still reads Title A, Body A, revision 1.

If the function replaced the title immediately after its allocation, the note could contain a new title with an old body. The candidate-first design avoids that partial state.

## Exercise and expected result
On paper, trace success, first-allocation failure and second-allocation failure. Record old live allocations, temporary live allocations and final revision. Successful replacement ends with two live allocations and revision 2. Each rejected replacement ends with the original two and revision 1.

## Diagnose a mismatch
Inspect the earliest assignment to `note->title` or `note->body`. It belongs after successful preparation. Do not weaken the failure assertions to accept mixed fields. A future production extension should use the existing Framework document transaction API and its ownership rules.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/fault-injection/note.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](05-untrusted-sizes-and-representations.md) · [Next lesson](07-allocator-context-and-test-doubles.md)

