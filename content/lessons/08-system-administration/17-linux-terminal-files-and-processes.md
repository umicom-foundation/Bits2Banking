# Chapter 17 — Linux terminal, home directory, files and processes

**Bits to Banking · System Administration: From Zero · Umicom Foundation**  
**Audience:** first-time users and returning learners; no prior system-administration knowledge required.  
**Code policy:** interactive PowerShell 7 and Bash commands; native C23/Assembly for Umicom executable development.  
**Estimated study time:** 25–50 minutes (longer when practising).

## What you will learn

Translate familiar Windows tasks into safe Linux equivalents.

## Why this matters

![A safe training folder is separate from real projects](../../assets/diagrams/sysadmin-safe-workspace-update38.svg)


Linux distributions usually provide a terminal emulator that starts a shell such as Bash. The user’s home directory is commonly under `/home/username` and is referred to as `$HOME`. Linux paths use `/` rather than Windows backslashes. `pwd` prints the current directory, `ls` lists entries, `cd` changes directory, and `mkdir -p` creates a directory tree.

A beginner does not need to memorise every shell option. They need to understand which system a command belongs to, how to request help and how to verify the result. PowerShell’s `Get-ChildItem` is conceptually similar to `ls` on Linux, although the programs differ in output and behaviour.

Linux commands can operate with elevated privileges through tools such as `sudo`. We avoid `sudo` in the initial exercises. A learner should know what a command is going to do before running it as an administrator.

## New words, explained

| Term | Plain-English meaning |
|---|---|
| **Distribution** | Linux operating-system distribution with packaged software and configuration. |
| **Bash** | Popular command shell on Linux. |
| **Home directory** | Per-user location for personal data and settings. |
| **sudo** | Command used to request privileged execution when authorised. |
| **Process ID** | Operating-system identifier for a running process. |

## Windows practice — PowerShell 7

> **Before typing:** Run these commands in a normal, non-elevated PowerShell window. Where a file is used, complete the previous practice-folder chapters first. Do not paste the `PS C:\...>` prompt into the terminal.

**Start:** Use the Windows Start menu or Windows Terminal to open PowerShell. Check the prompt is ready. Commands beginning with `$` are still commands; type them exactly as shown.

### Step 1 — On Windows, open PowerShell and check current location

```powershell
Get-Location
```

**Expected observation:** Windows prints its working path. Linux exercises below use a Linux terminal.

**Check:** Read the output before continuing. If it does not match, stop and investigate the specific command; do not add `-Force` or run as Administrator automatically.

### Step 2 — Compare a PowerShell directory listing

```powershell
Get-ChildItem "$HOME" | Select-Object -First 5
```

**Expected observation:** You see a subset of items in your Windows home.

**Check:** Read the output before continuing. If it does not match, stop and investigate the specific command; do not add `-Force` or run as Administrator automatically.

## Linux comparison — terminal/Bash

> Linux commands are alternatives on a Linux machine or authorised VM. Do not paste them into Windows PowerShell as though the shells have identical syntax.

### Linux step 1 — Show the home location and user

```bash
printf "Home: %s\n" "$HOME" && whoami
```

**Expected observation:** The shell prints the home path and current account.

### Linux step 2 — Create a safe Linux course directory

```bash
mkdir -p "$HOME/UmicomLearning/LinuxNotes"
```

**Expected observation:** The folder exists after this command.

### Linux step 3 — Navigate and list it

```bash
cd "$HOME/UmicomLearning/LinuxNotes" && pwd && ls -la
```

**Expected observation:** The path and directory contents are displayed.

### Linux step 4 — List a few current processes

```bash
ps -e | head -n 8
```

**Expected observation:** Process IDs and command names appear.

## Worked support scenario

A student follows a Windows guide on a Linux laptop and tries `Get-CimInstance`, receiving “command not found.” They should not install unrelated packages at random. Instead, identify the intended information and use the Linux command (`uname`, `free`, `df`, `ps`) documented for that subject.

## Common problems and how to respond

| Problem or assumption | Better response |
|---|---|
| Using backslashes as Linux directory separators | Linux commonly uses `/`. |
| Running `sudo` with every command | Most read-only beginner commands do not need administrator rights. |
| Expecting Windows drive letters in Linux | Linux mounts filesystems under a common directory tree. |

## Exercise: demonstrate understanding

1. Write down the purpose of **two commands** from this chapter, in your own words.
2. Run a **read-only command** and record only the information needed to answer its question.
3. Explain which command would change the machine, if any, and why the chapter avoids it.
4. Explain the difference between an observation, a conclusion and an unverified assumption.

## Review questions

1. What does `pwd` report on Linux?
2. Why is a Linux `/home` path not directly a Windows `C:` path?

<details><summary>Show the suggested answers</summary>

1. The current working directory.
2. The operating systems organise filesystem locations differently.

</details>

## How this connects to Umicom

Cross-platform Umicom native C23 components should preserve platform-neutral contracts. The same Framework design can have separate Windows and Linux adapters for system-specific operations.

## Where to go next

Continue with [Chapter 18 — Linux permissions, packages, services and logs](18-linux-users-permissions-packages-logs.md).
