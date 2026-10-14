# Chapter 58 — Rehearse restoration and document rollback

**System Administration From Zero · Stage 4 — Managed Services and Recovery**  
**Author:** Sammy Hegab · Umicom Foundation  
**Study time:** 70–90 minutes  
**Before starting:** Chapters 33, 41 and 57: checksum validation, RPO/RTO and recovery copies  
**Safety level:** observation-only on real systems; any practice writes are confined to a folder owned by the learner.

## What you will achieve

By the end of this chapter, you will be able to explain **rehearse restoration and document rollback**, identify the difference between an observation and a change, and interpret at least one Windows and one Linux administration result. You will also be able to describe the evidence that an authorised Umicom support engineer would need before taking action.

## Why this matters in everyday computing

The phrase ‘we have a backup’ is not enough when a service fails. Administrators must know exactly how to locate the right copy, restore it safely, check permissions and decide whether the application may return to normal use. Software rollback and data restoration are related but separate. An older executable may not understand a database that was migrated by a newer release.

This lesson demonstrates a harmless file restoration into a separate practice folder. It does not replace real application files, reboot a machine, restore a system partition or execute database recovery. The focus is on evidence and decision-making.

## A mental model you can remember

Imagine losing the original recipe for a class project. You have a saved copy, but before using it you check the page count and ingredients. You do not immediately throw away the damaged original. A safe data restore similarly writes into a controlled destination first, verifies content and only then considers a production cutover under approval. A rollback plan also needs to account for code, configuration, database and dependencies.

## New words, without jargon

| Term | Meaning |
|---|---|
| **Restore** | Bring back data from a protected copy into a chosen location. |
| **Rollback** | Return a changed system to an approved previous state. |
| **Cutover** | The controlled step that directs users or traffic to a newly prepared environment. |
| **Migration** | A controlled transformation of stored data or schema. |
| **Reconciliation** | Checking that recovered data agrees with authoritative expected records. |
| **Restore point** | A specific recoverable copy identified by date, version or immutable manifest. |

## Windows practical lesson — PowerShell 7

Open **Windows Terminal → PowerShell**, or search for **PowerShell 7**. Type only the commands inside each box; the example `PS C:\...>` prompt is not part of a command. Unless a step explicitly says otherwise, use your normal non-administrator account. The commands are interactive teaching instructions, not a `.ps1` script.

### Step 1 — Check the practice backup exists

```powershell
Test-Path -LiteralPath "$HOME\UmicomLearning\BackupStudy\notes-copy.txt"
```

**Expected result:** True means the previous chapter's practice copy is present.

**What it means:** A missing file is an expected condition if you have not completed Chapter 57; create only your own practice input first.

**If it looks different:** Never substitute a real company backup path in a public lesson.

### Step 2 — Make a separate restoration directory

```powershell
New-Item -ItemType Directory -Force -Path "$HOME\UmicomLearning\RestoreStudy"
```

**Expected result:** The new practice restore directory exists.

**What it means:** Restoring into a separate location prevents an unverified copy from overwriting the working document.

**If it looks different:** If this folder already contains valuable work, create another named training directory.

### Step 3 — Restore the practice copy without overwriting data

```powershell
Copy-Item -LiteralPath "$HOME\UmicomLearning\BackupStudy\notes-copy.txt" -Destination "$HOME\UmicomLearning\RestoreStudy\notes-restored.txt"
```

**Expected result:** A second practice file is created if the destination did not exist.

**What it means:** This is an ordinary file copy, not a system restore or application schema rollback.

**If it looks different:** If the destination exists, stop and inspect it; don't use -Force casually.

### Step 4 — Compare the source and restored fingerprints

```powershell
Get-FileHash -Algorithm SHA256 -LiteralPath "$HOME\UmicomLearning\BackupStudy\notes-copy.txt","$HOME\UmicomLearning\RestoreStudy\notes-restored.txt" | Select-Object Path, Hash
```

**Expected result:** Matching SHA-256 values support byte equality between the two practice files.

**What it means:** Also open the restored note and check that its contents are what the learner expects.

**If it looks different:** A binary application's successful restoration requires application-level checks beyond a hash.

### Step 5 — Read the restored content

```powershell
Get-Content -LiteralPath "$HOME\UmicomLearning\RestoreStudy\notes-restored.txt"
```

