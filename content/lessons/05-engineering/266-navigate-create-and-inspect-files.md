# Chapter 266 — Find, create, read and organise files safely

**Bits to Banking · Absolute Beginner Course · Unit 1**  
**Time:** 30–40 minutes · **Requirements:** PowerShell 7. **Safety:** all write operations stay in a new practice folder.

## A folder is a location, not a Git repository

A **drive** is a storage location such as `C:`. A **folder** (directory) groups files and folders. A **path** describes a location such as `C:\Users\Student\UmicomLearning\notes-practice`. `Get-Location` tells you where PowerShell is currently working. Creating a folder does not automatically put it under Git version control; that happens only after `git init` in Chapter 273.

We will work below `$HOME` (your own account's home directory) so you do not need administrator permissions or risk modifying a real Umicom checkout. In the examples, PowerShell resolves `$HOME` to your computer's actual user directory. Do not copy another learner's username into your commands.

## Guided exercise: your first safe workspace

**1. Ask where you are:**

```powershell
Get-Location
```

**2. Make a dedicated folder for course work:**

```powershell
New-Item -ItemType Directory -Path "$HOME\UmicomLearning" -Force
```

You may also type `mkdir "$HOME\UmicomLearning"`. `mkdir` is a convenient alias in PowerShell. We will use the full command when teaching specific options.

**3. Enter the folder:**

```powershell
Set-Location "$HOME\UmicomLearning"
```

**4. Check:**

```powershell
pwd
```

`pwd` is a short alias for `Get-Location`. The displayed path should end in `UmicomLearning`. If it does not, stop and correct the directory before writing files.

**5. Create a practice project folder and enter it:**

```powershell
New-Item -ItemType Directory -Path ".\notes-practice" -Force
Set-Location ".\notes-practice"
```

**6. Create a small Markdown document:**

```powershell
Set-Content -LiteralPath ".\README.md" -Value "# My first Umicom Notes project" -Encoding utf8
```

A `.md` file is a plain-text document written in **Markdown**, the format used for our learning pages. PowerShell has created a text file here; it has **not** created a PowerShell script.

**7. List and read the new file:**

```powershell
Get-ChildItem
Get-Content -LiteralPath ".\README.md"
```

You should see `README.md` listed, followed by its heading when you run `Get-Content`.

**8. Add another sentence:**

```powershell
Add-Content -LiteralPath ".\README.md" -Value "This is a safe local practice repository."
Get-Content -LiteralPath ".\README.md"
```

**9. Open the document in an editor:**

```powershell
notepad ".\README.md"
```

You may use `code ".\README.md"` if VS Code is installed. Close the editor after saving; the file is still in the same folder.

## Understand copying, moving and previewing deletion

Use a practice copy before testing rename or deletion operations:

```powershell
Copy-Item -LiteralPath ".\README.md" -Destination ".\README-copy.md"
Get-ChildItem
```

To rename the copy:

```powershell
Rename-Item -LiteralPath ".\README-copy.md" -NewName "README-backup.md"
```

Before removing anything, learn `-WhatIf`, which explains the action without doing it:

```powershell
Remove-Item -LiteralPath ".\README-backup.md" -WhatIf
```

The file should **still exist**. Verify with `Get-ChildItem`. We deliberately do **not** run a real deletion in this first course. On a real source tree, an accidental recursive deletion could destroy uncommitted work that Git cannot restore.

## Small terminal features that save time

You can often press **Tab** while typing a folder or command name to complete it. The **Up Arrow** recalls a recent command; always read it before pressing Enter again, especially if it modified files. `Clear-Host` clears the visible screen without deleting your files. `Get-Help Get-ChildItem -Examples` shows examples of a built-in command. If you start an unintended long-running command, **Ctrl+C** often requests interruption, but it cannot undo a command that has already changed the filesystem.

```powershell
Get-Help Get-ChildItem -Examples
Clear-Host
```

The examples are for learning; you should not copy a help example that deletes or overwrites real project files without understanding it.

## Relative and absolute paths

`./README.md` and `.\README.md` refer to the file in the current directory; `..` means the parent directory. `C:\umicom\Umicom-Bits2Banking` is an **absolute path**. When a lesson says `Set-Location`, follow it before entering subsequent relative paths. The same command can operate on a completely different file if your current directory is wrong.

## Check your understanding

Explain what `pwd`, `Get-ChildItem`, `Set-Location`, `Get-Content` and `-WhatIf` do. Why did we put the practice project under `$HOME` rather than altering the existing Umicom Framework directory? Write down one way to check your directory before using `git add -A` in the future.

**Next:** [Inspect the computer's hardware and storage](267-check-system-hardware-and-storage.md).
