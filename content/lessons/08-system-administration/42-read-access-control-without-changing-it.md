# Chapter 42 — Read access-control rules without changing them

**Bits to Banking · System Administration: From Zero · Umicom Foundation**  
**Audience:** beginners of any age; younger learners should use a supervised computer.  
**Suggested study time:** 55–75 minutes.  
**Before this chapter:** Chapters 9 and 26: least privilege and filesystem permissions.

## The question this chapter answers

**How can I understand and check this part of a computer without accidentally changing something important?**

## Why this matters

'Access denied' is a useful diagnostic result: it tells us that the attempted operation crossed a permission boundary. Beginners sometimes respond by running everything as administrator, but doing so hides the actual requirement and increases risk. The safer sequence is to identify the file owner, the current user, relevant groups and the permissions on the specific resource.

This lesson reads access-control information only. It does not edit registry permissions, run icacls grant commands, change ownership or modify system ACLs. Practice on a directory owned by the learner and never inspect other people's private documents without permission.

## A useful mental model

A secure door may check both identity and an access list. In Windows, an ACL contains access-control entries for users and groups, potentially including deny rules and inherited permissions. In Linux, basic mode bits describe owner, group and other access, while POSIX ACLs can add entries. Neither format is interchangeable with the other; each must be interpreted in its platform context.

## Key terms, explained before using them

| Term | Meaning |
|---|---|
| **ACL** | Access control list: rules attached to an object. |
| **ACE** | A single rule or entry inside an ACL. |
| **Owner** | Identity associated with an object, with specific administrative rights. |
| **Inheritance** | Permissions flowing from a containing folder under defined rules. |
| **Least privilege** | Granting only the capabilities needed for the authorised task. |
| **Permission denial** | A refused access attempt, not proof of a system malfunction. |

## Read this before typing commands

> **Authorisation and safety:** Use your own computer or an explicitly authorised learning environment. Start with an ordinary user account. Commands that install software, change access, restart services or modify networks are outside this exercise unless the text clearly identifies a harmless practice-file operation. You never need to disable a firewall or change system permissions to complete this chapter.

> **Reading code blocks:** Open PowerShell 7 on Windows (`pwsh`) or a terminal on Linux. Type the line inside the block, not the example prompt. Run one command at a time. Some examples contain multiple interactive commands separated by semicolons; verify their results individually. These are interactive commands, **not scripts added to Umicom**.

## Windows — PowerShell 7 practice

Do these steps on Windows. If you use Linux, read them for comparison and continue below. A missing command means that a tool or module may be unavailable; it is not a reason to bypass computer policy.

### Step 1 — Identify the current identity

```powershell
whoami
```

**Expected result:** Your signed-in Windows identity appears.

**Why this command matters:** Record this before comparing ACL entries. The account used by a scheduled service may be different.

**Safety and troubleshooting:** Never assume you are elevated just because the account belongs to an Administrators group.

### Step 2 — Create a practice directory if needed

```powershell
New-Item -ItemType Directory -Force -Path "$HOME\UmicomLearning\AclLab"
```

**Expected result:** A folder exists under your profile.

**Why this command matters:** The folder is for observations and optional fictional files. It is not a substitute for a dedicated security test environment.

**Safety and troubleshooting:** If a folder of that name already has important contents, pick another name rather than resetting its permissions.

### Step 3 — Read the folder's access control list

```powershell
Get-Acl -LiteralPath "$HOME\UmicomLearning\AclLab" | Format-List Owner, AccessToString
```

**Expected result:** An owner and access entries appear where allowed.

**Why this command matters:** ACL output may be long. Read each identity and right, and note whether the rules were inherited.

**Safety and troubleshooting:** Do not paste full ACL listings publicly if they expose organisation user names or domain names.

### Step 4 — Compare groups with actual rights

```powershell
whoami /groups
```

**Expected result:** Group memberships are printed.

**Why this command matters:** Group membership alone does not settle the effective permission; object-specific ACLs and denial rules also matter.

**Safety and troubleshooting:** A failed file read should be diagnosed, not fixed with blanket Full Control grants.

## Linux — terminal practice

