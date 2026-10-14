# Chapter 18 — Linux permissions, packages, services and logs

**Bits to Banking · System Administration: From Zero · Umicom Foundation**  
**Audience:** first-time users and returning learners; no prior system-administration knowledge required.  
**Code policy:** interactive PowerShell 7 and Bash commands; native C23/Assembly for Umicom executable development.  
**Estimated study time:** 25–50 minutes (longer when practising).

## What you will learn

Observe essential Linux administration concepts without changing a shared system.

## Why this matters

![Computer layers: each layer has a different job](../../assets/diagrams/sysadmin-os-layers-update38.svg)


Linux often represents traditional file permissions with owner, group and mode bits. For a file, the `r` permission means read, `w` means write and `x` can mean execute. A directory has related but different access semantics: entering it requires search/execute permission. Permission output is a first clue, not a complete security model; ACLs and other mechanisms may also apply.

Package managers differ among distributions. Debian and Ubuntu commonly use `apt`; Fedora often uses `dnf`; Arch Linux uses `pacman`. There is no universal command that you should copy from one distribution to another. We keep the exercises observational: inspect packages and service status, but do not start automatic upgrades without approval.

Systemd is common on Linux machines and uses services called units, but other init systems exist. Logs may be in the systemd journal or files under `/var/log`. The current account’s permissions determine what can be read.

## New words, explained

| Term | Plain-English meaning |
|---|---|
| **Owner/group** | Account and group associated with a file. |
| **Mode bits** | Traditional `rwx` permissions shown by `ls -l`. |
| **apt** | Package-manager interface on Debian-derived systems. |
| **systemd unit** | Configuration and state of a managed Linux service. |
| **journalctl** | Command for reading systemd journal events. |

## Windows practice — PowerShell 7

> **Before typing:** Run these commands in a normal, non-elevated PowerShell window. Where a file is used, complete the previous practice-folder chapters first. Do not paste the `PS C:\...>` prompt into the terminal.

**Start:** Use the Windows Start menu or Windows Terminal to open PowerShell. Check the prompt is ready. Commands beginning with `$` are still commands; type them exactly as shown.

### Step 1 — From PowerShell inspect a practice Windows file as comparison

```powershell
Get-Item "$HOME\UmicomLearning\Notes\README.md" | Select-Object Name, Length
```

**Expected observation:** You see Windows file metadata; Linux commands below are separate.

**Check:** Read the output before continuing. If it does not match, stop and investigate the specific command; do not add `-Force` or run as Administrator automatically.

## Linux comparison — terminal/Bash

> Linux commands are alternatives on a Linux machine or authorised VM. Do not paste them into Windows PowerShell as though the shells have identical syntax.

### Linux step 1 — Display identity and group membership

```bash
id
```

**Expected observation:** UID, GID and groups are printed.

### Linux step 2 — Inspect traditional file permissions

```bash
ls -l "$HOME/UmicomLearning/Notes/README.md"
```

**Expected observation:** A mode string, owner and group appear if the practice file exists.

### Linux step 3 — Read the apt version where available

```bash
apt --version
```

**Expected observation:** Shows apt version on Debian/Ubuntu; other distributions need their package manager.

### Linux step 4 — Inspect services without changing them

```bash
systemctl --type=service --state=running --no-pager | head -n 12
```

**Expected observation:** A summary of active systemd services appears if systemd is used.

### Linux step 5 — Read a few journal entries if permitted

```bash
journalctl -n 8 --no-pager
```

**Expected observation:** Recent journal events appear or permissions restrict access.

## Worked support scenario

A Linux service stops after an upgrade. First check the unit state and relevant journal messages, then identify the exact package version and configuration changes. Do not run a broad upgrade or reset permissions simply because one service failed.

## Common problems and how to respond

| Problem or assumption | Better response |
|---|---|
| Treating `chmod 777` as a normal troubleshooting tool | It grants overly broad access; understand the correct policy first. |
| Running `apt upgrade` automatically as a practice task | Inspect updates and obtain permission before changing installed software. |
| Assuming journal entries are visible to every user | Log access can be restricted by account and group. |

## Exercise: demonstrate understanding

1. Write down the purpose of **two commands** from this chapter, in your own words.
2. Run a **read-only command** and record only the information needed to answer its question.
3. Explain which command would change the machine, if any, and why the chapter avoids it.
4. Explain the difference between an observation, a conclusion and an unverified assumption.

## Review questions

1. What do `r`, `w`, and `x` represent in traditional file permissions?
2. Why must a package manager be selected for the distribution?

<details><summary>Show the suggested answers</summary>

1. Read, write and execute/search permissions.
2. Distributions use different package systems and repositories.

</details>

## How this connects to Umicom

Umicom OS host and recovery services should be diagnosed at the correct privilege boundary. Learners should distinguish a Linux service problem from a bug in Umicom Framework user-space code.

## Where to go next

Continue with [Chapter 19 — Git from zero: create, inspect, stage and commit](19-git-local-repository-and-first-commit.md).
