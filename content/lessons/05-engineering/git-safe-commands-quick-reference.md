# Git command quick reference — Umicom contributor edition

**Audience:** new contributors and experienced developers returning to Git after a break.  
**Principle:** identify the repository, inspect the state and preserve existing work before a modifying operation. Commands below are **interactive commands**, not a PowerShell script.

## A. Inspect (read-only unless indicated)

| Command | Why use it? |
|---|---|
| `git --version` | Confirm the Git executable is installed. |
| `git rev-parse --show-toplevel` | Identify the current repository root. |
| `git status --short --branch` | See active branch, tracked edits and untracked paths. |
| `git branch --show-current` | Show branch name; blank can indicate detached HEAD. |
| `git branch -vv` | See local branches and tracking information. |
| `git remote -v` | Verify remote names and destinations. |
| `git log --oneline --decorate --graph -12` | Read recent commit ancestry. |
| `git log --oneline origin/main..HEAD` | See commits reachable from HEAD but not remote main. |
| `git log --oneline HEAD..origin/main` | See commits reachable from remote main but not HEAD. |
| `git diff --stat` | Summarise unstaged tracked changes. |
| `git diff --cached --stat` | Summarise what is staged for the next commit. |
| `git diff --cached --check` | Check staged whitespace problems; does **not** test behaviour. |
| `git show --stat --oneline HEAD` | Describe the current commit and changed paths. |
| `git reflog -12` | Inspect recent local HEAD/reference movements. |
| `git stash list` | List stored local work snapshots. |
| `git submodule status framework` | Show the exact nested checkout's revision. |
| `git -C ".\framework" status --short` | Inspect the nested repository without leaving the parent. |

## B. Update remote knowledge or the local checkout

| Command | Effect / precondition |
|---|---|
| `git fetch origin main` | Downloads remote information; does not merge. |
| `git pull --ff-only origin main` | Fast-forwards a clean compatible branch; refuses diverged history. |
| `git submodule update --init framework` | Uses the parent's pinned submodule commit. |
| `git submodule update --init --remote framework` | Deliberately moves the child towards its tracked remote branch; may require parent commit. |
| `git switch main` | Changes checkout; inspect detached commits and local changes first. |
| `git restore --staged -- "PATH"` | Removes a path from staged changes without deleting local file edits. |

## C. Preserve work before a risky checkout

```powershell
git status
git fetch origin main
git log --oneline origin/main..HEAD
git stash push --include-untracked -m "backup: before synchronisation"
git stash list
git stash show --include-untracked --stat 'stash@{0}'
```

These commands are **not an instruction to stash blindly every day**. Review tracked/untracked changes and verify the stash succeeded. `--include-untracked` does not include ignored files. A detached unpublished commit needs a named reference such as a **uniquely named local tag** before switching away. Inspect saved changes against the target commit before considering `git stash apply`; keep the stash until reconciliation is proven.

## D. Stage and publish reviewed work (maintainers on `main`)

```powershell
git branch --show-current
git status
git add -A
git diff --cached --check
git diff --cached --stat
git diff --cached
git commit -m "docs: describe the verified change"
git push origin main
git status
```

Run **tests before committing**. Avoid `git add -A` when unrelated work or secrets are visible; stage only the approved paths instead. Never force-push to repair an ordinary non-fast-forward rejection.

## E. GitHub CLI

| Command | Purpose |
|---|---|
| `gh --version` | Confirm GitHub CLI is installed. |
| `gh auth login --hostname github.com --git-protocol https --web` | Begin browser-backed authentication. |
| `gh auth status` | Confirm the authenticated account. |
| `gh repo list` | Inspect repositories before creating one. |
| `gh repo create NAME --private --source . --remote origin --push` | Creates **a real remote repository** and publishes existing commits. |
| `gh repo view --web` | Open the current repository's GitHub page. |

## F. Emergency decision guide

**Detached HEAD?** Inspect `git log origin/main..HEAD`, status and any stash. Preserve unpublished commits before switching.  
**Push rejected?** Fetch, inspect ancestry, fast-forward if safe; do not force-push.  
**Submodule update blocked by files?** Preserve modified **and untracked** work, then compare with incoming content.  
**Staged too much?** Review `git diff --cached`, then `git restore --staged -- PATH`.  
**Published regression?** Review a `git revert` and tests instead of rewriting shared history.  
**Unsure which repository?** `git rev-parse --show-toplevel` comes first.

**Avoid as routine repair:** `git reset --hard`, `git clean -fd`, `git checkout -f`, `git submodule update --force`, `git push --force`. They can discard or conceal work. Their use requires a separately reviewed, explicit destructive operation.

## Official reference

- [Git documentation](https://git-scm.com/docs)
- [git-stash](https://git-scm.com/docs/git-stash)
- [git-submodule](https://git-scm.com/docs/git-submodule)
- [git-push](https://git-scm.com/docs/git-push)
- [git-restore](https://git-scm.com/docs/git-restore)
- [GitHub CLI manual](https://cli.github.com/manual/)

**Related lessons:** [182](182-git-working-tree-index-and-history.md) · [183](183-daily-umicom-git-workflow.md) · [184](184-git-remotes-fetch-pull-and-non-fast-forward.md) · [185](185-umicom-git-submodules-and-detached-head.md) · [186](186-stash-preserve-and-recover-work.md) · [187](187-github-cli-setup-and-repository-creation.md) · [188](188-read-history-diffs-and-provenance.md) · [189](189-review-recover-and-revert-safely.md) · [190](190-umicom-git-capstone-and-cheat-sheet.md).
