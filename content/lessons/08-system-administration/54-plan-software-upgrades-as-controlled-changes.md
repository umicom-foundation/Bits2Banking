# Chapter 54 — Plan software upgrades as controlled changes

**System Administration From Zero · Stage 4 — Managed Services and Recovery**  
**Author:** Sammy Hegab · Umicom Foundation  
**Study time:** 65–85 minutes  
**Before starting:** Chapters 8, 29 and 46: package managers and maintenance windows  
**Safety level:** observation-only on real systems; any practice writes are confined to a folder owned by the learner.

## What you will achieve

By the end of this chapter, you will be able to explain **plan software upgrades as controlled changes**, identify the difference between an observation and a change, and interpret at least one Windows and one Linux administration result. You will also be able to describe the evidence that an authorised Umicom support engineer would need before taking action.

## Why this matters in everyday computing

Installing a new application is usually straightforward. Upgrading software used by other people is harder: a library may be incompatible, a configuration file may change meaning, or a restart may interrupt active work. Professional administration therefore separates discovery, approval, installation, verification and rollback.

This lesson teaches how to find installed tool versions and plan a change without running an upgrade. We use Git, CMake and an imaginary Umicom Notes application as examples. Installing, upgrading and uninstalling packages remain outside this chapter unless a learner has explicit permission and an isolated practice environment.

## A mental model you can remember

A software update is like replacing a part in a working bicycle. You first identify the part, check compatibility, plan a safe time, keep the old part available, and test the bicycle afterward. ‘The part fits’ is not the same as ‘the bicycle is safe to ride’. Likewise, a successful installer exit code is not proof that all Umicom builds, tests and user workflows still pass.

## New words, without jargon

| Term | Meaning |
|---|---|
| **Package manager** | A programme that locates, installs and updates software packages. |
| **Dependency** | A library or component another programme requires. |
| **Maintenance window** | A planned period during which authorised changes may occur. |
| **Compatibility matrix** | A record of supported combinations of tools, runtimes and versions. |
| **Rollback plan** | The documented steps to return to a verified previous state after a failed change. |
| **Smoke test** | A small, focused check that essential functions still work after a change. |

## Windows practical lesson — PowerShell 7

Open **Windows Terminal → PowerShell**, or search for **PowerShell 7**. Type only the commands inside each box; the example `PS C:\...>` prompt is not part of a command. Unless a step explicitly says otherwise, use your normal non-administrator account. The commands are interactive teaching instructions, not a `.ps1` script.

### Step 1 — Check the Windows package manager

```powershell
winget --version
```

**Expected result:** The installed winget version appears if available.

**What it means:** `--version` asks only for information; it does not install or upgrade anything.

**If it looks different:** Some locked-down devices do not provide winget. Ask the device administrator instead of downloading random installers.

### Step 2 — Check the Git version

```powershell
git --version
```

**Expected result:** A Git version string appears.

**What it means:** Record the version in a private maintenance note before proposing a toolchain change.

**If it looks different:** If Git is not found, use Get-Command git to investigate installation and PATH.

### Step 3 — Inspect Git's package entry

```powershell
winget list --id Git.Git --exact
```

**Expected result:** A matching package entry appears if winget recognises the installed Git.

**What it means:** winget's available metadata depends on package sources and local detection; a missing entry is not proof that Git is absent.

**If it looks different:** This command is read-only; do not run winget upgrade --all on a shared machine.

### Step 4 — Check compiler and build tools

```powershell
cmake --version
```

**Expected result:** A CMake version and related information appear if installed.

**What it means:** When reporting a failed build, a version matrix (CMake, Ninja, GCC, GTK4) is more useful than guessing that the newest version fixes it.

**If it looks different:** Repeat with `git --version` and `ninja --version` only if those tools are installed.

### Step 5 — Record installed package versions

```powershell
Get-Command git,cmake,ninja -ErrorAction SilentlyContinue | Select-Object Name, Source
```

