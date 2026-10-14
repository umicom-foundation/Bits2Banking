# Chapter 25 — Users, groups and why identity matters

**Bits to Banking · System Administration: From Zero · Umicom Foundation**  

**Audience:** first-time users and returning learners; practical examples appropriate for supervised younger learners.  

**Estimated study time:** 45–65 minutes.  

**Prerequisites:** Chapters 2 and 9.


## Why this matters

A volunteer signs in to a shared training computer and sees that they can read a sample document but cannot install software. Another user can install software but cannot view the volunteer’s private files. Both outcomes may be correct. System administration begins by understanding **which account is acting** and what that account is permitted to do, rather than trying to make every operation work by elevating privileges.

![Users, groups and why identity matters](../../assets/diagrams/sysadmin-identity-and-roles-update39.svg)


## What you will be able to do

By the end of this chapter you should be able to explain the new terms in ordinary language, select a safe read-only command for the right operating system, recognise a normal result and identify an unverified result. You should also be able to describe what permission would be needed before making a real system change.


## The mental model

A user account answers “who is doing this?”. A group answers “which collection of users shares a permission?”. Authentication proves identity; authorisation checks whether that identity can take an action. A signed-in person can also start programs that run with another identity, such as a Windows service account or a Linux daemon. Do not confuse the visible account name with the privileges of every process. Windows also has a distinction between being a member of Administrators and actually running an elevated process under User Account Control (UAC). Linux commonly separates an ordinary account from controlled administrator actions performed with `sudo`.

### How accounts become effective permissions

Imagine an online classroom with a teacher, a learner and an application server. The learner must read lessons and create documents in their own folder. The teacher may edit shared lessons, and a background publishing service may read approved Markdown material. These are three distinct roles, not three reasons to make every account a local administrator. The right question is “which operation must this identity perform on which resource?”. Identify the smallest privilege that satisfies that task.

In a multi-user environment, **membership can change while a session remains active**. A permission update may not immediately affect an already issued access token or group membership visible to a running process. This is one reason an access problem should be reproduced with the same user and session rather than tested only as an administrator. A Windows computer joined to a domain may also display domain identity information unavailable to the local account commands used in this lesson. Record the environment rather than assuming all Windows computers are identical.


## Words you should know
| Term | Meaning |
|---|---|
| **Identity** | An account or principal whose actions can be attributed. |
| **Group** | A set of accounts that may share permissions. |
| **Privilege** | A permission with system-wide consequences. |
| **Least privilege** | Giving an account only the authority needed for its work. |
| **Service account** | An identity used by background software rather than everyday interactive use. |


## Windows: PowerShell 7, one command at a time

> Use a **normal non-elevated PowerShell** window. Do not type the `PS C:\...>` prompt. If a command is unavailable or returns Access Denied, record that result; do not attempt to defeat the restriction.

The lines in a code block may contain more than one interactive command. Run them in order, checking each result before continuing. **No `.ps1` file is created or required.**

### Windows step 1 — Identify the signed-in account

```powershell
whoami
```

**Expected result:** A computer or domain name followed by the account name. This is identity, not a list of all privileges.

**What this does:** PowerShell runs the command in your current session and displays information or, where clearly indicated, changes only your own practice files. If output differs, record the actual result before going further.

### Windows step 2 — Read the groups for this session

```powershell
whoami /groups
```

**Expected result:** Group membership and attributes appear. Do not copy the complete output into public chat; it can identify your organisation.

**What this does:** PowerShell runs the command in your current session and displays information or, where clearly indicated, changes only your own practice files. If output differs, record the actual result before going further.

### Windows step 3 — Inspect local users without changing them

```powershell
Get-LocalUser | Select-Object Name, Enabled
```

**Expected result:** Local account names and enabled state on supported Windows editions. A domain-managed or restricted machine may return an error: record that limitation.

**What this does:** PowerShell runs the command in your current session and displays information or, where clearly indicated, changes only your own practice files. If output differs, record the actual result before going further.

### Windows step 4 — Check your shell identity explicitly

```powershell
[System.Security.Principal.WindowsIdentity]::GetCurrent().Name
```

**Expected result:** A text identifier for the Windows security context of this process.

**What this does:** PowerShell runs the command in your current session and displays information or, where clearly indicated, changes only your own practice files. If output differs, record the actual result before going further.


## Linux: terminal and distribution differences

> Run the following only in an authorised Linux computer or VM. If you use Windows only, read this section for comparison. A program being absent does not mean the whole operating system is faulty.

### Linux step 1 — Identify the running account

```bash
id
```

**Expected result:** User ID (UID), primary group ID (GID) and supplementary groups.

### Linux step 2 — Show the short account name

```bash
whoami
```

**Expected result:** The effective user for the current command.

### Linux step 3 — Inspect groups in a friendly format

```bash
groups
```

**Expected result:** Group names for the current user; membership is not a reason to alter groups.


## Worked support scenario

A student cannot create a folder under `C:\Program Files`. Rather than reopening everything as Administrator, first inspect the current identity, then choose a personal learning directory such as `$HOME\UmicomLearning`. Installation into protected locations is a separate, explicitly authorised activity. If a service fails under its own account, the correct investigation concerns that service identity and the exact resource it needs—not the identity of the engineer who happens to be watching.


## Common mistakes and safe responses
| Mistake | Better response |
|---|---|
| “I belong to Administrators, so every process is elevated.” | UAC commonly starts ordinary processes with restricted privileges; membership and effective rights differ. |
| “Make the student administrator to fix it.” | Check the intended folder and required action first; use a user-writable practice location. |
| “A service uses the currently signed-in account.” | Many services run under independently configured identities. |


## Exercises

1. Write down the difference between authentication and authorisation.

2. Explain why inspecting groups is safer than adding everyone to a privileged group.

3. Imagine a backup service cannot read a private directory. Identify two facts to collect before proposing any change.


## Review questions and suggested answers

<details><summary>Show the suggested answers after attempting the exercises</summary>



1. Authentication checks who you are; authorisation checks what that identity may do.

2. Adding privilege affects many more resources and hides the actual root cause.

3. Record the service identity and the intended directory ACL before any modification.



</details>


## Connecting this chapter to Umicom

Production Umicom software should use the appropriate **Umicom Framework** service for identities, processes, filesystem operations, Git, diagnostics, build planning or observability. The teaching commands here are interactive; they are **not** substitute Python or PowerShell implementations. Any reusable new executable component must first be considered for Framework ownership and designed in C23 or justified Assembly.


## References and further reading

- https://learn.microsoft.com/windows/security/identity-protection/access-control/access-control

- https://www.gnu.org/software/coreutils/manual/html_node/id-invocation.html


**Course progression:** [Chapter 24](24-capstone-your-first-support-check.md) → **Chapter 25** → [Chapter 26](26-understand-ntfs-and-linux-permissions.md)


---

**Practical safety reminder:** No exercise requires access to private records, bank accounts, live production systems or another person’s computer. A successful “not permitted” or “not run” observation is an acceptable learning outcome.
