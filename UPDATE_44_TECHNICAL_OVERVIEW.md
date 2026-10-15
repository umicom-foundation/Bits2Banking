# Major Update 44 — Technical overview

## Education mission

Extend the dedicated *System Administration From Zero* course from **84 to 96** chapters with an accountable security-operations foundation suitable for absolute beginners and returning professionals. New material includes identity lifecycle and group review, safe configuration baselines, byte-level SHA-256 comparison, patch windows, endpoint-security observations, credential and certificate hygiene, redacted audit trails and independently verified recovery.

Every new chapter opens with a concrete operational question, defines terms before showing commands, offers separate Windows PowerShell 7 and Linux instructions, explains expected output and limitations, includes a fictional Umicom example and concludes with practical assessment questions. The age range affects clarity, not engineering rigour.

## C23 source composition

The new isolated `labs/native/security-operations-review` project composes **existing** training APIs rather than creating another service manager or security provider:

```text
Update 39: BtbAdminReview / sysadmin-evidence
    -> 40: BtbServiceGraph / service-readiness
    -> 41: BtbMaintenanceReview / maintenance-review
    -> 42: BtbDeploymentReview / deployment-rehearsal
    -> 43: BtbRemoteReview / remote-access-review
    -> 44: BtbSecurityReview / security-operations-review
```

`BtbSecurityInit()` copies a validated plan and a complete `BtbRemoteReview`. `BtbSecurityAttach()` accepts immutable, fictitious observations only once; source revision, 64-character lowercase SHA-256 configuration digest and policy revision must match. `BtbSecurityEvaluate()` invokes `BtbRemoteEvaluate()` and combines its outcome with required account, privilege, configuration, patch, restore, audit, credential, certificate and monitoring observations. Results are `PENDING`, `BLOCKED`, `REVIEWABLE` or `RESTORED_ONLY`. Invalid calls and identity mismatches preserve prior output.

The code stores no secret values or credentials. `REVIEWABLE` means **only that the supplied fictional checklist meets its modelled requirements**. It does not authenticate a remote host, prove certificate trust, compute a real SHA-256 file digest, inspect a real ACL or grant authority to deploy. These production capabilities already belong to Umicom Framework and the relevant OS security services.

## Important invariants

- Caller-owned records are copied: no retained borrowed pointers.
- Strings are bounded and validated without reading beyond fixed arrays.
- Illegal flags, identifiers and revisions are refused before changing the object.
- Source, configuration and policy identities must be consistent.
- An initial plan's review-window boundaries cannot be mutated after attachment without explicit mismatch detection.
- Stale capture IDs and observations outside the review window block readiness.
- A missing required observation creates a reason bit, never an optimistic ready state.
- An upstream failed deployment or restored-only history cannot be promoted to a successful update.
- No function executes a command, connects to a socket, writes a file or changes an account.

## Build architecture

The lab CMake file imports `remote-access-review` through `add_subdirectory()`, preserving earlier targets and registered tests. `btb-security-operations-lib` is the core in-memory library. `btb-security-fixture` is example-only and calls the earlier real teaching APIs to build deterministic fictional observations. The demonstration and test targets link the example fixture; the core library does not import fixture logic.

## Preserving the original course

The standalone course edition appends the 12 new chapters and five reference chapters to the previous Update 43 HTML. The prior 84 chapter article bodies were checked for exact equality before publication. Original attribution and authorship remain. The old *Umicom New Project Beginner Guide* remains in its earlier batch and is neither edited nor replaced here.

## Known boundaries

Linux GCC/Clang C23 and sanitizer validation are reported separately from Windows UCRT64. The complete MkDocs strict build, current user-managed Git tree and installed Framework SDK integration require the local maintainer's acceptance. No production Framework code was modified in this batch.
