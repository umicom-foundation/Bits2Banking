# Episode 69 — Understand Git's commit graph with native C23

**Bits to Banking · Umicom Foundation**
**Related chapters:** [202 — C23 ancestry model](../../lessons/05-engineering/202-model-git-ancestry-in-c23.md), [203 — Tests and Framework VCS](../../lessons/05-engineering/203-verify-git-graph-and-framework-contracts.md)
**Suggested length:** 10–12 minutes.

## 00:00–01:30 — What is a commit graph?

**Show:** `git-commit-dag.svg` with two branches from a common ancestor and one merge with two parents.

**Narration:** “Git history is not sorted merely by dates. Each commit records its parents. The graph tells us whether one branch can advance directly to another by fast-forward. A person can draw this on paper before they learn the implementation.”

## 01:30–04:00 — Read the C23 contract

Open `labs/native/git-history/graph.h`. Introduce `BtbGitCommit`, `BtbGitGraph`, `BtbGitRelation` and `BtbGitSnapshot`. Explain caller-owned storage, the maximum of 64 entries, and why the code rejects a parent ID that has not already been added. These are educational integer labels, **not Git hashes**. No network, Git executable or Python runtime is involved.

## 04:00–06:30 — Trace the algorithm

Open `graph.c`. Show that `BtbGitGraphClassify` checks equality, whether local is an ancestor of remote, and whether remote is an ancestor of local. If neither is true, the tips diverged. Explain the fixed visited array and the parent walk that does not use recursion. Review the error contract: missing IDs leave caller outputs unchanged.

## 06:30–09:00 — Run the native tests

Use the CMake, build and CTest commands from Chapter 202. Demonstrate an explicit invalid-parent failure, a divergent pair, a two-parent merge and the 20,000-iteration test. Show GCC's compiler warning checks. Do not claim a Windows pass before demonstrating it on Windows; the initial documented runs were on Linux GCC and Clang with sanitizers.

## 09:00–11:30 — Connect to real Framework reuse

Run `btb-git-history-demo` and explain the detached HEAD versus local main scenario. Contrast the simple teaching graph with Framework's `UmiVcsWorkingTreeRead`, gitlink parser and native submodule-lock contract. The Framework has the actual repository inspection and process interfaces; this lab only makes the mathematics inspectable. Ask which component should own Git subprocess execution in a production Umicom app, and answer: the shared Framework service, not another application-local script.

## Closing exercise

Ask learners to add an independent root commit and predict a diverged result. They should first draw the graph, then write a deterministic C23 test, compile, and run it. Remind them that changing the actual repository requires separate review, backup, testing and approval.
