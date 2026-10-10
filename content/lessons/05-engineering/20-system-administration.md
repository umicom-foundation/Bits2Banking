# 20. System administration on Windows and Linux

A program does not run in isolation. It needs an operating system, a user identity, memory, files, access permissions, installed libraries and sometimes network services. **System administration** means configuring, inspecting, protecting and maintaining that environment.

As a developer, you should be able to answer practical questions: Is the application running? Does it have permission to write its data? Is there enough disk space? Which service is listening on a network port? What changed just before an error?

## Inspect Windows without modifying it

Open a normal PowerShell terminal:

```powershell
Get-ComputerInfo | Select-Object OsName, OsVersion
Get-Process | Select-Object -First 10 ProcessName, Id, CPU
Get-PSDrive -PSProvider FileSystem
```

`Get-ComputerInfo` shows operating-system information. `Get-Process` lists processes; a process is a running instance of a program. `Get-PSDrive` shows available filesystem drives and their relevant properties.

For a particular process, try:

```powershell
Get-Process -Name notepad -ErrorAction SilentlyContinue |
    Select-Object ProcessName, Id, WorkingSet64
```

If Notepad is not open, the output may be empty. That is different from the command failing.

Windows has background components called **services**. You can inspect their states without changing them:

```powershell
Get-Service | Select-Object -First 10 Name, Status
```

Do not start, stop or disable a service until you understand why it exists and what depends on it.

## Inspect Linux

A Linux terminal provides similar information with different commands:

```bash
uname -a
pwd
df -h
ps -ef | head
```

`uname -a` reports kernel and system information. `df -h` displays filesystem capacity. `ps` lists processes. `head` limits the display to a few lines.

To inspect memory, use:

```bash
free -h
```

On many Linux systems managed by systemd, an administrator can read service status using `systemctl status SERVICE_NAME`. The exact service name depends on the installed software. Inspect first; do not change a service simply because it is stopped.

## Users and permissions

Operating systems limit which users and programs can read, write or execute files. On Linux, `ls -l` displays permission bits for the owner, group and others. On Windows, access control lists determine effective permissions.

A developer sometimes sees “permission denied” and immediately tries to run the whole program as an administrator. That is usually the wrong first response. Identify the intended file location and required permission, then correct the configuration through the appropriate owner. Giving an application unnecessary privilege increases the consequences of a defect.

## Logs and observable behaviour

A **log** records events such as startup, shutdown, errors and important state changes. Useful logs answer: what happened, when, in which process and what operation was being attempted? For financial applications, logs alone are not sufficient evidence that a trade or payment completed; business processing also needs explicit statuses, audit records and reconciliation.

An application should distinguish a warning from an error. A missing optional configuration can sometimes be reported and recovered from. A failed database transaction must not be presented as success.

## Backups and recovery

A backup is only useful if it can be restored. For your learning files, make a separate copy of `notes.json` or `tasks.db` before experimenting with changes. Later, you can test recovery by restoring that copy to a new practice directory and opening it there.

For a real service, backup planning includes data consistency, retention, encryption, access control, recovery point objectives and recovery-time objectives. A working source-code repository is not a substitute for backing up database records or private configuration.

## A short diagnostic exercise

Imagine a note-taking application reports that it cannot save. Follow this order:

1. Check the exact file path and the application's current working directory.
2. Check whether the destination folder exists.
3. Check whether the user has write permission.
4. Check free storage space.
5. Inspect the application's error message and logs.
6. Reproduce the problem using a disposable test file, not production data.

This order gathers evidence before making changes. It is a habit worth carrying into Umicom Framework, Umicom OS and financial-system operations.

**Next:** [Understand networks and APIs](21-networks-and-apis.md).
