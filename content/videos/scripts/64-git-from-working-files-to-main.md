# Episode 64 — Git: From Working Files to Reviewed `main`

**Bits to Banking · Umicom Foundation · Presenter script**  
**Companion lessons:** [182](../../lessons/05-engineering/182-git-working-tree-index-and-history.md), [183](../../lessons/05-engineering/183-daily-umicom-git-workflow.md), [184](../../lessons/05-engineering/184-git-remotes-fetch-pull-and-non-fast-forward.md).  
**Run time:** approximately 12 minutes · **Tools:** Git and interactive PowerShell commands.

### 00:00–01:45 — The three places a change can live

**Visual:** `git-three-states.svg`.

**Narration:** “A file that exists on your computer is not necessarily in the next Git commit. The working tree holds your edits. The index is the proposed snapshot. A commit records the chosen snapshot in history. We will use a bank reconciliation note to see all three without touching a production repository.”

### 01:45–04:20 — Make two practice commits

**Terminal demonstration:**

```powershell
New-Item -ItemType Directory -Force "$HOME\UmicomLearning\git-evidence" | Out-Null
Set-Location "$HOME\UmicomLearning\git-evidence"
git init -b main
Set-Content -LiteralPath ".\BANK_RECONCILIATION.md" -Value "# Bank reconciliation evidence"
git status --short
git add BANK_RECONCILIATION.md
git diff --cached --check
git commit -m "docs: establish reconciliation evidence"
```

**Narration:** “After staging, inspect `git diff --cached`. The point is not to commit quickly; the point is to know exactly what will be committed.”

Add another line, inspect unstaged diff, stage, inspect staged diff, commit. Show `git log --oneline`.

### 04:20–06:00 — Separate local Git and remote GitHub

**Narration:** “`git commit` works without the internet. `git push` needs an authorised remote. `origin` is a conventional remote name, not a magic server. Verify `git remote -v` before sending work.”

**Visual:** `git-sync-graph.svg`. Explain fast-forward and divergence, without suggesting force pushes.

### 06:00–08:15 — The Umicom maintainer checklist

**Screen:** Show the relevant steps in `UPDATE_30_BUILD_TEST_AND_GIT.md` and the real repository naming convention. Do not run a production push during the recording unless this is an approved release demonstration.

**Narration:** “Confirm repository and branch, fetch, fast-forward when compatible, build, test, examine the staged patch, commit to main and push. If any step fails, stop and investigate. Git can record a deletion just as accurately as a feature; preservation still requires engineering review.”

### 08:15–09:50 — Decode a rejected push

**Visual:** Use a screenshot-style diagram showing `! [rejected] main -> main (non-fast-forward)`.

**Narration:** “This is a safety decision based on commit ancestry. First `git fetch origin main`, then inspect the graph and identify unpublished local commits. If histories diverge, `git pull --ff-only` will refuse; forcing the push would risk other work.”

### 09:50–12:00 — Learner challenge

**On-screen questions:** What does `git add -A` include? Why does `git diff --cached --check` not prove that a source refactor is correct? What does a blank `git branch --show-current` mean? What is the difference between `git fetch` and `git pull --ff-only`?

**Closing:** Direct-to-main internal maintainer policy does not remove the need for tests and careful review. External contributors use the approved fork and pull-request workflow.
