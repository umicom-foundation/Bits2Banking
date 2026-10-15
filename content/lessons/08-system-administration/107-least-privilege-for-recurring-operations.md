# Chapter 107 — Least privilege for recurring tasks, credentials and audit trails

**Bits to Banking · System Administration From Zero · Stage 8**  
**Prerequisites:** Course Chapters 1–96 provide optional foundation; this lesson explains new terms before use.  
**Audience:** Beginners, returning professionals, and supervised young learners.  
**Safety:** Read-only observations on a computer you own or are permitted to use. Never copy real secrets into exercises.

## What we are going to learn

Scheduled work can be powerful because it repeats without direct supervision. Learn why permissions, secret storage, limited scope and audit are essential.

![Diagram — Least privilege for recurring tasks, credentials and audit trails](../../assets/diagrams/sysadmin-change-windows-update45.svg)

## Understand the idea before typing

A scheduled job that can read every file or administer every service creates unnecessary risk. A Notes export task may need access to **one training export directory**, not the administrator’s entire home folder or every user’s files. The task’s output must not print private credentials or access tokens.

For learners, avoid creating service accounts or storing passwords in Task Scheduler or cron. Inspect permissions conceptually and use fictional identity names in the workbook. In real projects, Umicom Framework provides shared identity, configuration, secrets and auditing contracts. Reusable native functionality belongs there, not in a newly invented Python or PowerShell maintenance script. Always use a supported secret provider and approved operating-system security facilities.

## New terms explained

| Term | Plain-English meaning |
|---|---|
| **Least privilege** | Grant only the permissions required for the task. |
| **Service identity** | The account or workload identity under which a service executes. |
| **Secret reference** | A pointer to a protected credential instead of the credential value. |
| **Rotation** | Replacing a credential under a planned process. |
| **Segregation of duties** | Separating request, approval and execution responsibilities. |
| **Audit trail** | Protected record of what was requested, approved, performed and observed. |


## Windows laboratory — PowerShell 7

Open **Windows Terminal → PowerShell** or search for **PowerShell**. The prompt looks like `PS C:\Users\...>`; do **not** type the prompt itself. On Windows PowerShell 5.1, read-only commands may still work, but the project teaches PowerShell 7. Type the commands one line at a time:

```powershell
whoami
whoami /groups
Get-Command Get-ScheduledTask
Get-ScheduledTask | Select-Object -First 5 TaskName, State
```

**What to expect:** `whoami /groups` reports Windows security groups for the current session and may be lengthy. It does not grant or remove permissions. Share only redacted information. The exact names, counts and times on your computer will differ; no precise output is assumed.

## Linux laboratory — terminal

Open your Linux terminal (for example a disposable virtual machine). These commands are read-only. If a command is unavailable, note your distribution and ask the instructor before installing anything.

```bash
id
umask
ls -ld "$HOME"
crontab -l
```

**What to expect:** `umask` shows the shell’s creation mask; it is not a complete file access-control policy. `id` reports local identity and groups. Do not run `chmod`, `chown`, `sudo` or edit cron as part of this read-only lesson.

## Worked Umicom case study

A fictional Notes backup job is proposed to run as a privileged administrator because that is “easier.” A reviewer asks what files it really needs, whether the backup destination is protected, what happens if the account expires, and how its output will avoid leaking credentials. The safer design uses a dedicated narrow identity, a controlled secret reference where technically necessary, a reviewed schedule and redacted audit evidence. The training exercise does not grant rights or connect to an identity provider.

## What if something goes wrong?

| Observation | Safe response |
|---|---|
| A job fails with Access denied | Check intended scope and account with its owner; do not give broad administrator rights as a shortcut. |
| A log contains a token | Treat as sensitive incident; stop distribution, follow approved rotation and notification procedures. |
| The job has no recorded reviewer | Mark review incomplete and escalate through the required approval channel. |

## Guided learner exercise

1. Write a permissions matrix for fictional Notes export: read source, write one destination, read unrelated files, modify system services. Mark Yes/No and justify each.
2. Explain why using your personal administrator account for a nightly job complicates offboarding.
3. Identify three fields in an audit record that are useful but not confidential credentials.

## Self-check and suggested answers

**Answer 1:** A dedicated account can be scoped and rotated without tying operations to an employee’s personal credentials.

**Answer 2:** Useful evidence includes timestamp, task identifier, change ticket and outcome; it should exclude secrets.

## What this proves — and what it does not

These exercises teach how to collect observations and describe decisions. They are not a certification of any real Umicom deployment. A command completing successfully does not automatically mean that a business operation finished. In live work, only an authorised owner should change service configuration, scheduled jobs, firewall policy, backup retention or credentials, after impact assessment and recovery planning. New reusable monitoring or scheduling software belongs in **Umicom Framework**, preferably implemented in C23 or Assembly rather than new PowerShell/Python scripts.

**Further reading:** [Stage 8 overview](stage-8-index.md) · [Safe command reference](stage-8-safe-command-reference.md) · [Stage 8 glossary](stage-8-glossary.md).
