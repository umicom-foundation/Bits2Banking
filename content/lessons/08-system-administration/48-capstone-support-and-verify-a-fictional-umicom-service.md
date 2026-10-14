# Chapter 48 — Capstone: support and verify a fictional Umicom service

**Bits to Banking · System Administration: From Zero · Umicom Foundation**  
**Audience:** beginners of any age; younger learners should use a supervised computer.  
**Suggested study time:** 90–140 minutes.  
**Before this chapter:** Chapters 37–47 and the Update 39 support-evidence laboratory.

## The question this chapter answers

**How can I understand and check this part of a computer without accidentally changing something important?**

## Why this matters

A learner is ready to move towards professional administration when they can investigate a problem without making it worse. This capstone combines the course's skills in one fictional incident. The Umicom Notes training application is said to be unavailable; students must establish where they are, identify their tools, inspect relevant service and storage signals, review a verified backup, and write a clear conclusion.

The exercise does not require an actual Notes server, does not touch Umicom Bank or live services and does not issue payments or trading orders. Students may use a teacher-provided fictional worksheet if they do not have permission to inspect their own machine.

## A useful mental model

The task is like assembling a puzzle from evidence. One piece says a process is running; another says a required filesystem is not available; another shows a backup from an older session. The pieces can be internally consistent and still not justify release readiness. You must distinguish observations, missing evidence, a proposed action and the acceptance criteria for declaring recovery complete.

![Capstone: support and verify a fictional Umicom service](../../assets/diagrams/sysadmin-service-dependency-readiness-update40.svg)

*Figure 48 — The concept and its safe evidence boundary.*

## Key terms, explained before using them

| Term | Meaning |
|---|---|
| **Incident** | An unplanned interruption or degradation of an expected service. |
| **Scope** | The machine, application, user group and time interval being investigated. |
| **Evidence** | A verifiable observation such as a command result or test report. |
| **Readiness gate** | A required check that must pass before service can be marked ready. |
| **Remediation** | An authorised action intended to address the verified cause. |
| **Closure** | A documented decision that the recovery criteria and communications have been satisfied. |

## Read this before typing commands

> **Authorisation and safety:** Use your own computer or an explicitly authorised learning environment. Start with an ordinary user account. Commands that install software, change access, restart services or modify networks are outside this exercise unless the text clearly identifies a harmless practice-file operation. You never need to disable a firewall or change system permissions to complete this chapter.

> **Reading code blocks:** Open PowerShell 7 on Windows (`pwsh`) or a terminal on Linux. Type the line inside the block, not the example prompt. Run one command at a time. Some examples contain multiple interactive commands separated by semicolons; verify their results individually. These are interactive commands, **not scripts added to Umicom**.

## Windows — PowerShell 7 practice

Do these steps on Windows. If you use Linux, read them for comparison and continue below. A missing command means that a tool or module may be unavailable; it is not a reason to bypass computer policy.

### Step 1 — Confirm the current shell and location

```powershell
$PSVersionTable.PSVersion; Get-Location
```

**Expected result:** The shell version and working directory are displayed.

**Why this command matters:** The assistant cannot infer your host settings. Record the actual version and path rather than copying example values into the report.

**Safety and troubleshooting:** Use a normal user shell. Do not elevate to bypass a missing or denied observation.

### Step 2 — Check that your practice data is present

```powershell
Test-Path -LiteralPath "$HOME\UmicomLearning\BackupLab\source\notes.txt"
```

**Expected result:** True if you completed Chapter 41, False otherwise.

**Why this command matters:** A False result is expected on a new computer and is recorded as NOT RUN or MISSING, not silently repaired by inventing evidence.

**Safety and troubleshooting:** Do not replace or overwrite any non-practice files.

### Step 3 — Review free space

```powershell
Get-PSDrive -PSProvider FileSystem
```

**Expected result:** Available volumes and free-space values appear where supported.

**Why this command matters:** Identify the volume containing your practice folder. A different drive's capacity does not explain a failure on the target drive.

**Safety and troubleshooting:** Do not delete build directories or logs solely to improve free space.

### Step 4 — Inspect recent application events without changing them

```powershell
Get-WinEvent -LogName Application -MaxEvents 6 | Select-Object TimeCreated, Id, ProviderName, LevelDisplayName
```

**Expected result:** A small recent sample appears where available.

**Why this command matters:** Unless an entry has matching application identity, time and operation, do not claim it proves the Notes incident.

**Safety and troubleshooting:** Never share raw logs containing personal data or tokens.

### Step 5 — Review an Umicom Git checkout only if it exists

```powershell
git -C "C:\umicom\Umicom-Bits2Banking" status --short
```

**Expected result:** Local source changes appear or an error explains the path is missing.

