# Chapter 46 — Plan software updates with approval, testing and rollback

**Bits to Banking · System Administration: From Zero · Umicom Foundation**  
**Audience:** beginners of any age; younger learners should use a supervised computer.  
**Suggested study time:** 60–85 minutes.  
**Before this chapter:** Chapters 8, 29 and 35: software updates and incident evidence.

## The question this chapter answers

**How can I understand and check this part of a computer without accidentally changing something important?**

## Why this matters

Updates close security vulnerabilities and fix defects, but they can also change APIs, dependencies and behaviour. An administrator should know what is proposed to change, who approved it, when users will be affected, what must be tested afterwards and how to recover if the change fails. An update window is a planned time with defined owners and acceptance criteria.

Our exercises list available updates and installed versions only. They do not execute winget upgrade --all, apt upgrade, restart a system or modify protected packages. Applying updates to a shared or production computer is a separate, authorised operational task.

## A useful mental model

Treat an update like replacing a bridge component while traffic depends on it. You first inspect the proposed replacement, plan a safe time and identify a bypass or rollback route. For software, record package identity, current version, target version, dependencies, known compatibility constraints and relevant test cases. A successful installer exit code is not the same as an application that still works correctly.

## Key terms, explained before using them

| Term | Meaning |
|---|---|
| **Patch** | A software change intended to correct defects or vulnerabilities. |
| **Maintenance window** | An agreed time for controlled changes. |
| **Dependency** | A library, service or package on which software relies. |
| **Rollback** | A return to a verified acceptable state. |
| **Acceptance test** | A measurable check proving a required behaviour still works. |
| **Change record** | A documented request, owner, reason, test and outcome. |

## Read this before typing commands

> **Authorisation and safety:** Use your own computer or an explicitly authorised learning environment. Start with an ordinary user account. Commands that install software, change access, restart services or modify networks are outside this exercise unless the text clearly identifies a harmless practice-file operation. You never need to disable a firewall or change system permissions to complete this chapter.

> **Reading code blocks:** Open PowerShell 7 on Windows (`pwsh`) or a terminal on Linux. Type the line inside the block, not the example prompt. Run one command at a time. Some examples contain multiple interactive commands separated by semicolons; verify their results individually. These are interactive commands, **not scripts added to Umicom**.

## Windows — PowerShell 7 practice

Do these steps on Windows. If you use Linux, read them for comparison and continue below. A missing command means that a tool or module may be unavailable; it is not a reason to bypass computer policy.

### Step 1 — Check whether winget is installed

```powershell
winget --version
```

**Expected result:** The Windows Package Manager version appears where installed.

**Why this command matters:** The version command does not change installed packages. On managed devices the package manager may be disabled by policy.

**Safety and troubleshooting:** If missing, use approved organisational software channels rather than downloading installers from unknown sites.

### Step 2 — List candidate updates without installing them

```powershell
winget upgrade
```

**Expected result:** Packages with available updates may appear; output format can change.

**Why this command matters:** This is a review step. Read publisher, source and proposed version before deciding whether anything should be upgraded.

**Safety and troubleshooting:** Do not run winget upgrade --all as part of an observation-only lesson.

### Step 3 — Read a few installed Windows updates

```powershell
Get-HotFix | Sort-Object InstalledOn -Descending | Select-Object -First 8 HotFixID, InstalledOn, Description
```

**Expected result:** Some recorded Windows updates appear.

**Why this command matters:** This cmdlet does not show every component or all update types. A missing entry is not conclusive proof a security fix is absent.

**Safety and troubleshooting:** Some computers restrict this view. State that a check was not available rather than guessing.

### Step 4 — Read application version before planning change

```powershell
git --version
```

**Expected result:** The installed Git version appears.

**Why this command matters:** For Umicom contributors, a Git update can change credential handling or command behaviour, so record the starting version before a planned upgrade.

**Safety and troubleshooting:** The command checks the executable resolved by PATH, not every installed copy of Git.

## Linux — terminal practice

Run these in a Linux terminal on an authorised computer or VM. Some distributions do not install the same commands. An unavailable check should be reported as unavailable; do not assume an unobserved result is successful. No command below requires `sudo`.

### Step 1 — Identify the package manager available

```bash
command -v apt; command -v dnf; command -v pacman
```

**Expected result:** Available commands print their paths; missing ones may cause a nonzero result.

**Why this command matters:** Debian/Ubuntu commonly use apt, Fedora/RHEL use dnf, and Arch uses pacman. Use the correct family for the machine.

**Safety and troubleshooting:** If this command is unavailable or access is refused, record the result. Do not alter system configuration simply to make the example succeed.

### Step 2 — List Debian/Ubuntu candidate updates only if apt exists

```bash
apt list --upgradable
```

**Expected result:** Candidate packages appear from existing metadata.

**Why this command matters:** This does not refresh metadata or install updates. Package information may be stale if the last refresh was long ago.

**Safety and troubleshooting:** If this command is unavailable or access is refused, record the result. Do not alter system configuration simply to make the example succeed.

### Step 3 — Read distribution details before planning

```bash
cat /etc/os-release
```

**Expected result:** Distribution and version details appear.

**Why this command matters:** Never copy upgrade instructions blindly from a different distribution or release.

**Safety and troubleshooting:** If this command is unavailable or access is refused, record the result. Do not alter system configuration simply to make the example succeed.

## Worked Umicom support scenario

A team wants to upgrade the MSYS2 GCC toolchain while Umicom Framework has a successful baseline. The maintenance record identifies the exact compiler version, the CMake preset and the selected regression tests. After the update they rerun the same builds and inspect ABI and test changes. If integration fails they revert to a verified toolchain according to the approved package policy, not by deleting arbitrary source files.

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
| Any available update should be installed immediately on every computer. | Security urgency matters, but operational deployment still requires approved controls, staged rollout and recovery. |
| A package manager's success means the application's tests passed. | Installation and application qualification are separate phases. |
| Rolling back a binary always rolls back data safely. | Database schemas or written data may not be backward compatible; recovery needs its own plan. |

## Practical exercises — try these before opening the answers

1. Design a small change record.
2. List four acceptance checks after a toolchain update.
3. Explain why an update list is not an action list.

<details>
<summary><strong>Suggested answers and reasoning</strong> — open after attempting the exercises</summary>

1. **Design a small change record.** Include request, scope, old/new version, owner, time window, tests, rollback and final outcome.
2. **List four acceptance checks after a toolchain update.** Compiler version, CMake configuration, native build and focused tests (plus wider regression when required).
3. **Explain why an update list is not an action list.** Available updates must be evaluated for scope, dependencies, priority and authorisation.

</details>

## Engineering connection: Umicom Framework

Umicom Framework's native build and release services should own technical qualification. A PowerShell package listing is an administrator's interactive observation, not a replacement for the Framework release pipeline, build evidence or source-preservation policy.

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

- https://learn.microsoft.com/windows/package-manager/winget/
- https://learn.microsoft.com/powershell/module/microsoft.powershell.management/get-hotfix

**Course progression:** [Chapter 45](45-recognise-service-health-versus-process-state.md) → **Chapter 46** → [Chapter 47](47-build-an-incident-timeline-from-logs-and-metrics.md).

---

**Safety reminder:** An honest *not available*, *not authorised* or *not run* result is better than a fabricated pass. No real system changes or remote repository writes are required.
