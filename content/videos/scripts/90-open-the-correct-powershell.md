# Episode 90 — Open the correct PowerShell on Windows

**Bits to Banking · Umicom Foundation · Beginner video series**  
**Companion lessons:** Chapters 264–266 · **Suggested duration:** 8–11 minutes.  
**Format:** screen demonstration, narration, short pauses for students to try a command.

## Opening — The search results can be confusing (0:00–2:00)

**On screen:** Display the learner-supplied Windows 11 search screenshot, then point to `Windows PowerShell`, `PowerShell`, `Windows PowerShell ISE`, `Windows PowerShell (x86)` and `Developer PowerShell for VS 2022`.

**Narration:** “These names look similar, but they are not the same programme. Windows Terminal is a window that can host different shells. PowerShell 7 is the newer shell we will use for the course. Older Windows PowerShell normally reports version 5.1. We can check the actual version instead of guessing from an icon.”

**Instructor cue:** Do not call Windows Terminal a programming language or promise that every item labelled PowerShell is version 7.

## First two commands (2:00–4:00)

Open the available PowerShell programme and show where the cursor waits at the prompt. Type, with a pause after each:

```powershell
Get-Location
$PSVersionTable.PSVersion
```

Explain what a location is and why everyone may see a different username or path. Explain that `$PSVersionTable` is a PowerShell object containing information about the running shell. Never ask for a screenshot that exposes a user's complete home directory if a simple statement of “7.x” is sufficient.

## Install and verify, if necessary (4:00–7:00)

In an older shell, demonstrate `winget --version`, then show the documented installation command for PowerShell 7. Explain that a separate installer may prompt for confirmation and may require permissions. Reopen the shell after installation and run `pwsh --version`.

```powershell
winget --version
winget install --id Microsoft.PowerShell --exact --source winget
```

**Failure branch:** If Winget is missing, show the official Microsoft package-manager documentation. Do not download or execute an unknown script.

## Create a safe practice location (7:00–10:00)

```powershell
New-Item -ItemType Directory -Path "$HOME\UmicomLearning" -Force
Set-Location "$HOME\UmicomLearning"
Get-Location
Get-ChildItem
```

**Narration:** “We create our own training folder. We do not start by modifying the Framework or Kernel. Most mistakes in command-line work become easier to diagnose when we know our exact location.”

## Wrap-up and activity

**Activity:** Learners demonstrate `Get-Location` and their PowerShell major version. Ask: “What is the difference between the terminal window and the shell inside it?”

**Next video:** inspect Windows computer information using read-only commands.
