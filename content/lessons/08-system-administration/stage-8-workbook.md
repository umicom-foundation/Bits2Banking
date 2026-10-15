# Stage 8 practical workbook and suggested answers

**Purpose:** Demonstrate understanding before attempting privileged administration. Learners may work entirely on paper, or use read-only commands on a practice computer. Keep real machine identity information out of public submissions.

## Exercise 1 — Check versus outcome

A scheduled task was enabled at 09:00. It produced no export file and no successful job-result evidence. Mark the statements “Task exists”, “Job finished” and “Export is correct” as Known, Unknown or False. **Suggested answer:** task existence is known; completion and correctness are **unverified**, not automatically false or successful. Investigate the task result and owner.

## Exercise 2 — Windows or Linux?

Explain where to observe scheduled work on Windows and on Linux. **Suggested answer:** Windows Task Scheduler (`Get-ScheduledTask`) and Linux systemd timers (`systemctl list-timers`) or the current user's cron (`crontab -l`). They are different technologies but require the same result/owner checks.

## Exercise 3 — A growing queue

The fictional Notes export queue is 2, 5, 8, 13 across four observations. CPU use remains moderate. What is the next safe question? **Suggested answer:** determine whether completed exports are keeping up, whether the oldest waiting job is growing older and which downstream dependency is blocked. Do not buy more CPUs by assumption.

## Exercise 4 — Write an actionable alert

Provide service, symptom, time, impact, source, owner and runbook link. **Suggested answer:** “NotesTraining, 10:05 UTC: practice save request 42 has not completed after the expected bound; two training users affected; source: named lab observation; owner: training operations; next review 10:20 UTC.” Do not include user secrets.

## Exercise 5 — Recoverable point

The last verified copy precedes an outage by 20 minutes. The RPO is 15 minutes. Was the objective met? **Suggested answer:** No. The observed data gap exceeds the allowed age by five minutes. This says nothing about how long restoring the service will take.

## Exercise 6 — Time to restore

The service becomes usable 130 minutes after an outage. Its RTO is 120 minutes. **Suggested answer:** The objective was missed by ten minutes. The time measurement must include whatever scope the owner defines as “usable service”.

## Exercise 7 — A practice restore

What must remain untouched? **Suggested answer:** the original source record and previous backup copies. Restore into a separate learner-owned directory and compare both bytes and the meaningful Notes workflow.

## Exercise 8 — A valid change window

A ticket says “Sunday morning”. What is missing? **Suggested answer:** exact date, start and end times, timezone or UTC representation, service, owner, approval, stop conditions and verification evidence. Daylight-saving changes can make local times ambiguous.

## Exercise 9 — Mixed machine logs

A storage log shows “save completed” before a workstation log says “save requested”. List two hypotheses. **Suggested answer:** clock skew and events representing different requests; also check buffering and delayed log writing. Use correlation IDs, timestamps and clock sources.

## Exercise 10 — Review source identity

The scheduled review tests revision A but the host is running revision B. Is the review valid? **Suggested answer:** No. Bind evidence to the exact revision or start a new review. A green test for A cannot be claimed as evidence for B.

## Exercise 11 — Failure followed by rollback

The new update fails; an old version is restored and independently tested. Classify both events. **Suggested answer:** **new update failed**, **previous service restored**. Never rewrite the failed-release result as a success.

## Exercise 12 — Capstone handover

Write a one-page seven-day runbook with daily observations, weekly backup review, monthly practice restoration, owner and deputy, escalation, RPO/RTO, source revision and an evidence-quality statement. **Suggested marking:** award credit for correctly identified unknowns and refused unsafe changes. A confident claim without evidence receives less credit than a precise “not verified”.

## Optional C23 verification questions

1. Why is `BtbOpsNextDue` a pure arithmetic function rather than a scheduler? **It does not hold a timer, thread or OS handle.**
2. What does `BtbOpsInit` reuse? **A copied, pre-existing Update 44 security-operations review.**
3. What happens if `outNextSeconds` cannot hold the result? **The operation returns INVALID and the caller's destination remains untouched.**
4. Can a `REVIEWABLE` classroom result approve an actual deployment? **No. Operational authority belongs to properly authenticated services and authorised people.**
