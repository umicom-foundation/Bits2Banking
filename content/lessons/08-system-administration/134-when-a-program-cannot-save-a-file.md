# 134. “The program cannot save”: find the cause before changing anything

*System Administration From Zero · Continued practical lessons*

A colleague tells you, “Our notes application can't save a document.” Should you reinstall the application? Restart the computer? Give everyone administrator permissions?

Not yet. “Cannot save” describes a **symptom**, not a cause. The disk might be full, the destination folder might not exist, the user might lack permission, or the application might be trying to save in the wrong place. A safe system administrator first collects a few facts and tests the simplest explanations without risking existing documents.

## Step 1 — find the exact error

Ask the colleague what happened and which document they tried to save. Record the exact text of the message if possible. Two examples point toward different investigations:

- **“No space left on device”** suggests a storage-capacity problem, although storage quotas or other limits can produce related symptoms.
- **“Access denied”** suggests an access or permission problem. It does not necessarily mean the entire computer is broken.

Do not ask the user to send a password, private document or full bank-account statement. A useful support report can record the error and relevant path while omitting private content.

## Step 2 — check the computer's free space

On **Windows**, open PowerShell and type:

```powershell
Get-PSDrive -PSProvider FileSystem
```

**Expected result:** A list of filesystem drives with available and used space where those values can be reported. Look for the drive containing the document folder. This command does not delete or change any files.

On **Linux**, use:

```bash
df -h
```

`df` reports filesystem usage; `-h` asks for readable units. The folder may be on a different mounted filesystem from your home directory, so check the correct mount point. Available space does not by itself prove that the application can write: quotas, permissions or filesystem state can still prevent saving.

## Step 3 — make sure the destination is what you think it is

On Windows, check whether your **own practice folder** exists:

```powershell
Test-Path "$HOME\UmicomLearning"
```

A result of `True` means the path exists. A result of `False` means it does not exist at that location. It does not tell you who should be allowed to write to it.

If you are checking an existing personal file, you can inspect its metadata without opening its content:

```powershell
Get-Item "$HOME\UmicomLearning" | Select-Object FullName, Attributes
```

On Linux, a comparable directory inspection is:

```bash
ls -ld "$HOME/UmicomLearning"
```

The output begins with file-type and permission characters on common Unix filesystems. Do not assume the letters grant you permission to every file inside; ownership and access-control rules may be more complicated.

## Step 4 — inspect permissions, don't widen them blindly

Windows can show the access rules for a folder:

```powershell
Get-Acl "$HOME\UmicomLearning" | Format-List Owner, Access
```

**Expected result:** Owner information and access entries if the directory exists and you can inspect it. Permissions may come from parent folders and group membership. If you do not understand an entry, ask the person responsible rather than experimenting with an “Everyone: Full Control” rule.

On Linux, useful read-only commands include:

```bash
id
ls -ld "$HOME/UmicomLearning"
```

`id` tells you which user and groups the session belongs to. `ls -ld` shows the directory's metadata. Do **not** run `chmod -R 777`, disable security checks or change ownership of a shared folder merely to see whether the error goes away. That could expose other people's files.

## Step 5 — decide what the evidence actually proves

Consider three possible findings:

| Finding | What you know | What you still need |
|---|---|---|
| The destination drive is full | Storage is a likely obstacle | Confirm the app's target and the applicable quota or filesystem limit |
| The folder does not exist | The path cannot be used as entered | Confirm the correct, approved destination before creating anything |
| The app reports “Access denied” | A permission or policy check failed | Confirm the acting user, destination, effective permissions and security controls |

Only after identifying the cause should you plan a repair. Sometimes the right action is to free approved temporary space; sometimes it is to correct a saved path; sometimes the application itself needs a bug fix. A good repair has a clear owner and a way to verify that the save now works **without exposing or losing the original document**.

## Try a safe classroom investigation

A fictional Notes service reports `Access denied` while saving to a shared department folder. You can see plenty of free disk space, and the folder exists. The service runs under a restricted service account rather than your own Windows login.

1. Which account's permissions matter most: yours or the service account's?
2. Is it sensible to grant everyone full access to the folder as a quick test?
3. What could you record in a support ticket without copying any user documents?

**Suggested answers:** The account actually running the service matters. Broadly opening permissions is not appropriate. Record the affected service and host, exact error, target directory (redacted if sensitive), service identity, relevant timestamp and what read-only checks have been completed. Leave the corrective change to the authorised owner.

This method—**observe, narrow the cause, change only with permission, then verify**—is useful for almost every problem in system administration, not just saving files.
