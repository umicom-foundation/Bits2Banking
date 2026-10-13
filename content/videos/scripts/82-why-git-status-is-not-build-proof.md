# Episode 82 — Why a Clean Git Status Is Not Proof of a Good Build

**Bits to Banking · Umicom Foundation · Sammy Hegab**  
**Companion chapters:** 240–241 and 244 · **Format:** 9–12 minutes  
**Production language:** UK English · **Implementation:** Git commands and C23 examples only.

## Learning outcomes

A viewer should be able to distinguish repository cleanliness, checkout identity, remote-tracking freshness, submodule gitlink state and evidence of a passing build. Demonstration paths are read-only; no destructive Git command is used.

## 00:00–01:15 — Opening case

**Visual:** Two windows labelled `Umicom-Applications` and `umicomOS`. Both contain a `framework/` directory. Above each, show the Framework commit that its parent repository records.

**Narration:** “These folders look alike, but they may be checked out at different commits. A clean Git status tells us something about the working tree. It does not tell us whether we tested the correct commit, whether the remote has changed, or whether another repository pins a different Framework revision.”

**On-screen:** The diagram `git-vcs-framework-ownership-update35.svg`.

## 01:15–04:00 — Examine Git references

Open a repository in PowerShell and execute these lines **one at a time**:

```powershell
git status
git branch --show-current
git rev-parse HEAD
git rev-parse main
git rev-parse origin/main
```

**Narration:** Explain that `HEAD` is the checkout, `main` is the local branch name, and `origin/main` is a local record of an upstream branch. A detached HEAD may have no branch name but still point at a valid commit. No comparison proves the remote has just been fetched.

## 04:00–06:30 — Inspect the child Framework

From an Umicom OS checkout:

```powershell
git ls-files --stage -- framework
git submodule status framework
git -C ".\framework" status --short
git diff --submodule=log -- framework
```

**Visual:** Highlight the mode `160000` entry separately from modified Framework source. Explain a changed gitlink versus changes inside the child. Neither situation is fixed by blindly resetting or forcing a checkout.

## 06:30–09:30 — Bridge to the real Framework API

Show `include/umicom/vcs/working_tree.h` and focus on `UmiVcsWorkingTreeRead`, `UmiVcsWorkingTreeDescribe` and `UmiVcsWorkingTreeDestroy`. The demonstration application should consume these existing APIs rather than parsing `git status` in its own C code. The summary distinguishes `detached`, `divergence_known`, `child_commits` and `dirty_children`.

**Narration:** “Read-only repository observation is a reusable Framework capability. A publishing decision is separate. A clean status cannot substitute for compilation or test evidence.”

## 09:30–End — Guided check

Ask viewers to record both parent and child SHAs for their own workspace, without modifying either repository. They should answer: which commit did we actually build, which Framework commit does OS pin, and which facts remain unknown?

**Safety note:** This episode neither commits nor switches branches. All commands are observational, and the viewer should preserve uncommitted work before any later submodule update.
