# Chapter 102 — Alerts, on-call responsibility and incident communication

**Bits to Banking · System Administration From Zero · Stage 8**  
**Prerequisites:** Course Chapters 1–96 provide optional foundation; this lesson explains new terms before use.  
**Audience:** Beginners, returning professionals, and supervised young learners.  
**Safety:** Read-only observations on a computer you own or are permitted to use. Never copy real secrets into exercises.

## What we are going to learn

An incident is managed through people as well as technology. Learn to record impact, contact the correct owner, protect evidence and communicate without speculation.

![Diagram — Alerts, on-call responsibility and incident communication](../../assets/diagrams/sysadmin-monitoring-escalation-update45.svg)

## Understand the idea before typing

A beginner sees an alert and may want to restart everything. That is unsafe when the service is processing trades, payments or irreplaceable documents. First define **what is happening to users**, its scope, the first known time and what is still unknown. Preserve diagnostic data before attempting corrective action.

A useful incident update states facts separately from hypotheses: “At 10:20 the Notes export queue contained 15 waiting jobs” is a fact from a named source; “the database is probably slow” is a hypothesis requiring investigation. Assign the next check to an owner and state when the next update is due. Never disclose credentials, customers or patient details in shared incident channels. If there is immediate danger to people or critical infrastructure, follow the organisation’s established emergency procedure rather than this classroom checklist.

## New terms explained

| Term | Plain-English meaning |
|---|---|
| **Incident** | An unplanned service disruption or meaningful degradation. |
| **Severity** | A category based on effect and urgency, defined by the organisation. |
| **On-call** | The person or team assigned to respond during a period. |
| **Escalation** | Passing a problem to a more suitable decision-maker or specialist. |
| **Acknowledgement** | Explicit confirmation that someone accepted responsibility. |
| **Handover** | A concise transfer of evidence, status and next actions. |


## Windows laboratory — PowerShell 7

Open **Windows Terminal → PowerShell** or search for **PowerShell**. The prompt looks like `PS C:\Users\...>`; do **not** type the prompt itself. On Windows PowerShell 5.1, read-only commands may still work, but the project teaches PowerShell 7. Type the commands one line at a time:

```powershell
Get-Date
Get-Process | Select-Object -First 5 Name, Id
Get-WinEvent -LogName System -MaxEvents 5 | Select-Object TimeCreated, Id, LevelDisplayName
```

**What to expect:** Event viewing may require permissions or produce private host information. Use a local training computer and redact usernames/paths in shared workbooks. The event ID alone is not a diagnosis. The exact names, counts and times on your computer will differ; no precise output is assumed.

## Linux laboratory — terminal

Open your Linux terminal (for example a disposable virtual machine). These commands are read-only. If a command is unavailable, note your distribution and ask the instructor before installing anything.

```bash
date -Is
journalctl --user -n 8 --no-pager
systemctl --user --failed --no-pager
```

**What to expect:** A user service manager may be absent on a VM or subsystem; record the limitation. `journalctl --user` is scoped to accessible user logs, avoiding requests to read system-protected journals.

## Worked Umicom case study

At 14:05 a fictional course coordinator reports that Notes documents are opening but cannot be saved. The first line of an incident record says “User impact: save operations not completing, three training users affected”. Add “Observation source: a practice test run at 14:08; version: training build X; storage status: unknown”. The issue is handed to a designated service owner. The operator does not change file permissions or deploy a new version without approval and a recovery plan.

## What if something goes wrong?

| Observation | Safe response |
|---|---|
| No one owns the alert | Escalate to the documented support contact, mark owner missing, and record the follow-up. |
| The first log line looks decisive | Cross-check time, correlation ID, earlier events and another independent observation. |
| Several people edit the incident note | Use a shared controlled record with timestamps and clearly named updates. |

## Guided learner exercise

1. Write a six-line fictional incident update with user impact, observation time, evidence, unknowns, owner and next-update time.
2. Mark each statement in your report as Observation, Hypothesis or Decision.
3. Explain why emergency action is different from an ordinary training maintenance step.

## Self-check and suggested answers

**Answer 1:** The on-call team is responsible for acknowledged investigation; a tool cannot own a decision.

**Answer 2:** Distinguishing facts from hypotheses prevents an incorrect assumption becoming an unauthorised fix.

## What this proves — and what it does not

These exercises teach how to collect observations and describe decisions. They are not a certification of any real Umicom deployment. A command completing successfully does not automatically mean that a business operation finished. In live work, only an authorised owner should change service configuration, scheduled jobs, firewall policy, backup retention or credentials, after impact assessment and recovery planning. New reusable monitoring or scheduling software belongs in **Umicom Framework**, preferably implemented in C23 or Assembly rather than new PowerShell/Python scripts.

**Further reading:** [Stage 8 overview](stage-8-index.md) · [Safe command reference](stage-8-safe-command-reference.md) · [Stage 8 glossary](stage-8-glossary.md).
