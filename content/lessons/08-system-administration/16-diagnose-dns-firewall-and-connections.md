# Chapter 16 — Troubleshoot a failed connection one layer at a time

**Bits to Banking · System Administration: From Zero · Umicom Foundation**  
**Audience:** first-time users and returning learners; no prior system-administration knowledge required.  
**Code policy:** interactive PowerShell 7 and Bash commands; native C23/Assembly for Umicom executable development.  
**Estimated study time:** 25–50 minutes (longer when practising).

## What you will learn

Record evidence distinguishing name resolution, connectivity and authentication problems.

## Why this matters

![Diagnose one network layer at a time](../../assets/diagrams/sysadmin-network-layers-update38.svg)


A useful network investigation follows a sequence. First, identify the exact operation that failed and its error message. Second, check whether the local network interface is connected and has an address. Third, ask DNS for the remote name. Fourth, attempt a connection to the expected service port. Finally, inspect application authentication and permissions. Do not disable the firewall or certificate checks simply to see whether the problem disappears.

The order matters because some errors have unrelated causes. A GitHub push rejection saying “non-fast-forward” is **not** a network outage—it means the remote branch has history that your local push would not preserve. A TLS certificate warning is also different from failure to resolve a DNS name.

The commands in this chapter are read-only connection probes to a known public service. They may time out on restricted networks. Write down the outputs and tell the reader what conclusion is justified by each, rather than assuming success everywhere.

## New words, explained

| Term | Plain-English meaning |
|---|---|
| **Connectivity** | Ability to exchange traffic with a service. |
| **Timeout** | Operation failed to complete within a limit. |
| **Firewall** | Policy enforcing which network traffic is allowed. |
| **TLS** | Protocol protecting communication with authentication and encryption. |
| **Authentication** | Process by which a system verifies account identity. |

## Windows practice — PowerShell 7

> **Before typing:** Run these commands in a normal, non-elevated PowerShell window. Where a file is used, complete the previous practice-folder chapters first. Do not paste the `PS C:\...>` prompt into the terminal.

**Start:** Use the Windows Start menu or Windows Terminal to open PowerShell. Check the prompt is ready. Commands beginning with `$` are still commands; type them exactly as shown.

### Step 1 — Check local adapter configuration

```powershell
Get-NetIPConfiguration
```

**Expected observation:** An active interface normally has a valid address and gateway.

**Check:** Read the output before continuing. If it does not match, stop and investigate the specific command; do not add `-Force` or run as Administrator automatically.

### Step 2 — Test name resolution separately

```powershell
Resolve-DnsName github.com
```

**Expected observation:** Addresses appear if the resolver succeeds.

**Check:** Read the output before continuing. If it does not match, stop and investigate the specific command; do not add `-Force` or run as Administrator automatically.

### Step 3 — Test the expected TCP endpoint

```powershell
Test-NetConnection github.com -Port 443
```

**Expected observation:** A successful TCP test is separate evidence from a DNS lookup.

**Check:** Read the output before continuing. If it does not match, stop and investigate the specific command; do not add `-Force` or run as Administrator automatically.

### Step 4 — Check GitHub CLI authentication separately

```powershell
gh auth status
```

**Expected observation:** The output describes account authentication if `gh` is installed.

**Check:** Read the output before continuing. If it does not match, stop and investigate the specific command; do not add `-Force` or run as Administrator automatically.

## Linux comparison — terminal/Bash

> Linux commands are alternatives on a Linux machine or authorised VM. Do not paste them into Windows PowerShell as though the shells have identical syntax.

### Linux step 1 — Test DNS through the normal resolver

```bash
getent hosts github.com
```

**Expected observation:** An address result means the configured resolver returned a response.

### Linux step 2 — Inspect service response headers with curl

```bash
curl -I --max-time 10 https://github.com
```

**Expected observation:** An HTTP response or a specific TLS/network error appears; internet access is required.

## Worked support scenario

Three contributors report “Git is broken.” One has no DNS response, one can reach GitHub but is not authenticated, and one has a non-fast-forward push rejection. They have different problems. A reproducible evidence sequence prevents installing software or editing repositories unnecessarily.

## Common problems and how to respond

| Problem or assumption | Better response |
|---|---|
| Disabling firewall protections to bypass a diagnostic | Obtain authorisation and find the actual failing boundary instead. |
| Confusing authentication errors with routing errors | Check reachability and `gh auth status` independently. |
| Assuming one successful request proves permanent reliability | Repeat during the incident window and collect relevant logs. |

## Exercise: demonstrate understanding

1. Write down the purpose of **two commands** from this chapter, in your own words.
2. Run a **read-only command** and record only the information needed to answer its question.
3. Explain which command would change the machine, if any, and why the chapter avoids it.
4. Explain the difference between an observation, a conclusion and an unverified assumption.

## Review questions

1. What does a non-fast-forward Git error usually indicate?
2. Why separate DNS and TCP tests?

<details><summary>Show the suggested answers</summary>

1. Remote and local commit ancestry, not a basic networking failure.
2. They diagnose different layers and can fail independently.

</details>

## How this connects to Umicom

Retain the full Git error output and compare it with Framework VCS observations before changing repository state. The safest diagnostic commands are read-only.

## Where to go next

Continue with [Chapter 17 — Linux terminal, home directory, files and processes](17-linux-terminal-files-and-processes.md).
