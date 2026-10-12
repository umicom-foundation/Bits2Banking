# Chapter 189 — Review staging, recover changes and revert safely

**Bits to Banking · Version-control track · Umicom Foundation**  
**Tools:** Git and PowerShell commands · **Prerequisite:** Chapter 188.

## Recovery must preserve the thing you are trying to fix

A contributor notices that `git add -A` staged generated build files as well as a new C23 source file. Another discovers a regression in a commit that was already pushed to `main`. These problems have **different safe remedies**. Treat “unstage a file”, “recover an unpublished edit” and “reverse a published change” as separate operations.

## Remove a path from the index, not the working tree

Read the staged inventory first:

```powershell
git status
git diff --cached --stat
git diff --cached --check
```

If a path was staged accidentally, you can unstage it without deleting its local bytes:

```powershell
git restore --staged -- "PATH_TO_REVIEW"
git status
git diff --cached --stat
```

Replace `PATH_TO_REVIEW` with an actual repository-relative path. Do not copy the placeholder literally. This operation changes the **index**; it is not the same as `git restore --worktree`, which can overwrite local edits. Review paths containing spaces by placing them inside quotes.

## Stage only the intended change

For a focused documentation correction:

```powershell
git add -- "content/lessons/05-engineering/16-git.md"
git diff --cached -- "content/lessons/05-engineering/16-git.md"
git diff --cached --check
```

For a larger source update, `git add -p` allows interactive selection of hunks, but it requires understanding dependencies between hunks. Do not stage half an API implementation while omitting its caller, tests or header.

## Restore historical content without blindly overwriting current work

`git show HEAD:path` writes an old file version to terminal output; it does not alter the working tree:

```powershell
git show HEAD:"content/lessons/05-engineering/16-git.md"
```

This is a useful **read-only** first step. To recover an older function, compare the old content with the current file in an editor or Beyond Compare and bring back only the reviewed sections. Avoid mass-checkout commands that overwrite all modified files.

If a file is untracked and important, create a protected backup before removing or renaming anything. Git cannot automatically reconstruct every untracked file that was never staged, stashed or backed up.

## Reversing a published commit

If a bad change was **already pushed to `main`**, prefer a reviewed `git revert` when the desired action is to undo that commit's effects without rewriting published history:

```powershell
git log --oneline -8
git show --stat --oneline COMMIT_TO_REVIEW
git revert COMMIT_TO_REVIEW
```

Substitute a real, reviewed commit hash. `git revert` may open an editor, create conflicts and create a new commit. Test the restored behaviour **before** pushing. A revert can also conflict with or disable later work that depends on the original change. Read the revert patch and perform regression tests; do not regard a clean `git revert` exit code as sufficient.

For a commit that was never published, there are several integration options; use the least destructive choice that preserves prior source and explains its intent. Do not apply a generic history rewrite to a shared main branch.

## Find a commit that was briefly checked out

```powershell
git reflog -12
git show --stat --oneline REVIEWED_COMMIT
```

`git reflog` records recent local reference movements. It is especially useful after moving from detached HEAD to `main`. However, reflogs are local and expire under retention policy; do not treat them as permanent backups. A reviewed tag can keep a critical commit reachable while you reconcile its history.

## Decision table

| Situation | First action | Avoid |
|---|---|---|
| Accidental staging | `git diff --cached`, then `git restore --staged -- path` | `reset --hard` |
| Uncommitted tracked/untracked changes | Inspect, stash with `--include-untracked`, review saved content | `clean -fd` |
| Detached unpublished commit | Inspect `origin/main..HEAD`, preserve a tag | switching away without a reference |
| Remote `main` ahead | `git fetch`, inspect ancestry, `pull --ff-only` where valid | `push --force` |
| Published faulty commit | Review `git revert` and run regression tests | rewriting shared history |
| Parent gitlink wrong | Inspect nested commit and update parent reference | copying Framework source into OS |

## Practical assessment

In a **practice** repository, deliberately stage an unwanted Markdown file, unstage it and verify the file is still present on disk. Create a commit, inspect it with `git show`, then use `git revert` and explain why history now contains two commits rather than an erased earlier commit. Keep this exercise out of the actual Umicom production branches.

**Next:** [Git capstone and a multi-repository release checkpoint](190-umicom-git-capstone-and-cheat-sheet.md).
