# Chapter 131 — Plan recovery before you change anything

*System Administration From Zero · Stage 10 · Umicom Foundation*

A software update can improve security or add features, but it can also introduce a fault. A careful administrator asks a simple question **before** starting: “If this change fails, how will we restore the previous working service?”

A **rollback** returns a particular change to an earlier state. **Recovery** is the broader job of restoring acceptable service. They are related but not always identical: rolling back an application file may not reverse a database migration or recover missing records.

## What makes a backup useful?

A file copied to another folder may be a backup, but it is only **proven recoverable** when a restore has been tested. The original file and backup also need enough context: version, creation time, purpose and location.

For a harmless practice, open PowerShell and type:

```powershell
New-Item -ItemType Directory -Force -Path "$HOME\UmicomLearning\Recovery\original" | Out-Null
New-Item -ItemType Directory -Force -Path "$HOME\UmicomLearning\Recovery\restored" | Out-Null
Set-Content "$HOME\UmicomLearning\Recovery\original\note.txt" "Practice version A"
Copy-Item "$HOME\UmicomLearning\Recovery\original\note.txt" "$HOME\UmicomLearning\Recovery\restored\note.txt"
```

Now compare the two copies:

```powershell
Get-FileHash "$HOME\UmicomLearning\Recovery\original\note.txt" -Algorithm SHA256
Get-FileHash "$HOME\UmicomLearning\Recovery\restored\note.txt" -Algorithm SHA256
```

The hashes should match. This simple exercise proves that the copied **bytes** agree. It does not prove that a database, full application or live environment could be restored using the same method.

## A safe change plan for a real service

Before an approved maintenance window, identify which files and data will change, who authorises it, what tests demonstrate success, how long the change may take, and when to decide to stop. Make sure restoration instructions have been rehearsed on an appropriate non-production system.

Suppose a new Umicom Notes release starts successfully but can no longer open existing notes. Restarting it repeatedly will not fix incompatible data or a missing permission. The team must compare the known-good release and data state, decide whether it is safe to roll back, and verify the actual user operation after recovery.

## Recovery must be checked independently

A process restarting is not enough. For our Notes example, success means an authorised user can open and save an appropriate practice note, expected records remain present, and logs show no unresolved errors within the agreed test scope.

**Exercise:** List the minimum things you would preserve before a controlled software update: release identity, configuration, data backup, approval, tests, rollback instructions and monitoring. Then explain why saving only the executable would not be enough if the update also changes database records.
