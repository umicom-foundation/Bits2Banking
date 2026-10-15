# Chapter 132 — Capstone: review a fictional Umicom Notes computer

*System Administration From Zero · Stage 10 · Umicom Foundation*

You are supporting a small Umicom Notes installation. A colleague reports that the application has become slow and sometimes fails to save a file. You are not allowed to make changes yet. Your job is to gather reliable evidence and suggest the next safe investigation.

This exercise combines identities, permissions, configuration, logs, software versions, storage and recovery. All details are fictional; use your own computer only for read-only observations.

## The incident report you receive

> “The Notes service was updated yesterday. It now opens slowly. The disk may be almost full. Someone thinks the password has expired, but no one has checked. We have a backup from last week.”

Notice how much is uncertain. “May be”, “thinks” and “have a backup” are not confirmed facts. A good administrator turns those statements into questions that can be answered safely.

## Step 1 — Identify the system

Record the computer name, operating system and relevant application version. On Windows, you might start with:

```powershell
Get-ComputerInfo | Select-Object WindowsProductName, OsVersion, OsArchitecture
```

For a Linux host, `uname -a` provides a first view of system and kernel information. The goal is not to collect every detail; it is to be sure you are investigating the correct host and release.

## Step 2 — Check what the machine reports

Inspect available storage and relevant service status. In Windows PowerShell:

```powershell
Get-PSDrive -PSProvider FileSystem
Get-Service | Select-Object -First 10 Name, Status
```

A list of ten services is only a teaching demonstration. In a real investigation, identify the **actual Notes service name** from the approved inventory rather than guessing one.

On Linux, `df -h` and an authorised `systemctl status SERVICE_NAME` provide related observations.

## Step 3 — Build the timeline

Write the date and time of the update, first reported failure, and one reproducible test. Find relevant logs around those times. Record the exact error, not just “save failed”. Compare the current configuration and approved release identity if those records are available.

Do not expose customer notes or passwords in your report. Ask the responsible owner before retrieving privileged logs or changing permissions.

## Step 4 — Check the recovery claim

“The backup exists” does not tell us whether it can restore data. Ask when it was created, what it contains and when a restore was last tested. The backup may predate the latest notes or configuration, affecting the recovery decision.

## Your final written report

Write a one-page note with four headings: **Observed facts**, **Unknowns**, **Proposed checks** and **Changes requiring approval**. Under observed facts, include only what you measured or what the system reported directly. Under unknowns, list things that still need evidence.

**Example conclusion:** “The application was reported slow after yesterday's update. Available disk space and service logs have not yet been checked. A backup is said to exist, but no restoration evidence has been supplied. No configuration changes are recommended until the release, storage and log evidence have been reviewed.”

A careful report like this is useful even when you cannot solve the incident immediately. It gives another administrator a clear starting point and protects both the system and its users.

**What comes next:** Later stages will combine safe configuration changes, structured testing, service monitoring and supervised recovery. Every change must have an owner and evidence that the business function still works afterwards.
