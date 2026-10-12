# Episode 73 — Publish and qualify an Umicom release safely

**Bits to Banking · Umicom Foundation · Approximate running time: 15–18 minutes**  
**Source chapters:** [210](../../lessons/05-engineering/210-release-tags-provenance-and-qualification.md), [215](../../lessons/05-engineering/215-complete-umicom-release-qualification-capstone.md).

## Learning outcome

Create a reviewable release evidence record, distinguish repository history from runtime qualification, and carry out the standard Git add/commit/push sequence without accidentally publishing another repository's files.

### 00:00–02:30 — A successful push is not a deployment

**Visual:** Side-by-side panels labelled Source SHA, Build, Tests, Documentation, Distribution and Approval.

**Narration:** “A Git push tells us that the remote accepted a ref update. It does not tell us whether a Windows application starts by double-click, whether a C23 test passed, whether Umicom OS boots under QEMU, or whether a website is actually live. Each claim needs its own evidence. ‘Not run’ is not the same as ‘passed’.”

Use `git-release-evidence-map-update32.svg` to connect source identity to independent validation records.

### 02:30–06:00 — Verify source and binaries

**Visual:** Show `git log -1 --format=%H`, `git status`, a CMake configure command and the CTest summary from a real disposable laboratory build.

**Narration:** “Record the full source identifier, exact toolchain and configuration. Keep logs attributable to a source revision. A binary checksum provides byte identity for a downloaded package, but does not by itself prove who produced it. We do not publish secrets in build logs.”

### 06:00–10:00 — Commit only the intended repository

**Visual:** Bits2Banking terminal. Review changes before staging. Then show the standard sequence:

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
git status
git branch --show-current
git add -A
git diff --cached --check
git diff --cached --stat
git commit -m "feat(learning): document native release qualification"
git push origin main
```

**Narration:** “These are *commands*, not a script. We do not perform the commit or push until the source diff and tests are reviewed and we are on the correct `main`. `git add -A` stages everything in the current repository; it cannot decide what belongs in this batch.”

For recording, execute write commands only in an authorised disposable practice repository unless there is a real, approved change to publish.

### 10:00–13:00 — When Framework is involved

**Visual:** Show canonical Framework source and two parent gitlinks.

**Narration:** “The Framework source commit must be published first. The OS child is then updated to that revision, OS is built and tested, and the parent gitlink is committed separately. Native `umicom repo verify .` previews the lock; `umicom repo lock .` stages the reference. It does not fetch, build or push. The boot tests remain independent of host CTest.”

### 13:00–16:30 — Tag and handoff after qualification

**Visual:** Demonstrate annotated tags only inside a disposable training repository. Show one page with full SHAs, binary hashes, test results, Git diff review and unresolved risks.

**Narration:** “A tag identifies a particular commit; a report explains why it was considered ready. Never retag a published release casually. If any required gate failed, preserve the evidence, correct the defect and requalify rather than editing the report to claim success.”

**Assessment prompt:** “An Umicom OS headless build passes, but QEMU boot was not executed. Is the diskless image qualified?” Answer: “No. Host build and boot are different acceptance gates.”

**Closing:** “The discipline is straightforward: know which repository owns the work, preserve its history, verify the exact revision, then publish only what has been reviewed.”