**Why this command matters:** This is a read-only Git command. It does not fetch, stage or commit anything.

**Safety and troubleshooting:** If the repository is missing, do not create a new checkout in the middle of the incident simply to make the result green.

## Linux — terminal practice

Run these in a Linux terminal on an authorised computer or VM. Some distributions do not install the same commands. An unavailable check should be reported as unavailable; do not assume an unobserved result is successful. No command below requires `sudo`.

### Step 1 — Check your identity and environment

```bash
id; pwd
```

**Expected result:** Current account and working directory appear.

**Why this command matters:** Record the environment before interpreting service and file-access results.

**Safety and troubleshooting:** If this command is unavailable or access is refused, record the result. Do not alter system configuration simply to make the example succeed.

### Step 2 — Review storage capacity

```bash
df -h .
```

**Expected result:** Filesystem usage for the current directory appears.

**Why this command matters:** State which mount point you inspected; do not attribute an unrelated disk to the incident.

**Safety and troubleshooting:** If this command is unavailable or access is refused, record the result. Do not alter system configuration simply to make the example succeed.

### Step 3 — Read a bounded service-log sample if allowed

```bash
journalctl --user -n 6 --no-pager
```

**Expected result:** Recent user journal messages appear or the command reports restricted/unavailable access.

**Why this command matters:** If no appropriate source exists, record the check as NOT RUN rather than writing a fabricated error.

**Safety and troubleshooting:** If this command is unavailable or access is refused, record the result. Do not alter system configuration simply to make the example succeed.

## Worked Umicom support scenario

A classroom worksheet supplies these fictional facts: (a) the Notes window exists, (b) its document storage is not accessible, (c) an old backup from a previous session has a matching hash, and (d) no current save-and-read test was performed. The correct outcome is BLOCKED. A running window and an old backup cannot substitute for current storage and application readiness checks. The learner writes a recovery proposal: verify permissions and storage, restore to a separate review location if approved, then rerun the actual Notes operation.

### A disciplined investigation sequence

1. **Describe the symptom precisely.** Identify what failed and the expected result.
2. **Identify the environment.** Record current account, machine class, working directory and observation time; redact private identifiers.
3. **Run the smallest relevant read-only check.** Choose evidence that distinguishes two possible causes.
4. **Compare results with the requirement.** Missing, blocked or outdated checks are not successful checks.
5. **Separate fact and interpretation.** Label hypotheses explicitly.
6. **Propose, do not silently apply, a change.** State approval, effect, rollback and validation criteria.

## Common mistakes and how to respond

| Incorrect assumption | Better engineering response |
|---|---|
| A successful backup hash proves the application is now ready. | Backup integrity and current service readiness are distinct; the former may not establish the latter. |
| Git status is clean, so the failure is resolved. | Version-control cleanliness does not prove runtime correctness or tests. |
| A missing test should be recorded as passed to complete the checklist. | A missing required test blocks the claim. An honest NOT RUN is better than false assurance. |

## Practical exercises — try these before opening the answers

1. Prepare a ten-line incident report.
2. Decide READY/REVIEW/BLOCKED for the fictional worksheet.
3. Demonstrate a non-destructive recovery plan.

<details>
<summary><strong>Suggested answers and reasoning</strong> — open after attempting the exercises</summary>

1. **Prepare a ten-line incident report.** Include incident ID, scope, observation time, symptoms, three checks, one uncertainty, proposed action and closure criteria.
2. **Decide READY/REVIEW/BLOCKED for the fictional worksheet.** BLOCKED: current required storage and application checks have not passed.
3. **Demonstrate a non-destructive recovery plan.** Verify backup, restore separately, test actual document read, obtain approval before replacing production state.

</details>

## Engineering connection: Umicom Framework

The Update 40 service-readiness C23 lab composes the existing Update 39 observation model. It evaluates fictional service dependencies, rejects stale or missing required checks and propagates blocked prerequisites. It does not inspect the host, replace real Framework supervision or authorise any recovery. The lab demonstrates why observation quality is part of engineering correctness.

## Short support-note template

```text
Observation ID: PRACTICE-____
Observed at (include timezone):
Authorised machine or learning environment:
User-visible symptom:
Command or test (never paste credentials):
Observed result:
What remains unknown:
Proposed next safe check:
Approval required before any change:
```

## References and further study

- https://learn.microsoft.com/powershell/
- https://docs.github.com/en/get-started/using-git/about-git

**Course progression:** [Chapter 47](47-build-an-incident-timeline-from-logs-and-metrics.md) → **Chapter 48** → [Advanced course index](advanced-index.md).

---

**Safety reminder:** An honest *not available*, *not authorised* or *not run* result is better than a fabricated pass. No real system changes or remote repository writes are required.
