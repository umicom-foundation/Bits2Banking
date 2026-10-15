# Episode 130 — Build and test the C23 security-operations review

**Bits2Banking · Umicom Foundation · 10–12 minutes**  
**Companion:** Engineering Chapters 308–311 and System Administration Chapter 96.  
**Coding policy:** ISO C23 core; no new PowerShell/Python application scripts; reuse existing Umicom Framework capabilities.

## Educational outcome

Show how the Update 44 source code composes five previous C23 libraries, validates fictional evidence, reports blocked conditions and preserves caller state when an operation is refused. The video **must not** imply that the model executes real administrative actions or independently verifies user accounts, credentials or certificates.

### 00:00–02:10 — Start at the public header

Open `labs/native/security-operations-review/security_operations_review.h` in a text editor. Explain the enum outcomes: `PENDING`, `BLOCKED`, `REVIEWABLE` and `RESTORED_ONLY`. Describe the caller-owned `BtbSecurityReview` and why input records are copied. Show that the header contains no SSH, Windows service, firewall or secret-handling API.

**Narration:** “The word REVIEWABLE is deliberate. This model answers a question about a fictional checklist, not whether we may connect to another person's computer.”

### 02:10–04:30 — Find actual reuse

Open the `CMakeLists.txt`. Follow the `add_subdirectory` into the earlier `remote-access-review` library, which already depends on deployment, maintenance, readiness and observation code. Explain that CMake links existing library targets: we do not copy their implementations or replace existing tests.

Open `training_fixture.c`, identify the calls to the original `BtbMaintenanceInit`, `BtbDeploymentInit`, `BtbRemoteInit` and related functions. These prepare **fictional** records; the new code does not inspect a real machine.

### 04:30–06:20 — Build and test

In Windows PowerShell 7, type the CMake commands given in Chapter 96; do not turn them into a `.ps1` script. Wait for configure, build and all CTest outputs. If prerequisites are missing, show the actual CMake diagnostic and explain why it should not be hidden.

Run `ctest --test-dir ... -R 'bits2banking.security-operations' --output-on-failure` to focus on the new cases. Run all tests after that to prove the older labs remain registered. **Never edit the displayed test counts in the video; use the results actually obtained.**

### 06:20–08:50 — What the negative tests prove

Run named cases `restore`, `stale`, `config-mismatch` and `upstream-restored`. Explain why missing independent recovery evidence blocks, stale capture IDs are not current observations, mismatched identity data is refused without modifying state, and a restored old release is not the successful new one.

Open `test_security.c`; find the 25,000 deterministic mutations that withhold one of fifteen required conditions at a time. Point out that this is an **offline state-machine test**, not security scanning.

### 08:50–10:50 — Review, commit and preserve

Explain the sequence: inspect local Git status, verify `main`, build and test, `git add -A`, review `git diff --cached --check` and the staged diff, commit, and `git push origin main`. Do not force-push or remove old code. Use the [security-operations laboratory](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/security-operations-review/README.md) for build commands and the [daily Git workflow](../../lessons/05-engineering/183-daily-umicom-git-workflow.md) for staging and publication.

**Closing challenge:** Ask the student what independent real-world evidence would be needed before a security owner could approve credential rotation. Suggested answer: authenticated provider audit, approved role, correctly scoped host, tested dependent services and recovery verification. The classroom result alone cannot provide those facts.
