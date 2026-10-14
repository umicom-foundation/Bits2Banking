# Chapter 12 — Windows Event Viewer and useful troubleshooting records

**Bits to Banking · System Administration: From Zero · Umicom Foundation**  
**Audience:** first-time users and returning learners; no prior system-administration knowledge required.  
**Code policy:** interactive PowerShell 7 and Bash commands; native C23/Assembly for Umicom executable development.  
**Estimated study time:** 25–50 minutes (longer when practising).

## What you will learn

Read event records safely and distinguish a symptom from its cause.

## Why this matters

![Diagnose a service by collecting several independent observations](../../assets/diagrams/sysadmin-process-log-update38.svg)


Programs, services and the operating system produce diagnostic events. A log record may include a timestamp, source and message. In Windows, Event Viewer groups records into logs such as Application and System. An Error event is worth investigating, but it does not automatically explain every user complaint, nor does the presence of warnings necessarily mean that a machine is unhealthy.

A useful investigation begins with the approximate time the problem occurred. Record the clock, including time zone if supporting someone remotely, then inspect the nearest relevant event and compare it with the user’s symptom. Use a small result limit so beginners are not overwhelmed by thousands of entries.

Some security logs require special privileges; do not request broader access simply to practise. Never delete event logs to make a warning disappear. Their value lies in retaining a trace of what happened.

## New words, explained

| Term | Plain-English meaning |
|---|---|
| **Event log** | Structured history of diagnostic events. |
| **Event ID** | Identifier for the event type, interpreted with its provider. |
| **Provider** | Component that recorded the event. |
| **Timestamp** | Recorded date and time. |
| **Correlation** | Connecting events that belong to the same underlying incident. |

## Windows practice — PowerShell 7

> **Before typing:** Run these commands in a normal, non-elevated PowerShell window. Where a file is used, complete the previous practice-folder chapters first. Do not paste the `PS C:\...>` prompt into the terminal.

**Start:** Use the Windows Start menu or Windows Terminal to open PowerShell. Check the prompt is ready. Commands beginning with `$` are still commands; type them exactly as shown.

### Step 1 — List details about the System log

```powershell
Get-WinEvent -ListLog System | Select-Object LogName, RecordCount, IsEnabled
```

**Expected observation:** Windows reports log metadata if available.

**Check:** Read the output before continuing. If it does not match, stop and investigate the specific command; do not add `-Force` or run as Administrator automatically.

### Step 2 — Read five recent system events

```powershell
Get-WinEvent -LogName System -MaxEvents 5 | Select-Object TimeCreated, Id, ProviderName, LevelDisplayName
```

**Expected observation:** A short set of events appears.

**Check:** Read the output before continuing. If it does not match, stop and investigate the specific command; do not add `-Force` or run as Administrator automatically.

### Step 3 — Open Event Viewer

```powershell
eventvwr.msc
```

**Expected observation:** A graphical console opens. Do not clear logs.

**Check:** Read the output before continuing. If it does not match, stop and investigate the specific command; do not add `-Force` or run as Administrator automatically.

## Linux comparison — terminal/Bash

> Linux commands are alternatives on a Linux machine or authorised VM. Do not paste them into Windows PowerShell as though the shells have identical syntax.

### Linux step 1 — View recent journal events if permitted

```bash
journalctl -n 10 --no-pager
```

**Expected observation:** Recent records appear; some systems restrict access by group membership.

### Linux step 2 — Inspect only the current user journal where supported

```bash
journalctl --user -n 10 --no-pager
```

**Expected observation:** User-specific records appear if journal access is configured.

## Worked support scenario

After an update, a reporting app fails to start. You record the failure time and compare the nearest related application event with the actual error displayed on screen. If the log refers to a missing DLL, you investigate package deployment before changing database records.

## Common problems and how to respond

| Problem or assumption | Better response |
|---|---|
| Searching the entire event history without a time range | Start near the incident time and widen gradually. |
| Treating any warning as the root cause | Check relevance, sequence and user impact. |
| Clearing logs to make a dashboard green | Preserve evidence; clearing removes useful history. |

## Exercise: demonstrate understanding

1. Write down the purpose of **two commands** from this chapter, in your own words.
2. Run a **read-only command** and record only the information needed to answer its question.
3. Explain which command would change the machine, if any, and why the chapter avoids it.
4. Explain the difference between an observation, a conclusion and an unverified assumption.

## Review questions

1. Why record the exact time of a problem?
2. Should you delete an event log to fix an application failure?

<details><summary>Show the suggested answers</summary>

1. It helps correlate logs and user actions.
2. No. It removes evidence and does not address the cause.

</details>

## How this connects to Umicom

Studio Problems, build logs, service health, and OS event records are separate evidence streams. Combine them without hiding errors or dropping the original transcript.

## Where to go next

Continue with [Chapter 13 — Inspect processor, memory, Windows version and resources](13-inspect-hardware-memory-and-os.md).
