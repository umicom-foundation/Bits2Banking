<!--
Umicom Bits2Banking
File: content/simple-steps/git-publish.md

PURPOSE:
Create a private GitHub repository for the reviewed practice files.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Step 9. Create a private GitHub repository

![Umicom Foundation](../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

You have a commit in the coffee-timer folder on your computer. In this lesson, you'll create an online copy in your own GitHub account and upload that commit.

## 1. Get the GitHub command

If you need an account, [create one at GitHub](https://github.com/signup). In PowerShell, type `gh --version`. If PowerShell can't find the `gh` command, install GitHub CLI.

```powershell
winget install --id GitHub.cli --exact --source winget
```

Open a new PowerShell window and try `gh --version` again. You should see a version number. [GitHub CLI installation options](https://github.com/cli/cli/blob/trunk/docs/install_windows.md)

## 2. Sign in

```powershell
gh auth login --hostname github.com --git-protocol https --web
```

Follow the prompt in PowerShell and finish signing in through the browser. Back in PowerShell, connect Git to that sign-in and check the account.

```powershell
gh auth setup-git --hostname github.com
gh auth status --hostname github.com
```

Check that GitHub CLI shows your account as the active account. [GitHub CLI sign-in instructions](https://cli.github.com/manual/gh_auth_login)

## 3. Check the project you will upload

```powershell
Set-Location (Join-Path $env:USERPROFILE 'Bits2Banking-Practice\coffee-timer')
Get-Location
git log --oneline main
git ls-files
git remote -v
```

Check the path and the `Add coffee timer` commit. If you followed the previous step, `git ls-files` lists `README.md` and `coffee.c`. `git remote -v` should print nothing. A remote is an address Git has saved for an online repository. If an address is already listed, check where it points before continuing.

## 4. Create the online copy and upload your commit

```powershell
gh repo create coffee-timer --private --source . --remote origin
```

Look for the new repository URL. `--source .` selects the current folder, and `origin` names the online address. If the name is already in use, pick a new name such as `coffee-timer-practice` and run the command with that name. [GitHub CLI repository creation](https://cli.github.com/manual/gh_repo_create)

Once the command succeeds, upload the `main` branch.

```powershell
git push -u origin main
gh repo view --web
```

The push should report `main -> main`. In your browser, check that the repository shows **Private**, `README.md` and `coffee.c`. If the push fails, check `gh auth status --hostname github.com` and `git remote -v` before trying the push again.

[Previous: Create a Git repository](git-local.md) · [Next: Clone the repository](git-clone.md)

[Full lesson: Share a practice project and clone it](../community/lessons/07-share-and-clone-a-project.md)
