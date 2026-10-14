# Chapter 26 — Understand file permissions without opening private data

**Bits to Banking · System Administration: From Zero · Umicom Foundation**  

**Audience:** first-time users and returning learners; practical examples appropriate for supervised younger learners.  

**Estimated study time:** 50–75 minutes.  

**Prerequisites:** Chapter 25 and Chapter 7.


## Why this matters

A project README is visible in one folder but access is denied in another. A beginner may assume the file has disappeared. Often the file exists, but the operating system has correctly refused an operation. The administrator’s job is to explain access decisions **without bypassing the owner or exposing private files**.

![Understand file permissions without opening private data](../../assets/diagrams/sysadmin-identity-and-roles-update39.svg)


## What you will be able to do

By the end of this chapter you should be able to explain the new terms in ordinary language, select a safe read-only command for the right operating system, recognise a normal result and identify an unverified result. You should also be able to describe what permission would be needed before making a real system change.


## The mental model

A folder path tells you *where* an item is; permissions decide *who* may read, write, or traverse it. Windows NTFS uses access-control lists (ACLs) with entries applying to users and groups. Rights may be inherited from the containing folder, and an explicit deny entry can influence access. Linux traditionally shows owner, group and other read/write/execute bits; directories use execute for **traversal**, so being able to read the directory name list is not the same as reaching a file. Additional ACL mechanisms and security layers can apply on either system. Never conclude “everyone can read” from one superficial permission view.

### What “effective access” really asks

Consider a Notes project with a `docs` directory. On Linux, a file may be readable according to its own mode but still inaccessible if the user lacks traverse permission on a parent directory. On Windows, an inherited ACL entry might grant read access while another relevant identity or policy changes the overall result. File ownership may permit altering permissions but does not automatically imply every ordinary access request succeeds. The exact behaviour depends on the operating system and the file and share permission layers involved.

**Do not test private documents to discover access rights.** Use a file you own. The responsible administrator asks the owner of the resource to approve any change and documents the intended access policy before modifying ACLs. The goal is not to make an error disappear; it is to ensure only the people and services with a genuine need can use the resource.


## Words you should know
| Term | Meaning |
|---|---|
| **ACL** | An access-control list of permissions and identities. |
| **Inheritance** | A child receiving permission rules from its parent. |
| **Read** | Permission to inspect content, when other controls allow it. |
| **Write** | Permission to change content or metadata. |
| **Traverse** | Permission to pass through a directory to reach a child. |


## Windows: PowerShell 7, one command at a time

> Use a **normal non-elevated PowerShell** window. Do not type the `PS C:\...>` prompt. If a command is unavailable or returns Access Denied, record that result; do not attempt to defeat the restriction.

The lines in a code block may contain more than one interactive command. Run them in order, checking each result before continuing. **No `.ps1` file is created or required.**

### Windows step 1 — Confirm your own practice document exists

```powershell
Test-Path "$HOME\UmicomLearning\Notes\README.md"
```

**Expected result:** True only if the training file exists at that path; if False, complete Chapter 6 or substitute your own harmless practice document.

**What this does:** PowerShell runs the command in your current session and displays information or, where clearly indicated, changes only your own practice files. If output differs, record the actual result before going further.

### Windows step 2 — Examine its owner and ACL

```powershell
Get-Acl "$HOME\UmicomLearning\Notes\README.md" | Format-List Owner, Access
```

**Expected result:** Entries identify permissions and inheritance. The list may be extensive.

**What this does:** PowerShell runs the command in your current session and displays information or, where clearly indicated, changes only your own practice files. If output differs, record the actual result before going further.

### Windows step 3 — View an alternative built-in Windows ACL report

```powershell
icacls "$HOME\UmicomLearning\Notes\README.md"
```

**Expected result:** Rights may appear as letter codes; this command only displays when called with no changes.

**What this does:** PowerShell runs the command in your current session and displays information or, where clearly indicated, changes only your own practice files. If output differs, record the actual result before going further.


## Linux: terminal and distribution differences

> Run the following only in an authorised Linux computer or VM. If you use Windows only, read this section for comparison. A program being absent does not mean the whole operating system is faulty.

### Linux step 1 — Inspect the permission string on your own test file

```bash
ls -l "$HOME/UmicomLearning/Notes/README.md"
```

**Expected result:** Owner, group, size and mode are shown.

### Linux step 2 — Inspect mode numerically on GNU/Linux

```bash
stat -c "%a %U %G %n" "$HOME/UmicomLearning/Notes/README.md"
```

**Expected result:** Numerical mode, user, group and path. Other Unix variants use different `stat` options.

### Linux step 3 — Inspect the directory separately

```bash
ls -ld "$HOME/UmicomLearning/Notes"
```

**Expected result:** Notice `x` on a directory permits traversal; it is not file execution.


## Worked support scenario

A colleague says “please run `chmod -R 777` because my Notes app cannot save”. Explain why the request is unsafe: it changes rights recursively, including files never involved in the incident, and grants broad access. Instead, identify the exact directory, the service identity, the operation attempted and any relevant OS or application log. Demonstrate by reading permissions on your *own* practice file, with no permission changes.


## Common mistakes and safe responses
| Mistake | Better response |
|---|---|
| “Read-only commands should be run as Administrator just in case.” | Normal-user inspection is the default; escalation should be justified, reviewed and time-limited. |
| “A Linux `x` bit always means running a program.” | On directories, `x` means search/traverse permission. |
| “An ACL line fully explains every access decision.” | Inheritance, groups and additional controls may influence the effective result. |


## Exercises

1. Explain the three common Linux permission classes.

2. Identify one reason a file might exist yet remain inaccessible.

3. Find the owner of a harmless file you created for training, then stop without changing its ACL.


## Review questions and suggested answers

<details><summary>Show the suggested answers after attempting the exercises</summary>



1. Owner, group and other; an ACL can add further granularity.

2. Insufficient permission on the file or a parent directory, among other possibilities.

3. Use `Get-Acl` or `ls -l`; no elevation or broad permission changes are needed.



</details>


## Connecting this chapter to Umicom

Production Umicom software should use the appropriate **Umicom Framework** service for identities, processes, filesystem operations, Git, diagnostics, build planning or observability. The teaching commands here are interactive; they are **not** substitute Python or PowerShell implementations. Any reusable new executable component must first be considered for Framework ownership and designed in C23 or justified Assembly.


## References and further reading

- https://learn.microsoft.com/windows-server/administration/windows-commands/icacls

- https://www.gnu.org/software/coreutils/manual/html_node/File-permissions.html


**Course progression:** [Chapter 25](25-users-groups-and-real-identity.md) → **Chapter 26** → [Chapter 27](27-windows-service-diagnosis-and-event-evidence.md)


---

**Practical safety reminder:** No exercise requires access to private records, bank accounts, live production systems or another person’s computer. A successful “not permitted” or “not run” observation is an acceptable learning outcome.