**Expected result:** Found tool paths are displayed without printing environment secrets.

**What it means:** This helps distinguish two installations of the same programme on PATH.

**If it looks different:** Missing optional tools should be recorded as unavailable, not labelled broken.

## Linux practical comparison

On a Linux computer or an authorised virtual machine, open a terminal. These are **Bash-compatible commands**; do not type the `$` prompt. A minimal container, Chromebook or non-systemd distribution may have a different set of tools. A missing optional tool should be recorded rather than bypassed.

### Linux step 1 — Check a package's candidate version (Debian/Ubuntu)

```bash
apt-cache policy git
```

**Expected result:** Installed and candidate versions are reported on compatible distributions.

**Interpretation:** This is a query, not a package update. On Fedora/RHEL a comparable read-only command is `dnf info git`.

### Linux step 2 — Read the installed compiler version

```bash
gcc --version
```

**Expected result:** The compiler version appears if GCC is installed.

**Interpretation:** A compiler's version is part of build evidence; do not infer compatibility from the number alone.

### Linux step 3 — Read recent package activity (when permitted)

```bash
journalctl -n 10 --no-pager
```

**Expected result:** A few log entries appear, but they are not necessarily package-related.

**Interpretation:** For an update investigation, use the distribution's package-management logs only if authorised, and redact private entries.

## Worked support scenario — Umicom Notes

The Umicom Notes teaching lab was built with one GCC and CMake configuration. A contributor suggests upgrading all developer tools before a demonstration. The maintainer first records current versions, confirms available backups, chooses a separate test host, checks whether the application still builds and runs its native C23 tests there. Only after review is a host upgrade considered. A successful upgrade must not be equated with completed validation.

**Evidence record:** In your own words, describe the issue, the observation time, the command used, what you actually saw, what you have *not* proved, and who would approve a change. Avoid copying usernames, credentials, private filenames, IP addresses or confidential logs into public notes.

## Common mistakes and how to correct them

| Misunderstanding | Better interpretation |
|---|---|
| The newest package always works best. | Compatibility with your project and other dependencies may be more important than version number alone. |
| If the upgrade command exits zero, users have no remaining risk. | Post-change build, functional tests and recovery evidence are still required. |
| Rollback means copying one executable back. | Changes to configuration or data schemas may require independent recovery steps and explicit approval. |

## Guided practice and suggested responses

**Exercise 1.** Prepare a two-column version baseline.

*Suggested response:* List each installed tool and its purpose; do not change versions as part of the exercise.

**Exercise 2.** Write one maintenance-window checklist.

*Suggested response:* Include communication, scope, backup, approval, install plan, smoke test and rollback decision.

**Exercise 3.** Identify a stop condition.

*Suggested response:* For example, required CTest cases report Not Run or a restored dataset fails reconciliation.

## Questions for discussion

1. Which part of today's plan software upgrades as controlled changes exercise was **read-only**, and how do you know?
2. What does a successful command prove, and what would it *not* prove?
3. Explain **Package manager** to somebody who has never opened a terminal.
4. If an expected result does not appear, what evidence would you collect before changing anything?
5. How would you explain this issue to a colleague without exposing private data?

## Connection to Umicom Framework and software engineering

Real Umicom releases should use existing Framework build, deployment, test and repository-evidence services. The native course lab in Update 41 models the decision boundary without installing packages or introducing shell automation. Framework and parent application gitlinks should be qualified independently before publication.

## Further reading (optional internet access)

- https://learn.microsoft.com/windows/package-manager/winget/
- https://learn.microsoft.com/powershell/

## Learning checkpoint

You are ready to proceed if you can explain **the command, its expected output, the boundary of what it proves, and a safe response to unexpected output**. If the exercise needed unavailable administrator access, record *not performed*; do not mark it as passed.

**Next:** [Chapter 55 — Monitor service health using baselines and sensible alerts](./55-monitor-service-health-with-baselines-and-alerts.md).
