# Chapter 237 — Recover commits with reflog and read-only probes

**Bits to Banking · Professional repository recovery · Umicom Foundation**  
**Prerequisites:** Chapters 228–236 · **Duration:** 45–60 minutes.

## A missing branch reference is not necessarily lost work

During Umicom OS Framework synchronisation, someone checks out a newer remote revision, then notices a locally committed feature no longer appears in the working directory. Before resetting anything, inspect **Git's reflog**: a local record of recent movements of HEAD and other references. It may still identify the earlier commit even when no branch points to it.

A reflog is a **local recovery aid**, not an immutable archive or remote backup. Entries can expire or be pruned, so a detached local-only commit should be identified and preserved promptly. Do not assume GitHub contains it until publication is verified.

## Recovery inspection from the affected repository

```powershell
Set-Location "C:\umicom\umicomOS\framework"
git status
git reflog show --date=iso --all -25
git log --oneline --decorate -20
git log --oneline origin/main..HEAD
```

If a reflog entry identifies an interesting SHA, use read-only commands:

```powershell
git show --stat <EXACT_COMMIT_SHA>
git cat-file -t <EXACT_COMMIT_SHA>
git cat-file -p <EXACT_COMMIT_SHA>
git diff <OLDER_SHA> <NEWER_SHA> --stat
```

Replace placeholders with **real** commit identifiers. `git show` shows the actual source changes associated with the commit. Determine whether they were already published, superseded or still needed. Use Beyond Compare before trying to restore any file; never copy arbitrary source bytes into a Framework checkout without review.

## Understand what reflog can and cannot tell you

| Evidence | Establishes | Does not establish |
|---|---|---|
| `git reflog` | A reference or HEAD moved locally | That the commit is still backed up remotely |
| `git cat-file -t SHA` | Git can currently read the object type | That its contents compile |
| `git show SHA` | The committed patch or content | That tests passed |
| `git branch -vv` | Local branch/upstream relationship | That remote tracking refs have just been refreshed |
| `git status --short` | Current checkout changes | Whether a previously detached commit is reachable |

For advanced recovery, `git fsck --no-reflogs --unreachable` can list dangling objects; this is read-only diagnostic work, not a promise of recovery. Treat unavailable objects or corrupted stores as an incident requiring a backup plan, not as a reason for force pushes.

## What not to do

Never immediately run `git reset --hard`, `git clean -fd`, `git gc --prune=now` or `git push --force` on a repository with unverified work. Garbage collection can remove otherwise recoverable unreachable objects once retention conditions allow. Hard reset and cleaning can discard working changes; force push can rewrite colleagues' published history.

If local-only commits exist and the worktree is dirty, do **not** blindly run `git switch main`. First record the exact commit SHA, preserve any uncommitted edits, inspect relative ancestry and plan a reviewed integration path. That process can be completed without adding permanent development branches to the Umicom workflow.

## Capstone question

A developer says `git status` reports clean, `git branch --show-current` is blank, and `git reflog` contains a local commit absent from `origin/main`. What is the safe next step? Record the SHA and inspect the commit and its ancestry; preserve it before changing HEAD. A clean working tree is not evidence that unpublished commits are safe to discard.

**Next:** define release tags and evidence boundaries before publishing a final application integration.
