# Chapter 01 — What does a system administrator do?

**Bits to Banking · System Administration: From Zero · Umicom Foundation**  
**Audience:** first-time users and returning learners; no prior system-administration knowledge required.  
**Code policy:** interactive PowerShell 7 and Bash commands; native C23/Assembly for Umicom executable development.  
**Estimated study time:** 25–50 minutes (longer when practising).

## What you will learn

Identify the responsibilities of someone who keeps a computer useful, secure and recoverable.

## Why this matters

![Computer layers: each layer has a different job](../../assets/diagrams/sysadmin-os-layers-update38.svg)


A system administrator keeps computers and services dependable for the people who rely on them. That may mean setting up an account for a new colleague, explaining why an application will not launch, checking whether a disk is nearly full, confirming that a backup can be restored, or investigating unusual activity. A household computer needs the same principles on a smaller scale. A school computer room, a charity office and a bank apply them to more people and higher consequences.

Administration is not the same as programming. A developer changes how software works. An administrator installs, configures, monitors and protects the environment where software runs. The roles overlap: a Umicom contributor who compiles a C23 application also needs to understand storage, permissions, running processes and logs.

A useful professional habit is to separate observation from change. Looking at free disk space is observation. Deleting old files is a change. Before a change, know what system it affects, what success looks like, how you could undo it and whether you are authorised to perform it.

## New words, explained

| Term | Plain-English meaning |
|---|---|
| **System** | The computer, its operating system, installed software, data, users and connected services. |
| **Service** | A program that supplies a capability, often without a visible window. |
| **Availability** | Whether people can use the service when they need it. |
| **Backup** | A separate recoverable copy of data. |
| **Least privilege** | Having only the access needed for a task. |

## Windows practice — PowerShell 7

> **Before typing:** Run these commands in a normal, non-elevated PowerShell window. Where a file is used, complete the previous practice-folder chapters first. Do not paste the `PS C:\...>` prompt into the terminal.

**Start:** Use the Windows Start menu or Windows Terminal to open PowerShell. Check the prompt is ready. Commands beginning with `$` are still commands; type them exactly as shown.

### Step 1 — Open PowerShell and ask where you are

```powershell
Get-Location
```

**Expected observation:** A path is displayed. You have observed the current folder, not changed it.

**Check:** Read the output before continuing. If it does not match, stop and investigate the specific command; do not add `-Force` or run as Administrator automatically.

### Step 2 — Identify the signed-in account

```powershell
whoami
```

**Expected observation:** Windows prints the account under which the command is running.

**Check:** Read the output before continuing. If it does not match, stop and investigate the specific command; do not add `-Force` or run as Administrator automatically.

### Step 3 — List the visible files

```powershell
Get-ChildItem
```

**Expected observation:** A list is returned or nothing is shown for an empty directory.

**Check:** Read the output before continuing. If it does not match, stop and investigate the specific command; do not add `-Force` or run as Administrator automatically.

## Linux comparison — terminal/Bash

> Linux commands are alternatives on a Linux machine or authorised VM. Do not paste them into Windows PowerShell as though the shells have identical syntax.

### Linux step 1 — Ask which account is running

```bash
whoami
```

**Expected observation:** The current account name appears.

### Linux step 2 — Show current folder

```bash
pwd
```

**Expected observation:** Linux prints the current path.

## Worked support scenario

A teacher reports that an application cannot save assignments. Do not immediately reinstall it. First confirm the affected account, the path being saved to, the free space, and the error message. Record whether another document can be saved in a safe training folder. Only then select a corrective action. This is a miniature incident investigation, not guesswork.

## Common problems and how to respond

| Problem or assumption | Better response |
|---|---|
| Changing settings before gathering evidence | Write down the symptom and inspect the environment first. |
| Assuming administrator access is always required | Begin with an ordinary account; elevation is a separate decision. |
| Treating a successful program launch as proof everything works | Verify the real user task, such as saving and reopening a file. |

## Exercise: demonstrate understanding

1. Write down the purpose of **two commands** from this chapter, in your own words.
2. Run a **read-only command** and record only the information needed to answer its question.
3. Explain which command would change the machine, if any, and why the chapter avoids it.
4. Explain the difference between an observation, a conclusion and an unverified assumption.

## Review questions

1. What is the difference between observing and changing a system?
2. Why should an administrator have a recovery plan?

<details><summary>Show the suggested answers</summary>

1. Observation collects evidence; a change alters the system state.
2. Changes can cause unintended effects, and recovery limits data loss and downtime.

</details>

## How this connects to Umicom

For Umicom Studio, observation means checking the current build, logs and user workspace before editing Framework source. For Umicom OS, the distinction is even stronger: a successful boot does not prove that every user-space service is healthy.

## Where to go next

Continue with [Chapter 02 — Understand the computer, operating system and user account](02-computer-os-and-user-accounts.md).
