# Chapter 39 — Understand accounts, groups and scheduled work

**Bits to Banking · System Administration: From Zero · Umicom Foundation**  
**Audience:** beginners of any age; younger learners should use a supervised computer.  
**Suggested study time:** 60–80 minutes.  
**Before this chapter:** Chapters 9, 25 and 26: identities and permissions.

## The question this chapter answers

**How can I understand and check this part of a computer without accidentally changing something important?**

## Why this matters

An administrator must know who is allowed to run a task and when it will run. A user account represents an identity; a group groups permissions; a scheduled task executes at a chosen trigger such as logon or a time. A task may run under a different identity from the person who configured it. This difference explains why a task that succeeds in an interactive terminal sometimes fails unattended.

The safe beginner exercise is read-only. We will inspect our identity and the existence of scheduled work. Creating scheduled jobs that alter system settings or run privileged commands requires separate approval and is not part of this batch.

## A useful mental model

Picture a library. The cardholder is the identity, membership in the staff group allows certain actions, and an appointment book says when work happens. A scheduled task has all three concerns: a trigger, an execution identity and an action. A human typing a command has an interactive session and usually a different environment from a background task.

## Key terms, explained before using them

| Term | Meaning |
|---|---|
| **Security principal** | An identity that can receive permissions. |
| **Group** | A named set of identities used to simplify authorisation. |
| **Scheduled task** | An OS-managed declaration of what should run and when. |
| **Trigger** | An event or time that makes a task eligible to run. |
| **Service account** | An identity intended to run software rather than represent a human user. |
| **Environment** | Settings and paths available to a process when it starts. |

## Read this before typing commands

> **Authorisation and safety:** Use your own computer or an explicitly authorised learning environment. Start with an ordinary user account. Commands that install software, change access, restart services or modify networks are outside this exercise unless the text clearly identifies a harmless practice-file operation. You never need to disable a firewall or change system permissions to complete this chapter.

> **Reading code blocks:** Open PowerShell 7 on Windows (`pwsh`) or a terminal on Linux. Type the line inside the block, not the example prompt. Run one command at a time. Some examples contain multiple interactive commands separated by semicolons; verify their results individually. These are interactive commands, **not scripts added to Umicom**.

## Windows — PowerShell 7 practice

Do these steps on Windows. If you use Linux, read them for comparison and continue below. A missing command means that a tool or module may be unavailable; it is not a reason to bypass computer policy.

### Step 1 — Identify your signed-in Windows account

```powershell
whoami
```

**Expected result:** The current account appears in domain-or-machine\username form.

**Why this command matters:** This reads the identity of the current process. It does not list passwords or prove which permissions a remote service has.

**Safety and troubleshooting:** Avoid posting your full account identifier publicly if privacy matters.

### Step 2 — Inspect group memberships

```powershell
whoami /groups
```

**Expected result:** Group names and security attributes appear.

**Why this command matters:** Membership can explain why a command is authorised or refused, but some tokens have disabled or filtered groups.

**Safety and troubleshooting:** Do not assume the presence of Administrators in the output means the current command prompt is elevated.

### Step 3 — Inspect a sample of scheduled tasks

```powershell
Get-ScheduledTask | Select-Object -First 8 TaskName, State, TaskPath
```

**Expected result:** A small table of task names and states appears where the module is available.

**Why this command matters:** This is an inventory operation. Task State such as Ready does not prove a task succeeded on its last run.

**Safety and troubleshooting:** Managed environments may restrict task visibility. Record the limitation rather than changing permissions.

### Step 4 — Read details of one existing task without changing it

```powershell
Get-ScheduledTask | Select-Object -First 1 | Select-Object TaskName, State, TaskPath
```

**Expected result:** The selected task's visible properties are displayed.

**Why this command matters:** Use Get-ScheduledTaskInfo separately when authorised to inspect execution results and timings.

**Safety and troubleshooting:** Avoid running, disabling or editing tasks that belong to the operating system.

## Linux — terminal practice

Run these in a Linux terminal on an authorised computer or VM. Some distributions do not install the same commands. An unavailable check should be reported as unavailable; do not assume an unobserved result is successful. No command below requires `sudo`.

