# A file, a draft and a saved document

Understand editing, saving and visual components through the same Framework state model.

Lesson 1 of 2. Read [Start here](../../../../courses/framework-and-finance/start.html) first. No banking account or live connection is needed.

A **file** is named data stored on a device. A document opened in an editor usually has a working copy in memory. That working copy is a **draft**. Changing the draft does not necessarily change the file. The word **dirty** means the draft contains changes that have not been saved.

Imagine a file containing `total = 10;`. You change 10 to 12. The screen should show 12, while the original file still contains 10 until saving succeeds. If writing fails, the application should keep the draft and show an error. Clearing the dirty marker before the write succeeds could mislead the user into closing valuable work.

```text
disk: 10 → open → draft: 10 → edit → draft: 12
disk: 10 ← unchanged on failed save
disk: 12 ← successful save ← draft: 12
```

Framework's document coordinator joins the document store to toolkit-neutral views. **Toolkit-neutral** means the contract does not depend on a particular button or window library. Document identity, selection, undo history and external-file conflict checks are shared concerns; a tab is one presentation of them.

## Try the workflow with disposable work

1. Create a new folder you own for exercises. Use a copy of a small text file.
2. In Studio, choose Open File and select that copy. If no chooser appears, record that failure; do not assume the file opened.
3. Change one character. Observe whether the document becomes dirty.
4. Save, close and reopen the file. Confirm the character is present.
5. Open a second file, switch tabs and confirm each retains its own text and selection.

The expected result is independently retained drafts and persisted saved bytes. These are acceptance steps to perform on your build, not evidence that your build passed them. You can complete the paper trace first if the application is unavailable.

Two programs may edit the same file. A conflict check compares the current disk state with the state originally read. A mismatch should prompt a deliberate decision; it should not silently overwrite another editor's work.

## Read a real Umicom source contract

In a local checkout, open `C:\umicom\Umicom-Applications\framework\include\umicom\document\coordinator.h`. A **contract** states what an operation accepts, returns and promises. Read its comments before its implementation.

The following excerpt comes from that source file. The surrounding declarations and comments are part of the contract too.

```text
typedef struct UmiDocumentWorkingCopySnapshot {
    UmiDocumentId document_id;
    char view_id[UMI_UI_ID_CAPACITY];
    char path[UMI_PATH_CAPACITY];
    char uri[UMI_DOCUMENT_URI_CAPACITY];
    char display_name[UMI_DOCUMENT_NAME_CAPACITY];
    char language_id[UMI_DOCUMENT_LANGUAGE_CAPACITY];
    UmiDocumentTextEncoding encoding;
    UmiDocumentLineEnding line_ending;
    UmiDocumentConflictState conflict;
    size_t text_length;
    size_t undo_count;
    size_t redo_count;
    uint64_t revision;
```

1. Locate the file in your editor. You are reading it; do not edit your working product to complete this exercise.
2. Find the maximum-file-bytes comment and the history capacity. Explain why the encoded file size can differ from the editor's decoded text size.
3. Write the input, expected result and a possible failure in your own words.

The source reference identifies an existing implementation or contract. It does not establish that an application has wired every operation, or that its build has passed. If your checkout differs, compare the current declarations and record the difference.

## Check your understanding

The title changed to a new filename but the write failed. Is the save complete?

### Worked answer

No. A title is presentation state. Completion requires a successful write to the intended destination. Preserve the draft and report the failed operation.

## Keep a learning checkpoint

Write one observation, one unanswered question and the result of the exercise. In Studio you may record a private checkpoint as explained in [Start here](../../../../courses/framework-and-finance/start.html#progress). Opening the page alone is not completion.

---

[Read this lesson in HTML](../../../../courses/framework-and-finance/studio-workflows/lessons/documents-and-saving.html) · [Learning sequence](../../../../start/learning-sequence.md)
