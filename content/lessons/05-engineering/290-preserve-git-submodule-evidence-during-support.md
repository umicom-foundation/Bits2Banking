# Chapter 290 — Preserve Git, submodule and backup evidence during support

**Bits to Banking · Advanced Engineering · Umicom Foundation**  
**Implementation language:** C23.  
**Prerequisite:** System Administration Chapters 1–36 and Engineering Chapter 287.

## Why this matters

A common source of support problems in the Umicom ecosystem is confusing the state of a **parent** repository with the state of its **Framework submodule**. Multiple parents can pin different Framework commits, while both depend on the same canonical remote repository. Reproducible diagnosis requires recording both revisions.

## Read-only Git inspection first

```powershell
Set-Location "C:\umicom\umicomOS"
git status
git submodule status framework
git -C ".\framework" status --short
git -C ".\framework" branch --show-current
git -C ".\framework" log -1 --oneline
```

If the branch name is blank, the submodule may be in detached HEAD. That is not itself an error, and it does not automatically mean commits are lost. If untracked files exist, record them and preserve them before any operation which might check out another revision. Never use `git reset --hard`, `git clean -fd` or `git push --force` as a routine training repair.

## Revision evidence comes before a repair plan

A successful `git pull --ff-only origin main` in the **parent** does not prove that an `--remote` update of Framework is safe. The parent pins an exact Git commit. The Framework repository can contain unpublished local commits or modified and untracked files. Inspect those states independently, then choose a reviewed update procedure. `umicom repo verify .` is a native Framework-owned read-only check; the native `umicom repo lock .` stages gitlinks but never fetches, commits or pushes for you.

## Keep backups separate from Git history

A Git commit protects tracked source revisions but is **not** a replacement for backups of private user files, ignored configuration or work that was never committed. A `git stash push --include-untracked` can preserve tracked and untracked *non-ignored* local changes temporarily, but it is not a durable off-machine backup and must be reviewed before reapplying. Treat a local stash as a Git maintenance aid, not the only backup of critical material.

## Case study

An engineer sees a Framework submodule checkout refusal because local source files would be overwritten. A safe handover identifies the parent, submodule, target commit, working-tree status and exact blocking paths. It does not attempt force checkout. The next authorised step is to review and preserve local work before synchronisation. Only after the intended Framework commit has been tested should the parent gitlink be committed.

## Exercises

1. Explain what a gitlink records and why it is separate from a Framework file diff.
2. Why can a clean `umicomOS` working tree coexist with a detached Framework HEAD?
3. Which command observes the current submodule commit without changing it?

**Answers:** A gitlink pins the child's commit; submodules commonly checkout the pinned SHA detached; use `git submodule status framework`.


## The Umicom Framework ownership rule

This chapter teaches a reproducible concept and, where applicable, uses a stand-alone learning-only model. Production tools must reuse Framework-owned VCS, build, diagnostics, process, security, storage and observability contracts before any new shared functionality is proposed. No PowerShell or Python implementation files are introduced.

## Safe completion criterion

Write one short paragraph distinguishing **observed facts**, **policy decisions** and **not-yet-verified outcomes**. Preserve the previous source and comments. If you cannot reproduce a result on your operating system, state the limitation rather than guessing.
