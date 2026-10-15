# Chapter 109 — Build a trustworthy inventory of several computers

**Bits to Banking · System Administration From Zero · Stage 9**  
**Audience:** Absolute beginners, adults, returning professionals and supervised younger learners.  
**Safety:** Observe only your own computer or an explicitly authorised practice environment. Live changes are not required.

## Why this matters

A host is a computer or virtual machine with an operating system. When you manage more than one host, you need an **inventory**: a dated record of each machine's name, purpose, owner, OS, application version and evidence source. A baseline is an approved inventory snapshot that can be compared with later observations. A host name is a useful label, not proof of ownership or authenticity. Write **not checked** when you cannot verify a detail.

Our fictional Umicom Notes product uses `notes-gateway` for incoming requests and `notes-storage` to store documents. A green status page on the gateway does not establish that the storage host was checked. Each host needs independent, time-stamped evidence. Never collect private credentials or patient/customer information in a training inventory.

![Diagram: Build a trustworthy inventory of several computers](../../assets/diagrams/sysadmin-fleet-inventory-update46.svg)

## Learning objectives

After the lesson you should be able to explain the new terminology, run and understand a small read-only observation, distinguish observations from assumptions, and record the next safe action when a check is incomplete. A professional answer can be **not checked**, **not authorised** or **requires escalation**.

## Step-by-step Windows laboratory — PowerShell 7

Open Start, type **PowerShell**, and choose PowerShell 7 where available. Do not type the `PS C:\...>` prompt. Run each command one line at a time. PowerShell 5.1 may also run these read-only commands where the associated feature is installed.

```powershell
Get-Location
hostname
Get-ComputerInfo | Select-Object WindowsProductName, OsVersion, OsArchitecture
Get-Date -Format o
```

**Interpret the result:** The output will describe *your* computer, not the fictional Umicom hosts. Names, dates and versions will differ. Record the time and the important fields. If the command cannot run or permission is denied, mark the observation incomplete rather than inventing a value. A command's exit status only reports the command's own work.

## Step-by-step Linux laboratory — Terminal

On Linux use an account you own or are permitted to use, preferably in a disposable VM. These are observational commands unless the lesson explicitly describes a practice file you create in your home directory; you do not need `sudo`.

```bash
hostname
cat /etc/os-release
uname -m
date -Is
```

**Interpret the result:** Not all distributions install the same management tools or use systemd. Preserve errors as troubleshooting evidence. Do not install random replacements, change unit files or edit firewall rules to make classroom output look identical to a screenshot.

### Read the result, not merely its colour

`hostname` prints the machine's own reported name. `OsArchitecture` or `uname -m` describes the processor/operating-system architecture. `Get-Date -Format o` and `date -Is` show a timestamp with an offset, which is essential when you later compare hosts. A good inventory record has an **as-of time**; a screenshot with no time cannot establish current state. Be careful not to label your local test machine `notes-storage`: the fictional machine is not being queried.

## Worked Umicom example

Create a six-column inventory: *Host*, *Role*, *Owner*, *OS*, *Observed at* and *Verified?*. On your own computer, record a genuine observation. For the two fictional Umicom hosts, use `unknown` rather than copying your own results into their rows. A Git commit ID for application source is not the same as an OS version or installed package identity.

## Exercises

What proves that a host has been checked? Explain why an old screenshot does not count as current evidence. Give a reason that two computers can use the same Umicom Framework source revision but run different operating-system versions.

## Suggested answer and review criteria

A complete answer names the host, exact observation, source, timestamp with a time-zone offset, and reviewer or next owner. It also states what the command **does not** prove. In particular, a process Running is not proof of a completed Notes save, and an old release restored after failure does not make the failed proposed release successful.

## Common questions

**What if my command gives an error?** Read the exact message and check where you are with `Get-Location` on Windows or `pwd` on Linux. If the tool is not installed, note that fact. If it requires permissions you do not have, stop and contact the owner.

**What if my output differs from the book?** Computers differ. Compare the *fields and meaning* rather than expecting the same host name, drive size or process list. Never fabricate a result.

**Can I apply these commands to another person's machine?** Only after permission has been given and the information has been classified appropriately. This course never grants system-administration authority.

**Further practice:** Review [Chapter 108](108-capstone-seven-day-operations-plan.md) for the seven-day plan, then complete the Stage 9 workbook and [Chapter 120](120-capstone-investigate-two-fictional-umicom-notes-hosts.md) for the two-host exercise.
