# Chapter 06 — Create, open and read text files without scripting

**Bits to Banking · System Administration: From Zero · Umicom Foundation**  
**Audience:** first-time users and returning learners; no prior system-administration knowledge required.  
**Code policy:** interactive PowerShell 7 and Bash commands; native C23/Assembly for Umicom executable development.  
**Estimated study time:** 25–50 minutes (longer when practising).

## What you will learn

Create a Markdown note, read its contents and recognise file extensions.

## Why this matters

![A safe training folder is separate from real projects](../../assets/diagrams/sysadmin-safe-workspace-update38.svg)


A text file stores characters. A Markdown document (`.md`) is plain text with conventions for headings, links and lists. A C source file (`.c`) is also text but is interpreted by a compiler rather than a documentation renderer. A word-processing document (`.docx`) uses a different structured format. System administrators frequently inspect configuration and log files, so distinguishing these formats matters.

In the practice folder, use Notepad to create a short `README.md`. You do not need to write a PowerShell script to make this file. You can also write a short line interactively using `Set-Content`. However, the course does not create `.ps1` or Python implementation files.

PowerShell `Get-Content` displays a text file. `Get-Item` reports file metadata such as size and modification time. `Get-FileHash` calculates a fingerprint used later when learning backup verification. Opening a text document is normally a reversible, low-risk activity, but opening an unknown executable or script is not equivalent.

## New words, explained

| Term | Plain-English meaning |
|---|---|
| **Text editor** | Tool for changing plain-text files. |
| **Extension** | Suffix such as `.md`, `.txt` or `.c` that often indicates format. |
| **Metadata** | Information about a file, such as size and last modification time. |
| **Encoding** | Rule for representing characters as bytes. |
| **Markdown** | Readable plain-text formatting used by Bits2Banking lessons. |

## Windows practice — PowerShell 7

> **Before typing:** Run these commands in a normal, non-elevated PowerShell window. Where a file is used, complete the previous practice-folder chapters first. Do not paste the `PS C:\...>` prompt into the terminal.

**Start:** Use the Windows Start menu or Windows Terminal to open PowerShell. Check the prompt is ready. Commands beginning with `$` are still commands; type them exactly as shown.

### Step 1 — Go to the safe Notes directory

```powershell
Set-Location "$HOME\UmicomLearning\Notes"
```

**Expected observation:** The working directory is your practice Notes folder.

**Check:** Read the output before continuing. If it does not match, stop and investigate the specific command; do not add `-Force` or run as Administrator automatically.

### Step 2 — Create or open the README in Notepad

```powershell
notepad .\README.md
```

**Expected observation:** Notepad opens. Enter a title and save the document if prompted.

**Check:** Read the output before continuing. If it does not match, stop and investigate the specific command; do not add `-Force` or run as Administrator automatically.

### Step 3 — Read the text file back in PowerShell

```powershell
Get-Content .\README.md
```

**Expected observation:** You see the text you saved in Notepad.

**Check:** Read the output before continuing. If it does not match, stop and investigate the specific command; do not add `-Force` or run as Administrator automatically.

### Step 4 — Inspect the file information

```powershell
Get-Item .\README.md | Select-Object Name, Length, LastWriteTime
```

**Expected observation:** File name, size in bytes and modified timestamp appear.

**Check:** Read the output before continuing. If it does not match, stop and investigate the specific command; do not add `-Force` or run as Administrator automatically.

## Linux comparison — terminal/Bash

> Linux commands are alternatives on a Linux machine or authorised VM. Do not paste them into Windows PowerShell as though the shells have identical syntax.

### Linux step 1 — Open or create a Markdown file in an available editor

```bash
nano "$HOME/UmicomLearning/Notes/README.md"
```

**Expected observation:** If `nano` is installed it opens the file; otherwise use your system text editor.

### Linux step 2 — Read its contents

```bash
cat "$HOME/UmicomLearning/Notes/README.md"
```

**Expected observation:** The saved text appears in the terminal.

## Worked support scenario

A Umicom learning contributor receives a request to fix an inaccurate documentation title. The correct tool is a text editor, not the C compiler. They read the file, change the smallest necessary phrase and verify the saved contents before considering a Git commit.

## Common problems and how to respond

| Problem or assumption | Better response |
|---|---|
| Writing text into the wrong directory | Check `Get-Location`, then use the full expected file path. |
| Confusing opening a file with executing it | `Get-Content` reads text; `& .\program.exe` executes a program. |
| Changing file extensions merely to make a file open | Extensions do not convert the underlying format. |

## Exercise: demonstrate understanding

1. Write down the purpose of **two commands** from this chapter, in your own words.
2. Run a **read-only command** and record only the information needed to answer its question.
3. Explain which command would change the machine, if any, and why the chapter avoids it.
4. Explain the difference between an observation, a conclusion and an unverified assumption.

## Review questions

1. Why is `README.md` suitable for source repository documentation?
2. Does `Get-Content` run the text as a PowerShell program?

<details><summary>Show the suggested answers</summary>

1. It is plain text, version-controllable and readable in a text editor.
2. No; it displays the contents as data.

</details>

## How this connects to Umicom

The Umicom Bits2Banking course is written in Markdown, while executable teaching examples use native C23 and Assembly. Keep learning content and application code in their intended folders.

## Where to go next

Continue with [Chapter 07 — Copy, rename and remove files carefully](07-copy-move-delete-with-rollback.md).
