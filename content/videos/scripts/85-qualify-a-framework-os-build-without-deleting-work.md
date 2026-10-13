# Episode 85 — Qualify an Umicom Framework and OS Build Without Deleting Work

**Bits to Banking · Umicom Foundation · Sammy Hegab**  
**Companion chapters:** 248–251 · **Format:** 13–16 minutes  
**Implementation:** Git, Framework C23 APIs, CMake and CTest.

## Learning outcomes

Demonstrate the safe publication sequence across Framework and its consumers, including gitlink review, actual build/test evidence, and the standard direct-to-main Git commands.

## 00:00–02:20 — Establish the scenario

Two contributors have Framework work; Umicom OS still pins an older Framework commit. One attempts `git submodule update --remote`, and Git refuses because tracked and untracked source would be overwritten.

**Narration:** “Git is protecting valuable work. A conflict is not permission to delete code. Our first objective is to determine what exists locally, what is already upstream, and what the parent repository actually references.”

**Visual:** `umicom-change-verification-update35.svg`.

## 02:20–06:20 — Preserve and inspect

```powershell
Set-Location "C:\umicom\umicomOS"
git status
git -C ".\framework" status --short
git -C ".\framework" log -1 --oneline
git submodule status framework
```

Discuss why dirty files, untracked paths, detached HEAD and a changed parent gitlink are different facts. If source needs temporary protection, use a reviewed stash or commit; do not silently discard the work. The live demonstration should remain read-only unless a disposable training clone is explicitly prepared.

## 06:20–09:40 — Integrate the correct Framework revision

Explain the approved path: commit Framework in the authoritative `Umicom-Applications\framework` checkout on `main`; build and test it; then synchronise the separate OS Framework checkout. Build/test Umicom OS against the candidate child SHA; run Framework's `umicom repo verify .` and `umicom repo lock .` where installed; inspect staged gitlink changes.

Be explicit: **repo lock stages a pointer; it does not pull, commit or push**. A Framework unit-test pass is not an OS launch acceptance. For the Kernel, compile and QEMU boot validation are separate evidence.

## 09:40–13:30 — Final staging commands

From the correctly selected repository on its established `main` branch, after acceptance:

```powershell
git status
git branch --show-current
git add -A
git diff --cached --check
git diff --cached --stat
git commit -m "chore(os): qualify updated Framework dependency"
git push origin main
git status
```

Explain `git add -A` thoroughly: it stages modifications, additions and deletions in **that repository**. Review the staged diff and exclude unrelated work before committing. Never force-push merely because the remote rejected the change. Fetch and compare histories first.

## End — Learner assessment

Ask the viewer to produce a one-page evidence report containing the Framework child SHA, Umicom OS parent SHA, exact build profile, test counts, observed problems, not-run gates, and publication order. The correct outcome may be “stop and preserve work”. That is a successful engineering judgement when evidence is incomplete.

**Closing:** “The objective is not a green Git command. It is a traceable, tested change that preserves the functionality we already built.”
