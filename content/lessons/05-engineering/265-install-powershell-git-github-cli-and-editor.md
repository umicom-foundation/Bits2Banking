# Chapter 265 — Install PowerShell 7, Git, GitHub CLI and a text editor

**Bits to Banking · Absolute Beginner Course · Unit 1**  
**Time:** 25–45 minutes plus downloads · **Requirements:** Windows with an internet connection; installation permissions may be required.

## What each tool does

**PowerShell 7** is the command-line shell in which we type instructions. **Git** records changes to local project files and lets you compare earlier versions. **GitHub** is a website that hosts Git repositories for sharing and collaboration. **GitHub CLI** (`gh`) is a command-line tool for your GitHub account: signing in, creating a repository and opening a browser page. **Visual Studio Code** is a text editor for source files; it is optional and does not replace Git. CMake, Ninja and GCC are build tools we will install later when needed.

A command beginning with `winget` asks **Windows Package Manager** to install software. A command beginning with `git` uses Git. The spaces and the **two adjacent hyphens** in `--version` are important. `git - -version` is *not* the same command as `git --version`.

## Step 1 — Check the Windows package manager

Open PowerShell as in Chapter 264. Type:

```powershell
winget --version
```

You should see a version identifier such as `v1.x`. The exact number changes as Winget is updated. If Windows says it cannot find `winget`, first check **App Installer** through Microsoft Store / your organisation's IT support, or follow Microsoft's official guide: https://learn.microsoft.com/windows/package-manager/winget/ . Do not download installers from unofficial advertising pages.

## Step 2 — Install PowerShell 7

If you are currently in Windows PowerShell 5.1, you can use it to run this installation command:

```powershell
winget install --id Microsoft.PowerShell --exact --source winget
```

Accept the installer prompts only after reviewing what is being installed. Modern releases can use MSIX; older installations may use MSI. This command does not remove Windows PowerShell 5.1. **Close the old window, open PowerShell 7 from Start, and verify:**

```powershell
$PSVersionTable.PSVersion
pwsh --version
```

Microsoft's official instructions: https://learn.microsoft.com/powershell/scripting/install/install-powershell-on-windows . If installation is restricted by your organisation, ask the administrator before proceeding.

## Step 3 — Install Git and GitHub CLI

Enter one line, wait for it to finish, and only then enter the next:

```powershell
git --version
```

If Git is missing, install it:

```powershell
winget install --id Git.Git --exact --source winget
```

Check GitHub CLI:

```powershell
gh --version
```

If it is missing:

```powershell
winget install --id GitHub.cli --exact --source winget
```

Newly installed commands sometimes require a new terminal so Windows can refresh its PATH. Close and reopen PowerShell 7, then retry both version checks. **Do not guess installation folders or edit system PATH as a first response.**

## Step 4 — Install an editor (recommended)

You can use **Notepad** if you prefer, but Visual Studio Code makes it easier to see project files and compare changes:

```powershell
winget install --id Microsoft.VisualStudioCode --exact --source winget
```

Verify that its `code` launcher is available:

```powershell
code --version
```

If the editor is installed but `code` is not found, open it from the Start menu; the command-line launcher may need to be added by the installer or a new session.

## Step 5 — Find the command locations

```powershell
Get-Command pwsh, git, gh | Select-Object Name, Source
```

`Get-Command` locates commands available to the current shell. `Select-Object` displays only the properties we asked for. Each row should show a name and a file location. The list can vary according to how software was installed, and an unavailable command may produce an error rather than a row.

## Stop and verify

Record four facts in a text note: your PowerShell major version, Git version, GitHub CLI version and whether VS Code opens. Do not share authentication tokens or private configuration files in a classroom message. **Installing Git does not create a GitHub account, sign you in, or create a repository**; those are separate steps in Chapter 272.

**Common problems:** If Winget cannot find a package, check spelling and your network connection. If access is denied, review installation permissions. If the programme works from Start but not PowerShell, reopen PowerShell and try again. Avoid copying random installation scripts from the internet.

**Next:** [Find, create and inspect folders safely](266-navigate-create-and-inspect-files.md).
