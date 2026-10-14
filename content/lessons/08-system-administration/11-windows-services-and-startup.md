# Chapter 11 — Windows services: background programs and startup

**Bits to Banking · System Administration: From Zero · Umicom Foundation**  
**Audience:** first-time users and returning learners; no prior system-administration knowledge required.  
**Code policy:** interactive PowerShell 7 and Bash commands; native C23/Assembly for Umicom executable development.  
**Estimated study time:** 25–50 minutes (longer when practising).

## What you will learn

Identify a Windows service and understand status without changing it.

## Why this matters

![Diagnose a service by collecting several independent observations](../../assets/diagrams/sysadmin-process-log-update38.svg)


Some programs begin running when the computer starts or when a user signs in. Windows services are a particular class of background programs managed through the Service Control Manager. A service can be running, stopped or in a transition. Not every background process is a Windows service, and not every stopped service indicates a fault: many start only when their feature is needed.

PowerShell `Get-Service` observes service status. Windows also provides the Services management console for a graphical view. Configuration and restart actions can affect other applications or users, so we do not run `Restart-Service` in this beginner chapter.

A reliable diagnostic identifies a particular service by name, records its state, consults the relevant events and verifies the user-visible function. An administrator should distinguish the technical process from the service the user actually cares about.

## New words, explained

| Term | Plain-English meaning |
|---|---|
| **Windows service** | Background service managed by the Windows Service Control Manager. |
| **Status** | Current observed service state, such as Running or Stopped. |
| **Startup type** | Policy controlling when a service may start. |
| **Dependency** | Another service required by a component. |
| **Service manager** | Windows component that controls service lifecycle. |

## Windows practice — PowerShell 7

> **Before typing:** Run these commands in a normal, non-elevated PowerShell window. Where a file is used, complete the previous practice-folder chapters first. Do not paste the `PS C:\...>` prompt into the terminal.

**Start:** Use the Windows Start menu or Windows Terminal to open PowerShell. Check the prompt is ready. Commands beginning with `$` are still commands; type them exactly as shown.

### Step 1 — List a few services

```powershell
Get-Service | Select-Object -First 10 Name, DisplayName, Status
```

**Expected observation:** A short list of services is displayed.

**Check:** Read the output before continuing. If it does not match, stop and investigate the specific command; do not add `-Force` or run as Administrator automatically.

### Step 2 — Inspect details of a service that is installed

```powershell
Get-Service -Name Spooler -ErrorAction SilentlyContinue | Format-List *
```

**Expected observation:** If the Print Spooler exists, PowerShell shows its properties; an empty result is not an error.

**Check:** Read the output before continuing. If it does not match, stop and investigate the specific command; do not add `-Force` or run as Administrator automatically.

### Step 3 — Open the graphical Services console

```powershell
services.msc
```

**Expected observation:** A service list opens; view settings without modifying them.

**Check:** Read the output before continuing. If it does not match, stop and investigate the specific command; do not add `-Force` or run as Administrator automatically.

## Linux comparison — terminal/Bash

> Linux commands are alternatives on a Linux machine or authorised VM. Do not paste them into Windows PowerShell as though the shells have identical syntax.

### Linux step 1 — Show services on a systemd-based Linux machine

```bash
systemctl list-units --type=service --state=running --no-pager | head -n 12
```

**Expected observation:** A list of running systemd services appears where systemd is present.

### Linux step 2 — Inspect a named service when installed

```bash
systemctl status ssh --no-pager
```

**Expected observation:** Status appears if the `ssh` unit exists; some distributions use `sshd`, and others may not have SSH installed.

## Worked support scenario

A shared classroom printer is unavailable. The service name `Spooler` is relevant on Windows, but a stopped service alone does not prove the printer hardware or network is working. Record the service status, printer connection and reported queue state before choosing a fix.

## Common problems and how to respond

| Problem or assumption | Better response |
|---|---|
| Restarting an unknown service just to “see what happens” | Observe its purpose and potential dependencies first. |
| Assuming every stopped service is broken | Some services are optional or start only when needed. |
| Confusing startup applications with services | Startup apps and service units use different management mechanisms. |

## Exercise: demonstrate understanding

1. Write down the purpose of **two commands** from this chapter, in your own words.
2. Run a **read-only command** and record only the information needed to answer its question.
3. Explain which command would change the machine, if any, and why the chapter avoids it.
4. Explain the difference between an observation, a conclusion and an unverified assumption.

## Review questions

1. Does stopped always mean failed?
2. Why should service restarts be approved?

<details><summary>Show the suggested answers</summary>

1. No; a service may legitimately be disabled or started on demand.
2. They can interrupt active work and dependent systems.

</details>

## How this connects to Umicom

Application service health needs business-level verification. A running native Umicom service may still be unable to load a workspace or fulfil a request.

## Where to go next

Continue with [Chapter 12 — Windows Event Viewer and useful troubleshooting records](12-read-windows-events-and-logs.md).
