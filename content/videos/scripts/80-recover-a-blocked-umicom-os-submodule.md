# Episode 80 — Recover a blocked Umicom OS Framework submodule

**Bits to Banking · Umicom Foundation · Sammy Hegab**  
**Target duration:** 11 minutes · **Companion:** Chapters 235–237.

## 00:00–01:45 — Reproduce the conceptual failure

**Narration:** "Umicom OS has its own Git history and a Framework gitlink. The Framework child is a separate checkout that may have local edits, a detached HEAD or a branch behind GitHub. Running `git submodule update --remote` when files would be overwritten must stop. That stop protects work; it is not a defect to bypass."

**Screen:** Display `git-framework-gitlinks-update34.svg`. Clearly distinguish `C:\umicom\Umicom-Applications\framework` (source owner) and `C:\umicom\umicomOS\framework` (consumer checkout).

## 01:45–04:20 — Read-only preflight

```powershell
Set-Location "C:\umicom\umicomOS"
git status
git ls-files --stage framework
git submodule status framework
git -C ".\framework" status --short
git -C ".\framework" branch -vv
git -C ".\framework" log --oneline origin/main..HEAD
git -C ".\framework" stash list
```

**Narration:** "We need five distinct answers: parent pin, checked-out child commit, current branch or detached state, uncommitted changes, and unpublished child commits. If any is unknown, we do not switch or reset."

## 04:20–06:25 — Preservation and ancestor investigation

Explain what `git stash push --include-untracked -m 'backup: ...'` saves and what it does **not** save. Verify a stash with `git stash show --include-untracked --stat`. An existing stash must not be overwritten or automatically popped; a child with unpublished commits requires separate SHA preservation.

```powershell
git -C ".\framework" fetch origin main
git -C ".\framework" rev-list --left-right --count HEAD...origin/main
git -C ".\framework" log --oneline --left-right HEAD...origin/main
```

Interpret behind-only versus divergence, using sample counts clearly labelled as examples. `git fetch` updates remote-tracking information but does not merge local source.

## 06:25–08:50 — Only after a clean approved checkout

Explain the conditional choice to `git switch main` and `git pull --ff-only origin main` **when the child has no unpublished work**. Do not run these on a production checkout during a recording without an approved preservation plan.

Show Framework-owned `umicom repo verify .`, then `umicom repo lock .`, with `git diff --cached --submodule=log`; explain that these operations do not fetch, test or push.

## 08:50–11:00 — Qualify the parent

After the Framework revision is tested with OS headless/GTK4 targets, review the staged OS gitlink and publish **the OS parent** separately. Show `git add -A`, `git diff --cached --check`, `git diff --cached --stat`, `git commit -m 'chore(os): pin tested Umicom Framework commit'`, and `git push origin main`. Explain why blindly pushing the detached child is not equivalent.

**Viewer assignment:** Produce a three-SHA inventory of a read-only checkout and mark source changes, child revision and parent gitlink individually. **Do not push any changes merely to complete the exercise.**
