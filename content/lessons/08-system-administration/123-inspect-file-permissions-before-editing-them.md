# Chapter 123 — Why some files open and others say “Access denied”

*System Administration From Zero · Stage 10 · Umicom Foundation*

You double-click a document and it opens. You try another file and Windows says **Access denied**. The message can be frustrating, but it may show that the computer is protecting information belonging to another person or service.

A **file permission** defines who can read, change or otherwise use a file or folder. A permission is not necessarily a problem to fix. Sometimes refusal is the correct result.

## Who owns a file?

On common filesystems, permissions relate to users and groups. A folder might let staff read course notes but permit only the instructor to modify them. Umicom applications also need clearly defined rights to their configuration, logs, installation files and user data.

Windows commonly uses **access-control lists (ACLs)** on NTFS. Linux commonly uses owner/group/other permission bits, with ACLs available on many installations. The mechanisms differ, but the question is similar: *which identity is allowed to do what?*

## Inspect a practice folder on Windows

Open PowerShell and run these commands in your own user profile:

```powershell
New-Item -ItemType Directory -Force -Path "$HOME\UmicomLearning\Permissions" | Out-Null
Set-Location "$HOME\UmicomLearning\Permissions"
Set-Content -Path ".\practice.txt" -Value "This is my own practice document."
Get-Acl ".\practice.txt" | Select-Object Owner, AccessToString
```

The first command creates a safe practice directory. The second enters it. The third writes an ordinary text file. `Get-Acl` **reads** the file's ownership and access information; it does not change permissions.

The access information may be long. Note the **Owner** and one example of an allowed right, but do not try to remove entries yet.

## Observe permissions on Linux

Choose a file in your home directory and run:

```bash
ls -l "$HOME"
stat "$HOME"
```

A line such as `drwx------` describes a directory and its permissions. The initial `d` means directory; later characters describe whether the owner, group and others can read, write or access it. Directory execute permission is about traversing or searching the directory, not running it as a program.

## What could go wrong?

Suppose a system administrator makes an application data folder writable by everyone because a service has reported *Permission denied*. The error may disappear, but now unauthorised users can potentially change the service's data. A better investigation identifies the service account and grants only the required access under an approved plan.

**Exercise:** Explain why “make everything writable by everybody” is a poor solution. Name two things to check before changing permissions.

**Answer:** Broad permissions may expose private information and allow accidental or malicious changes. Check the file's purpose, owner, required service identity and legitimate access needs first.
