<!--
Umicom Bits2Banking
File: content/simple-steps/git-local.md

PURPOSE:
Record the first source version of the practice project with Git.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Step 8. Create a Git repository

![Umicom Foundation](../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

Git records versions of your files. A repository is a project folder with this history. You'll save the first version of your coffee timer on your computer.

## 1. Check for Git

In PowerShell, type `git --version`. If you see a version number, go to the next step. If PowerShell can't find Git, type this.

```powershell
winget install --id Git.Git --exact --source winget
```

When the installer finishes, open a new PowerShell window and run `git --version` again. If WinGet is unavailable, use the [Git for Windows installer](https://git-scm.com/install/windows).

## 2. Open the project folder

```powershell
Set-Location (Join-Path $env:USERPROFILE 'Bits2Banking-Practice\coffee-timer')
Get-Location
Get-ChildItem -Name
```

The path should end in `Bits2Banking-Practice\coffee-timer`. Look for `coffee.c`. If it is missing, return to the [C lesson](c.md) and check where you saved it.

If the folder has no `README.md`, create a short note with the project name.

```powershell
New-Item -ItemType File -Path .\README.md -Value '# Coffee timer'
```

## 3. Start the history

```powershell
git init -b main
git status --short --branch
```

The status should show the `main` branch. Git calls a saved version of your files a *commit*. `main` is the name of the first line of commits.

Set the name and email Git should put on your commits in this project. The name can be one you want to use for your work. An email becomes part of the commit history. If you plan to upload the project and want to keep your personal address private, use the [address provided by GitHub](https://docs.github.com/en/account-and-profile/how-tos/email-preferences/setting-your-commit-email-address).

```powershell
git config --local user.name (Read-Host 'Name for your commits')
git config --local user.email (Read-Host 'Email for your commits')
```

## 4. Save your first version

First select the two files you want Git to save, then check the selection.

```powershell
git add -- README.md coffee.c
git --no-pager diff --cached
```

You should see additions for `README.md` and `coffee.c`. The compiled `coffee.exe` stays in your practice folder. If the selection looks right, save it.

```powershell
git commit -m 'Add coffee timer'
git log -1 --oneline
```

Look for `Add coffee timer` beside a short commit ID. If Git asks who you are, fill in the two identity settings in step 3 and try the commit again.

[Previous: Write, compile and run C](c.md) · [Next: Create a private GitHub repository](git-publish.md)

[Full lesson: Record two versions with Git](../community/lessons/06-make-two-local-commits.md)
