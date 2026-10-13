# Git command reference — inspect, preserve, qualify, publish

**Bits to Banking · Umicom Foundation · Author: Sammy Hegab**

These are commands to **type interactively into PowerShell**; this is not a `.ps1` script. Run each command from the correct repository. Read the effects before using write commands. For production Umicom repositories, the normal policy is direct commits to `main`, after build/test/review; external contributor pull requests are a separate collaboration workflow.

| Question | Command | What it proves / caution |
|---|---|---|
| Where am I? | `Get-Location` | PowerShell directory, not necessarily repository root |
| Which repository? | `git rev-parse --show-toplevel` | Checkout root only |
| What changed? | `git status --short` | Index/worktree paths; not remote freshness |
| What is staged? | `git diff --cached --stat` | Review scope, not correctness |
| Show unstaged content | `git diff` | Current unstaged diff |
| Show staged content | `git diff --cached` | Candidate commit contents |
| Check whitespace | `git diff --cached --check` | Whitespace issues, not source correctness |
| Which branch? | `git branch --show-current` | Blank is normal on detached HEAD |
| Current commit | `git rev-parse HEAD` | Full checked-out object ID |
| Local main | `git log -1 --oneline main` | May differ from HEAD |
| Remote-tracking main | `git log -1 --oneline origin/main` | Only last fetched view |
| Refresh remote refs | `git fetch origin main` | Local fetch; does not change tracked source files |
| Local-only commits | `git log --oneline origin/main..HEAD` | Critical before switching detached HEAD |
| Ahead/behind | `git rev-list --left-right --count HEAD...origin/main` | Graph reachability, not code compatibility |
| Compare both sides | `git log --oneline --left-right HEAD...origin/main` | Split histories |
| Stashes | `git stash list` | Local saved working-tree snapshots |
| Inspect stash | `git stash show --include-untracked --stat 'stash@{0}'` | Not a guarantee all ignored files were saved |
| Recent HEAD movement | `git reflog --date=iso -12` | Local reflog only |
| OS parent gitlink | `git ls-files --stage framework` | Mode 160000 and pinned child SHA |
| Submodule checkout | `git submodule status framework` | Child relative to parent gitlink |
| Child changes | `git -C framework status --short` | Child tree, independent of parent |
| Parent pointer diff | `git diff --cached --submodule=log` | Staged gitlink review |
| Framework native preview | `umicom repo verify .` | Read-only repository lock plan, if installed |
| Framework native stage | `umicom repo lock .` | Stages gitlinks; DOES NOT pull, commit or push |

## Standard Umicom Bits2Banking publication commands

Only after the new lessons have been merged, the C23 laboratory tested, current `main` confirmed and the staged file list reviewed:

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
git status
git branch --show-current
git add -A
git diff --cached --check
git diff --cached --stat
git commit -m "feat(learning): add Framework Git evidence and native C23 observation timeline"
git push origin main
git status
```

`git add -A` stages deletions too. If the stage lists unexpected removals, do not commit until those are reconciled. Do not treat `git push` errors as a request to force-push. No Python or PowerShell implementation scripts are introduced by this update.

## Never use as a generic repair

Do not run `git reset --hard`, `git clean -fd`, `git push --force` or `git submodule update --force` to silence status warnings. Their destructive effects can be appropriate in deliberately disposable sandboxes, but they conflict with the Umicom preservation-first rule when applied to active source without complete review and approval.
