# Episode 68 — From reviewed source to a reproducible Umicom release

**Bits to Banking · Umicom Foundation**
**Related chapters:** [196 — Stage and commit](../../lessons/05-engineering/196-audit-git-add-a-and-commit.md), [199 — Tags and evidence](../../lessons/05-engineering/199-annotated-tags-and-release-evidence.md), [200 — Repository order](../../lessons/05-engineering/200-coordinate-umicom-repositories.md)
**Suggested length:** 11–13 minutes.

## Outline

This episode teaches that “the push succeeded” is only one milestone. A proper release also requires source identity, dependency identity, build output, test evidence, archive manifest and honest reporting of environments not tested.

### 00:00–02:00 — What are we releasing?

**Show:** A small C23 Umicom Notes service contained in Framework and a thin application that consumes it. Contrast the actual Framework source commit with a parent application's mode-160000 Framework gitlink. Explain that the two commits belong to separate repositories.

### 02:00–04:00 — Review before staging

**Show:** `git status`, `git diff --check` and `git diff --name-status` in a test repository. Include an unintended generated binary and one tracked deletion. Explain what `git add -A` would stage and why reviewers must inspect the staged list and contents after running it. Avoid silently removing a feature simply because newer code exists.

### 04:00–06:30 — Publish the Framework source

**On screen:** CMake configure, build and CTest for the actual changed module. Show `git branch --show-current`, `git add -A`, `git diff --cached --check`, `git diff --cached --stat`, `git commit -m "feat(framework): ..."` and `git push origin main`. Use a real specific commit message only for the **practice repository**. State that these are interactive commands, not a PowerShell script.

### 06:30–09:00 — Verify and lock a consumer revision

**Show:** update a practice parent to the tested child commit, compare the gitlink, run a read-only `repo verify` where available, then inspect what `repo lock` would stage. Rebuild the consumer and run its tests. Explain that a tested Foundation app may require a separate GUI or headless acceptance gate.

### 09:00–11:00 — Evidence for release

**Show:** a source manifest containing full SHAs, CMake configuration, compiler, OS, test case counts, untested gates and SHA-256 of the ZIP. Mention that a checksum detects accidental changes but does not certify authorship. Discuss annotated tags as release markers only after a maintainer approves a specific revision. Never move an existing public tag silently.

### 11:00–13:00 — Final check

Ask the viewer: “What if Framework built on Linux, but the OS installer was not built on Windows?” Correct answer: report Linux Framework validation only; Windows OS installer remains unverified. Conclude with the Update 31 Git command reference and the full build/test workflow.
