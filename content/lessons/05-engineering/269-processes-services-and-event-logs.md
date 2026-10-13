# Chapter 269 — Inspect processes, services and Windows event logs

**Bits to Banking · Absolute Beginner Course · Unit 2**  
**Time:** 25–40 minutes · **Mode:** read-only observation.

## A programme and a process are not the same thing

A **programme** is executable code stored on disk. A **process** is a running instance with its own identifier (**PID**) and resources. Opening two windows of an application can create two processes or one process with multiple windows, depending on the application. A **service** is software supervised by the operating system for ongoing work; not every process is a service.

When Umicom Studio appears not to open, first distinguish “the executable did not start” from “the process started then exited” and “the process runs but the window is hidden”. A successful compile proves none of these runtime states.

## Step 1 — List running processes

```powershell
Get-Process | Select-Object -First 10 Name, Id, CPU
```

The results are a snapshot; processes start and stop constantly. CPU is often accumulated processor time, not a live percentage. To examine one familiar application, replace the name if necessary:

```powershell
Get-Process -Name explorer -ErrorAction SilentlyContinue |
    Select-Object Name, Id, WorkingSet64
```

`-ErrorAction SilentlyContinue` hides a simple “not found” error when Explorer is not running, but do not use it to suppress a real failed build or test.

## Step 2 — List services

```powershell
Get-Service | Select-Object -First 12 Name, Status, DisplayName
```

A service can be `Running`, `Stopped` or in a transitional state. A stopped service is not always an error; some run only when required. Do not start or stop unfamiliar services in a classroom exercise. For a named service you are responsible for, consult its approved administration guide before changing it.

## Step 3 — View a few recent events

```powershell
Get-WinEvent -LogName System -MaxEvents 5 |
    Select-Object TimeCreated, Id, LevelDisplayName, ProviderName
```

Windows records events from many providers. A warning in Event Viewer does not necessarily explain an unrelated Umicom crash. Compare the timestamp, application name and exact event message before drawing conclusions. Some logs require permissions; in that case, do not bypass your organisation's access policy.

## Step 4 — Relate to Umicom builds

A CMake configure step prepares the build plan. Ninja compiles and links binaries. CTest launches registered test programmes. Windows then starts the completed executable. If a programme never appears, inspect the earliest failing stage: compiler output, link error, missing executable or runtime crash. Keep exact error text and paths; they are the evidence a developer needs.

**Practice:** List ten processes, ten services and five recent system events. Name one difference between a warning, a process exit and a build error. Record what each command can prove and what it cannot prove.

**Next:** [Understand networking and test DNS safely](270-network-and-dns-first-steps.md).