### Step 1 — Inspect your effective identity and groups

```bash
id
```

**Expected result:** UID, primary GID and supplementary groups appear.

**Why this command matters:** Linux permission checks use numeric identifiers as well as names; they are not the same as Windows security identifiers.

**Safety and troubleshooting:** If this command is unavailable or access is refused, record the result. Do not alter system configuration simply to make the example succeed.

### Step 2 — List current user timer units on systemd systems

```bash
systemctl --user list-timers --all --no-pager
```

**Expected result:** Timers appear, or the list may be empty.

**Why this command matters:** A timer can trigger a service unit. Some systems do not use systemd; absence of the command does not mean Linux lacks scheduling.

**Safety and troubleshooting:** If this command is unavailable or access is refused, record the result. Do not alter system configuration simply to make the example succeed.

### Step 3 — Inspect your user account entry

```bash
getent passwd "$USER"
```

**Expected result:** A passwd database record may appear.

**Why this command matters:** Account listings are configuration metadata and never contain recoverable modern login passwords.

**Safety and troubleshooting:** If this command is unavailable or access is refused, record the result. Do not alter system configuration simply to make the example succeed.

## Worked Umicom support scenario

An overnight report did not run. The report works when started manually. Before changing anything, the administrator checks the task's configured account, trigger, last result, working directory and required network resources. A scheduled task can fail because its environment differs or its credential has expired; simply running it as Administrator can conceal the real cause and weaken controls.

### A disciplined investigation sequence

1. **Describe the symptom precisely.** Identify what failed and the expected result.
2. **Identify the environment.** Record current account, machine class, working directory and observation time; redact private identifiers.
3. **Run the smallest relevant read-only check.** Choose evidence that distinguishes two possible causes.
4. **Compare results with the requirement.** Missing, blocked or outdated checks are not successful checks.
5. **Separate fact and interpretation.** Label hypotheses explicitly.
6. **Propose, do not silently apply, a change.** State approval, effect, rollback and validation criteria.

## Common mistakes and how to respond

| Incorrect assumption | Better engineering response |
|---|---|
| The task exists, therefore it ran. | Configuration and execution evidence are separate. Look for last run time, result and application output. |
| An account name tells me every permission. | Effective permissions combine account, groups, ACLs, policy and current execution token. |
| A scheduled task should be fixed by granting broad admin rights. | First identify the specific resource and permission required; least privilege is the default. |

## Practical exercises — try these before opening the answers

1. Draw the three parts of scheduled work.
2. Explain an environment-dependent failure.
3. Invent a safe diagnostic question.

<details>
<summary><strong>Suggested answers and reasoning</strong> — open after attempting the exercises</summary>

1. **Draw the three parts of scheduled work.** Identify trigger, execution account and program/action.
2. **Explain an environment-dependent failure.** A scheduled task may lack an interactive PATH, mapped drive or working directory expected by manual execution.
3. **Invent a safe diagnostic question.** Ask whether the task was triggered and what process/result was recorded before suggesting a configuration change.

</details>

## Engineering connection: Umicom Framework

Recurring builds, data imports and reconciliation jobs must use Framework-owned task services and explicit service identities. A future Umicom administration panel may display schedules, but it must not silently create privileged Windows Task Scheduler or systemd jobs from untrusted user input.

## Short support-note template

```text
Observation ID: PRACTICE-____
Observed at (include timezone):
Authorised machine or learning environment:
User-visible symptom:
Command or test (never paste credentials):
Observed result:
What remains unknown:
Proposed next safe check:
Approval required before any change:
```

## References and further study

- https://learn.microsoft.com/powershell/module/scheduledtasks/get-scheduledtask
- https://www.freedesktop.org/software/systemd/man/latest/systemd.timer.html

**Course progression:** [Chapter 38](38-capture-an-operating-system-baseline.md) → **Chapter 39** → [Chapter 40](40-understand-disks-volumes-and-free-space.md).

---

**Safety reminder:** An honest *not available*, *not authorised* or *not run* result is better than a fabricated pass. No real system changes or remote repository writes are required.
