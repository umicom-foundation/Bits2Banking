# Chapter 08 — Install and verify PowerShell 7, Git and development tools

**Bits to Banking · System Administration: From Zero · Umicom Foundation**  
**Audience:** first-time users and returning learners; no prior system-administration knowledge required.  
**Code policy:** interactive PowerShell 7 and Bash commands; native C23/Assembly for Umicom executable development.  
**Estimated study time:** 25–50 minutes (longer when practising).

## What you will learn

Use trusted package managers and check that programs really work.

## Why this matters

![Professional administration separates observation from change](../../assets/diagrams/sysadmin-observe-change-update38.svg)


A package manager installs software from configured sources. On Windows, `winget` is the Windows Package Manager command-line interface. It is useful for installing PowerShell 7, Git, GitHub CLI and Visual Studio Code. You can run it from Windows PowerShell 5.1 while installing the newer PowerShell 7. The two products can coexist.

Before installing anything, run `winget --version`. If it is missing, consult Microsoft’s App Installer guidance rather than downloading an unfamiliar installer. When `winget install` is used, the package ID identifies the intended product. Review prompts about source agreements, licensing or elevated permissions rather than automatically accepting everything.

After installation, open a fresh terminal. Executable search paths may not refresh in an already-open shell. `Get-Command` tells you which executable the shell would run. A version command confirms that the program launches, which is different from proving it is compatible with a particular project build.

## New words, explained

| Term | Plain-English meaning |
|---|---|
| **Package manager** | Software that installs and updates programs from configured sources. |
| **Package ID** | Unique identifier, such as `Git.Git`, used to choose a package. |
| **PATH** | Locations searched when you type an executable name. |
| **CLI** | Command-line interface, such as `gh` for GitHub. |
| **Toolchain** | Programs such as a compiler, CMake and Ninja used to build software. |

## Windows practice — PowerShell 7

> **Before typing:** Run these commands in a normal, non-elevated PowerShell window. Where a file is used, complete the previous practice-folder chapters first. Do not paste the `PS C:\...>` prompt into the terminal.

**Start:** Use the Windows Start menu or Windows Terminal to open PowerShell. Check the prompt is ready. Commands beginning with `$` are still commands; type them exactly as shown.

### Step 1 — Check that winget exists

```powershell
winget --version
```

**Expected observation:** A version appears; if the command is not found, consult Microsoft installation guidance.

**Check:** Read the output before continuing. If it does not match, stop and investigate the specific command; do not add `-Force` or run as Administrator automatically.

### Step 2 — Inspect the PowerShell package before installing

```powershell
winget show --id Microsoft.PowerShell --exact
```

**Expected observation:** Read the package name, publisher and installer information.

**Check:** Read the output before continuing. If it does not match, stop and investigate the specific command; do not add `-Force` or run as Administrator automatically.

### Step 3 — Install PowerShell 7 if needed

```powershell
winget install --id Microsoft.PowerShell --exact --source winget
```

**Expected observation:** After any prompts and completion, open a *new* PowerShell 7 window.

**Check:** Read the output before continuing. If it does not match, stop and investigate the specific command; do not add `-Force` or run as Administrator automatically.

### Step 4 — Install Git when required

```powershell
winget install --id Git.Git --exact --source winget
```

**Expected observation:** Git is installed; close and reopen the terminal to refresh PATH.

**Check:** Read the output before continuing. If it does not match, stop and investigate the specific command; do not add `-Force` or run as Administrator automatically.

### Step 5 — Install GitHub CLI when required

```powershell
winget install --id GitHub.cli --exact --source winget
```

**Expected observation:** The `gh` command becomes available after installation.

**Check:** Read the output before continuing. If it does not match, stop and investigate the specific command; do not add `-Force` or run as Administrator automatically.

### Step 6 — Check which executables were installed

```powershell
Get-Command pwsh, git, gh -ErrorAction SilentlyContinue | Select-Object Name, Source
```

**Expected observation:** Available tools are listed with their installed paths.

**Check:** Read the output before continuing. If it does not match, stop and investigate the specific command; do not add `-Force` or run as Administrator automatically.

## Linux comparison — terminal/Bash

> Linux commands are alternatives on a Linux machine or authorised VM. Do not paste them into Windows PowerShell as though the shells have identical syntax.

### Linux step 1 — Read package manager version on Ubuntu or Debian

```bash
apt --version
```

**Expected observation:** The package-manager version is displayed.

### Linux step 2 — Inspect a package before requesting installation

```bash
apt show git
```

**Expected observation:** Package metadata appears when the distribution can find Git.

## Worked support scenario

A beginner says “Git is installed but PowerShell cannot find it.” Instead of reinstalling repeatedly, ask them to close the old terminal, open a new PowerShell 7 window, run `Get-Command git` and then `git --version`. This distinguishes a PATH refresh issue from an actual installation failure.

## Common problems and how to respond

| Problem or assumption | Better response |
|---|---|
| Typing `winget - -version` | The correct syntax is `winget --version` with adjacent hyphens. |
| Installing an unknown similarly named package | Use the exact verified package ID and inspect `winget show`. |
| Believing successful installation proves authentication | `gh --version` tests the program; `gh auth status` tests the GitHub sign-in. |

## Exercise: demonstrate understanding

1. Write down the purpose of **two commands** from this chapter, in your own words.
2. Run a **read-only command** and record only the information needed to answer its question.
3. Explain which command would change the machine, if any, and why the chapter avoids it.
4. Explain the difference between an observation, a conclusion and an unverified assumption.

## Review questions

1. Why check `Get-Command` after installing a tool?
2. Does `winget install` require you to write a PowerShell script?

<details><summary>Show the suggested answers</summary>

1. It shows whether the shell can locate the intended executable.
2. No. It is an interactive command; we do not add `.ps1` implementation files.

</details>

## How this connects to Umicom

For native C23 development, verify MSYS2 UCRT64 GCC, CMake and Ninja using the project’s documented toolchain. Do not mix toolchain families silently or change live build presets without reviewing them.

## Where to go next

Continue with [Chapter 09 — Users, administrators and the meaning of permissions](09-accounts-permissions-least-privilege.md).
