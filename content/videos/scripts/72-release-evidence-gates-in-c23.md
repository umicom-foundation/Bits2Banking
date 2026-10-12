# Episode 72 — Build and test release evidence gates in C23

**Bits to Banking · Umicom Foundation · Approximate running time: 15–18 minutes**  
**Source chapters:** [213](../../lessons/05-engineering/213-build-a-native-release-evidence-model.md), [214](../../lessons/05-engineering/214-test-fail-closed-release-gates.md).  
**Source:** `labs/native/git-release-evidence/gate.h`, `gate.c`, `test_gate.c`, `gate_demo.c`.

## Learning outcome

Read and test a C23 failure-atomic release-decision API. Distinguish evidence from permission, invalid input from blocked qualification, and a teaching-only gate from Framework's real repository services.

### 00:00–02:30 — The decision boundary

**Visual:** `release-evidence-gate-update32.svg` with observation, evidence snapshot, gate and human authorisation.

**Narration:** “Git status is a fact. A passing test is a fact. A release decision combines multiple facts under an explicit policy. We should not bury that policy in a GTK4 button handler or an unreviewed automation script. This C23 laboratory isolates the decision so it can be tested deterministically.”

Explain that real Git observation and repository control already belong to Umicom Framework; this lab never reads a repository or contacts GitHub.

### 02:30–06:00 — Read the C23 contract

**Visual:** `gate.h`. Identify `BtbGateAction`, `BtbGateProof`, `BtbGateSnapshot` and `BtbGateReport`.

**Narration:** “A single Boolean `ready` cannot explain three simultaneous problems. The report therefore retains an issue bitmask and a count. The caller owns both input and output. The evaluator borrows the input only for the duration of the call. On invalid evidence, it leaves the output unchanged, which is an important memory-safety and state-management contract.”

Show the fixed-length child SHA buffers. A commit ID must have forty hexadecimal digits and a terminator in this lesson's model. Mention that a real Git implementation can have different object formats; this lab intentionally models the currently expected SHA-1-style gitlinks, not a universal future-proof Git object-ID parser.

### 06:00–10:30 — Build and test

**Visual:** Run PowerShell commands that launch CMake/Ninja/CTest directly. Do not create a `.ps1` or Python file:

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
cmake -S ".\labs\native\git-release-evidence" -B ".\output\learning-build\git-release-evidence" -G Ninja -DBUILD_TESTING=ON
cmake --build ".\output\learning-build\git-release-evidence" --parallel 2
ctest --test-dir ".\output\learning-build\git-release-evidence" --output-on-failure
```

**Narration:** “We test commit, push and pin separately. A safe-looking worktree does not make an unpublished child commit acceptable. A passing Framework test does not qualify a different Framework SHA. An index full of unrelated changes is not a reviewed parent pin.”

### 10:30–14:00 — Make the refusal visible

**Visual:** Run `btb-git-release-gate-demo.exe`. Highlight the `READY` state followed by the `BLOCKED` state after a modelled remote change. Open `test_gate.c` and show a malformed SHA test, an unpublished-child test and the 100,000 deterministic negative mutations.

**Narration:** “A malformed snapshot returns INVALID without replacing the previous report. A legitimate request with insufficient evidence returns BLOCKED with precise reasons. Neither result changes Git. The model cannot know whether a contributor lied about running the tests. That obligation belongs to trusted evidence collection and human review.”

### 14:00–17:00 — Apply the architecture

**Visual:** Show the real Framework `UmiVcsWorkingTreeRead` signature and the `umicom repo verify/lock` workflow.

**Narration:** “Future integrations should use the Framework source-of-truth APIs to collect data, feed an application-owned policy decision, display reasons and only enable approved actions. This sample is not production enforcement. There is no unattended push, no duplicated Git parser and no new scripting runtime.”

**Assessment prompt:** “What should happen when tests have not run but the branch is up to date?” Answer: “BLOCKED, with a tests-not-run reason.”
