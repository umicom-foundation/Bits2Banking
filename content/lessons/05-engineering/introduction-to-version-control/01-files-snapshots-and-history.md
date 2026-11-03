# Files, snapshots and history

A file contains the text you are working on now. Version control keeps named snapshots so you can explain what changed and compare earlier work.

## Start with one real example

In Umicom Kernel, `programs/diagnostic/main.c` contains the diagnostic program. The compiler reads that file and produces an executable. Git records the source file when you make a commit. It does not run the compiler, prove that the program works, or automatically record every keystroke.

 <svg viewbox="0 0 700 110" role="img" aria-label="Review working text, select the snapshot to record, then create a commit." style="width:100%;max-width:700px"><title>Review working text, select the snapshot to record, then create a commit.</title><rect x="10" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="115" y="53" text-anchor="middle" fill="white" font-size="17">Working files</text><path d="M220 47h18l-7 -6m7 6l-7 6" fill="none" stroke="#287b78" stroke-width="3"></path><rect x="240" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="345" y="53" text-anchor="middle" fill="white" font-size="17">Staged snapshot</text><path d="M450 47h18l-7 -6m7 6l-7 6" fill="none" stroke="#287b78" stroke-width="3"></path><rect x="470" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="575" y="53" text-anchor="middle" fill="white" font-size="17">Commit</text></svg>

Review working text, select the snapshot to record, then create a commit.

A **repository** is a collection of files with Git history. A **commit** records a tree of file contents, an author and a message, together with links to earlier commits. The long identifier you see is a content-derived name. A **branch**, such as `main`, is a movable name for a commit. **HEAD** identifies your current position.

## Read without changing anything

Open PowerShell and choose a repository you already have. The following commands only inspect it.

```text
Set-Location "C:\umicom\umicom-kernel"
git status --short --branch
git log -3 --oneline
git diff -- programs/diagnostic/main.c
```

1. `Set-Location` chooses the folder. A path describes where a file or folder lives.
2. `status` tells you the branch and working-file changes. A clean status means no reported tracked differences or ordinary untracked files; it says nothing about test success.
3. `log -3` shows up to three commits. Their messages explain why changes were recorded.
4. `diff` shows unstaged changes to the named source file. An empty result is normal when it is unchanged.

## Read a small difference

```text
-    return 0xe007U;
+    return 0xe009U;
```

The minus line is the earlier text and the plus line is its replacement. They are display markers, not characters to paste into C. This example changes a diagnostic result; it does not establish whether that new result is correct. Read the surrounding condition and its tests before accepting it.

## Check your understanding

A source file has changed, but you have not committed. Does the last commit contain the edit?

<details>

<summary>Answer</summary>

No. The working file and the recorded snapshot are different states. Even after staging, the next commit has not yet been created. This distinction lets you review before recording.

</details>

If Git reports that the folder is not a repository, check your location. Do not initialise Git inside an existing application simply to silence that message. Return to the repository root you intended.

---

[Read this lesson in HTML](../../../courses/introduction-to-version-control/lessons/01-files-snapshots-and-history.html) · [Learning sequence](../../../start/learning-sequence.md)
