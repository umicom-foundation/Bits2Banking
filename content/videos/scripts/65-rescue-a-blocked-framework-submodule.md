# Episode 65 — Rescue a Blocked Umicom Framework Submodule

**Bits to Banking · Umicom Foundation · Presenter script**  
**Companion lessons:** [185](../../lessons/05-engineering/185-umicom-git-submodules-and-detached-head.md), [186](../../lessons/05-engineering/186-stash-preserve-and-recover-work.md), [189](../../lessons/05-engineering/189-review-recover-and-revert-safely.md), [190](../../lessons/05-engineering/190-umicom-git-capstone-and-cheat-sheet.md).  
**Run time:** approximately 13 minutes · **Tools:** Git and interactive PowerShell commands.

### 00:00–02:15 — The real failure message

**Screen:** A prepared text capture (not a live destructive operation):

```text
error: Your local changes ... would be overwritten by checkout
error: The following untracked working tree files would be overwritten
fatal: Unable to checkout ... in submodule path 'framework'
```

**Narration:** “Git has identified two kinds of protected work: modifications to tracked files and new untracked files. The correct first action is not to force the checkout. Our engineering policy says to preserve the existing source, including previous comments and functionality.”

### 02:15–04:10 — Know the parent and the child

**Visual:** `git-submodule-graph.svg`.

**Narration:** “Umicom OS has its own history. Framework has another history. An OS commit stores an exact gitlink pointing to the Framework commit it expects. The newest Framework revision is not automatically the right dependency for the OS build.”

**Read-only terminal:**

```powershell
Set-Location "C:\umicom\umicomOS"
git submodule status framework
git -C ".\framework" status --short --branch
git -C ".\framework" log --oneline origin/main..HEAD
```

### 04:10–06:30 — Preserve the work

**Visual:** `git-safe-recovery.svg`.

**Narration:** “Inspect the tree and stash list. If there are uncommitted tracked and ordinary untracked files, `git stash push --include-untracked` can preserve them locally. If there are unpublished commits in detached HEAD, give the commit a unique local rescue tag before changing checkouts. These are two separate problems; a stash does not automatically move branch pointers.”

**Teaching emphasis:** Check the stash operation succeeded, and remember that ignored files are not included.

### 06:30–08:45 — The difficult part is comparison

**Narration:** “After a successful, non-forced update, do not immediately run `git stash pop`. The incoming Framework commits may already include some or all of the work you saved. Compare saved tracked and untracked changes with the target revision using Git and Beyond Compare. Restore only what is missing; do not silently reintroduce older code.”

**Screen:** Read-only commands `git stash list` and `git stash show --include-untracked --stat 'stash@{0}'`.

### 08:45–10:45 — Explain detached HEAD and non-fast-forward

**Narration:** “`git push` failed because HEAD was detached. `git push origin main` was rejected because the **local branch named `main`** was behind the remote. Those are different questions about different references. Never attempt a force push as the default response.”

Show a two-branch ancestry diagram, then display the safe `fetch` + inspect commands from Chapter 184.

### 10:45–13:00 — Recovery and acceptance

**Narration:** “Publish approved Framework implementation first, then test and commit Umicom OS's gitlink, then publish the teaching update from Bits2Banking. Keep test evidence connected to the commit actually tested. Do not create a PowerShell or Python script to hide the sequence: explicit commands show exactly which repository is being changed.”

**Final question:** Why must Umicom OS update and commit the Framework gitlink even after Framework `main` has been pushed successfully? **Because the parent repository's dependency revision is a separate committed fact.**

**Safety closing:** This video teaches inspection and preservation; use a throwaway practice repository for any command that would modify history or discard files.
