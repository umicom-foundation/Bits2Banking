# Chapter 55 — Monitor service health using baselines and sensible alerts

**System Administration From Zero · Stage 4 — Managed Services and Recovery**  
**Author:** Sammy Hegab · Umicom Foundation  
**Study time:** 65–85 minutes  
**Before starting:** Chapters 13, 35, 38 and 45: hardware, metrics, baselines and readiness  
**Safety level:** observation-only on real systems; any practice writes are confined to a folder owned by the learner.

## What you will achieve

By the end of this chapter, you will be able to explain **monitor service health using baselines and sensible alerts**, identify the difference between an observation and a change, and interpret at least one Windows and one Linux administration result. You will also be able to describe the evidence that an authorised Umicom support engineer would need before taking action.

## Why this matters in everyday computing

A computer may be busy for a perfectly good reason: a backup is running or an application is compiling. It may also be struggling: storage is full, memory pressure is high or an essential service has stopped responding. Looking at one number without context can lead to false alarms.

An administrator starts with a baseline: what the machine normally does at an agreed time and workload. Then they define signals that deserve investigation. This lesson shows how to observe a small set of Windows and Linux counters without installing agents or exporting logs. It avoids turning every harmless variation into an emergency.

## A mental model you can remember

Imagine checking the temperature of a classroom. A single warm reading after everyone arrives has a different meaning from a long-lasting extreme temperature with a broken ventilation system. Monitoring similarly needs context: expected load, observation time, duration, threshold and functional impact. An alert is a request to investigate, not proof of root cause.

## New words, without jargon

| Term | Meaning |
|---|---|
| **Metric** | A numerical measurement such as available memory, disk space or process CPU time. |
| **Baseline** | Measurements representing known, ordinary behaviour under stated conditions. |
| **Threshold** | A value at which a measurement triggers review. |
| **Alert** | A signal that an agreed threshold or check warrants attention. |
| **False positive** | An alert that fires even though the relevant system is operating acceptably. |
| **Readiness probe** | A check of whether a service can perform a meaningful request. |

## Windows practical lesson — PowerShell 7

Open **Windows Terminal → PowerShell**, or search for **PowerShell 7**. Type only the commands inside each box; the example `PS C:\...>` prompt is not part of a command. Unless a step explicitly says otherwise, use your normal non-administrator account. The commands are interactive teaching instructions, not a `.ps1` script.

### Step 1 — Record the observation time

```powershell
Get-Date -Format o
```

**Expected result:** A timestamp with timezone offset appears.

**What it means:** Any comparison across machines needs time context; do not assume their clocks are identical.

**If it looks different:** Keep the output in private study notes, not a public machine-identity dump.

### Step 2 — Inspect a few processes

```powershell
Get-Process | Sort-Object CPU -Descending | Select-Object -First 5 ProcessName, Id, CPU
```

**Expected result:** Processes with large accumulated CPU time may appear near the top.

**What it means:** The CPU field is cumulative CPU seconds, not an instantaneous CPU percentage. Explain this difference before drawing conclusions.

**If it looks different:** A short-lived process may disappear before you inspect it again.

### Step 3 — Inspect available physical memory

```powershell
Get-CimInstance Win32_OperatingSystem | Select-Object FreePhysicalMemory, TotalVisibleMemorySize
```

**Expected result:** Memory figures appear, generally reported by this CIM class in kibibyte-sized units.

**What it means:** This is a snapshot. Always record the unit and time when comparing measurements.

**If it looks different:** A laptop with little free memory may still be using memory effectively for cache.

### Step 4 — Check drive capacity

```powershell
Get-PSDrive -PSProvider FileSystem | Select-Object Name, Used, Free
```

**Expected result:** Filesystem drives and byte counts are displayed.

**What it means:** Large log growth or a full target filesystem may affect services even when the system drive has free capacity.

**If it looks different:** Do not delete logs or build folders without review.

