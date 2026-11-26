<!--
Umicom Bits2Banking
File: content/simple-steps/git-clone.md

PURPOSE:
Clone the practice repository to a new folder and compare commit identities.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Step 10. Clone the repository

![Umicom Foundation](../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A clone downloads the files and their Git history into a new folder. Keep your original coffee-timer folder so you can compare the two copies.

## 1. Get the repository address

In PowerShell, open the original project and get the address from the previous lesson.

```powershell
Set-Location (Join-Path $env:USERPROFILE 'Bits2Banking-Practice\coffee-timer')
$repoUrl = git remote get-url origin
$repoUrl
```

Check that the address is the GitHub repository you just created. If Git says `No such remote 'origin'`, return to [Step 9](git-publish.md).

## 2. Download into a separate folder

```powershell
Set-Location ..
Get-Location
```

The path should end in `Bits2Banking-Practice`. Check `Test-Path .\coffee-timer-copy`. If it returns `True`, keep that folder and choose a new destination name. Use that name in both commands below.

```powershell
git clone --branch main $repoUrl .\coffee-timer-copy
Set-Location .\coffee-timer-copy
```

Continue after the clone succeeds. If GitHub denies access to your private repository, check the active account with `gh auth status --hostname github.com` and retry the clone.

## 3. Check the clone

```powershell
git -C ..\coffee-timer rev-parse HEAD
git rev-parse HEAD
git ls-files
```

The first two commands show the current commit ID in the original and the clone. The IDs should match if you haven't saved another commit in the original since the upload. Both `README.md` and `coffee.c` should appear in the list. Open the cloned `coffee.c` to see the same code you wrote. You can now work from this copy.

[Previous: Create a private GitHub repository](git-publish.md) · [Next: Build a project with CMake](build-project.md)

[Full lesson: Share a practice project and clone it](../community/lessons/07-share-and-clone-a-project.md)
