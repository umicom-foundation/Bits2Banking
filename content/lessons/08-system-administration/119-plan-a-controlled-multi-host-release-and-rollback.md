# Chapter 119 — Plan a controlled multi-host release and rollback

**Bits to Banking · System Administration From Zero · Stage 9**  
**Audience:** Absolute beginners, adults, returning professionals and supervised younger learners.  
**Safety:** Observe only your own computer or an explicitly authorised practice environment. Live changes are not required.

## Why this matters

A **rollout** moves a proposed release to one or more hosts. A **canary** checks one small deployment before expanding exposure. A **rollback** returns to a previous state but is not recovery evidence until tested. An administrator must know each host's current revision, approved artifact checksum, owner, maintenance window, acceptance test and stop rule.

When one host's checksum differs, do not assume two files with similar names are identical. Stop and compare provenance. A working gateway canary cannot prove that a storage update is safe. A failed canary must block expansion even if a restart makes a green uptime graph. This is a planning lesson; no real software is installed or services restarted.

![Diagram: Plan a controlled multi-host release and rollback](../../assets/diagrams/sysadmin-rollout-review-update46.svg)

## Learning objectives

After the lesson you should be able to explain the new terminology, run and understand a small read-only observation, distinguish observations from assumptions, and record the next safe action when a check is incomplete. A professional answer can be **not checked**, **not authorised** or **requires escalation**.

## Step-by-step Windows laboratory — PowerShell 7

Open Start, type **PowerShell**, and choose PowerShell 7 where available. Do not type the `PS C:\...>` prompt. Run each command one line at a time. PowerShell 5.1 may also run these read-only commands where the associated feature is installed.

```powershell
Get-Date -Format o
Get-ComputerInfo | Select-Object WindowsProductName, OsVersion
Get-PSDrive -PSProvider FileSystem
```

**Interpret the result:** The output will describe *your* computer, not the fictional Umicom hosts. Names, dates and versions will differ. Record the time and the important fields. If the command cannot run or permission is denied, mark the observation incomplete rather than inventing a value. A command's exit status only reports the command's own work.

## Step-by-step Linux laboratory — Terminal

On Linux use an account you own or are permitted to use, preferably in a disposable VM. These are observational commands unless the lesson explicitly describes a practice file you create in your home directory; you do not need `sudo`.

```bash
date -Is
cat /etc/os-release
df -h
```

**Interpret the result:** Not all distributions install the same management tools or use systemd. Preserve errors as troubleshooting evidence. Do not install random replacements, change unit files or edit firewall rules to make classroom output look identical to a screenshot.

### Review gates in a safe order

Start with inventory and exact release identity, then check package provenance, staging environment, impact and rollback design. Perform an approved small canary only in a disposable environment, collect independent evidence, and stop on a failed requirement. A new release needs its own functional and dependency tests, not just a successful process start. If the old release is restored, report recovery **separately** from success of the attempted change.

## Worked Umicom example

Fictional plan: record gateway and storage baselines; stage a reviewed artifact; run a Notes save/load exercise on an isolated canary; compare the result with the acceptance plan; obtain independent approval before any additional host. If the save fails, record the attempted release as Failed and verify the previous release separately.

## Exercises

Create a rollout checklist with approved revision, package digest, host owner, user-facing acceptance, stop trigger and restored-old-version check. What extra review does a data migration require?

## Suggested answer and review criteria

A complete answer names the host, exact observation, source, timestamp with a time-zone offset, and reviewer or next owner. It also states what the command **does not** prove. In particular, a process Running is not proof of a completed Notes save, and an old release restored after failure does not make the failed proposed release successful.

## Common questions

**What if my command gives an error?** Read the exact message and check where you are with `Get-Location` on Windows or `pwd` on Linux. If the tool is not installed, note that fact. If it requires permissions you do not have, stop and contact the owner.

**What if my output differs from the book?** Computers differ. Compare the *fields and meaning* rather than expecting the same host name, drive size or process list. Never fabricate a result.

**Can I apply these commands to another person's machine?** Only after permission has been given and the information has been classified appropriately. This course never grants system-administration authority.

**Further practice:** Review [Chapter 108](108-capstone-seven-day-operations-plan.md) for the seven-day plan, then complete the Stage 9 workbook and [Chapter 120](120-capstone-investigate-two-fictional-umicom-notes-hosts.md) for the two-host exercise.
