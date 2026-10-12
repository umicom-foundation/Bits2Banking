# Chapter 209 — Diagnose a rejected Git push without force

**Bits to Banking · Professional Git track · Umicom Foundation**  
**Prerequisites:** Chapters [194](194-detached-head-and-push-identity.md), [206](206-fast-forward-without-rewriting-history.md).

## The actual failure we want to understand

A maintainer runs `git push` inside `C:\umicom\umicomOS\framework` and sees “You are not currently on a branch.” Next, `git push origin main` is rejected as non-fast-forward. These are two different pieces of evidence. The first says the **current checkout** is a detached HEAD. The second says the **local branch named `main`** cannot be published as a fast-forward of remote `main`. Running `git push origin main` does not automatically push the detached HEAD commit.

A serious developer must distinguish references before choosing a repair. `HEAD`, `refs/heads/main` and `refs/remotes/origin/main` may all name different commits. No command in this chapter erases a branch or removes a source file.

## Gather evidence in the affected child repository

```powershell
Set-Location "C:\umicom\umicomOS\framework"
git status
git branch -vv
git log -1 --format=%H HEAD
git fetch origin main
git log -1 --format=%H origin/main
git log --oneline origin/main..HEAD
git log --oneline HEAD..origin/main
git stash list
```

`git branch -vv` distinguishes a checked-out branch from other local branches. `git log origin/main..HEAD` asks whether the detached HEAD includes unpublished work after the fetch. Do not switch away if it does. A stash may preserve working files, but it does **not** automatically anchor every detached commit or include ignored files.

## Interpret the common outcomes

**Case A — Detached HEAD equals an old published Framework commit.** The worktree is clean, and there are no local-only commits. It is safe to follow the approved OS Framework update procedure: switch to the existing local `main`, fast-forward from `origin/main`, build the OS, and commit its parent gitlink. You do not need to push Framework because it is already published.

**Case B — Detached HEAD has a new, unpublished commit.** Do not switch until that commit has been preserved and its changes reviewed. The commit may represent original Framework work that should be published via the canonical Framework development checkout. Capture the SHA and compare the patch with remote `main` before deciding how to integrate it.

**Case C — Local `main` diverged from `origin/main`.** A fast-forward is impossible. Record both tip SHAs and compare unique commits. There may be valid local work to integrate or an obsolete local branch. The resolution requires an explicit approved history plan, not `--force`.

**Case D — Untracked files block the checkout.** Preserve them before attempting another checkout. `git stash push --include-untracked -m "..."` is one temporary option when the result is verified, but ignored files are not included. Do not rely on a stash as your only long-term backup.

## Check which repository owns the intended change

If the intended work is inside Framework C files, the publication target is `umicom-framework`. If the intended work is only the OS dependency pointer, the publication target is `umicom-os`. The two changes have independent commit and push operations. A parent `git push` cannot push a child's unreferenced local commit for you.

A published Framework child must be reachable from an appropriate remote ref. Once the child is published and tested, the OS parent can stage its gitlink and create its own commit. Avoid duplicate source copies under both Framework checkouts.

## Safety checklist before any write

Confirm the working-tree status, current HEAD, local `main` SHA, remote `main` SHA, local-only commits, and stash state. Confirm the parent pointer separately. Review exactly which repository you are in using `Get-Location` or `pwd`; this is especially important when several PowerShell windows are open. Perform one reversible operation at a time and inspect the result immediately.

## Assessment

A learner claims “the remote rejected my push, so I should run `git push --force`.” Explain why this is unsafe, which three reference identities need comparison, and why a successful `git pull` in Umicom OS does not prove that Framework is current. The correct answer uses commit ancestry and repository ownership, not an ad hoc reset.

**Next:** [Chapter 210 — Release tags and provenance](210-release-tags-provenance-and-qualification.md).
