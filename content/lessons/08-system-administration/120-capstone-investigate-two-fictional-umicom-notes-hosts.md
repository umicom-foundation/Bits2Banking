# Chapter 120 — Capstone: investigate two fictional Umicom Notes hosts

**Bits to Banking · System Administration From Zero · Stage 9**  
**Audience:** Absolute beginners, adults, returning professionals and supervised younger learners.  
**Safety:** Observe only your own computer or an explicitly authorised practice environment. Live changes are not required.

## Why this matters

This assessment combines the previous lessons into a two-host investigation. **No real remote machines exist in this exercise.** Gateway reports Notes save failure at 14:03 UTC, even though its process is Running. Storage reports a read-only data filesystem at 14:02 UTC and a mismatched package checksum. The last verified restore drill was six weeks ago against a four-week limit. Host clocks differ by three minutes. A prior proposed release was rolled back and the independent reviewer has not completed the recovery check.

Your goal is an evidence-based support report—not to execute fixes. Separate known observations, unverified claims and hypotheses. Do not assume the timestamps establish causation. Explain why the newer release must not be described as successful even if the old revision is restored.

![Diagram: Capstone: investigate two fictional Umicom Notes hosts](../../assets/diagrams/sysadmin-rollout-review-update46.svg)

## Learning objectives

After the lesson you should be able to explain the new terminology, run and understand a small read-only observation, distinguish observations from assumptions, and record the next safe action when a check is incomplete. A professional answer can be **not checked**, **not authorised** or **requires escalation**.

## Step-by-step Windows laboratory — PowerShell 7

Open Start, type **PowerShell**, and choose PowerShell 7 where available. Do not type the `PS C:\...>` prompt. Run each command one line at a time. PowerShell 5.1 may also run these read-only commands where the associated feature is installed.

```powershell
Get-Location
Get-Date -Format o
Get-ComputerInfo | Select-Object WindowsProductName, OsVersion
Get-PSDrive -PSProvider FileSystem
```

**Interpret the result:** The output will describe *your* computer, not the fictional Umicom hosts. Names, dates and versions will differ. Record the time and the important fields. If the command cannot run or permission is denied, mark the observation incomplete rather than inventing a value. A command's exit status only reports the command's own work.

## Step-by-step Linux laboratory — Terminal

On Linux use an account you own or are permitted to use, preferably in a disposable VM. These are observational commands unless the lesson explicitly describes a practice file you create in your home directory; you do not need `sudo`.

```bash
pwd
date -Is
cat /etc/os-release
df -h
```

**Interpret the result:** Not all distributions install the same management tools or use systemd. Preserve errors as troubleshooting evidence. Do not install random replacements, change unit files or edit firewall rules to make classroom output look identical to a screenshot.

### An example of a defensible decision

Record “**BLOCKED — user-facing Notes save failed; storage may be read-only; artifact digest mismatch and stale restore drill need owner review**.” Record the earlier release as “**Failed**” and the previous version as “**Restored only if independently verified**.” The clocks disagree by three minutes, so event ordering is uncertain. The correct next action is an authorised evidence review and safe, isolated recovery drill—not unapproved restarts, force pushes or file deletion.

## Worked Umicom example

Write a support timeline, list at least four blockers, assign next steps to an authorised owner and identify a safe business-facing restore check. Then build the C23 `labs/native/fleet-readiness` exercise: it reports PENDING with missing host evidence, BLOCKED on a failed Notes operation, REVIEWABLE only when all required fictional controls pass, and RESTORED_ONLY for independent recovery of the previous revision.

## Exercises

Deliver a one-page incident report with source, timestamps, observation status, unknowns, permissions and next owner. List why mismatched package provenance, stale recovery evidence, failed save and clock skew block a new release.

## Suggested answer and review criteria

A complete answer names the host, exact observation, source, timestamp with a time-zone offset, and reviewer or next owner. It also states what the command **does not** prove. In particular, a process Running is not proof of a completed Notes save, and an old release restored after failure does not make the failed proposed release successful.

## Common questions

**What if my command gives an error?** Read the exact message and check where you are with `Get-Location` on Windows or `pwd` on Linux. If the tool is not installed, note that fact. If it requires permissions you do not have, stop and contact the owner.

**What if my output differs from the book?** Computers differ. Compare the *fields and meaning* rather than expecting the same host name, drive size or process list. Never fabricate a result.

**Can I apply these commands to another person's machine?** Only after permission has been given and the information has been classified appropriately. This course never grants system-administration authority.

**Further practice:** Review [Chapter 108](108-capstone-seven-day-operations-plan.md) for the seven-day plan, then complete the Stage 9 workbook and [Chapter 120](120-capstone-investigate-two-fictional-umicom-notes-hosts.md) for the two-host exercise.
