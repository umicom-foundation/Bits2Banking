# Major Update 33 — Instructor guide

**Audience:** learners who have completed Git basics and C23 source labs, plus Umicom contributors returning to professional multi-repository engineering.  
**Author:** Sammy Hegab · **Organisation:** Umicom Foundation.

## Intended delivery

Use Chapters 216–221 as the Git operations track, Chapters 222–226 as the native evidence track, and Chapter 227 as a two-hour assessed capstone. Learners should not need to stage or push real Framework changes merely to pass the class. Use prerecorded read-only evidence, a disposable practice repository, and the native fictional C23 demonstration when working with beginners.

| Session | Time | Activity | Observable result |
|---|---:|---|---|
| A: Git evidence | 60 minutes | Compare `git status`, HEAD, `main`, `origin/main`, parent gitlink | Evidence table identifies owners and limitations |
| B: Protect source | 60 minutes | Classify tracked, untracked, ignored and local-only work | Written preservation plan without destructive commands |
| C: Native contracts | 90 minutes | Build C23 lab; locate ownership, input validation and stale-proof tests | CTest results and explanation of lifetime invariants |
| D: Existing Framework APIs | 50 minutes | Read Framework VCS header and optional adapter source | No duplicated Git parser; correct ABI boundary |
| E: Capstone | 120 minutes | Simulate Framework-to-OS publication review | Explicit READY/BLOCKED/NOT RUN evidence decisions |

## Assessment criteria

A competent learner can: distinguish detached HEAD from a behind local branch; explain when a remote-tracking reference may be stale; read a 160000 gitlink; identify what a stash does *not* preserve; describe `UmiVcsWorkingTreeRead` ownership; build and run the named C23 tests; explain why a newer observation resets green build/test evidence; and list the exact tests required before recording a new OS gitlink.

## Teaching safeguards

Do not teach `git reset --hard`, `git clean -fd`, force-push or forced submodule update as generic repairs. Do not have participants type `git add -A` inside a valuable repository before they have reviewed all changes. Do not teach students that a deterministic model verifies actual Git remote state. Do not create Python or PowerShell scripts for tooling — compile native C23 and use the existing Framework.

The capstone rubric rewards accurate admissions of missing evidence. A correctly blocked publication is better engineering than a fabricated pass. Preserve every existing source file, author credit, comment and lesson during review. When a later implementation supersedes existing production code, retain the superseded logic for review under the established preservation policy rather than silently deleting it.

## Prepared answers to frequent misunderstandings

- **“`git pull` succeeded, so Framework is current.”** A parent pull advances the parent history; the child is pinned independently.
- **“`git push origin main` pushes the commit I can see.”** It pushes the local `main` reference, which may differ from detached HEAD.
- **“`stash --include-untracked` saves absolutely everything.”** It does not save ignored paths; a stash does not publish commits.
- **“The C23 tests passed, so OS boots.”** Native tests do not substitute for actual GUI startup or QEMU boot evidence.
- **“A valid SHA string is a verified Git commit.”** It is only syntactically valid until checked against the real repository.

## Instructors' evidence pack

Ask learners to submit a terminal transcript of read-only commands, native `ctest` results, a diagram of parent and child Git ownership, and an annotated decision report. Full end-to-end Framework integration is outside this learning batch; it should be developed in the Framework only after reviewing its existing native services.
