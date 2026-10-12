# Chapter 197 — Use the Git reflog to investigate apparently lost commits

**Bits to Banking · Repository recovery · Umicom Foundation**
**Prerequisites:** [Git history and provenance](188-read-history-diffs-and-provenance.md), Chapter 195.

## A commit can exist without a convenient branch name

A Git commit is an object identified by its content hash. A branch or tag is a named reference that makes commits easy to reach. Detached HEADs and history operations can leave valuable commits no longer reachable from the current branch tip. That does not mean they disappeared immediately. Git's **reflog** records recent movements of local refs and HEAD; it is an excellent diagnostic tool, but its records are local and subject to retention and expiry. It is not a substitute for pushing reviewed commits or keeping backups.

Suppose an Umicom Framework developer commits a correction while in detached HEAD and later switches to `main`. The working tree looks normal, but the commit might no longer appear in `git log main`. The correct response is to search for the commit and inspect it—not to overwrite Framework with a folder copy.

## Read-only investigation

```powershell
Set-Location "C:\umicom\Umicom-Applications\framework"
git status
git reflog --date=iso -20
git log --graph --decorate --oneline --all -30
```

The reflog includes entries such as checkout, commit and reset movements. Select a possible commit identifier from the actual output, then read its content:

```powershell
git show --stat <COMMIT_ID>
git show --format=fuller --no-patch <COMMIT_ID>
git diff <BASE_COMMIT> <COMMIT_ID> --stat
```

Replace angle-bracket placeholders with real commit IDs; do not type the brackets. The last comparison requires an identified base. Evidence matters: a commit that only changes a generated file is different from a commit introducing a tested Framework service.

## Reconcile, do not duplicate

When you identify an unpublished commit, determine whether its source changes already exist upstream, whether its dependencies are still valid, and whether tests pass at the intended target revision. Cherry-picking a commit may be appropriate **after a reviewed plan**, but it can conflict or introduce a second copy of already integrated functionality. If the change needs to be reintroduced, stage and commit a tested version in the appropriate canonical repository. A reflog is for discovery; it does not authorise an automatic repair.

## Limitations and failure cases

- The reflog records movements in the local clone. It cannot reveal commits created only on another computer unless those commits were fetched or copied here.
- Reflog entries may expire and unreachable objects can be pruned. A missing entry is not proof that no code ever existed.
- A commit can be reachable from another ref even when absent from `main`.
- Uncommitted edits are not commits. Use `git status`, any reviewed stash and backups to investigate those separately.

## Exercise

In a disposable Git practice repository, make three commits, record their IDs, inspect `git reflog`, and then use `git show` to explain exactly which files changed in each commit. Do not reset the project or intentionally discard source files. Compare how `git log` presents reachable commits versus how reflog shows recent reference movements.

**Next:** [Use Git bisect to locate a regression](198-bisect-a-c23-regression.md).
