# Stage 7 — Guided workbook, capstone and assessment

**System Administration From Zero · Umicom Foundation**  
**Use:** Print or complete in a personal Notes document. All examples are fictional and read-only unless they explicitly create harmless training files.

## Workbook A — Observe before acting (Chapters 85–87)

**Task A1.** In PowerShell, execute `Get-Date`, `whoami` and a limited `Get-Service` listing. Do not paste the full output into a public report. Write the command, what it reports and what it does **not** prove.

**Task A2.** Draw a roles-and-permissions table: Reader may open training documents; Maintainer may approve changes; service account may read a designated training store; independent Reviewer may inspect evidence. Why should Reader not also be the deployment approver? Record your answer.

**Expected learning evidence:** Three read-only observations; one least-privilege access matrix; recognition that an OS group is not the same as a financial transaction authorisation.

## Workbook B — The baseline experiment (Chapters 88–89)

**Task B1.** Make the harmless `notes-training.conf` in your personal `UmicomLearning/SecurityOps` folder using the commands in Chapter 88. Verify that it contains exactly the two example lines.

**Task B2.** Copy it to `notes-training.baseline.conf`. Calculate SHA-256 hashes for each. Are they equal? Write *yes/no* and what this tells you.

**Task B3.** Edit only `notes-training.conf` to change the log level. Recalculate the digests. What changed? Explain whether this proves the running service accepted that setting.

**Expected answer:** The baseline and source begin with equal byte-content digests, then differ after editing. This does not prove approved configuration or effective runtime behaviour.

## Workbook C — Maintenance and controls (Chapters 90–94)

Create a fictional change request for an Umicom Notes update. Fill in this table:

| Field | Example fictional value | Your answer |
| --- | --- | --- |
| Change ticket | 500 | |
| Source revision | 40-character hexadecimal teaching value | |
| Owner | MakerA | |
| Independent reviewer | CheckerB | |
| Why change is needed | A training-only security update | |
| Pre-change proof | Baseline and restore plan | |
| Exposure controls | Listener/firewall review | |
| Secret handling | No real secrets in notes | |
| Certificates | Correct endpoint and expiry | |
| Post-change proof | Notes save/open and monitoring | |
| Rollback decision | Restore only under approval | |

**Task C2.** A firewall-profile command fails because the relevant provider is missing. Should you mark the security control as failed, passed or not verified? Explain when a separate supported tool is required.

**Task C3.** Write a three-line fictional incident timeline that includes timezone offsets and an explicit unknown. Do not invent a cause that the observations do not prove.

**Expected:** An unavailable observation is Not verified; a different supported source is required. An incident timeline distinguishes actual observations from possible explanations.

## Workbook D — Recover independently (Chapter 95)

Copy the harmless baseline file to a new name ending in `-restored.conf`, compare the SHA-256 digests, then record whether any application-level test was run. The **correct** answer for the second part is *not run*, because copying a training file did not restart any service. Explain this distinction in one paragraph.

## Workbook E — Native C23 capstone (Chapter 96)

Run the CMake/CTest steps described in Chapter 96 **only if Updates 39–43 are merged and a working C23 toolchain is available**. Record the actual configured test count. Run these named cases:

```powershell
ctest --test-dir '.\output\learning-build\security-operations-review' -R 'bits2banking.security-operations.(restore|stale|upstream-restored)' --no-tests=error --output-on-failure
```

Describe what each case verifies. A test that passes when it *correctly blocks* unsafe evidence is a valid positive test of the rejection policy. A failed CTest case must be recorded as failed, not disguised as an expected block.

## Assessment rubric (30 marks)

| Criterion | Marks | Full-credit answer |
| --- | ---: | --- |
| Correct terminology | 5 | Defines account, ACL, baseline, patch, TLS, audit and recovery |
| Safe command use | 5 | Uses own files and read-only observations; no privileged shortcuts |
| Evidence interpretation | 5 | Separates observation, unknown, approval and action |
| Configuration digest exercise | 5 | Records before/after SHA results and their limitations |
| Recovery distinction | 5 | Distinguishes restored bytes, recovered function and failed change |
| Native C23/incident capstone | 5 | Records actual test results and correct blocked/restored-only reasons |

**Pass guideline:** 23/30 or more **and** no serious safety breach. Learners who cannot build C23 can complete a written review first, marked Not Run for binary validation, then finish the practical assessment later.

## Suggested answers to common misunderstandings

**“A hash matches, so our server is secure.”** Not established: the active service could use a different configuration and different identity controls.

**“I am an Administrator, so I should retry every command as Administrator.”** Wrong: diagnosis comes first, and privileges must match an approved task.

**“The update failed but we rolled back, so the update passed.”** Wrong: record a failed release and a separately verified restoration.

**“This Boolean says rotation reviewed, so a secret was rotated.”** Wrong: a classroom flag is not an authenticated secret-provider audit record.

## Handover form

**Scope and owner:** ____________________  
**Last verified source revision:** ____________________  
**Time (include timezone):** ____________________  
**Observed success:** ____________________  
**Missing or stale evidence:** ____________________  
**Data/secret redaction completed:** Yes / No  
**Requested next action and responsible person:** ____________________  
**Decision:** Reviewable training record / Blocked / Restored only / Not evaluated.
