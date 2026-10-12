# Git command reference — Umicom Framework, Applications, OS and Bits2Banking

**Audience:** Umicom maintainers and new contributors. **Default policy:** direct commits to `main` after source review and tests; no additional internal branches. **Implementation language policy:** C23 and Assembly; these are interactive PowerShell **commands**, not `.ps1` scripts.

## First inspect the repository you are in

```powershell
Get-Location
git rev-parse --show-toplevel
git status
git branch --show-current
git remote -v
git log -1 --oneline
```

An empty branch name indicates detached HEAD, which is common in submodules. Do not assume `git push origin main` will push the checked-out commit.

## Daily Bits2Banking commit (after review and successful tests)

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
git status
git branch --show-current
git add -A
git diff --cached --check
git diff --cached --stat
git diff --cached --name-status
git commit -m "feat(learning): add advanced Git and C23 ancestry training"
git push origin main
git status
```

`git add -A` stages deletions as well as additions. If the staged list contains unrelated changes, stop and review or unstage selectively before committing. Confirm you are on `main`, that the remote has not advanced unexpectedly and that no secrets or build artefacts are staged.

## Canonical Framework commit — only when Framework implementation actually changed

```powershell
Set-Location "C:\umicom\Umicom-Applications\framework"
git status
git branch --show-current
git add -A
git diff --cached --check
git diff --cached --stat
git commit -m "feat(framework): describe the reviewed shared change"
git push origin main
```

Use this only after the Framework-specific build/test acceptance; it is **not** required for a Bits2Banking-only learning ZIP. When Framework is unchanged, do not create an empty or placeholder commit.

## Umicom OS: inspect/update the child, then commit the parent pointer

```powershell
Set-Location "C:\umicom\umicomOS"
git submodule status framework
git -C ".\framework" status
git -C ".\framework" log --oneline origin/main..HEAD
```

If the Framework child has unsaved files or unpublished detached commits, stop and preserve them. Only once it is safe and you deliberately want the latest Framework tip:

```powershell
git submodule update --init --remote framework
git submodule status framework
git diff --submodule=log -- framework
```

After the required OS build/tests and optional native `umicom repo verify .` / `umicom repo lock .` check:

```powershell
git add -A
git diff --cached --check
git diff --cached --stat
git diff --cached --submodule=log
git commit -m "chore(os): record tested Framework gitlink"
git push origin main
```

This publishes an OS **gitlink**; the Framework commit it references must already be published. Use direct-to-main only when the parent branch really is `main`.

## Fetch and diagnose a rejected push

```powershell
git status --short --branch
git fetch origin main
git log -1 --oneline HEAD
git log -1 --oneline main
git log -1 --oneline origin/main
git log --oneline origin/main..main
git log --oneline main..origin/main
git rev-list --left-right --count main...origin/main
```

If local `main` is **behind only** and clean, `git switch main` followed by `git pull --ff-only origin main` may be correct. If the histories diverged, require review. Never use force-push to paper over an unknown divergence.

## Preserve tracked and untracked work

```powershell
git status --short
git log --oneline origin/main..HEAD
git stash push --include-untracked -m "backup: before reviewed sync"
git stash list
git stash show --include-untracked --stat 'stash@{0}'
```

Stash does not include ignored files and does not rescue detached-only commits. Review an existing stash carefully before `git stash apply`. Avoid `git stash pop`, `git reset --hard`, `git clean -fd` and forced submodule updates as default recovery tools.

## Investigate history

```powershell
git log --graph --decorate --oneline --all -20
git reflog --date=iso -20
git diff --name-status <BASE_COMMIT> <TARGET_COMMIT>
git show --stat <COMMIT_ID>
```

Replace placeholders with actual commit identifiers from the repository. These commands provide evidence; they do not build or validate source.

## A one-minute decision table

| Observed condition | Do this before changing anything |
|---|---|
| Detached HEAD | Inspect `HEAD`, `main`, `origin/main` and unpublished commits. |
| Untracked files blocking a submodule update | Preserve and review them; a tracked-only stash is insufficient. |
| Push rejected non-fast-forward | Fetch; compare commit graph in both directions. |
| Parent reports `framework (new commits)` | Inspect the child HEAD and parent mode-160000 gitlink. |
| Build fails after gitlink update | Do not publish parent integration; inspect target revisions and build evidence. |
| Accidental staged deletion | Review `git diff --cached --name-status` and unstage the unintended path. |

**Related:** [Complete Update 31 learning path](update-31-learning-path.md), [native C23 ancestry lab](202-model-git-ancestry-in-c23.md) and Umicom Framework's `docs/SHARED_FRAMEWORK_SUBMODULE_UPDATE_POLICY.md`.
