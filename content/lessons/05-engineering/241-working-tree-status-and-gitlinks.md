# Chapter 241 — Working-tree status, index changes and Framework gitlinks

**Bits to Banking · Engineering track · Umicom Foundation**  
**Primary language:** C23 · **Reference:** `framework/include/umicom/vcs/working_tree.h`  
**Prerequisites:** Chapter 240 and the Git three-way merge chapters.

## Why this matters

A change to `Umicom-Applications\framework\src\...` is a change **inside the Framework repository**. A change to the parent `Umicom-Applications` gitlink records **which Framework commit the parent consumes**. They are separate commits, even though both appear somewhere under the directory named `framework`. Treating the parent as an ordinary directory can produce missing commits, misleading release evidence, and a submodule update that refuses to overwrite local work.

The original Umicom policy provides two equally important rules: update Framework at its authoritative checkout, then publish the consumer's gitlink; and do not copy Framework implementation files into every application. The Kernel remains independent of Framework because a bootable kernel must not need the user-space runtime.

## What Git stores

A normal file in Git's index uses a blob entry. A submodule entry is a **gitlink**, mode `160000`, containing an exact commit identifier from another repository. Git does not store the submodule's source files in the parent commit. A parent working-tree report can therefore show a changed child commit even while the child itself is clean.

Try these read-only commands from `C:\umicom\umicomOS`:

```powershell
Set-Location "C:\umicom\umicomOS"
git status
git ls-files --stage -- framework
git submodule status framework
git diff --submodule=log -- framework
git -C ".\framework" status --short
git -C ".\framework" log -1 --oneline
```

A line beginning with `160000` is the parent gitlink. A leading `+` from `git submodule status` means the checked-out child differs from the recorded commit; it does **not**, by itself, mean the child has unpublished work. A leading `-` indicates an uninitialised submodule, not a failed Framework build. Read all indicators before taking action.

## Framework fields and authority

`UmiVcsWorkingTreeSummary.child_commits` counts changed child revisions, while `dirty_children` records modified child worktrees. These are not interchangeable. A child may be clean at a newer HEAD yet require a parent gitlink commit. Alternatively, the parent may pin the expected child commit while the child contains uncommitted edits that must be preserved before synchronisation.

Framework already provides `include/umicom/repository/gitlink.h` and the native submodule lock contract. The lock operation stages exact checked-out submodule commit IDs. **It does not fetch, build, test, commit or push.** We therefore have to review the child revision first, and verify its build before staging its parent reference.

## A safe review order

1. Confirm the Framework child checkout is clean, or preserve any changes without deleting source.
2. Review the child commit: `git -C .\framework log -1 --oneline`.
3. If a remote update is intended, `git -C .\framework fetch origin main`, then compare `HEAD` with `origin/main` before selecting a checkout operation.
4. Build and test the parent against that exact child SHA.
5. Use Framework's existing `umicom repo verify .` and, only after review, `umicom repo lock .` where the native tool is installed.
6. Inspect `git diff --cached --submodule=log` before the parent commit.

**Do not** use `git submodule update --force`, `git clean -fd` or `git reset --hard` to solve a local-work collision. Those commands remove precisely the evidence a contributor needs to understand.

## Practical case: Umicom OS

Imagine Framework `main` receives six reviewed commits while Umicom OS still pins the previous SHA. The OS may continue to build correctly using its earlier pin; that is reproducibility, not negligence. Upgrading the OS to the later Framework is a separate integration change. It requires OS-specific tests, because a successful Framework unit test cannot prove that the OS GTK4 shell launches or that the new library is packaged correctly.

The parent commit message should describe the integration, such as `chore(os): synchronise Framework submodule after host tests`. Framework's own changes were committed separately in Framework. Commit ordering matters: the parent must never reference a Framework commit that has not yet been made accessible to other contributors.

## Review questions

**Why does `git add -A` in the parent not commit child source?** Because the parent tracks a gitlink, not nested source blobs. **What does a clean child prove?** Only that its checkout has no tracked or untracked changes according to the performed observation. **What proves the parent is ready to publish?** A tested child commit, reviewed parent gitlink, and a complete integration test result for that exact pair.

**Next:** Chapter 242 studies the matching ownership rule for compiler and build diagnostics.
