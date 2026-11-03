# Review and record a change

Use a separate practice folder to learn staging and commits before publishing changes to an application.

## Create a small practice repository

A repository may hold code, documentation or both. Choose a new, empty folder for this exercise. Do not reuse a product folder.

```text
New-Item -ItemType Directory "C:\umicom-learning\version-control"
Set-Location "C:\umicom-learning\version-control"
git init -b main
```

`New-Item` creates the directory. If it already exists, stop and inspect it rather than overwriting someone else's exercise. `git init -b main` starts a new history on a branch named main; it is not an update command for an existing repository.

In a text editor, create `notes.txt` containing `A Kernel program asks for a service through an environment call.` Save the file. This is a short summary of the real `UmicomProgramSystemCall` bridge in `umicom-kernel/programs/diagnostic/entry.S`.

## Inspect, stage, inspect again

```text
git status --short --branch
git add -A
git diff --cached --check
git diff --cached --stat
git diff --cached
git commit -m "docs: explain a native Kernel service request"
git status --short --branch
```

Run each line separately and stop on an error. `git add -A` stages additions, modifications and deletions throughout this repository. It does not recursively commit nested repositories. `--cached` asks to inspect the staged snapshot. `--check` finds some whitespace problems; it does not find private information or logic errors. Read the full staged difference.

 <svg viewbox="0 0 700 110" role="img" aria-label="The recorded content is the reviewed staged content, not every future edit." style="width:100%;max-width:700px"><title>The recorded content is the reviewed staged content, not every future edit.</title><rect x="10" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="115" y="53" text-anchor="middle" fill="white" font-size="17">Edit notes.txt</text><path d="M220 47h18l-7 -6m7 6l-7 6" fill="none" stroke="#287b78" stroke-width="3"></path><rect x="240" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="345" y="53" text-anchor="middle" fill="white" font-size="17">Review staged text</text><path d="M450 47h18l-7 -6m7 6l-7 6" fill="none" stroke="#287b78" stroke-width="3"></path><rect x="470" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="575" y="53" text-anchor="middle" fill="white" font-size="17">Record explanation</text></svg>

The recorded content is the reviewed staged content, not every future edit.

If Git asks for your identity, configure a name and email you are willing to include in commits for this repository. An email may be visible after publication. If Git says nothing to commit, there is no new staged snapshot; do not invent a change merely to create a commit.

## Practise two independent states

1. Add a second sentence about the `a7` operation register and stage it.
2. Add a third sentence about the `a0` return register, but do not stage again.
3. Read `git diff`, then `git diff --cached`.
4. Explain which sentences the next commit would contain. Stage again only if the third sentence belongs in that same change.

<details>

<summary>Expected explanation</summary>

The unstaged diff shows the third sentence relative to the staged text. The cached diff shows the second sentence relative to the previous commit. A commit records the staging area. It does not silently include the later unstaged sentence.

</details>

## Private files and generated output

A `.gitignore` rule can keep ordinary untracked build output out of future staging. It does not untrack an already recorded file and does not remove earlier history. Keep passwords, personal notes and raw private logs outside public repositories, and inspect staged text before publishing.

---

[Read this lesson in HTML](../../../courses/introduction-to-version-control/lessons/02-review-and-record-a-change.html) · [Learning sequence](../../../start/learning-sequence.md)
