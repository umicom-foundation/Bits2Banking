# Chapter 98 — Windows Task Scheduler: discover tasks without changing them

**Bits to Banking · System Administration From Zero · Stage 8**  
**Prerequisites:** Course Chapters 1–96 provide optional foundation; this lesson explains new terms before use.  
**Audience:** Beginners, returning professionals, and supervised young learners.  
**Safety:** Read-only observations on a computer you own or are permitted to use. Never copy real secrets into exercises.

## What we are going to learn

Windows can run work at selected times or events. Learn to inspect existing scheduled tasks, their state and last result before creating or changing anything.

![Diagram — Windows Task Scheduler: discover tasks without changing them](../../assets/diagrams/sysadmin-task-schedulers-update45.svg)

## Understand the idea before typing

Do not confuse **Windows Terminal** (a window for shells) with **Task Scheduler** (a Windows system service). Scheduled tasks may belong to Windows, software vendors or administrators. Their settings can expose command lines, accounts and directories. Our beginner exercises **inspect** tasks; they do not enable, disable, run, register or remove them.

A task is described by a *trigger, an action, an execution identity, conditions and history*. For instance, a fictional Umicom Notes report might start every weekday. The trigger might fire, yet the action could fail because a path no longer exists, the user account lost permission or the machine was asleep. Checking only the trigger hides those problems. When a task has a nonzero last result, consult the action documentation and task history rather than assuming every nonzero code means the same failure.

## New terms explained

| Term | Plain-English meaning |
|---|---|
| **Task Scheduler** | Windows service that can launch a command on a trigger. |
| **Trigger** | A condition that starts a task, such as a time or sign-in. |
| **Action** | The executable and arguments associated with a scheduled task. |
| **Run-as identity** | The Windows account under which the task executes. |
| **Last task result** | A code returned by a task; interpretation depends on the action. |


## Windows laboratory — PowerShell 7

Open **Windows Terminal → PowerShell** or search for **PowerShell**. The prompt looks like `PS C:\Users\...>`; do **not** type the prompt itself. On Windows PowerShell 5.1, read-only commands may still work, but the project teaches PowerShell 7. Type the commands one line at a time:

```powershell
Get-Command Get-ScheduledTask
Get-ScheduledTask | Select-Object -First 8 TaskName, TaskPath, State
Get-ScheduledTask | Where-Object TaskName -Like "*Update*" | Select-Object -First 5 TaskName, TaskPath, State
```

**What to expect:** Run these commands on **Windows PowerShell 5.1 or PowerShell 7 on Windows**. `Get-ScheduledTask` may return many entries. `Select-Object -First` limits the output and is read-only. Do not copy an unknown task name into a “disable” command. The exact names, counts and times on your computer will differ; no precise output is assumed.

## Linux laboratory — terminal

Open your Linux terminal (for example a disposable virtual machine). These commands are read-only. If a command is unavailable, note your distribution and ask the instructor before installing anything.

```bash
systemctl list-timers --all --no-pager
crontab -l
```

**What to expect:** These are **comparisons**, not Windows Task Scheduler commands. `systemctl` works on a Linux system with systemd. `crontab -l` displays the current user’s cron entries; “no crontab for user” is a normal result. Neither creates jobs.

## Worked Umicom case study

Suppose a classroom Notes export is expected by 08:30 but the file is missing. A first-line operator inspects the task name and scheduled state, then asks the owner for its documented output path and success criterion. Seeing a Ready state does not mean the export finished. A safe investigation records the task path, trigger details, most recent run and **actual file evidence**, with private account details removed from the shared note. If the account lacks permission to view a task, the operator records the limitation instead of escalating privileges without approval.

## What if something goes wrong?

| Observation | Safe response |
|---|---|
| The cmdlet is unavailable | Confirm Windows and whether the ScheduledTasks module exists; use graphical Task Scheduler with authorised access. |
| Task shows Ready | Ready describes scheduling state, not successful business processing. |
| Task runs manually but not automatically | Review trigger, run-as identity, conditions and last-run history with the owner; do not edit silently. |

## Guided learner exercise

1. Open Windows search and find Task Scheduler, but do not change any system task. Compare its interface with the read-only PowerShell output.
2. Identify the difference between TaskName and TaskPath. Why may two tasks have a similar name?
3. Sketch an Umicom Notes report task, giving it a trigger, expected output, read-only success check and responsible owner.

## Self-check and suggested answers

**Answer 1:** TaskPath identifies the task folder/namespace, while TaskName identifies the item in that folder.

**Answer 2:** Task readiness and report completion need separate evidence.

## What this proves — and what it does not

These exercises teach how to collect observations and describe decisions. They are not a certification of any real Umicom deployment. A command completing successfully does not automatically mean that a business operation finished. In live work, only an authorised owner should change service configuration, scheduled jobs, firewall policy, backup retention or credentials, after impact assessment and recovery planning. New reusable monitoring or scheduling software belongs in **Umicom Framework**, preferably implemented in C23 or Assembly rather than new PowerShell/Python scripts.

**Further reading:** [Stage 8 overview](stage-8-index.md) · [Safe command reference](stage-8-safe-command-reference.md) · [Stage 8 glossary](stage-8-glossary.md).
