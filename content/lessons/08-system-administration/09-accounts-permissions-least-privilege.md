# Chapter 09 — Users, administrators and the meaning of permissions

**Bits to Banking · System Administration: From Zero · Umicom Foundation**  
**Audience:** first-time users and returning learners; no prior system-administration knowledge required.  
**Code policy:** interactive PowerShell 7 and Bash commands; native C23/Assembly for Umicom executable development.  
**Estimated study time:** 25–50 minutes (longer when practising).

## What you will learn

Explain which account runs a command and why elevated rights are exceptional.

## Why this matters

![Professional administration separates observation from change](../../assets/diagrams/sysadmin-observe-change-update38.svg)


Operating systems use identities to decide who may open, modify or execute a resource. Your signed-in account usually has a personal home folder and limited access to system-wide settings. An administrator account can perform more powerful operations. That extra power is useful for approved maintenance, but it also increases the damage a mistaken command can cause.

A permission is a rule attached to a resource. On Windows, NTFS access control lists can grant different rights to users and groups. On Linux, files have owners, groups and permission bits, with additional mechanisms such as ACLs. Changing permissions without understanding them can expose confidential documents or stop applications from working.

In this chapter we **observe** identity rather than changing membership or granting rights. If an installation asks for elevation, confirm that the source is trustworthy and that the installation is intended. Never solve a confusing error by turning off protection, recursively changing folder ownership or making the entire system writable.

## New words, explained

| Term | Plain-English meaning |
|---|---|
| **Identity** | The user or service account under which an operation runs. |
| **Administrator** | Account with elevated system-management privileges. |
| **ACL** | Access control list specifying who may use a resource. |
| **Group** | Set of accounts that may share permissions. |
| **Permission denied** | Operating-system refusal because the account lacks required access. |

## Windows practice — PowerShell 7

> **Before typing:** Run these commands in a normal, non-elevated PowerShell window. Where a file is used, complete the previous practice-folder chapters first. Do not paste the `PS C:\...>` prompt into the terminal.

**Start:** Use the Windows Start menu or Windows Terminal to open PowerShell. Check the prompt is ready. Commands beginning with `$` are still commands; type them exactly as shown.

### Step 1 — Show the current identity

```powershell
whoami
```

**Expected observation:** The Windows account name appears.

**Check:** Read the output before continuing. If it does not match, stop and investigate the specific command; do not add `-Force` or run as Administrator automatically.

### Step 2 — Display current identity and group context

```powershell
whoami /groups
```

**Expected observation:** Group membership information is displayed.

**Check:** Read the output before continuing. If it does not match, stop and investigate the specific command; do not add `-Force` or run as Administrator automatically.

### Step 3 — Inspect permissions on a practice file

```powershell
Get-Acl "$HOME\UmicomLearning\Notes\README.md" | Format-List Owner, AccessToString
```

**Expected observation:** The file owner and readable access rules are shown.

**Check:** Read the output before continuing. If it does not match, stop and investigate the specific command; do not add `-Force` or run as Administrator automatically.

### Step 4 — Verify your practice file exists before inspecting it

```powershell
Test-Path "$HOME\UmicomLearning\Notes\README.md"
```

**Expected observation:** True indicates the file exists; False means you should complete Chapter 6.

**Check:** Read the output before continuing. If it does not match, stop and investigate the specific command; do not add `-Force` or run as Administrator automatically.

## Linux comparison — terminal/Bash

> Linux commands are alternatives on a Linux machine or authorised VM. Do not paste them into Windows PowerShell as though the shells have identical syntax.

### Linux step 1 — Show the current user and groups

```bash
id
```

**Expected observation:** User ID, primary group and supplementary groups appear.

### Linux step 2 — Inspect file permissions

```bash
ls -l "$HOME/UmicomLearning/Notes/README.md"
```

**Expected observation:** The permission string, owner and group appear if the file exists.

## Worked support scenario

A colleague cannot edit a training document in a shared folder. First check which identity they are using and who owns the file. Do not immediately grant Everyone full control: establish what access the colleague actually needs and ask the resource owner to approve that permission.

## Common problems and how to respond

| Problem or assumption | Better response |
|---|---|
| Launching every terminal “as Administrator” | Use a standard terminal unless a justified action requires elevation. |
| Applying recursive permission changes to unknown directories | Inspect the relevant file and authorisation boundary first. |
| Confusing “file exists” with “I can write it” | Existence and access permissions are separate checks. |

## Exercise: demonstrate understanding

1. Write down the purpose of **two commands** from this chapter, in your own words.
2. Run a **read-only command** and record only the information needed to answer its question.
3. Explain which command would change the machine, if any, and why the chapter avoids it.
4. Explain the difference between an observation, a conclusion and an unverified assumption.

## Review questions

1. What is least privilege?
2. Why does a correct password not guarantee access to every file?

<details><summary>Show the suggested answers</summary>

1. Granting only the permissions required for a task.
2. The account still has permissions that may restrict access.

</details>

## How this connects to Umicom

Framework repositories, build outputs, financial reports and patient records have different access boundaries. Training exercises never access real customer or beneficiary data.

## Where to go next

Continue with [Chapter 10 — Processes: what is running on your computer?](10-understand-running-processes.md).
