# Chapter 51 — Read systemd units and understand service startup order

**System Administration From Zero · Stage 4 — Managed Services and Recovery**  
**Author:** Sammy Hegab · Umicom Foundation  
**Study time:** 70–90 minutes  
**Before starting:** Chapters 28, 45 and 49: Linux services, dependencies and readiness  
**Safety level:** observation-only on real systems; any practice writes are confined to a folder owned by the learner.

## What you will achieve

By the end of this chapter, you will be able to explain **read systemd units and understand service startup order**, identify the difference between an observation and a change, and interpret at least one Windows and one Linux administration result. You will also be able to describe the evidence that an authorised Umicom support engineer would need before taking action.

## Why this matters in everyday computing

When a Linux computer starts, systemd can arrange for services to start in a suitable order. Each unit has settings about dependencies, commands and restart behaviour. A system administrator often needs to understand why a service did not start or why it started before a required resource was available.

This lesson explains unit files without asking students to install a custom system service. We read existing configuration from an authorised Linux host. On Windows, we compare the similar idea through the Windows Service Control Manager. You will learn why configured startup order cannot substitute for a real application readiness check.

## A mental model you can remember

A theatre performance has a sequence of events: the stage lights need power, the doors open, the actors enter, and then the show begins. ‘After’ in a unit file is like saying the actors enter after the lights are switched on. It does not necessarily mean that every seat is occupied or that the actors have learned their lines. Dependencies coordinate lifecycle events; functional readiness must still be checked separately.

## New words, without jargon

| Term | Meaning |
|---|---|
| **Unit file** | Configuration describing a systemd service or another managed object. |
| **After=** | An ordering relation: start this unit after another when both are scheduled. |
| **Requires=** | A stronger unit dependency with failure implications; details depend on the transaction. |
| **Wants=** | A weaker relationship that requests another unit without the same failure coupling. |
| **Restart=** | A policy controlling whether systemd retries a terminated service. |
| **Readiness probe** | A functional test that decides whether the service can do its intended work. |

## Windows practical lesson — PowerShell 7

Open **Windows Terminal → PowerShell**, or search for **PowerShell 7**. Type only the commands inside each box; the example `PS C:\...>` prompt is not part of a command. Unless a step explicitly says otherwise, use your normal non-administrator account. The commands are interactive teaching instructions, not a `.ps1` script.

### Step 1 — Read service startup configuration

```powershell
Get-Service -Name EventLog | Select-Object Name, Status, StartType
```

**Expected result:** The service's startup type appears, normally Automatic for EventLog.

**What it means:** Automatic means the manager is configured to start it. It does not guarantee that your application will be ready afterward.

**If it looks different:** Do not modify Set-Service options on a shared computer.

### Step 2 — See service dependencies

```powershell
Get-Service -Name EventLog | Select-Object -ExpandProperty ServicesDependedOn
```

**Expected result:** Zero or more dependent service records appear.

**What it means:** An empty result can be valid. A dependency graph and a process state are different observations.

**If it looks different:** If querying the service is restricted, keep the evidence and ask an authorised administrator.

### Step 3 — Read the exact configured service name

```powershell
Get-Service -Name EventLog | Format-List Name,DisplayName,Status,StartType
```

**Expected result:** The individual service properties are shown.

**What it means:** `Format-List` is a display operation, not a change to the service. In shared notes capture only fields needed for troubleshooting.

**If it looks different:** Do not post computer names or account identities publicly.

## Linux practical comparison

On a Linux computer or an authorised virtual machine, open a terminal. These are **Bash-compatible commands**; do not type the `$` prompt. A minimal container, Chromebook or non-systemd distribution may have a different set of tools. A missing optional tool should be recorded rather than bypassed.

### Linux step 1 — Read the journal unit's configuration

```bash
systemctl cat systemd-journald.service --no-pager
```

**Expected result:** The effective unit file and any visible drop-in configuration are printed.

**Interpretation:** Read headings such as [Unit] and [Service]. Do not copy configuration from the example into /etc/systemd/system.

### Linux step 2 — Inspect ordering relationships

```bash
systemctl show systemd-journald.service -p After -p Requires -p Wants --no-pager
```

**Expected result:** The names of related units appear as space-separated property values.

**Interpretation:** A listed unit is not proof that it responded successfully to an application request.

### Linux step 3 — Inspect recent unit messages

```bash
journalctl -u systemd-journald.service -n 10 --no-pager
```

**Expected result:** Up to ten recent unit-related log lines are shown, subject to permissions.

**Interpretation:** Logs may contain private paths or identifiers. Redact before sharing with a course group.

## Worked support scenario — Umicom Notes

A fictional Umicom OS Notes service is configured to start after storage mounts. Its service process launches, but its storage index is still being reconstructed. A service manager reports the process active while the Notes readiness check remains blocked. The correct design is to retain the ordering configuration and add a functional readiness gate through approved Framework supervision, not to add arbitrary sleep delays.

**Evidence record:** In your own words, describe the issue, the observation time, the command used, what you actually saw, what you have *not* proved, and who would approve a change. Avoid copying usernames, credentials, private filenames, IP addresses or confidential logs into public notes.

## Common mistakes and how to correct them

| Misunderstanding | Better interpretation |
|---|---|
| After= means the dependent application is ready. | After= primarily describes ordering, not successful completion of business work. |
| Restart=always solves every fault. | Repeated retries may create noise or worsen failures. Diagnose underlying causes and limits. |
| Editing a unit is the easiest beginner experiment. | An error in a real service unit can disrupt the machine; start with read-only inspection and an isolated VM for future writes. |

## Guided practice and suggested responses

**Exercise 1.** Explain two dependency types.

*Suggested response:* Contrast ordering and a required relationship without changing either.

**Exercise 2.** Find one unit setting.

*Suggested response:* Use systemctl cat, record a visible setting and explain it in plain language.

**Exercise 3.** Identify a functional probe.

*Suggested response:* Suggest a harmless test that would show fictional Notes storage can actually read a practice file.

## Questions for discussion

1. Which part of today's read systemd units and understand service startup order exercise was **read-only**, and how do you know?
2. What does a successful command prove, and what would it *not* prove?
3. Explain **Unit file** to somebody who has never opened a terminal.
4. If an expected result does not appear, what evidence would you collect before changing anything?
5. How would you explain this issue to a colleague without exposing private data?

## Connection to Umicom Framework and software engineering

Umicom Framework's supervised module lifecycle and readiness contracts should remain distinct from host systemd startup ordering. A module might report started but not yet ready until its Data Server or storage requirements are available. The C23 readiness laboratory from Update 40 models that distinction without using systemd APIs or scripts.

## Further reading (optional internet access)

- https://www.freedesktop.org/software/systemd/man/latest/systemd.unit.html
- https://www.freedesktop.org/software/systemd/man/latest/systemd.service.html

## Learning checkpoint

You are ready to proceed if you can explain **the command, its expected output, the boundary of what it proves, and a safe response to unexpected output**. If the exercise needed unavailable administrator access, record *not performed*; do not mark it as passed.

**Next:** [Chapter 52 — Inspect scheduled tasks, cron and systemd timers](./52-inspect-scheduled-tasks-cron-and-systemd-timers.md).
