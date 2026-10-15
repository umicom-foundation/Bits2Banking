# Chapter 311 — Capstone: Framework-first security operations review

**Bits to Banking · Native C23 engineering · Umicom Foundation**  
**Prerequisite:** Chapters 308–310 and System Administration Chapter 96.

## Objective

Demonstrate how to turn a reported Umicom issue into a controlled engineering investigation without guessing at the cause, deleting code, bypassing permissions or confusing training policy flags with authenticated production evidence. You will use the C23 lab and existing CMake/CTest tools. You will **not** change a real Windows service, Linux unit, operating-system account or firewall.

## The incident narrative

A fictional Umicom Notes training service has a proposed credential change. Its build passed, but an independent restore drill is missing and nobody verified where monitoring alerts are delivered. Source revision and configuration digests are recorded. The right conclusion is **not yet qualified**, even if the GUI opens. Your engineering job is to prove that the policy evaluator refuses the missing evidence and preserves previous state after invalid input.

## Complete the native laboratory

From PowerShell 7, in `C:\umicom\Umicom-Bits2Banking`, configure and build `labs/native/security-operations-review` with GCC C23 and Ninja. Run `ctest --test-dir .\output\learning-build\security-operations-review --no-tests=error --output-on-failure`. Verify the actual registered test count. Run the demonstration executable and record the two printed states.

Then inspect the source with your preferred text editor. Follow `BtbSecurityInit`, `BtbSecurityAttach`, `BtbSecurityEvaluate` and the actual upstream `BtbRemoteEvaluate`. Show the team where the module reuses previous implementation rather than creating a duplicate Git client, SSH manager, secrets store or service controller.

## A safe change-control evidence table

| Subject | Claimed state | Independent evidence required |
| --- | --- | --- |
| Commit and package identity | Reported | Verified repository/release identity and artefact checks |
| Configuration | Matching digest claimed | Approved configuration and effective runtime state |
| Account and group permissions | Reported reviewed | Authorised account and group inventory |
| Credential rotation | Proposed | Controlled provider audit and dependent-service checks |
| Restore capability | **Not performed** | Approved restore exercise and independent functional verification |
| Monitoring | **Not verified** | Owner-reviewed alert routing and response test |
| Remote identity | Training fixture only | Trusted host identity before any real connection |

The native model cannot itself supply the third column. Those checks must be performed through the proper Framework/OS and organisational processes, by someone with authorisation.

## Validate failure atomicity

Choose the `config-mismatch` test. Before attaching a changed digest, the test saves the review object. The API refuses the mismatch and leaves the original object unchanged. Next, inspect `fail-atomic`, which fills an output record with a visible pattern and confirms that a malformed request does not overwrite it. These checks make failures reviewable instead of hiding partial changes.

## Prove honest outcomes

Run the `upstream-rollback` and `upstream-restored` tests. Explain why a restored service is still a failed update. Inspect the test source and identify the separate evidence captures for baseline, deployment, remote observation and security review. Capture identity is useful for ordering in this class; it is **not an authenticated timestamp or event signature**.

## Submission checklist

A complete submission contains a diagram of the library composition, the actual local compiler/CTest result, one positive and three negative observations, the source and configuration identity used by the fixture, a paragraph explaining authority boundaries, and a reviewed Git diff showing that no earlier source file was deleted.

### Reviewer questions

**Why not implement this policy directly inside Umicom OS?** Shared production security mechanisms belong in the Framework, while OS owns integration; the classroom model stays in Bits2Banking until an approved production contract exists.

**Why should previously superseded implementations be preserved?** They provide reviewability and protect against silent regression until the project owner approves removal.

**When is the capstone complete?** When its code, tests and documentation pass the actual local acceptance checks and the learner can explain the limitations, not merely when a download exists.

## Git check-in after validation

Use the normal per-repository Git process. Verify `main`, run `git add -A`, inspect `git diff --cached --check`, `git diff --cached --stat` and the staged diff, commit an accurate message and push `origin main`. Do not force a push or silently merge unrelated changes.

**Next:** The next native engineering stage will use existing Framework observability and release tooling for more complete cross-platform operational verification, without replacing it with scripts.
