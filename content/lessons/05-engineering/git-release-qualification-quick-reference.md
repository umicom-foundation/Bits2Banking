# Git release qualification — Umicom quick reference

**Bits to Banking · Umicom Foundation · Maintainer checklist**  
**Purpose:** A compact command reference supplementing Chapters 204–215. PowerShell appears only as interactive commands; no `.ps1` file is required.

## Know the exact repository before changing it

```powershell
Get-Location
git status
git branch --show-current
git remote -v
git log -1 --format=%H
```

A `git status` result for Umicom OS does **not** describe all nested Framework files. A detached HEAD inside a submodule is normal until you need to publish Framework source. Do not push from a detached checkout without understanding the unpublished history.

## Fetch, compare, then fast-forward

```powershell
git fetch origin main
git log --oneline HEAD..origin/main
git log --oneline origin/main..HEAD
git merge-base --is-ancestor HEAD origin/main
```

If the last command has exit code zero and the worktree is clean, `git merge --ff-only origin/main` can advance local `main`. If the histories diverge, review unique commits. Do not force push or hard reset merely to dismiss the error.

## Stage, review, commit, push to main

```powershell
git status
git branch --show-current
git add -A
git diff --cached --check
git diff --cached --stat
git diff --cached --name-status
git commit -m "feat(learning): explain verified Umicom release workflows"
git push origin main
git status
```

`git add -A` stages all detected changes in the current repository. The sample message must match the actual reviewed changes. **Do not commit** if compilation, required tests, documentation checks or the staged diff have not been verified. An empty staged diff means there is nothing to commit.

## Framework child and parent pin are separate

```powershell
Set-Location "C:\umicom\umicomOS"
git submodule status framework
git -C ".\framework" status
git -C ".\framework" log -1 --format=%H
git ls-files --stage framework
git diff --cached --submodule=log
```

After Framework source is committed, pushed and tested, a clean OS child can fast-forward. Build/test OS, use the existing native Framework `umicom repo verify .` and `umicom repo lock .`, and review the staged parent gitlink before committing OS itself. **Never** copy the Framework source into another checkout as a shortcut.

## Before publishing an update

Verify that the exact source SHA is known, local branch is `main`, remote ancestry was refreshed, the worktree and index contain only intended changes, all required build/tests/docs passed, and every submodule SHA is both **published** and **tested**. If evidence is missing, report `NOT RUN` or `BLOCKED`, not `PASSED`.

## Commands deliberately omitted

This reference does not offer `reset --hard`, `clean -fd`, forced checkout or force push as routine fixes. Those operations may discard source, complicate recovery or rewrite shared history. Use the professional Git chapters for conflict investigation and preservation.
