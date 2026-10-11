# Episode 14 — Who owns this memory? Building a Notes model in C23

**Duration:** 15–18 minutes  
**Companion lesson:** [Memory ownership in C23](../../lessons/03-native-code/58-memory-ownership-in-c23.md)  
**Source:** [Owned Notes laboratory](https://github.com/umicom-foundation/Bits2Banking/tree/main/labs/native/owned-notes)

## 00:00–02:00 — Why a simple note needs an owner

**On screen:** A Notes application with a list of tasks: review a source file, add a test, submit a pull request. Show one task selected.

**Narration:**

> Imagine you are writing a Notes application for new contributors to the Umicom projects. A contributor types a title, saves it, closes the editor panel and opens the note again. The text must still be there. But what part of the programme holds it? Who is responsible for releasing the memory when the note is deleted?
>
> These questions lead us to memory ownership. In C, we need explicit answers. Today we will create a small Notes model that copies the text it receives, lets us read it safely and releases every allocation it owns.

## 02:00–05:00 — Memory addresses and the two copies

**On screen:** Display `notes-memory-ownership.svg`. Highlight the caller's `char title[]`, the Notes store's allocation and the output buffer.

**Narration:**

> A local character array is owned by the function that created it. If a Notes model stores only the address of that array, it may later refer to memory that has disappeared. The safer design is to make an owned copy. We allocate enough bytes for the text and its terminating zero, then copy those bytes.
>
> Notice that the caller's buffer remains separate from the store's copy. Changing the caller's array should not change the saved note. And if the caller reads the note into another buffer, that output buffer also has its own owner.

**Demonstration:** Open `notes.h` and identify `BtbNoteStoreCreate`, `BtbNoteStoreAdd` and `BtbNoteStoreDestroy`. Explain the opaque `BtbNoteStore` type without introducing its private implementation yet.

## 05:00–09:00 — Prepare an edit before publishing it

**On screen:** Open `notes.c`. Highlight `BtbOwnedPair`, `BtbReserve` and `BtbNoteStoreReplace`.

**Narration:**

> Allocations may fail. In the replacement function, we do not delete the old text first. Instead, we allocate the new title and body while the earlier note remains valid. Only when both allocations have succeeded do we install the replacements.
>
> There is a second important detail in the array-growth function. We save the result of `realloc` in a temporary pointer. If `realloc` fails, our existing array pointer is still valid. That one decision prevents losing access to the entire collection.

**Demonstration:** Point to the `NULL` check and trace the ownership of the title and body on the success path and on the failure path.

## 09:00–13:00 — Build and run the tests

**On screen:** In PowerShell, work from `C:\umicom\Umicom-Bits2Banking`. Enter the commands from the lesson to configure, build and run CTest.

**Narration:**

> A successful build tells us that the compiler and linker accepted our programme. Tests tell us something else: whether it behaves correctly for the cases we deliberately check.
>
> Our test first changes the original input arrays after adding a note. Then it reads the note and confirms that the saved text has not changed. Next, it gives the model output buffers that are too small and checks that the buffers remain untouched. Finally, it attempts an invalid replacement and makes sure the earlier note survives.

**Demonstration:** Show the relevant assertions in `test_notes.c`. Run CTest. Explain the test name and reported result rather than reading the terminal output word by word.

## 13:00–16:00 — One change and one further application

**On screen:** Add a second task to `main.c`, build, run, then inspect the Framework memory header in GitHub.

**Narration:**

> Now create a second note. Predict the two IDs, compile and check. Try removing the first note; the ID of the second should stay the same. We are separating the identity of a note from where it happens to be stored in an array.
>
> Real Umicom applications use Framework-owned document and memory services instead of copying our small training model. But the questions are the same: who owns an allocation, how long does it live, and what happens if an operation fails?
>
> Read the complete lesson and source files on Bits2Banking. If you find a useful improvement, create a focused test and share it with other learners.

**End screen:** Written lesson, source repository, and the next episode on checked arithmetic.