**Expected result:** The fictional Notes sentence appears.

**What it means:** Keep a record of the path, restore time and verifier rather than declaring all backups safe.

**If it looks different:** Do not restore a real finance file or database without authorised procedures.

## Linux practical comparison

On a Linux computer or an authorised virtual machine, open a terminal. These are **Bash-compatible commands**; do not type the `$` prompt. A minimal container, Chromebook or non-systemd distribution may have a different set of tools. A missing optional tool should be recorded rather than bypassed.

### Linux step 1 — Check the practice backup file

```bash
test -f "$HOME/UmicomLearning/BackupStudy/notes-copy.txt" && printf 'Backup present\n'
```

**Expected result:** The message appears when the file exists; otherwise the command exits with a nonzero status.

**Interpretation:** Nonzero here may simply mean the Chapter 57 practice file has not been created.

### Linux step 2 — Prepare a separate restore folder

```bash
mkdir -p "$HOME/UmicomLearning/RestoreStudy"
```

**Expected result:** A separate directory exists.

**Interpretation:** Do not restore on top of the only remaining copy.

### Linux step 3 — Copy and inspect the recovered file

```bash
cp -n "$HOME/UmicomLearning/BackupStudy/notes-copy.txt" "$HOME/UmicomLearning/RestoreStudy/notes-restored.txt" && sha256sum "$HOME/UmicomLearning/RestoreStudy/notes-restored.txt"
```

**Expected result:** The file is copied if it did not exist, and its checksum is shown.

**Interpretation:** `-n` avoids replacement where supported. Confirm whether the destination already exists before treating the command as a new restore.

## Worked support scenario — Umicom Notes

A fictional Umicom Notes release includes a new database schema. The desktop crashes afterward. Rolling back the executable alone may not work against the new schema. The operations team should have an approved migration backup, a verified restoration procedure, a downtime plan and a test proving that the previous release can read the recovered data. A human change owner decides whether to recover; a CLI warning is not permission to override controls.

**Evidence record:** In your own words, describe the issue, the observation time, the command used, what you actually saw, what you have *not* proved, and who would approve a change. Avoid copying usernames, credentials, private filenames, IP addresses or confidential logs into public notes.

## Common mistakes and how to correct them

| Misunderstanding | Better interpretation |
|---|---|
| A successful copy equals a complete restore. | The recovered file also needs functional inspection, correct identity and permission checks. |
| Returning to the old executable always fixes the problem. | Data schema or configuration may have changed incompatibly. |
| A failed restore should be hidden and retried silently. | Report the failure and preserve the evidence; uncontrolled retries may overwrite valid information. |

## Guided practice and suggested responses

**Exercise 1.** Draw a rollback dependency table.

*Suggested response:* Include executable, configuration, database, compatibility and verification owners.

**Exercise 2.** Perform the dedicated practice restore.

*Suggested response:* Use the commands above and verify both hash and content.

**Exercise 3.** State a safe stop condition.

*Suggested response:* For example, recovered data fails reconciliation or the restore destination unexpectedly exists.

## Questions for discussion

1. Which part of today's rehearse restoration and document rollback exercise was **read-only**, and how do you know?
2. What does a successful command prove, and what would it *not* prove?
3. Explain **Restore** to somebody who has never opened a terminal.
4. If an expected result does not appear, what evidence would you collect before changing anything?
5. How would you explain this issue to a colleague without exposing private data?

## Connection to Umicom Framework and software engineering

Real Umicom application data must be recovered through Data Server and authorised operational contracts. Umicom Framework should own reusable restore/report facilities rather than distributing product-specific scripts. Update 41's C23 lab can record a fictional restoration decision; it cannot restore real data or prove that a production machine is healthy.

## Further reading (optional internet access)

- https://learn.microsoft.com/powershell/module/microsoft.powershell.management/copy-item
- https://www.freedesktop.org/software/systemd/man/latest/systemd.service.html

## Learning checkpoint

You are ready to proceed if you can explain **the command, its expected output, the boundary of what it proves, and a safe response to unexpected output**. If the exercise needed unavailable administrator access, record *not performed*; do not mark it as passed.

**Next:** [Chapter 59 — Triage incidents and communicate with evidence](./59-triage-incidents-and-communicate-with-evidence.md).
