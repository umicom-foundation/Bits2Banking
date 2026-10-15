# Teaching work dispatch and Git

**Audience:** instructors, mentors and self-study contributors to Umicom Foundation. This guide extends, rather than replaces, the earlier source-led lessons.

## Teaching expectations

Use real application cases, such as an Umicom Bank cash-position report, Umicom Studio source indexing and the OS → Framework dependency. Learners should justify each command or state transition rather than memorise terminal output. Avoid live trading, payments or destructive Git operations during exercises. Use separate practice Git repositories when testing recovery behaviour.

## Chapters 177–181: reference answers

**177 — Who owns a request?** Before submission, the caller owns the input byte range. After `BtbWorkSubmit` succeeds, the existing work queue owns its private copy; the original buffer may be modified or released. `BtbWorkAcquire` lends a const pointer to the synchronous processor. `BtbDispatchReceive` copies a receipt and releases the original work slot. **Do not** hold the borrowed pointer after release.

**178 — Why compose?** The handoff queue already has bounded FIFO and generation tokens. The completion FIFO already has a small fixed notification ring. Changing either module or rewriting either ring duplicates mature teaching functionality. The adapter exists to connect their distinct contracts and store an explicit correlation record. That design does not automatically imply the corresponding functionality belongs in a production app; Framework owns reusable service infrastructure.

**179 — Why backpressure?** A completion queue of four cannot accept a fifth terminal notice. The dispatcher refuses `Step` *before* acquiring another request. Cancellation of a queued request also needs a terminal notice and therefore refuses if the completion queue is full. After a receipt is consumed, the downstream capacity increases by one. FIFO work acquisition and completion-notification order are different policies.

**180 — What is stale?** An old `slot` alone is not a stable identity. `requestId` and `generation` distinguish different lifetimes sharing physical storage. A late cancellation must fail with `STALE` after a slot has been released and reused. `FINAL` instead means the matching request still exists but has already completed or been cancelled. Quiescence blocks future admissions; full draining requires delivery and release.

**181 — What did the tests prove?** The nine new CTests exercise a serial deterministic model. They do not prove thread safety, network correctness, crypto security, financial business correctness or successful Windows packaging. A clean Linux sanitizer test adds evidence about some classes of memory defects but does not certify the module for production.

## Chapters 182–190: reference answers

**182 — Working tree vs index:** `git diff` normally compares unstaged working-tree changes with the index. `git diff --cached` compares staged content with `HEAD`. `git add` stages, `git commit` records; neither pushes to GitHub.

**183 — Why inspect before `git add -A`?** That command can stage unrelated modifications and deletions. Run `git status`, then inspect `git diff --cached --stat` and the patch. Direct-to-main is an internal repository policy and does not bypass testing or review requirements.

**184 — Why two push failures?** A detached HEAD is not a local branch. `git push origin main` publishes the **local branch named `main`**, which can be behind remote `main` even when detached HEAD points at a newer commit. Inspect ancestry using `git fetch`, `git log origin/main..HEAD`, branch pointers and `git merge-base --is-ancestor`. Do not force-push to repair a normal rejection.

**185 — Why parent commit after child commit?** The OS repository stores a gitlink to the Framework commit; it does not automatically follow Framework `main`. An approved Framework upgrade is published in Framework first, and then a verified OS parent commit records the new dependency revision. Pinned checkout differs from `--remote` upgrade.

**186 — Stash and detached commits:** `git stash push --include-untracked` protects tracked edits and ordinary untracked files but not ignored files. Unpublished commits in detached HEAD require a named reference such as a unique local tag before checkout. Never blind-pop changes after updating, because the new remote commit may already include them. Review conflicts individually.

**187 — Git vs GitHub vs gh:** Git tracks local history; GitHub hosts authorised remotes and collaboration; `gh` is a command-line interface to GitHub. Creating a local repository does not create a GitHub remote. Authentication information must remain outside committed files.

**188 — Source provenance:** A reproducible defect report identifies the repository, commit, build configuration, compiler and test steps. `git blame` identifies the latest line-associated change, not necessarily original design authorship. Read previous commits before deciding a function is obsolete.

**189 — Recovery:** `git restore --staged -- path` changes the index, not the working file. Read old content with `git show HEAD:path` before any overwrite. For a published faulty commit, review `git revert` and rerun tests; reflog is a local recovery aid, not an enduring backup.

**190 — Capstone:** Framework implementation first (if genuinely modified); OS gitlink second (only after confirming availability and acceptance); Bits2Banking lessons third. Every repository has a distinct test and commit record. The classroom exercise does not require modifying Framework or OS.

## Suggested assessment (100 points)

| Area | Points | Evidence |
|---|---:|---|
| Correct C23 ownership diagram and explanation | 20 | Distinguishes submit, step, terminal notice and delivery. |
| Tests and limits | 20 | Nine named results, failed-input behaviour, honest platform limitations. |
| Git states and safe staging | 15 | Correct use of status, diff, cached diff and staged review. |
| Remotes and submodules | 20 | Explains pinned gitlink, detached HEAD, fast-forward and non-fast-forward. |
| Preservation and conflict recovery | 15 | Protects both untracked and tracked work, separately protects unpublished commits. |
| Professional release evidence | 10 | Relevant source hashes, compiler, CTest results and no premature success claims. |

A learner must not receive a passing mark for a procedure that discards source work without review, suppresses failed tests, force-pushes over remote changes or claims that this lab performs real financial operations.

## Review references

Official resources include the [Git manual](https://git-scm.com/docs), the [Git Book](https://git-scm.com/book/en/v2), and the [GitHub CLI manual](https://cli.github.com/manual/). The Umicom-specific operational steps in this course reflect the repository policies documented alongside the project source; they are not universal Git requirements.
