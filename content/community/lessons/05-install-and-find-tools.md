# Install and find your everyday tools

Check PowerShell, Git, GitHub CLI and an editor without installing duplicates.

**Before you start:** Windows with internet access. Begin in Windows PowerShell or PowerShell 7. Installation may ask you to approve changes on your own computer.

[Community learning route](../index.md) · [Printable HTML](../handouts/05-install-and-find-tools.html)

## Know what each program does

PowerShell runs commands. Git records versions of local project files. GitHub hosts repositories online. GitHub CLI, started with gh, helps manage that online account. An editor lets you change source files. These are separate jobs; installing Git does not create a GitHub account.

We will use Windows Package Manager, started with winget, to request specific packages. A package manager downloads and installs software from its configured sources.

## 1. Check first

```powershell
winget --version
Get-Command pwsh, git, gh, code -ErrorAction SilentlyContinue
```

The version option has two adjacent hyphens: --version. Get-Command shows programs PowerShell can currently find. Missing entries mean the program is not on the current search path; it may still be installed. Check Start or installed applications before installing it again.

## 2. Install missing programs

Run only the lines for tools you need. Read the installer prompts before accepting them.

```powershell
winget install --id Microsoft.PowerShell --exact --source winget
winget install --id Git.Git --exact --source winget
winget install --id GitHub.cli --exact --source winget
winget install --id Microsoft.VisualStudioCode --exact --source winget
```

--id selects a package identifier, --exact avoids a loose name match and --source selects the catalogue. Visual Studio Code is optional for these first exercises; Notepad can edit our text files.

## 3. Open a fresh PowerShell 7 window

```powershell
$PSVersionTable.PSVersion
git --version
gh --version
code --version
Get-Command pwsh, git, gh | Select-Object Name, Source
```

New terminals pick up installer changes to PATH, the list of folders searched for commands. Select-Object chooses the columns to display. You should see the command names and their executable locations. Skip code --version if you kept Notepad.

## If installation is unavailable

If winget is not recognised, use the official PowerShell installation page linked below. If a work or school computer prevents installation, ask its administrator for the tools. Do not disable security software to get through this lesson. If installation succeeded but a command is missing, close and reopen the terminal before trying another install.

## Your turn

Create a note listing which tools you have and what each one does. No GitHub sign-in is needed until you decide to use the online service.

## Continue when you are ready

[Previous: Copy, rename and preview a deletion](04-copy-and-preview-changes.md) · [Next: Record two versions with Git](06-make-two-local-commits.md)

[Explore the related course](../../courses/introduction-to-version-control/index.html). You can finish this exercise without leaving this page.

## Further reading

- [PowerShell on Windows](https://learn.microsoft.com/en-us/powershell/scripting/install/installing-powershell-on-windows)
- [WinGet install command](https://learn.microsoft.com/en-us/windows/package-manager/winget/install)

[Video teaching script](../video-scripts/05-install-and-find-tools.md) · [Short community message](../messages/05-install-and-find-tools.md)
