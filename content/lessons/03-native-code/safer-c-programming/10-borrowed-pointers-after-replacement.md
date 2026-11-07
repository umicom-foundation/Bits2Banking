<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/safer-c-programming/10-borrowed-pointers-after-replacement.md

PURPOSE:
Explain the lesson: Know when a borrowed pointer stops being valid.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Know when a borrowed pointer stops being valid

## Prepare
Read the comment above `BtbNoteTitle` and `BtbNoteBody`. The returned pointers are borrowed: the note owns the strings, and the caller may read them during their stated lifetime.

Borrowing does not transfer responsibility to release memory. Calling `free` on one of these pointers would break the note's ownership.

## Draw the ownership
```text
note ──owns──> title allocation
     └─owns──> body allocation
reader ─borrows─> title bytes
```

After a successful replacement, the old allocations are released. The reader's old pointer must no longer be dereferenced, even if a debugger still displays familiar bytes at that address. Memory contents remaining visible is not proof of a live object.

After a rejected replacement, the old note remains valid under this lab's contract. After destruction, both borrowed fields are invalid.

## Plan a safe reader
For immediate display, read the pointer and use it before any operation that can replace or destroy the note. If text must survive those operations, make an independently owned copy while the borrow is valid, then release that copy according to its own ownership.

Do not hide this decision inside a long-lived UI callback that assumes a pointer lasts forever.

## Exercise
For each event, decide whether an earlier borrow can still be used:
- a revision-conflict rejection;
- a successful replacement;
- reading the revision;
- destroying the note.

The answer is yes, no, yes, no, provided no other actor mutates the note. The original pointer's numerical value does not change these answers.

## Check without invoking undefined behaviour
Write tests that inspect the new note through fresh accessor calls. Track release counts in the allocator. Do not “test” a released pointer by dereferencing it and expecting a crash; undefined behaviour has no reliable required result.

In Framework applications, read the actual API's borrow/retain/copy documentation. Similar-looking accessor names can have different lifetime contracts. Record the lifetime next to the field in a design diagram so UI and worker code share the same understanding.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/fault-injection/note.h). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](09-revisions-and-stale-writers.md) · [Next lesson](11-destruction-and-idempotence.md)

