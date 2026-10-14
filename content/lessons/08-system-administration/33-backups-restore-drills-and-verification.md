# Chapter 33 — Backups, restore drills and proving that recovery works

**Bits to Banking · System Administration: From Zero · Umicom Foundation**  

**Audience:** first-time users and returning learners; practical examples appropriate for supervised younger learners.  

**Estimated study time:** 60–90 minutes.  

**Prerequisites:** Chapter 14 and Chapter 7.


## Why this matters

A backup file exists, but does it contain the latest version? Can it actually be opened? A backup strategy is useful only when a restore can be demonstrated. In this practical exercise we will make a copy of **your own harmless training README** and restore that copy to a separate test location.

![Backups, restore drills and proving that recovery works](../../assets/diagrams/sysadmin-backup-verification-update39.svg)


## What you will be able to do

By the end of this chapter you should be able to explain the new terms in ordinary language, select a safe read-only command for the right operating system, recognise a normal result and identify an unverified result. You should also be able to describe what permission would be needed before making a real system change.


## The mental model

The common 3-2-1 planning heuristic describes three copies of important data, on two types of storage, with at least one copy elsewhere. It is not a substitute for considering encryption, retention, access controls, immutable copies or ransomware. A *backup* is a recoverable copy; a *restore drill* proves whether it can be used; a *hash* helps compare exact bytes. A matching SHA-256 digest of two files is strong evidence that their contents match, but it does not prove the backup job had permission to capture every required file or that a complete application can be restored.

### The difference between a safe sample restore and disaster recovery

In this lesson the restored file is a Markdown README. That is deliberate. A banking ledger, medical record system or live treasury service may store interconnected files, transaction logs and databases. Copying only one database file while the server is changing it can create an inconsistent backup. Production recovery needs application-aware snapshots, tested dependencies, security controls and a documented sequence to return the complete service safely.

The training drill also protects the previous copy. We first check whether the destination exists, then copy the practice file, then hash both copies, then restore to a **third** location. These stages are observable and reversible. A good restore runbook names the original source, backup location, restore destination and result of a meaningful application-level check. The very first lesson for a beginner is that verifying a backup means testing what can be recovered—not merely counting backup files.


## Words you should know
| Term | Meaning |
|---|---|
| **Restore drill** | A controlled trial that recovers data from a backup. |
| **Retention** | How long copies must be preserved. |
| **RPO** | Recovery Point Objective: acceptable data loss measured in time. |
| **RTO** | Recovery Time Objective: acceptable time to restore a service. |
| **Checksum/hash** | A compact calculated value used to compare content identity. |


## Windows: PowerShell 7, one command at a time

> Use a **normal non-elevated PowerShell** window. Do not type the `PS C:\...>` prompt. If a command is unavailable or returns Access Denied, record that result; do not attempt to defeat the restriction.

The lines in a code block may contain more than one interactive command. Run them in order, checking each result before continuing. **No `.ps1` file is created or required.**

### Windows step 1 — Check the training source and stop if missing

```powershell
Test-Path "$HOME\UmicomLearning\Notes\README.md"
```

**Expected result:** Proceed only if True. Do not substitute an actual private work document.

**What this does:** PowerShell runs the command in your current session and displays information or, where clearly indicated, changes only your own practice files. If output differs, record the actual result before going further.

### Windows step 2 — Create a dedicated backup practice folder

```powershell
New-Item -ItemType Directory -Path "$HOME\UmicomLearning\BackupDrill" -Force
```

**Expected result:** Creates or reuses a folder in your personal learning area.

**What this does:** PowerShell runs the command in your current session and displays information or, where clearly indicated, changes only your own practice files. If output differs, record the actual result before going further.

### Windows step 3 — Check whether a prior test copy already exists

```powershell
Test-Path "$HOME\UmicomLearning\BackupDrill\README-backup.md"
```

**Expected result:** If True, stop rather than overwrite a previous backup exercise.

**What this does:** PowerShell runs the command in your current session and displays information or, where clearly indicated, changes only your own practice files. If output differs, record the actual result before going further.

### Windows step 4 — Copy only the authorised sample file

```powershell
Copy-Item -LiteralPath "$HOME\UmicomLearning\Notes\README.md" -Destination "$HOME\UmicomLearning\BackupDrill\README-backup.md"
```

**Expected result:** Performs one copy. Run only when the destination was absent and the source exists.

**What this does:** PowerShell runs the command in your current session and displays information or, where clearly indicated, changes only your own practice files. If output differs, record the actual result before going further.

### Windows step 5 — Prove the copy matches the source

