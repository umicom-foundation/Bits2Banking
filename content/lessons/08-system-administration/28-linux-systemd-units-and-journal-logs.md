# Chapter 28 — Understand Linux systemd units, logs and safe inspection

**Bits to Banking · System Administration: From Zero · Umicom Foundation**  

**Audience:** first-time users and returning learners; practical examples appropriate for supervised younger learners.  

**Estimated study time:** 45–65 minutes.  

**Prerequisites:** Chapters 17–18 and 27.


## Why this matters

On a Linux host, the same application may run as a systemd service rather than a Windows service. A beginner can still ask the same useful questions: Which component should be running? What state is it in? Who started it? What evidence shows that the application works?

![Understand Linux systemd units, logs and safe inspection](../../assets/diagrams/sysadmin-service-lifecycle-update39.svg)


## What you will be able to do

By the end of this chapter you should be able to explain the new terms in ordinary language, select a safe read-only command for the right operating system, recognise a normal result and identify an unverified result. You should also be able to describe what permission would be needed before making a real system change.


## The mental model

Many Linux distributions use `systemd` as the system and service manager. A **unit** is a declarative description of a managed resource; service units commonly end in `.service`. System units and per-user units are different. The `journalctl` command reads the systemd journal, where records may be restricted by permissions and may not persist after restart on some configurations. A container or a Windows Subsystem for Linux environment may not be running systemd at all. Learning to recognise “not applicable” is more professional than issuing commands until something stops reporting an error.

### Why user services are different from system services

A desktop user may run a background synchronisation process attached to their login session. A server may run the same kind of process as a system unit using a dedicated service account. These lifetimes and permission boundaries are different. A command using `systemctl --user` asks the user service manager; a command without `--user` usually asks the system manager. Neither should be used to modify a service merely because its name sounds familiar.

The presence of `systemctl` does not guarantee systemd is PID 1. Some containers, rescue environments and distributions use different service managers, and a limited systemd instance may not have all journal facilities. Start by reading the environment. If a service's unit and journal are unavailable, record the limitation and consult the local operating-system guidance rather than installing services or creating config files without permission.


## Words you should know
| Term | Meaning |
|---|---|
| **Unit** | A systemd configuration describing a managed resource. |
| **Service unit** | A unit that manages a process or service. |
| **User unit** | A systemd unit managed within a user session. |
| **Journal** | A structured collection of messages managed by systemd-journald. |
| **Enabled** | Configured to be activated by dependency/startup triggers; not the same as currently active. |


## Windows: PowerShell 7, one command at a time

> Use a **normal non-elevated PowerShell** window. Do not type the `PS C:\...>` prompt. If a command is unavailable or returns Access Denied, record that result; do not attempt to defeat the restriction.

The lines in a code block may contain more than one interactive command. Run them in order, checking each result before continuing. **No `.ps1` file is created or required.**

### Windows step 1 — Compare the current system’s manager

```powershell
Get-Service | Select-Object -First 5 Name, Status
```

**Expected result:** Windows uses Service Control Manager rather than systemd.

**What this does:** PowerShell runs the command in your current session and displays information or, where clearly indicated, changes only your own practice files. If output differs, record the actual result before going further.

### Windows step 2 — Open the documentation before changing anything

```powershell
Get-Help Get-Service -Online
```

**Expected result:** Only opens an official help page if browser access is configured; no service state is changed.

**What this does:** PowerShell runs the command in your current session and displays information or, where clearly indicated, changes only your own practice files. If output differs, record the actual result before going further.


## Linux: terminal and distribution differences

> Run the following only in an authorised Linux computer or VM. If you use Windows only, read this section for comparison. A program being absent does not mean the whole operating system is faulty.

### Linux step 1 — Check what process is PID 1

```bash
ps -p 1 -o comm=
```

**Expected result:** Commonly prints `systemd` on systemd hosts; another name means follow that environment’s service model.

### Linux step 2 — List currently running service units

```bash
systemctl list-units --type=service --state=running --no-pager
```

**Expected result:** If systemd is available, displays units. Do not change or restart them during the exercise.

### Linux step 3 — Inspect the state of a chosen unit

```bash
systemctl status --no-pager ssh.service
```

**Expected result:** `ssh.service` may have a different name or may not be installed. Use an actually listed service instead; `status` is a read-only probe.

### Linux step 4 — Read only the last few journal messages

```bash
journalctl --no-pager -n 10
```

**Expected result:** Your permissions determine which messages are visible.


## Worked support scenario

You are asked why a Linux training service did not start. First confirm whether the host uses systemd, then inspect the unit’s active state and the journal around the reported time. If the message says a configuration file is missing, do not create guessed settings in `/etc`. Report the specific path, the expected owner and the relevant documentation so the responsible maintainer can supply the approved configuration.


## Common mistakes and safe responses
| Mistake | Better response |
|---|---|
| “`systemctl enable` starts a service immediately.” | Enable changes activation relationships; use `is-enabled` or read documentation and distinguish it from `start`. |
| “Everything with a `.service` suffix is running.” | A unit file may exist while the service is inactive or failed. |
| “No log output means no problem.” | Journal permissions, filtering or retention can hide records. |


## Exercises

1. Compare a service unit with an ordinary running process.

2. On a Linux practice machine, list running units or record “systemd unavailable”.

3. Identify what you would record before requesting a service restart.


## Review questions and suggested answers

<details><summary>Show the suggested answers after attempting the exercises</summary>



1. A unit adds configuration and lifecycle semantics; a process is a currently executing program.

2. Either result is valid if supported by evidence.

3. Service identity, status, reason for restart, observed error, expected impact, and rollback plan.



</details>


## Connecting this chapter to Umicom

Production Umicom software should use the appropriate **Umicom Framework** service for identities, processes, filesystem operations, Git, diagnostics, build planning or observability. The teaching commands here are interactive; they are **not** substitute Python or PowerShell implementations. Any reusable new executable component must first be considered for Framework ownership and designed in C23 or justified Assembly.


## References and further reading

- https://www.freedesktop.org/software/systemd/man/latest/systemctl.html

- https://www.freedesktop.org/software/systemd/man/latest/journalctl.html


**Course progression:** [Chapter 27](27-windows-service-diagnosis-and-event-evidence.md) → **Chapter 28** → [Chapter 29](29-plan-windows-and-linux-software-updates.md)


---

**Practical safety reminder:** No exercise requires access to private records, bank accounts, live production systems or another person’s computer. A successful “not permitted” or “not run” observation is an acceptable learning outcome.
