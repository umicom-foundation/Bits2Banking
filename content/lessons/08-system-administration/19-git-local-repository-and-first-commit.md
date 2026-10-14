# Chapter 19 — Git from zero: create, inspect, stage and commit

**Bits to Banking · System Administration: From Zero · Umicom Foundation**  
**Audience:** first-time users and returning learners; no prior system-administration knowledge required.  
**Code policy:** interactive PowerShell 7 and Bash commands; native C23/Assembly for Umicom executable development.  
**Estimated study time:** 25–50 minutes (longer when practising).

## What you will learn

Make a complete history of a practice document before publishing anything.

## Why this matters

![Git snapshots and publication are separate actions](../../assets/diagrams/sysadmin-git-staging-update38.svg)


Git keeps versions of project files locally. A **working tree** is the files you are editing. The **staging area** selects changes for the next commit. A **commit** records a snapshot with an identifier, an author and an explanation. A **branch** is a movable reference to a line of commits; `main` is commonly the default branch. Git works without GitHub, which is a remote hosting service.

You can learn Git safely in a private practice folder without a remote. This prevents experimental commits from entering real Umicom repositories. Keep changes small and messages specific. Inspect `git diff` before staging and `git diff --cached` after staging. `git add -A` includes deletions as well as additions; reviewing is essential.

For the first exercise create a repository under `$HOME\UmicomLearning\git-first-project`. Do not call `git init` inside an existing parent Git repository unless that nesting is intentional. The practice area is separate from the actual Umicom-Applications workspace.

## New words, explained

| Term | Plain-English meaning |
|---|---|
| **Working tree** | Editable files visible on disk. |
| **Index/staging area** | Selected snapshot waiting for the next commit. |
| **Commit** | Identified, recorded version of a repository. |
| **Branch** | Named reference to a commit history. |
| **Remote** | Another Git repository address, often on GitHub. |

## Windows practice — PowerShell 7

> **Before typing:** Run these commands in a normal, non-elevated PowerShell window. Where a file is used, complete the previous practice-folder chapters first. Do not paste the `PS C:\...>` prompt into the terminal.

**Start:** Use the Windows Start menu or Windows Terminal to open PowerShell. Check the prompt is ready. Commands beginning with `$` are still commands; type them exactly as shown.

### Step 1 — Create a dedicated Git practice folder

```powershell
New-Item -ItemType Directory -Path "$HOME\UmicomLearning\git-first-project" -Force
```

**Expected observation:** The folder exists without affecting existing Umicom repositories.

**Check:** Read the output before continuing. If it does not match, stop and investigate the specific command; do not add `-Force` or run as Administrator automatically.

### Step 2 — Enter the folder and begin Git history

```powershell
Set-Location "$HOME\UmicomLearning\git-first-project"
git init -b main
```

**Expected observation:** Git reports it created an empty repository on `main`.

**Check:** Read the output before continuing. If it does not match, stop and investigate the specific command; do not add `-Force` or run as Administrator automatically.

### Step 3 — Write an introductory Markdown file

```powershell
Set-Content -Path .\README.md -Value "# My Umicom training project"
```

**Expected observation:** README.md now contains a short heading.

**Check:** Read the output before continuing. If it does not match, stop and investigate the specific command; do not add `-Force` or run as Administrator automatically.

### Step 4 — Inspect unstaged changes

```powershell
git status
git diff -- README.md
```

**Expected observation:** Status reports README.md as untracked; an untracked file does not appear in ordinary `git diff`.

**Check:** Read the output before continuing. If it does not match, stop and investigate the specific command; do not add `-Force` or run as Administrator automatically.

### Step 5 — Stage the file and review the snapshot

```powershell
git add -A
git diff --cached --check
git diff --cached
```

**Expected observation:** The staged diff contains the README addition; no unrelated file should appear.

**Check:** Read the output before continuing. If it does not match, stop and investigate the specific command; do not add `-Force` or run as Administrator automatically.

### Step 6 — Commit the reviewed file

```powershell
git commit -m "docs: start practice project"
```

**Expected observation:** Git records one local commit.

**Check:** Read the output before continuing. If it does not match, stop and investigate the specific command; do not add `-Force` or run as Administrator automatically.

### Step 7 — Inspect the history

```powershell
git log --oneline -3
git status
```

**Expected observation:** One commit appears; status should report a clean working tree.

**Check:** Read the output before continuing. If it does not match, stop and investigate the specific command; do not add `-Force` or run as Administrator automatically.

## Linux comparison — terminal/Bash

> Linux commands are alternatives on a Linux machine or authorised VM. Do not paste them into Windows PowerShell as though the shells have identical syntax.

### Linux step 1 — Use Git in an independent Linux practice folder

```bash
mkdir -p "$HOME/UmicomLearning/git-first-project" && cd "$HOME/UmicomLearning/git-first-project" && git init -b main
```

**Expected observation:** An empty practice repository is created. Configure author identity before committing.

## Worked support scenario

A contributor is editing two files: an approved documentation correction and an unrelated experimental configuration change. Before `git add -A`, they inspect both changes. If they are unrelated, they stage only the approved document. The ability to control the snapshot is why Git has a staging area.

## Common problems and how to respond

| Problem or assumption | Better response |
|---|---|
| Confusing `git add` with publishing | `git add` stages locally; `git push` publishes commits to a remote. |
| Committing from the wrong directory | Verify `Get-Location` and `git status` before staging. |
| Assuming untracked files appear in `git diff` | Use `git status` and stage a file before viewing its staged diff. |

## Exercise: demonstrate understanding

1. Write down the purpose of **two commands** from this chapter, in your own words.
2. Run a **read-only command** and record only the information needed to answer its question.
3. Explain which command would change the machine, if any, and why the chapter avoids it.
4. Explain the difference between an observation, a conclusion and an unverified assumption.

## Review questions

1. Does `git commit` upload changes to GitHub?
2. What command inspects staged changes?

<details><summary>Show the suggested answers</summary>

1. No. It creates a local commit.
2. `git diff --cached`.

</details>

## How this connects to Umicom

When contributing to Bits2Banking, preserve original lessons and comments. For the real project, check branch `main` and include `git diff --cached --check` and a staged review before the commit.

## Where to go next

Continue with [Chapter 20 — GitHub: authenticate, publish and collaborate responsibly](20-github-cli-publish-and-collaborate.md).
