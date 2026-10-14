# Chapter 24 — Capstone: perform a safe support check from start to finish

**Bits to Banking · System Administration: From Zero · Umicom Foundation**  
**Audience:** first-time users and returning learners; no prior system-administration knowledge required.  
**Code policy:** interactive PowerShell 7 and Bash commands; native C23/Assembly for Umicom executable development.  
**Estimated study time:** 25–50 minutes (longer when practising).

## What you will learn

Combine terminal use, system facts, a sample backup, Git and testing into one evidence-based exercise.

## Why this matters

![Professional administration separates observation from change](../../assets/diagrams/sysadmin-observe-change-update38.svg)


The capstone combines skills from the course without requiring administrator privileges or changing any live Umicom source. Imagine a friend says the learning Notes application will not save a document and Git reports confusing changes. Your job is to identify the computer, confirm the working directory, inspect the practice file, preserve a copy, review Git status if working in a repository, and produce a short factual report.

A complete answer distinguishes observed facts from assumptions. You might be able to show that the practice file exists, is readable and has a matching verified copy. That does not prove that the user’s separate Notes application works. Similarly, a clean Git working tree says nothing about whether the latest revision passes CTest.

This exercise is appropriate for individual learners, classrooms and supervised volunteer training. Do it inside your personal `$HOME\UmicomLearning` sandbox. Do not inspect other people’s files or actual charity beneficiary records.

## New words, explained

| Term | Plain-English meaning |
|---|---|
| **Checklist** | Ordered, verifiable sequence of administration actions. |
| **Evidence bundle** | Collected outputs supporting what was checked. |
| **Known limitation** | A test or observation that remains unverified. |
| **Acceptance criterion** | Clear condition required to call a step successful. |
| **Handover** | Record that allows another person to continue the investigation. |

## Windows practice — PowerShell 7

> **Before typing:** Run these commands in a normal, non-elevated PowerShell window. Where a file is used, complete the previous practice-folder chapters first. Do not paste the `PS C:\...>` prompt into the terminal.

**Start:** Use the Windows Start menu or Windows Terminal to open PowerShell. Check the prompt is ready. Commands beginning with `$` are still commands; type them exactly as shown.

### Step 1 — Confirm your active shell and user

```powershell
$PSVersionTable.PSVersion
whoami
```

**Expected observation:** Write down PowerShell version and account name.

**Check:** Read the output before continuing. If it does not match, stop and investigate the specific command; do not add `-Force` or run as Administrator automatically.

### Step 2 — Record OS and CPU context

```powershell
Get-ComputerInfo | Select-Object WindowsProductName, OsArchitecture
Get-CimInstance Win32_Processor | Select-Object -First 1 Name
```

**Expected observation:** A small environment inventory is displayed.

**Check:** Read the output before continuing. If it does not match, stop and investigate the specific command; do not add `-Force` or run as Administrator automatically.

### Step 3 — Confirm the exact practice file

```powershell
Test-Path "$HOME\UmicomLearning\Notes\README.md"
```

**Expected observation:** True means the training document exists.

**Check:** Read the output before continuing. If it does not match, stop and investigate the specific command; do not add `-Force` or run as Administrator automatically.

### Step 4 — Read it, not execute it

```powershell
Get-Content "$HOME\UmicomLearning\Notes\README.md"
```

**Expected observation:** The expected Markdown heading appears.

**Check:** Read the output before continuing. If it does not match, stop and investigate the specific command; do not add `-Force` or run as Administrator automatically.

### Step 5 — Verify backup and file identity

```powershell
Get-FileHash "$HOME\UmicomLearning\Notes\README.md" -Algorithm SHA256
Get-FileHash "$HOME\UmicomLearning\Notes\README-verified-copy.md" -Algorithm SHA256
```

**Expected observation:** Hashes should match if Chapter 14 created the copy and it has not changed.

**Check:** Read the output before continuing. If it does not match, stop and investigate the specific command; do not add `-Force` or run as Administrator automatically.

### Step 6 — Inspect any practice Git status

```powershell
Set-Location "$HOME\UmicomLearning\git-first-project"
git status
```

**Expected observation:** Git reports the current branch and modified/untracked files, if any.

**Check:** Read the output before continuing. If it does not match, stop and investigate the specific command; do not add `-Force` or run as Administrator automatically.

## Linux comparison — terminal/Bash

> Linux commands are alternatives on a Linux machine or authorised VM. Do not paste them into Windows PowerShell as though the shells have identical syntax.

### Linux step 1 — Confirm location, user and free space

```bash
whoami && pwd && df -h "$HOME"
```

**Expected observation:** Read-only user and storage context is shown.

### Linux step 2 — Verify safe backup if present

```bash
sha256sum "$HOME/UmicomLearning/Notes/README.md" "$HOME/UmicomLearning/Notes/README-verified-copy.md"
```

**Expected observation:** Matching hashes are expected if both copies are unchanged.

## Worked support scenario

Write a five-sentence handover: “I checked the account and the OS, inspected the sandbox path, confirmed the Notes Markdown file can be read, verified its copied hash, and observed the practice Git repository status. I did not inspect the real user’s documents or alter system configuration. Further work is required to reproduce the reported application save failure.”

## Common problems and how to respond

| Problem or assumption | Better response |
|---|---|
| Marking the whole incident resolved because one file is readable | Distinguish sandbox evidence from the original user problem. |
| Ignoring warnings from missing files | Record “not run” and return to the prerequisite chapter instead of inventing success. |
| Posting full log contents publicly | Remove credentials and private identifiers before sharing. |

## Exercise: demonstrate understanding

1. Write down the purpose of **two commands** from this chapter, in your own words.
2. Run a **read-only command** and record only the information needed to answer its question.
3. Explain which command would change the machine, if any, and why the chapter avoids it.
4. Explain the difference between an observation, a conclusion and an unverified assumption.

## Review questions

1. What is an honest “not verified” outcome?
2. Which actions in this capstone modify live Umicom code?

<details><summary>Show the suggested answers</summary>

1. A statement that a required check could not be completed with available evidence.
2. None. All exercises use observation and private practice files.

</details>

## How this connects to Umicom

Capstone acceptance requires clear evidence and honest reporting, not a perfect-looking dashboard. The same practice applies to real Umicom Kernel boot tests, Studio CTest results, and Framework/OS gitlink qualification.

## Where to go next

Return to the [course contents](index.md) and complete the final assessment before attempting advanced system changes.