### Step 5 — Look at services without restarting them

```powershell
Get-Service -Name EventLog | Select-Object Name, Status
```

**Expected result:** Service status is displayed.

**What it means:** A running service is one evidence item; a useful alert may also check that the application emits or consumes expected events.

**If it looks different:** Stop-Service and Restart-Service are deliberately excluded.

## Linux practical comparison

On a Linux computer or an authorised virtual machine, open a terminal. These are **Bash-compatible commands**; do not type the `$` prompt. A minimal container, Chromebook or non-systemd distribution may have a different set of tools. A missing optional tool should be recorded rather than bypassed.

### Linux step 1 — Inspect uptime and load

```bash
uptime
```

**Expected result:** The system uptime and load averages appear on many Linux systems.

**Interpretation:** Load average is not the same as CPU percentage; interpret it with CPU count and workload.

### Linux step 2 — Inspect available memory

```bash
free -h
```

**Expected result:** Memory statistics appear in human-readable units.

**Interpretation:** Available memory matters more than treating all cache as permanently unavailable.

### Linux step 3 — Inspect filesystem space

```bash
df -h .
```

**Expected result:** Capacity and available space for the current filesystem are shown.

**Interpretation:** The dot means the current directory. A service may use another filesystem for its data, so document the target path.

## Worked support scenario — Umicom Notes

A fictional Umicom Notes student reports that saving is slow. The volunteer checks the time, application readiness, free space and a baseline from the previous day. The disk is nearly full, but the Notes data directory resides on a different volume with space available. The volunteer records the difference and checks the actual service path before proposing any clean-up. Observation prevents a destructive guess.

**Evidence record:** In your own words, describe the issue, the observation time, the command used, what you actually saw, what you have *not* proved, and who would approve a change. Avoid copying usernames, credentials, private filenames, IP addresses or confidential logs into public notes.

## Common mistakes and how to correct them

| Misunderstanding | Better interpretation |
|---|---|
| The process at the top of CPU time must be faulty. | Cumulative CPU time is not a direct speed or fault measurement. |
| One threshold works on every computer. | Workload, hardware and accepted service targets differ. |
| Deleting logs is a safe way to recover space. | Logs may be required for audit or incident recovery; retain evidence and seek approval. |

## Guided practice and suggested responses

**Exercise 1.** Design a three-metric baseline.

*Suggested response:* Include measure, unit, time, expected range and reason it matters.

**Exercise 2.** Write an alert response.

*Suggested response:* Describe what you would inspect if the Notes storage volume fell below a small agreed free-space threshold.

**Exercise 3.** Distinguish measurement from conclusion.

*Suggested response:* Explain why one high CPU measurement cannot prove a regression in Notes.

## Questions for discussion

1. Which part of today's monitor service health using baselines and sensible alerts exercise was **read-only**, and how do you know?
2. What does a successful command prove, and what would it *not* prove?
3. Explain **Metric** to somebody who has never opened a terminal.
4. If an expected result does not appear, what evidence would you collect before changing anything?
5. How would you explain this issue to a colleague without exposing private data?

## Connection to Umicom Framework and software engineering

Use Umicom Framework observability, diagnostics and health contracts when developing production monitors. The course deliberately avoids creating a second logging agent or Python polling script. Framework components should publish bounded, authorised observations and keep alerts separate from automatic actions.

## Further reading (optional internet access)

- https://learn.microsoft.com/powershell/module/microsoft.powershell.management/get-process
- https://man7.org/linux/man-pages/man1/uptime.1.html

## Learning checkpoint

You are ready to proceed if you can explain **the command, its expected output, the boundary of what it proves, and a safe response to unexpected output**. If the exercise needed unavailable administrator access, record *not performed*; do not mark it as passed.

**Next:** [Chapter 56 — Check local listeners and understand network exposure](./56-check-local-listeners-and-network-exposure.md).
