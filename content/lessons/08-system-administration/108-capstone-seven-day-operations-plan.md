# Chapter 108 — Capstone: build a seven-day Umicom Notes operations and recovery plan

**Bits to Banking · System Administration From Zero · Stage 8**  
**Prerequisites:** Course Chapters 1–96 provide optional foundation; this lesson explains new terms before use.  
**Audience:** Beginners, returning professionals, and supervised young learners.  
**Safety:** Read-only observations on a computer you own or are permitted to use. Never copy real secrets into exercises.

## What we are going to learn

Bring together scheduling, monitoring, capacity, alert ownership, backups, recovery targets and approval gates into one clearly documented beginner-level operations plan.

![Diagram — Capstone: build a seven-day Umicom Notes operations and recovery plan](../../assets/diagrams/sysadmin-disaster-recovery-update45.svg)

## Understand the idea before typing

Your final assignment concerns a **fictional** Umicom Notes system, not any real Umicom user or server. Students do not need elevated permissions or their own domain to complete the work. Start from a one-page service description: a Notes desktop, a service, data storage and one scheduled export. Record what each dependency does. The challenge is to decide **what you know, what is missing and who should act**.

The exercise deliberately contains a contradiction: a report says “backup healthy”, but the last independent restore drill is older than policy. It also contains a successful process-start check, but an untested user-facing save operation. A good administrator does not turn those into passing gates. The plan must assign owners, prioritise impact, preserve original evidence, and describe a safe practice restore into a separate destination before any real change is proposed.

## New terms explained

| Term | Plain-English meaning |
|---|---|
| **Operations plan** | A written schedule of checks, owners, thresholds and responses. |
| **Runbook** | Actions and verifications prepared for a specific scenario. |
| **Evidence gap** | A required observation that has not been collected or verified. |
| **Recovery objective** | A documented data-loss or time target such as RPO/RTO. |
| **Release identity** | The exact software revision or artifact under review. |
| **Closure** | Recorded decision that required checks are complete, not a guess. |


## Windows laboratory — PowerShell 7

Open **Windows Terminal → PowerShell** or search for **PowerShell**. The prompt looks like `PS C:\Users\...>`; do **not** type the prompt itself. On Windows PowerShell 5.1, read-only commands may still work, but the project teaches PowerShell 7. Type the commands one line at a time:

```powershell
Get-Location
Get-Date
Get-PSDrive -PSProvider FileSystem
Get-Process | Select-Object -First 5 Name, Id
git --version
```

**What to expect:** These commands produce your own local training-machine observations. They do not probe a real Notes service or GitHub repository. Put them in a workbook labelled “local computer, not production”. The exact names, counts and times on your computer will differ; no precise output is assumed.

## Linux laboratory — terminal

Open your Linux terminal (for example a disposable virtual machine). These commands are read-only. If a command is unavailable, note your distribution and ask the instructor before installing anything.

```bash
pwd
date -Is
df -h
ps -eo pid,comm --sort=pid | head -n 6
git --version
```

**What to expect:** Run inside a disposable Linux account or VM if available. No `sudo` or service changes are required.

## Worked Umicom case study

**Given fictional evidence:** source revision `012345…4567` is noted; last heartbeat was 2 minutes ago and the permitted age is 3 minutes; a backup copy exists but the last *verified* restore was six weeks ago against a four-week review rule; queue depth is 7 against a threshold of 5; the on-call owner is unassigned; a deployment from yesterday was rolled back to the previous version. **Your decision:** do not label the proposed new version healthy or the release successful. Mark the stale restore drill, queue threshold and missing owner explicitly. The rollback may have restored old service, but that is a distinct result. Escalate to the appropriate reviewers and schedule a controlled training-only restore rehearsal.

## What if something goes wrong?

| Observation | Safe response |
|---|---|
| Learner calls `git push` to “fix” a service | Git publication cannot fix operational readiness; first investigate the relevant dependency and release identity. |
| Learner proposes running tasks on production | Stop and keep work inside the authorised practice environment. |
| Learner confuses restored old version with upgraded version | Record `RESTORED_ONLY`, and keep the failed change evidence intact. |

## Guided learner exercise

1. Prepare a seven-day table with at least one daily observation, weekly backup check and independent test. Include owner and evidence source.
2. Write a fictional incident report with the data above. Name at least three blockers and one next safe action.
3. Optional advanced lab: build `labs/native/operational-resilience`, run tests, and compare `REVIEWABLE`, `BLOCKED` and `RESTORED_ONLY`.

## Self-check and suggested answers

**Answer 1:** Blockers include the stale restore exercise, queue above the threshold, and missing on-call ownership; a rollback is not a successful upgrade.

**Answer 2:** A verified practice restore requires a separate destination, a documented source copy, a safe procedure and independent functional verification.

## What this proves — and what it does not

These exercises teach how to collect observations and describe decisions. They are not a certification of any real Umicom deployment. A command completing successfully does not automatically mean that a business operation finished. In live work, only an authorised owner should change service configuration, scheduled jobs, firewall policy, backup retention or credentials, after impact assessment and recovery planning. New reusable monitoring or scheduling software belongs in **Umicom Framework**, preferably implemented in C23 or Assembly rather than new PowerShell/Python scripts.

**Further reading:** [Stage 8 overview](stage-8-index.md) · [Safe command reference](stage-8-safe-command-reference.md) · [Stage 8 glossary](stage-8-glossary.md).
