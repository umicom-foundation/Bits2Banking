# Git recovery and three-way conflict review — quick reference (Update 34)

**Bits to Banking · Umicom Foundation · Sammy Hegab**  
Use interactive PowerShell **commands**, not a `.ps1` script. Work in the correct repository. Commands below operate on the current directory unless `git -C` supplies a child path.

| Purpose | Read-only or reviewed command | Important caveat |
|---|---|---|
| Which repository? | `git rev-parse --show-toplevel` | A submodule is a distinct repository. |
| Current checkout? | `git status` and `git branch -vv` | Detached HEAD can be normal in a submodule. |
| Actual checked-out commit? | `git rev-parse HEAD` | HEAD is not necessarily local main. |
| Local vs remote history? | `git fetch origin main` then `git rev-list --left-right --count HEAD...origin/main` | Fetch updates tracking refs; it does not merge. |
| Common ancestor? | `git merge-base HEAD origin/main` | Ancestry is not source correctness. |
| Where are unresolved paths? | `git diff --name-only --diff-filter=U` | The index may contain extra stages. |
| Read the three versions | `git show :1:path`, `:2:path`, `:3:path` | Some stages absent for add/add or delete/edit. |
| Inspect stashes | `git stash list`, `git stash show --include-untracked --stat 'stash@{0}'` | The stash may not contain ignored files. |
| Recover local history reference | `git reflog show --date=iso --all -25` | Reflog is local and retention-limited. |
| Inspect OS Framework pin | `git ls-files --stage framework` | Mode `160000` identifies a gitlink. |
| Inspect child HEAD | `git -C '.\framework' rev-parse HEAD` | Different from parent gitlink. |
| Inspect source changes | `git diff --stat`, `git diff --cached --stat` | Unstaged and staged are different. |
| Check for accidental deletions | `git diff --cached --name-status` | Review before commit. |
| Check a proposed parent pin | `git diff --cached --submodule=log` | Inspect the specific selected Framework SHA. |
| Native Framework preflight | `umicom repo verify .` | Dry-run observation; no fetch or commit. |
| Native Framework pin staging | `umicom repo lock .` | Stages current child HEAD; does not pull/push. |

## Main-only commit sequence — after tests and a staged review

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
git status
git branch --show-current
git add -A
git diff --cached --check
git diff --cached --stat
git diff --cached --name-status
git commit -m "feat(learning): add Git merge recovery and C23 three-way lab"
git push origin main
git status
```

`git add -A` stages all changes in the current repository, including deletions. If that is not the intended scope, stop and review or stage only the selected files before committing. **Do not force-push**, hard reset or clean to hide a failed merge or rejected push.

## Preserve-before-checkout checklist

- Record `git status`, `git branch -vv` and current SHA.
- Record local-only commits: `git log --oneline origin/main..HEAD`.
- Review tracked changes, untracked files, ignored work products and existing stashes.
- If a stash is appropriate, save with `--include-untracked`, then **verify** its contents before updating. Never assume all work is covered automatically.
- Compare recovered source against the newer Framework implementation; retain approved logic, headers, licences and comments.
- Qualify the precise Framework revision, then the parent OS/Applications integration, **before** pushing the parent gitlink.

**Boundary:** This document is a command reference; it makes no changes itself. The accompanying C23 teaching lab never accesses `.git` or invokes Git.
