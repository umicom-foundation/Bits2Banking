# Episode 71 — Why a parent Git pull does not update Framework

**Bits to Banking · Umicom Foundation · Approximate running time: 14–16 minutes**  
**Source chapters:** [206](../../lessons/05-engineering/206-fast-forward-without-rewriting-history.md), [207](../../lessons/05-engineering/207-publish-a-tested-framework-gitlink.md), [209](../../lessons/05-engineering/209-troubleshoot-a-rejected-push.md).

## Learning outcome

Explain the relationship between a source repository, a submodule checkout and the parent gitlink, and diagnose detached HEAD and non-fast-forward errors without force pushing or deleting files.

### 00:00–02:00 — The recurring Umicom OS error

**Visual:** Terminal excerpt showing `git pull --ff-only origin main` succeeding in Umicom OS and a later Framework update refusing to overwrite local files.

**Narration:** “These commands operate on different repositories. The OS parent has one history; its Framework submodule has another. A successful parent pull can leave the child at an older, intentionally pinned revision. If the child contains local modifications, Git refuses to overwrite them. This refusal protects work.”

Use `git-framework-publish-sequence-update32.svg` to show the shared Framework source, the OS child checkout, and the parent gitlink.

### 02:00–05:00 — Inspect references, not assumptions

**Visual:** In the OS root, run:

```powershell
Set-Location "C:\umicom\umicomOS"
git status
git submodule status framework
git -C ".\framework" status
git -C ".\framework" branch -vv
```

**Narration:** “A detached HEAD often means the submodule is checked out at the exact commit recorded by its parent. That is normal. A detached local commit not yet published is different; switching blindly can lose the easiest reference to that work.”

Show `git -C .\framework log --oneline origin/main..HEAD` after `git fetch`. Explain that an empty result may indicate no local-only commits relative to the last fetched remote reference.

### 05:00–08:00 — Non-fast-forward is about ancestry

**Visual:** Render a local and remote commit graph. Demonstrate in a disposable clone:

```powershell
git fetch origin main
git log --oneline HEAD..origin/main
git log --oneline origin/main..HEAD
git merge-base --is-ancestor HEAD origin/main
```

**Narration:** “`git push origin main` pushes the local branch named `main`, not necessarily detached HEAD. If local `main` is behind the remote, Git rejects the update. The repair is to understand the history and integrate authorised work; it is not to force a remote branch backward.”

### 08:00–11:30 — The approved source-to-parent sequence

**Visual:** Walk through the Framework documentation `docs/SHARED_FRAMEWORK_SUBMODULE_UPDATE_POLICY.md` and highlight the sequence. Framework source is built, tested, committed and pushed once through the canonical checkout. A clean OS Framework child fast-forwards to that published revision. OS is then built and tested. The native Framework command `umicom repo verify .` previews gitlink changes; `umicom repo lock .` stages the parent gitlink. The OS parent commit is separate.

**Narration:** “`repo lock` cannot fetch, compile or publish Framework. It only records the current child HEAD in the parent index. We need separate evidence that the chosen child commit is available remotely.”

### 11:30–14:30 — Safe recovery and recap

**Visual:** Show `git stash list`, `git status --short`, and the precise staging review commands. Explain that a stash including untracked files is temporary and does not include ignored files. Avoid using `reset --hard`, `clean -fd` or force-push in the demonstration.

**Assessment prompt:** “The Framework child is current but the OS remote still references the previous SHA. Which repository needs a new commit?” Pause. Answer: “The OS parent needs its reviewed gitlink commit and push.”

**Closing:** “Git keeps histories independent. A dependable release connects them through published commits and tested pins.”
