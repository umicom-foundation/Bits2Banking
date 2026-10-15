# Chapter 81 — SFTP, file transfer and source/destination ownership

**Bits to Banking · System Administration From Zero · Stage 6 · Umicom Foundation**  
**Prerequisite:** SSH identity and public/private keys (Chapters 75–76).  
**Safety:** Default to a local practice copy. Remote transfer is an optional, explicitly authorised exercise.

## The difference between copying and transferring

You already know how to copy a file from one folder to another. A **remote transfer** copies bytes between machines. The same safety questions remain: where are the source and destination, which account may read and write them, how do we detect an accidental overwrite, and how do we verify that the received data is complete?

**SFTP** stands for SSH File Transfer Protocol. It operates through SSH and is distinct from the old plain-text **FTP** protocol. Although both transfer files, they do not use the same trust or security model. SFTP does not automatically provide backup history, business approval or permission to export confidential data.

## Terms and boundaries

| Word | Meaning |
|---|---|
| Source | The file you intend to copy. |
| Destination | The new path that receives the bytes. |
| Overwrite | Replacing a file already present at the destination. |
| Integrity hash | A calculated digest used to compare file contents. |
| Remote account | A separately authorised identity on the destination host. |
| Transfer log | A record of what was attempted and observed, excluding secrets. |

We will rehearse everything locally first. This avoids touching production servers or transmitting personal information during basic lessons.

## Windows PowerShell — safe local rehearsal

**Step 1.** Create a practice folder inside your own profile:

```powershell
$Root = Join-Path $HOME "UmicomLearning\transfer-practice"
New-Item -ItemType Directory -Path $Root -Force
Set-Location $Root
```

**Step 2.** Create a fictional non-sensitive report with your editor:

```powershell
notepad .\notes-status.txt
```

Enter `Umicom Notes training status: READY TO REVIEW` and save. If a file already exists, inspect it before editing or choose a new practice folder.

**Step 3.** Make a separate receive directory and check before copying:

```powershell
New-Item -ItemType Directory -Path ".\received" -Force
Test-Path ".\received\notes-status.txt"
```

Only if the result is `False`, copy the training document:

```powershell
Copy-Item -LiteralPath ".\notes-status.txt" -Destination ".\received\notes-status.txt"
```

**Step 4.** Compute both SHA-256 hashes:

```powershell
Get-FileHash -Algorithm SHA256 -LiteralPath ".\notes-status.txt"
Get-FileHash -Algorithm SHA256 -LiteralPath ".\received\notes-status.txt"
```

**Expected:** Two identical hashes if the files contain the same bytes. A matching hash demonstrates content equality under that algorithm; it does not prove that you were authorised to copy the file.

## Linux terminal — equivalent private practice

```bash
mkdir -p "$HOME/UmicomLearning/transfer-practice/received"
cd "$HOME/UmicomLearning/transfer-practice"
```

Use your editor to create `notes-status.txt`. Before copying, check whether the destination already exists:

```bash
ls -l notes-status.txt
ls -l received/
```

Only if the destination is vacant, use:

```bash
cp -n notes-status.txt received/notes-status.txt
sha256sum notes-status.txt received/notes-status.txt
```

`cp -n` requests no overwrite; implementation and error behaviour can vary slightly by platform. The important rule remains: **verify the destination before any copy**.

## What a real authorised SFTP session looks like

When the teacher provides an approved host, SSH host-key fingerprint, individual account and remote practice directory, an example command shape is:

```powershell
sftp student@APPROVED_TRAINING_HOST
```

That placeholder is **not** an actual target and must be replaced only with an approved name. The SFTP session has its own commands such as `pwd`, `lpwd`, `ls` and `lls` for remote/local directories. Do not upload a file before checking which side each directory belongs to. A typical controlled workflow is to list the remote directory, upload one harmless training file into an explicitly assigned path, list it again, and compare contents via an approved integrity procedure.

## Failure examples

| Symptom | Meaning or risk | Action |
|---|---|---|
| `Permission denied` | Account lacks required rights, or target is not correct. | Verify the approved destination; do not escalate privileges. |
| Host-key change warning | Remote identity may have changed. | Stop and verify independently. |
| File already exists | Overwrite risk. | Choose a new training filename or request an approved versioning strategy. |
| Same filename, different hash | Bytes differ. | Preserve both copies; investigate before publishing or acting on them. |

## Questions and answers

1. Why is SFTP different from old plain FTP? **It uses SSH's authenticated, encrypted transport.**
2. Does a matching hash prove authorisation? **No, only matching content for the compared files.**
3. When should you stop before a transfer? **When the host identity, target, permissions or overwrite policy is unknown.**

**Next:** Chapter 82 — safely separating service configuration from deployed program files.
