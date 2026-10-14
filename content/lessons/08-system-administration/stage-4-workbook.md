# Stage 4 Workbook — Safe Administration and Recovery

**Audience:** older children with an adult mentor, adult beginners, returning professionals and Umicom contributors.
**Equipment:** non-administrator PowerShell 7 or an authorised Linux terminal, ordinary practice files and (for the capstone) a checked-out Bits2Banking repository with Updates 39–41.

## Observation log template

| Field | Student note |
|---|---|
| Time and timezone | |
| Host category (do not publish host identifier) | Windows / Linux / training VM |
| Command / tool | |
| Expected result | |
| Actual result | |
| What it proves | |
| What it does **not** prove | |
| Was the step read-only? | |
| Next authorised owner | |

## Exercises by chapter

For each exercise, run no more than the read-only steps supplied in the chapter and keep a short note of the result. Written explanations are acceptable when the OS/tool is not available.

| Chapter | Exercise | What earns credit |
|---|---|
| 49 | Describe two dependencies for Notes. | For instance, a writable practice folder and a correctly loaded document index. |
| 50 | Compare two identities. | Explain why the service's StartName may differ from whoami. |
| 51 | Explain two dependency types. | Contrast ordering and a required relationship without changing either. |
| 52 | Write a hypothetical task contract. | Include purpose, owner, trigger, input, output, success signal and retry policy. |
| 53 | Draw a configuration precedence diagram. | Use compiled defaults, approved application settings and an explicit per-run override, noting which source wins. |
| 54 | Prepare a two-column version baseline. | List each installed tool and its purpose; do not change versions as part of the exercise. |
| 55 | Design a three-metric baseline. | Include measure, unit, time, expected range and reason it matters. |
| 56 | Classify three bind addresses. | Contrast 127.0.0.1, ::1 and 0.0.0.0. |
| 57 | Choose an RPO and RTO for a fictional school portal. | Explain separately how much data loss and downtime are acceptable. |
| 58 | Draw a rollback dependency table. | Include executable, configuration, database, compatibility and verification owners. |
| 59 | Create an incident record template. | Include unique reference, start time, affected function, observed evidence, actions, owner and next update. |
| 60 | Write your complete change request. | Include the fictional workload, scope, source revision, backup, reviewer, before/after checks, failure condition and recovery plan. |

## Applied exercise A — Why the report did not arrive

A scheduled fictional Notes report was expected at 17:00 but is missing. The machine was offline earlier. Explain the difference between scheduler configuration, attempt evidence and business output; note which commands from Chapters 52, 55 and 59 would be safe. Prepare a short incident note with a confidence label on every hypothesis. No real scheduled job should be run.

**Suggested answer:** Read the timetable and last-run evidence, compare with the host availability timeline, check whether the expected report artefact exists in an authorised training directory, then escalate to the job owner. A configured trigger proves neither an attempt nor successful report production.

## Applied exercise B — Restore a fictional note into a separate folder

Use Chapters 57 and 58 to write a private practice note, copy it, verify SHA-256, restore the copy to another private folder, compare the digests and read the restored content. No production backup, school data or bank account is used.

**Suggested answer:** Both selected files should have identical byte hashes and the restored text should match the expected sentence. Record that one disk containing multiple copies does not satisfy a disaster-recovery policy.

## Applied exercise C — C23 change-window simulation

Read the three public headers in `sysadmin-evidence`, `service-readiness` and `maintenance-review`. Build the new C23 target, run the full CTest suite and the standalone demonstration. Record the exact number passed, compiler version and output showing `ROLLBACK_REQUIRED` followed by `RESTORED`. Explain why neither the demo nor the tests prove that an actual OS service was changed.

**Suggested answer:** The three libraries share ownership through linked C23 contracts. The planned change cannot finish after blocked post-change evidence. A distinct restored observation changes the *educational state*, not the host. Real approval, backups, runtime metrics and independent test evidence would be needed before production release.

## Assessment rubric (100 points)

| Area | Points |
|---|---:|
| Correctly explains terminology without guessing | 20 |
| Commands used within authorised, safe scope | 20 |
| Writes accurate expected versus actual observations | 20 |
| Distinguishes scope, hypothesis and proof | 20 |
| Explains recovery and Framework ownership | 20 |

**Pass guidance:** 70+ points, with no unauthorised system modification. A student who declines an unsafe step and explains why should receive credit for good judgement rather than be marked down.
