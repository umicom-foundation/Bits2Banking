# Chapter 206 — Verify a fast-forward before integrating remote history

**Bits to Banking · Professional Git track · Umicom Foundation**  
**Prerequisites:** Chapters [192](192-fetch-and-divergent-history.md), [205](205-review-index-and-working-tree-evidence.md).

## The two different meanings of “up to date”

A developer running `git pull --ff-only origin main` on Umicom OS may see “Already up to date.” That statement describes the **Umicom OS repository**. It does not imply that `umicomOS/framework` matches Framework's latest `origin/main`. A parent Git repository and every Git submodule are separate histories, separate branches and separate staging areas. The success of one pull does not update the other histories.

A **fast-forward** is possible when the local commit is an ancestor of the desired remote commit. Git can move `main` forward without creating a merge commit. If the histories diverged, `--ff-only` refuses to integrate them. Refusal is valuable: it stops a routine synchronisation from silently inventing a history-resolution policy.

## Preflight: local working tree and branch

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
git status
git branch --show-current
git remote -v
git log -1 --oneline HEAD
```

A local dirty working tree can block a fast-forward if files would be overwritten. Preserve work before updating. If the branch is detached, determine whether HEAD contains unpublished commits before switching: `git log --oneline origin/main..HEAD` identifies local commits not reachable from the remote-tracking reference, **provided `origin/main` has been fetched**.

## Fetch before deciding

```powershell
git fetch origin main
git log --oneline --decorate --graph -8 HEAD origin/main
git log --oneline HEAD..origin/main
git log --oneline origin/main..HEAD
```

The first range shows commits present upstream but not locally. The second shows local commits not present upstream. Neither command modifies files. If the local checkout is the ancestor of `origin/main`, verify that fact explicitly:

```powershell
git merge-base --is-ancestor HEAD origin/main
```

On success this command exits with code zero and prints nothing. PowerShell makes the exit code available as `$LASTEXITCODE`. A nonzero code is a decision point, not permission to force a reset.

Only after a clean-worktree review and verified ancestry should the maintainer integrate:

```powershell
git merge --ff-only origin/main
```

Equivalent convenience syntax is `git pull --ff-only origin main`, but the two-step fetch/inspect/merge workflow is easier to teach and audit. Fetching does not guarantee that a remote push later will succeed; another developer can publish between your observation and your push.

## Interpreting outcomes

| Observation | Interpretation | Safe next action |
|---|---|---|
| `HEAD..origin/main` has commits, reverse range empty | Local branch behind upstream | Review and fast-forward |
| Reverse range has commits, first range empty | Local branch ahead | Review tests and staged state; push if authorised |
| Both ranges have commits | Histories diverged | Stop; reconcile intent, do not force |
| Both ranges empty | Same commit | No synchronisation necessary |
| Detached HEAD | No active branch to advance | Examine local-only commits and saved edits first |

A failed fast-forward is not automatically a corrupted repository. It is evidence that the requested history movement requires a different, explicit decision.

## Umicom demonstration

Suppose Framework `main` contains new chart-inspection code but the Umicom OS parent pins a previous Framework commit. In `umicomOS/framework`, a clean `git switch main` followed by fetch and fast-forward updates the child checkout. That change alone does not update the OS remote: the OS parent must test, stage its gitlink, commit and push its own `main` afterward. Do not run a parent-wide `git add -A` until unexpected OS changes have been identified.

## Knowledge check

Explain whether each of the following commands writes repository history: `git fetch`, `git log`, `git merge --ff-only`, `git add -A`, `git push`. Fetch updates remote-tracking state but creates no local commit; log is read-only; a successful fast-forward moves a branch ref; add stages snapshots; push publishes local refs to the remote. Identify at which step conflicts can occur and why the request to force a push is unsafe.

**Next:** [Chapter 207 — Publish a tested Framework gitlink](207-publish-a-tested-framework-gitlink.md).
