# Commands used in the videos

## Explore computer hardware (Windows PowerShell)

```powershell
Get-CimInstance Win32_Processor
Get-CimInstance Win32_ComputerSystem
Get-CimInstance Win32_OperatingSystem
```

These commands display system information without changing the computer.

## Create a Git practice repository (Windows PowerShell)

```powershell
New-Item -ItemType Directory -Force -Path "$HOME\GitPractice" | Out-Null
Set-Location "$HOME\GitPractice"
git init -b main
Set-Content README.md '# Notes project'
git status
git add README.md
git diff --cached --check
git diff --cached
git commit -m "docs: add notes project introduction"
git status
```

Git will ask for a commit author name and email if they have not been configured. No internet account or remote repository is needed for this exercise.

## Explore the Framework source

Open the [Framework demonstration in GitHub](https://github.com/umicom-foundation/umicom-framework/blob/main/examples/framework_demo/main.c), then examine the module descriptor and controller lifecycle in the C source.
