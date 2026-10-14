# Chapter 13 — Inspect processor, memory, Windows version and resources

**Bits to Banking · System Administration: From Zero · Umicom Foundation**  
**Audience:** first-time users and returning learners; no prior system-administration knowledge required.  
**Code policy:** interactive PowerShell 7 and Bash commands; native C23/Assembly for Umicom executable development.  
**Estimated study time:** 25–50 minutes (longer when practising).

## What you will learn

Gather a reproducible system profile without installing diagnosis software.

## Why this matters

![Computer layers: each layer has a different job](../../assets/diagrams/sysadmin-os-layers-update38.svg)


When a program runs slowly or fails to install, support teams often need the operating-system version, CPU architecture, available memory and free storage. These facts help identify compatibility problems and resource pressure. They are not performance guarantees. A machine with many CPU cores can still be limited by disk speed, memory pressure or a program waiting for network data.

PowerShell can query Windows management information using `Get-CimInstance`. The `Win32_Processor` class describes processors and core counts. `Win32_ComputerSystem` provides total physical memory. We display sizes in GiB-style binary units using the PowerShell `1GB` numeric multiplier, and round the result for readability. The rounded value is an observation, not an inventory record of installed module part numbers.

In a shared support request, collect only the information needed to investigate the problem. Avoid publishing machine serial numbers, IP addresses or personal account paths in public issue reports unless explicitly approved.

## New words, explained

| Term | Plain-English meaning |
|---|---|
| **Architecture** | Processor/OS instruction and binary compatibility family, such as x64. |
| **Core** | Independent CPU execution unit. |
| **Logical processor** | Thread execution context reported by the OS. |
| **Capacity** | Resource amount, not necessarily current available resource. |
| **GiB** | Binary unit equal to 1,073,741,824 bytes. |

## Windows practice — PowerShell 7

> **Before typing:** Run these commands in a normal, non-elevated PowerShell window. Where a file is used, complete the previous practice-folder chapters first. Do not paste the `PS C:\...>` prompt into the terminal.

**Start:** Use the Windows Start menu or Windows Terminal to open PowerShell. Check the prompt is ready. Commands beginning with `$` are still commands; type them exactly as shown.

### Step 1 — Read Windows release and architecture

```powershell
Get-ComputerInfo | Select-Object WindowsProductName, OsVersion, OsArchitecture
```

**Expected observation:** Windows release fields appear.

**Check:** Read the output before continuing. If it does not match, stop and investigate the specific command; do not add `-Force` or run as Administrator automatically.

### Step 2 — Read processor details

```powershell
Get-CimInstance Win32_Processor | Select-Object Name, NumberOfCores, NumberOfLogicalProcessors
```

**Expected observation:** CPU model and core/thread counts appear.

**Check:** Read the output before continuing. If it does not match, stop and investigate the specific command; do not add `-Force` or run as Administrator automatically.

### Step 3 — Read installed physical memory

```powershell
[math]::Round((Get-CimInstance Win32_ComputerSystem).TotalPhysicalMemory / 1GB, 2)
```

**Expected observation:** A rounded numeric value in binary gigabyte units appears.

**Check:** Read the output before continuing. If it does not match, stop and investigate the specific command; do not add `-Force` or run as Administrator automatically.

### Step 4 — Inspect available drive capacity

```powershell
Get-PSDrive -PSProvider FileSystem
```

**Expected observation:** Drive capacities and free-space values appear for accessible file-system drives.

**Check:** Read the output before continuing. If it does not match, stop and investigate the specific command; do not add `-Force` or run as Administrator automatically.

## Linux comparison — terminal/Bash

> Linux commands are alternatives on a Linux machine or authorised VM. Do not paste them into Windows PowerShell as though the shells have identical syntax.

### Linux step 1 — Show architecture

```bash
uname -m
```

**Expected observation:** The current machine architecture is printed.

### Linux step 2 — Show memory

```bash
free -h
```

**Expected observation:** Used, available and total memory are displayed.

### Linux step 3 — Show processor summary if utility exists

```bash
lscpu | head -n 15
```

**Expected observation:** CPU information appears when `lscpu` is installed.

## Worked support scenario

A student cannot build a large native project on a low-memory laptop. Instead of assuming the compiler is defective, compare memory capacity, concurrent build jobs and log evidence. Reducing build parallelism from eight to two is a configuration decision, but first verify the actual machine constraints.

## Common problems and how to respond

| Problem or assumption | Better response |
|---|---|
| Confusing total and available memory | Total memory is installed capacity; available is the amount the OS estimates can be used. |
| Publishing private device identifiers in a public issue | Share only required, non-sensitive details. |
| Assuming a version string guarantees a toolchain works | Run an actual configure/build/test acceptance for the intended project. |

## Exercise: demonstrate understanding

1. Write down the purpose of **two commands** from this chapter, in your own words.
2. Run a **read-only command** and record only the information needed to answer its question.
3. Explain which command would change the machine, if any, and why the chapter avoids it.
4. Explain the difference between an observation, a conclusion and an unverified assumption.

## Review questions

1. What does NumberOfLogicalProcessors report?
2. Why might lowering `--parallel` help a build?

<details><summary>Show the suggested answers</summary>

1. OS-visible processing threads, not necessarily physical cores.
2. It can reduce peak memory and CPU contention on a constrained machine.

</details>

## How this connects to Umicom

Umicom Framework, Studio and OS qualification needs hardware and toolchain context attached to test evidence, not just the claim that compilation succeeded.

## Where to go next

Continue with [Chapter 14 — Disks, backups and checking that restoration works](14-disks-backups-and-restore-verification.md).
