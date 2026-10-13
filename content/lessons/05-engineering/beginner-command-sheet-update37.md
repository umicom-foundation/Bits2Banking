# Beginner Command Sheet — Windows PowerShell 7, Git and GitHub CLI

**Bits to Banking · Major Update 37 · Keep this page open beside your terminal.**  
Commands are meant to be entered **one line at a time**, unless a backtick explicitly joins a multiline command. Replace example paths with your own before running them. Never copy example prompt text such as `PS C:\Users\Student>`.

## First identify the shell and current folder

| What do you want to do? | Type in PowerShell 7 | What to check |
|---|---|---|
| Show current folder | `Get-Location` or `pwd` | Is this your intended project? |
| Show PowerShell version | `$PSVersionTable.PSVersion` | Prefer major version 7 |
| List files | `Get-ChildItem` or `ls` | Do you recognise the filenames? |
| Enter a folder | `Set-Location "$HOME\UmicomLearning"` | Use `Get-Location` again |
| Create practice folder | `New-Item -ItemType Directory -Path "$HOME\UmicomLearning" -Force` | Confirm it was created in your home directory |
| Read a text file | `Get-Content ".\README.md"` | Is it the file you intended? |
| Preview a delete | `Remove-Item ".\practice-copy.md" -WhatIf` | File should remain intact |

## Install essential tools (Windows)

```powershell
winget --version
winget install --id Microsoft.PowerShell --exact --source winget
winget install --id Git.Git --exact --source winget
winget install --id GitHub.cli --exact --source winget
winget install --id Microsoft.VisualStudioCode --exact --source winget
```

Install only what is missing or approved. After installation, **reopen PowerShell** and check:

```powershell
pwsh --version
git --version
gh --version
code --version
Get-Command pwsh, git, gh | Select-Object Name, Source
```

`code` is optional. An error after `winget --version` means the package manager may be missing; follow the official Microsoft documentation rather than unknown online installation scripts.

## See your Windows computer's capabilities

```powershell
Get-ComputerInfo | Select-Object WindowsProductName, OsVersion, OsArchitecture
Get-CimInstance Win32_Processor | Select-Object Name, NumberOfCores, NumberOfLogicalProcessors
Get-PSDrive -PSProvider FileSystem
[math]::Round((Get-CimInstance Win32_ComputerSystem).TotalPhysicalMemory / 1GB, 2)
```

These commands inspect Windows and hardware. They do not install software or modify system settings.

## Git and GitHub — first-time configuration

```powershell
git config --global user.name (Read-Host "Your display name")
git config --global user.email (Read-Host "Your verified commit email")
git config --global --get user.name
git config --global --get user.email
gh auth status
```

If authentication is required: `gh auth login`, then follow the official browser prompts. Do not share passwords, tokens or recovery codes.

## Git — create a **practice-only** repository

```powershell
Set-Location "$HOME\UmicomLearning\notes-practice"
git init -b main
git status
git add README.md
git diff --cached --check
git commit -m "docs: add Notes practice introduction"
git log --oneline -5
```

Never run `git init` inside an existing Umicom checkout without a deliberate reason. A repository stores commits locally even when GitHub is unavailable.

## GitHub — publish a **private practice** repository

```powershell
gh auth status
gh repo create notes-practice --private --source . --remote origin --push
git remote -v
gh repo view --web
```

`--push` sends existing commits. Only run `gh repo create` once for this new repository; if it already exists, inspect the existing `origin` remote.

## Daily reviewed Git workflow — authorised `main` only

```powershell
git status
git branch --show-current
git diff
git add -A
git diff --cached --check
git diff --cached --stat
git commit -m "docs(learning): explain a verified source change"
git push origin main
git status
```

Check the current folder first. `git add -A` stages additions, modifications **and deletions**. A rejected push must be investigated, never overridden with a force push as a quick fix.

## Native build and test (after Chapter 276)

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\contributor-notes" -B ".\output\learning-build\contributor-notes" -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" -DBUILD_TESTING=ON
cmake --build ".\output\learning-build\contributor-notes" --parallel 2
ctest --test-dir ".\output\learning-build\contributor-notes" --no-tests=error --output-on-failure
```

Expected on the default standalone lab: **8/8 CTest cases passing**. If a test is *Not Run*, it is not a pass. Use the full lab chapter for explanation and recovery.

## Quick diagnosis (do not delete anything)

| Symptom | First check |
|---|---|
| `pwsh` missing | `winget --version`, then Chapter 265 |
| `git` not recognised | `Get-Command git` and reopen PowerShell |
| `not a git repository` | `Get-Location` and `Get-ChildItem -Force` |
| GitHub authentication failure | `gh auth status`, then `gh auth login` |
| Non-fast-forward push rejection | `git fetch origin` and compare `HEAD...origin/main` |
| Detached HEAD in a submodule | `git status`; preserve changes before switching |
| CMake cannot locate compiler | `Test-Path "C:\msys64\ucrt64\bin\gcc.exe"` |
| CTest Not Run | Check configure/build completion, then `ctest -N` |

**Do not use** `git reset --hard`, `git clean -fd`, `git push --force` or unreviewed recursive delete commands to repair a learning environment. Request guidance using the exact failed command and error text.
