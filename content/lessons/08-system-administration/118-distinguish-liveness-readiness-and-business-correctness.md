# Chapter 118 — Distinguish liveness, readiness and business correctness

**Bits to Banking · System Administration From Zero · Stage 9**  
**Audience:** Absolute beginners, adults, returning professionals and supervised younger learners.  
**Safety:** Observe only your own computer or an explicitly authorised practice environment. Live changes are not required.

## Why this matters

A process can exist, a TCP port can listen and a website can respond while the application's intended work still fails. **Liveness** asks whether a process is running. **Readiness** asks whether it can accept appropriate work. **Business correctness** asks whether the required authorised operation completed with the right result. These are not synonyms.

Umicom Notes gateway may pass a health route but be unable to save documents because storage is unavailable. Restarting the gateway does not repair a read-only filesystem. Tests must state precisely what was checked and which dependency remains unknown. Do not run production write tests without authorisation; use fictional evidence for this course.

![Diagram: Distinguish liveness, readiness and business correctness](../../assets/diagrams/sysadmin-windows-service-path-update46.svg)

## Learning objectives

After the lesson you should be able to explain the new terminology, run and understand a small read-only observation, distinguish observations from assumptions, and record the next safe action when a check is incomplete. A professional answer can be **not checked**, **not authorised** or **requires escalation**.

## Step-by-step Windows laboratory — PowerShell 7

Open Start, type **PowerShell**, and choose PowerShell 7 where available. Do not type the `PS C:\...>` prompt. Run each command one line at a time. PowerShell 5.1 may also run these read-only commands where the associated feature is installed.

```powershell
Get-Process | Select-Object -First 6 Name, Id, CPU
Get-Service | Select-Object -First 6 Name, Status
Test-NetConnection -ComputerName 127.0.0.1 -Port 8765
```

**Interpret the result:** The output will describe *your* computer, not the fictional Umicom hosts. Names, dates and versions will differ. Record the time and the important fields. If the command cannot run or permission is denied, mark the observation incomplete rather than inventing a value. A command's exit status only reports the command's own work.

## Step-by-step Linux laboratory — Terminal

On Linux use an account you own or are permitted to use, preferably in a disposable VM. These are observational commands unless the lesson explicitly describes a practice file you create in your home directory; you do not need `sudo`.

```bash
ps -eo pid,comm --sort=pid | head -n 8
ss -ltn | head -n 8
systemctl is-system-running
```

**Interpret the result:** Not all distributions install the same management tools or use systemd. Preserve errors as troubleshooting evidence. Do not install random replacements, change unit files or edit firewall rules to make classroom output look identical to a screenshot.

### Interpret the three kinds of checks

A liveness check observes that a process exists; readiness checks whether dependencies needed for work are available; correctness checks a specific authorised outcome. On a typical machine, `Get-Process` and `ps` are the first kind. A local listener may support the second but cannot establish it alone. The third needs a safe Notes-specific operation with expected data. Do not use a write-based test on a system you do not administer: record the missing check and ask the responsible owner.

## Worked Umicom example

Create separate green/amber/red fields for process, service, storage and Notes save. A process Running cannot change a failed Notes save to Pass. A restored previous release should be recorded as RESTORED_ONLY rather than the attempted new deployment succeeding.

## Exercises

Propose one check for each of liveness, readiness and business correctness. Is a successful ping or open TCP port a valid Notes save test?

## Suggested answer and review criteria

A complete answer names the host, exact observation, source, timestamp with a time-zone offset, and reviewer or next owner. It also states what the command **does not** prove. In particular, a process Running is not proof of a completed Notes save, and an old release restored after failure does not make the failed proposed release successful.

## Common questions

**What if my command gives an error?** Read the exact message and check where you are with `Get-Location` on Windows or `pwd` on Linux. If the tool is not installed, note that fact. If it requires permissions you do not have, stop and contact the owner.

**What if my output differs from the book?** Computers differ. Compare the *fields and meaning* rather than expecting the same host name, drive size or process list. Never fabricate a result.

**Can I apply these commands to another person's machine?** Only after permission has been given and the information has been classified appropriately. This course never grants system-administration authority.

**Further practice:** Review [Chapter 108](108-capstone-seven-day-operations-plan.md) for the seven-day plan, then complete the Stage 9 workbook and [Chapter 120](120-capstone-investigate-two-fictional-umicom-notes-hosts.md) for the two-host exercise.