```powershell
Get-FileHash "$HOME\UmicomLearning\Notes\README.md" -Algorithm SHA256
Get-FileHash "$HOME\UmicomLearning\BackupDrill\README-backup.md" -Algorithm SHA256
```

**Expected result:** The two hash values should match. These are two interactive commands, not a stored script.

**What this does:** PowerShell runs the command in your current session and displays information or, where clearly indicated, changes only your own practice files. If output differs, record the actual result before going further.

### Windows step 6 — Restore into a *different* place and read it

```powershell
New-Item -ItemType Directory -Path "$HOME\UmicomLearning\RestoreDrill" -Force
Copy-Item -LiteralPath "$HOME\UmicomLearning\BackupDrill\README-backup.md" -Destination "$HOME\UmicomLearning\RestoreDrill\README.md"
Get-Content "$HOME\UmicomLearning\RestoreDrill\README.md"
```

**Expected result:** Only run when the restore destination is absent. The restored heading should be readable.

**What this does:** PowerShell runs the command in your current session and displays information or, where clearly indicated, changes only your own practice files. If output differs, record the actual result before going further.


## Linux: terminal and distribution differences

> Run the following only in an authorised Linux computer or VM. If you use Windows only, read this section for comparison. A program being absent does not mean the whole operating system is faulty.

### Linux step 1 — Create two harmless practice folders

```bash
mkdir -p "$HOME/UmicomLearning/BackupDrill" "$HOME/UmicomLearning/RestoreDrill"
```

**Expected result:** Creates user-owned practice directories only.

### Linux step 2 — Copy the example without replacing an existing backup

```bash
cp -n "$HOME/UmicomLearning/Notes/README.md" "$HOME/UmicomLearning/BackupDrill/README-backup.md"
```

**Expected result:** GNU `cp -n` refuses overwrite; inspect existence first to be certain the intended copy was made.

### Linux step 3 — Compare the two files by digest

```bash
sha256sum "$HOME/UmicomLearning/Notes/README.md" "$HOME/UmicomLearning/BackupDrill/README-backup.md"
```

**Expected result:** Matching digests indicate the two read files have matching content.

### Linux step 4 — Restore to a separate test folder

```bash
cp -n "$HOME/UmicomLearning/BackupDrill/README-backup.md" "$HOME/UmicomLearning/RestoreDrill/README.md"
```

**Expected result:** Do not run if a prior restored copy exists.


## Worked support scenario

A course coordinator wants a backup of a volunteer-run support tracker before a software update. Describe how you would agree a restore target, define an RPO/RTO, prevent private information from leaking into public cloud storage, verify that the backup completed, and practise restoration to a separate safe environment. The classroom exercise uses only the README; no personal or financial information should be copied.


## Common mistakes and safe responses
| Mistake | Better response |
|---|---|
| “Backup completed” means it can restore an application. | A job log cannot prove a complete restore; test the actual recovery path. |
| “Never mind overwriting yesterday’s copy.” | Overwriting the only previous snapshot removes a recovery point; use a retention policy. |
| “Publish a checksum and filenames publicly.” | Paths and backup inventories can be sensitive. Keep evidence appropriately restricted. |


## Exercises

1. Explain RPO and RTO using a training Notes service.

2. Verify a separate, harmless restored file without opening private directories.

3. State which additional steps a real production database would require beyond copying one README.


## Review questions and suggested answers

<details><summary>Show the suggested answers after attempting the exercises</summary>



1. RPO describes the age of acceptable restored state; RTO describes the time allowed to recover.

2. Compare hashes and open the restored test file.

3. Consistent snapshots, application-aware backup, database transaction recovery, permissions and operational acceptance.



</details>


## Connecting this chapter to Umicom

Production Umicom software should use the appropriate **Umicom Framework** service for identities, processes, filesystem operations, Git, diagnostics, build planning or observability. The teaching commands here are interactive; they are **not** substitute Python or PowerShell implementations. Any reusable new executable component must first be considered for Framework ownership and designed in C23 or justified Assembly.


## References and further reading

- https://www.cisa.gov/resources-tools/resources/backup-recovery

- https://learn.microsoft.com/powershell/module/microsoft.powershell.utility/get-filehash


**Course progression:** [Chapter 32](32-storage-space-filesystems-and-disk-health.md) → **Chapter 33** → [Chapter 34](34-passwords-mfa-least-privilege-and-secrets.md)


---

**Practical safety reminder:** No exercise requires access to private records, bank accounts, live production systems or another person’s computer. A successful “not permitted” or “not run” observation is an acceptable learning outcome.