Run these in a Linux terminal on an authorised computer or VM. Some distributions do not install the same commands. An unavailable check should be reported as unavailable; do not assume an unobserved result is successful. No command below requires `sudo`.

### Step 1 — Read identity and group IDs

```bash
id
```

**Expected result:** Numeric and human-readable account and group data appear.

**Why this command matters:** The kernel checks numeric IDs and effective credentials, not just friendly names.

**Safety and troubleshooting:** If this command is unavailable or access is refused, record the result. Do not alter system configuration simply to make the example succeed.

### Step 2 — Inspect your home directory's mode

```bash
ls -ld "$HOME"
```

**Expected result:** Permission characters, owner and group appear.

**Why this command matters:** The first character describes file type; the following nine represent owner/group/other access for basic mode bits.

**Safety and troubleshooting:** If this command is unavailable or access is refused, record the result. Do not alter system configuration simply to make the example succeed.

### Step 3 — Read formatted mode metadata

```bash
stat -c '%A %U:%G %n' "$HOME"
```

**Expected result:** Human-readable mode, owner and path appear.

**Why this command matters:** Some filesystems expose additional ACLs or mount restrictions not visible in mode bits alone.

**Safety and troubleshooting:** If this command is unavailable or access is refused, record the result. Do not alter system configuration simply to make the example succeed.

## Worked Umicom support scenario

A student cannot write a build artefact to a shared folder. They verify they can write to their own home folder and inspect the shared location's policy with an authorised supervisor. This isolates a permission issue from a compiler error. The correct remedy may be using an approved build directory rather than changing the shared folder's permissions.

### A disciplined investigation sequence

1. **Describe the symptom precisely.** Identify what failed and the expected result.
2. **Identify the environment.** Record current account, machine class, working directory and observation time; redact private identifiers.
3. **Run the smallest relevant read-only check.** Choose evidence that distinguishes two possible causes.
4. **Compare results with the requirement.** Missing, blocked or outdated checks are not successful checks.
5. **Separate fact and interpretation.** Label hypotheses explicitly.
6. **Propose, do not silently apply, a change.** State approval, effect, rollback and validation criteria.

## Common mistakes and how to respond

| Incorrect assumption | Better engineering response |
|---|---|
| Running as Administrator is a harmless test. | It changes the security context and can create files owned by the wrong account. |
| File ownership means unrestricted access. | Owner rights differ across systems and may be constrained by ACLs, encryption and policy. |
| Everyone should receive Full Control to make a project build. | Find the minimum required access for the chosen build directory instead. |

## Practical exercises — try these before opening the answers

1. Identify three factors in an access decision.
2. Explain why a build succeeds only as administrator.
3. Describe a safe alternative.

<details>
<summary><strong>Suggested answers and reasoning</strong> — open after attempting the exercises</summary>

1. **Identify three factors in an access decision.** Principal, object-specific permissions and execution context.
2. **Explain why a build succeeds only as administrator.** It may target a protected folder, require an inappropriate installation path or rely on privileged environment settings.
3. **Describe a safe alternative.** Build in a user-owned workspace and request focused access through approved administration processes if needed.

</details>

## Engineering connection: Umicom Framework

Umicom Framework process, filesystem and security services should report permission errors with context, not silently retry with elevated privileges. Studio should not require Administrator rights merely to compile a user's own C23 learning project.

## Short support-note template

```text
Observation ID: PRACTICE-____
Observed at (include timezone):
Authorised machine or learning environment:
User-visible symptom:
Command or test (never paste credentials):
Observed result:
What remains unknown:
Proposed next safe check:
Approval required before any change:
```

## References and further study

- https://learn.microsoft.com/powershell/module/microsoft.powershell.security/get-acl
- https://man7.org/linux/man-pages/man1/stat.1.html

**Course progression:** [Chapter 41](41-make-and-verify-a-recoverable-backup.md) → **Chapter 42** → [Chapter 43](43-follow-one-network-request-from-name-to-port.md).

---

**Safety reminder:** An honest *not available*, *not authorised* or *not run* result is better than a fabricated pass. No real system changes or remote repository writes are required.
