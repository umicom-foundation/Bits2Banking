# Chapter 195 — Preserve untracked files and restore stashes carefully

**Bits to Banking · Recovery engineering · Umicom Foundation**
**Prerequisites:** [stashing fundamentals](186-stash-preserve-and-recover-work.md), Chapter 194.

## What a stash preserves—and what it does not

A stash is a temporary Git-managed record of a working-tree and index state. `git stash push --include-untracked` captures tracked modifications and ordinary untracked files, then removes those changes from the worktree if the operation succeeds. **Ignored files are not included**, and a stash is not a complete replacement for a verified backup. A stash also does **not** rescue arbitrary commits reachable only from a detached HEAD: those are a separate history problem.

In your recent Umicom OS error, Git reported both tracked Framework changes and untracked new C23 sources. A tracked-only stash could leave many untracked paths behind and fail to unblock checkout. Equally, blindly applying a stash after updating could reintroduce older copies of files already incorporated upstream.

## Preserve with evidence

From the child Framework directory:

```powershell
Set-Location "C:\umicom\umicomOS\framework"
git status --short
git log --oneline origin/main..HEAD
git stash push --include-untracked -m "backup: Framework state before synchronisation"
git status --short
git stash list
```

Stop if the stash reports an error. Do not proceed unless all valuable changes are either committed or represented in the stash and `git status` is acceptably clean. When ignored build artefacts contain important source-like data, make a separate deliberate backup; neither `-u` nor a normal commit includes ignored files automatically.

## Review before restoration

After updating to the intended Framework source, inspect the stash:

```powershell
git stash list
git stash show --include-untracked --stat 'stash@{0}'
git stash show --include-untracked --patch 'stash@{0}'
git diff --stat 'stash@{0}' HEAD
```

The final `git diff` is a **snapshot comparison**, not a complete verdict on saved untracked files. Some stash layouts store untracked content in another parent tree. Inspect the stash with `--include-untracked` and compare relevant files with Beyond Compare. If the updated Framework already contains the same implementation, do not apply the stash merely to make the stash disappear.

Where missing work remains and a restoration has been reviewed, `git stash apply 'stash@{0}'` retains the stash for safety while attempting to reapply edits. It may conflict. Inspect the resulting tree and tests. Do **not** use `git stash pop` as an automatic cleanup step, and do not delete the stash before proving that all important content survives elsewhere.

## Source-preservation exercise

Make a disposable practice repository containing a `CMakeLists.txt` and an untracked C23 header. Modify the CMake file, stash with and without `--include-untracked` in separate trials, and observe the different outcomes. Use another directory or a backup to retain the original practice work. Explain why a successfully restored CMake configuration still needs rebuilding and testing.

## Common misconceptions

**“The working tree is clean, so all work is on GitHub.”** A clean checkout can point to a local unpublished commit or a parent gitlink that has not been pushed.

**“The stash is redundant because the same filenames exist remotely.”** Filename equality is not content or behavioural equality.

**“Stash is a long-term backup.”** Stash references can be dropped or expire after becoming unreachable. Integrate reviewed work into normal commits, not indefinite temporary storage.

**Next:** [Review everything `git add -A` would stage](196-audit-git-add-a-and-commit.md).
