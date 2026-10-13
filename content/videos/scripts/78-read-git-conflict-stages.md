# Episode 78 — Read the three versions behind a Git conflict

**Bits to Banking · Umicom Foundation · Sammy Hegab**  
**Target duration:** 9 minutes · **Companion:** Chapters 228–231.  
**Recording environment:** Windows PowerShell, Git CLI, Beyond Compare; **no new scripts**.

## Teaching objective

Show why a conflict can be investigated safely without accepting either side, and demonstrate that the index preserves stage 1/2/3 blobs even when a working-tree file contains visible conflict markers.

## 00:00–01:00 — Opening example

**Narration:** "Two Umicom Bank developers edit ledger validation. One checks integer overflow, the other records rejected transfers for audit. Git cannot assume which change takes precedence. The correct outcome may be an integrated third implementation. Our job is to preserve the evidence before editing."

**Screen:** Show the `git-three-way-versions-update34.svg` diagram and briefly point to the base, ours and theirs panels. **On-screen rule:** *Never use a conflict-resolution button as a substitute for code review.*

## 01:00–03:10 — Inspect a safe practice merge

**Narration:** "We will reproduce a merge using two separate clones of a disposable bare repository, both on `main`. This avoids touching any real Umicom source." Open the practice exercise in Chapter 230 and run those commands in a throwaway directory under `$HOME\UmicomLearning`. Configure commit identity first if Git requires it.

After the intended merge conflict appears, show:

```powershell
git status
git diff --name-only --diff-filter=U
git ls-files --unmerged
```

**Point out:** Stage numbers appear alongside blob identifiers; a line of output is not a source-file copy in the working tree.

## 03:10–05:30 — Examine stages

```powershell
git show ":1:README.md"
git show ":2:README.md"
git show ":3:README.md"
```

**Narration:** "Stage 1 is the shared ancestor. Stage 2 is the checked-out side. Stage 3 is the incoming side. These labels change meaning across operations such as rebase; inspect the operation rather than trusting your memory."

Show `git-index-stages-update34.svg`, then the working-tree conflict markers. Explain that an add/add conflict can lack stage 1, and delete/modify can lack one descendant stage.

## 05:30–07:40 — What a correct resolution needs

**Narration:** "For a real banking module, read both files, list both business requirements, then combine them. Keep public APIs, important comments and superseded code for review under an explained disabled block when the project requires it."

Demonstrate selecting and editing `README.md` in the disposable repository only; show `git diff --check`, `git add README.md`, `git diff --cached -- README.md`, and `git status`. Do **not** merge application source automatically on screen.

## 07:40–09:00 — Recap and challenge

Ask: "Which stage represents the ancestor? Can a clean merge prove that an API was preserved? Why is `git add -A` risky if unrelated files are modified?" Show answers: stage 1; no; because all changes are staged. If keeping the practice repo, commit its reviewed resolution, but do not push to any real Umicom remote.

**Viewer assignment:** Return to Chapter 230, reproduce the conflict, record the three versions and explain the final resolution. This episode intentionally does **not** use Umicom Framework as a testing target.
