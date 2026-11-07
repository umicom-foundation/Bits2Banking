# Make a folder for your practice work

Create a practice folder and move into it without touching product source.

**Before you start:** PowerShell on Windows. Open it from Start. Get-Location shows your current folder.

[Community learning route](../index.md) · [Printable HTML](../handouts/02-make-a-practice-folder.html)

## Choose a place you can find again

We will keep the exercises in a folder called Umicom-Practice inside your user folder. Your user folder holds files belonging to your Windows account. The example uses its location from Windows, so you do not have to copy someone else’s user name.

A path is an address for a file or folder. An absolute path starts from a drive, such as C:\Users\Alex. A relative path starts from your current folder. . means the current folder; .. means its parent.

## 1. Create your practice folder

```powershell
Set-Location $env:USERPROFILE
Get-Location
New-Item -ItemType Directory -Path "Umicom-Practice"
```

$env:USERPROFILE reads the user-folder path from your environment. An environment value is a setting made available to programs. Set-Location moves into that folder. New-Item creates something; -ItemType Directory says it must be a folder. Quotes keep the path together as one value.

## 2. Enter the folder

```powershell
Set-Location "Umicom-Practice"
Get-Location
Get-ChildItem
```

The location should end in Umicom-Practice. An empty listing is fine: we have not created files yet. If New-Item said the folder already exists, do not remove it. List it first and use a new name if it contains work you want to keep.

## 3. Add a project folder

```powershell
New-Item -ItemType Directory -Path "notes-practice"
Set-Location "notes-practice"
New-Item -ItemType Directory -Path "src", "include", "tests", "docs"
Get-ChildItem
```

src will hold source code, include will hold shared declarations, tests will hold checks, and docs will hold explanations. These are conventions: names people agree to use. Empty folders are useful while working, but Git will later record files rather than empty folders on their own.

## 4. Leave and return

```powershell
Set-Location ..
Get-Location
Set-Location ".\notes-practice"
```

.. moves one level up. .\notes-practice selects the project under the current folder. Check Get-Location whenever you are unsure. Typing cd instead of Set-Location also works in PowerShell.

## If a command fails

Path not found normally means the spelling or current folder differs from the example. Run Get-Location and Get-ChildItem before trying again. Access denied may mean you selected a protected folder. Use a folder you own; these exercises do not need administrator access.

## Your turn

Create a folder called drawings inside docs. Return to the project folder and list docs to check it. Keep this practice project for the next lesson.

## Continue when you are ready

[Previous: Open PowerShell and find your place](01-open-your-terminal.md) · [Next: Write and read your first Markdown file](03-write-your-first-readme.md)

[Explore the related course](../../courses/introduction-to-version-control/index.html). You can finish this exercise without leaving this page.

[Video teaching script](../video-scripts/02-make-a-practice-folder.md) · [Short community message](../messages/02-make-a-practice-folder.md)
