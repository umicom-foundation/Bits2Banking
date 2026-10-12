# Episode 66 — Why a Git push was rejected

**Bits to Banking · Umicom Foundation**
**Related chapters:** [192 — Divergent history](../../lessons/05-engineering/192-fetch-and-divergent-history.md), [194 — Detached HEAD](../../lessons/05-engineering/194-detached-head-and-push-identity.md)
**Suggested length:** 9–11 minutes · **Audience:** new Umicom contributors and maintainers.

## Learning promise

By the end, the viewer can identify `HEAD`, local `main` and `origin/main`, explain non-fast-forward rejection, and choose diagnostic commands before making any change. This is a recorded screen demonstration, not an automated script.

## 00:00–01:15 — Introduce the failure

**Show:** A neutral terminal reproduction of two real error messages: “not currently on a branch” and “non-fast-forward”. Do not reveal private repository credentials or personal files.

**Narration:** “These errors seem to contradict one another. One says there is no branch, and the other says the branch we tried to push is behind. Both can be correct. The first message is about the commit checked out by HEAD. The second is about the named local `main` branch that the push command selected.”

**Instructor note:** Never say that `git push origin main` pushes whatever commit happens to be checked out. It pushes the local ref named `main`.

## 01:15–03:15 — Draw three pointers

**Show:** `git-ref-identity.svg`. Label a small commit sequence A→B→C→D, then put local main at B, origin/main at D, and detached HEAD at D.

**Narration:** “Git stores commits as objects and uses references to identify tips. A submodule commonly checks out an exact commit, which gives us detached HEAD. The ordinary named main branch can stay at an older commit. If you push the name main, Git sends that older tip. This is not repaired by adding recurse-submodules=check.”

## 03:15–05:45 — Diagnose on screen

Use the commands on a prepared, disposable copy:

```powershell
git status --short --branch
git branch -vv
git log -1 --oneline HEAD
git log -1 --oneline main
git fetch origin main
git log -1 --oneline origin/main
git log --oneline origin/main..main
git log --oneline main..origin/main
```

**Narration:** “Notice that `fetch` does not merge or change our tracked working files, but it does refresh remote-tracking references and local object data. We are not fixing anything yet. We are recording evidence. The order of the two `git log A..B` commands matters: the right-hand side contributes commits we want to examine.”

## 05:45–08:30 — Choose a safe resolution

**Show:** a decision table. If working files are clean, no detached unpublished commits exist and main is simply behind, explain `git switch main` and `git pull --ff-only origin main`. Do not run these in a real user workspace in the demonstration. If the histories diverge or detached HEAD has unique commits, stop and inspect the source. Never show a force push as a normal repair.

**Narration:** “The goal is not to silence Git. It is to publish the correct history without losing an implementation that someone has been working on.”

## 08:30–10:30 — Verify learning

Ask viewers to predict what is pushed when HEAD=D and local main=B. Pause for an answer, then show the C23 graph demonstration from Chapter 202. The answer must identify B as the selected branch tip. End by showing the exact commands from the [Git command reference](../../lessons/05-engineering/git-operations-quick-reference.md) and reminding viewers to inspect files and tests before every commit.
