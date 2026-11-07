# Video script: Install and find your everyday tools

**Aim:** Check PowerShell, Git, GitHub CLI and an editor without installing duplicates.

**Preparation:** Windows with internet access. Begin in Windows PowerShell or PowerShell 7. Installation may ask you to approve changes on your own computer. Use a separate practice folder and hide notifications or personal account details before recording.

[Lesson and exact commands](../lessons/05-install-and-find-tools.md)

## Opening words

Next, we will take this topic one step at a time: install and find your everyday tools. Follow one step at a time. Pause the video whenever you need a little more time.

## Scene 1

Show the tool check before any install. Explain why Git and GitHub are separate.

## Scene 2

Install one missing tool and leave room for the learner’s prompts and download time. Do not film credentials or account details.

## Scene 3

Open a fresh PowerShell 7 window, check the version and locate Git. Explain PATH as a list of places to look.

## Walkthrough and pauses

### Know what each program does

**Say:** PowerShell runs commands. Git records versions of local project files. GitHub hosts repositories online. GitHub CLI, started with gh, helps manage that online account. An editor lets you change source files. These are separate jobs; installing Git does not create a GitHub account.

**Say:** We will use Windows Package Manager, started with winget, to request specific packages. A package manager downloads and installs software from its configured sources.

### 1. Check first

**On screen — type one line at a time:**

```powershell
winget --version
Get-Command pwsh, git, gh, code -ErrorAction SilentlyContinue
```

Pause. Read the result before continuing.

**Say:** The version option has two adjacent hyphens: --version. Get-Command shows programs PowerShell can currently find. Missing entries mean the program is not on the current search path; it may still be installed. Check Start or installed applications before installing it again.

### 2. Install missing programs

**Say:** Run only the lines for tools you need. Read the installer prompts before accepting them.

**On screen — type one line at a time:**

```powershell
winget install --id Microsoft.PowerShell --exact --source winget
winget install --id Git.Git --exact --source winget
winget install --id GitHub.cli --exact --source winget
winget install --id Microsoft.VisualStudioCode --exact --source winget
```

Pause. Read the result before continuing.

**Say:** --id selects a package identifier, --exact avoids a loose name match and --source selects the catalogue. Visual Studio Code is optional for these first exercises; Notepad can edit our text files.

### 3. Open a fresh PowerShell 7 window

**On screen — type one line at a time:**

```powershell
$PSVersionTable.PSVersion
git --version
gh --version
code --version
Get-Command pwsh, git, gh | Select-Object Name, Source
```

Pause. Read the result before continuing.

**Say:** New terminals pick up installer changes to PATH, the list of folders searched for commands. Select-Object chooses the columns to display. You should see the command names and their executable locations. Skip code --version if you kept Notepad.

### If installation is unavailable

**Say:** If winget is not recognised, use the official PowerShell installation page linked below. If a work or school computer prevents installation, ask its administrator for the tools. Do not disable security software to get through this lesson. If installation succeeded but a command is missing, close and reopen the terminal before trying another install.

### Your turn

**Say:** Create a note listing which tools you have and what each one does. No GitHub sign-in is needed until you decide to use the online service.

## Closing words

Before moving on, try the exercise once more in your own practice folder. If the result is different, compare the command and current location with the lesson. You can come back to this step at any time.
