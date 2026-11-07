# Copy, rename and preview a deletion

Keep a practice copy and understand what a file command will change.

**Before you start:** PowerShell and a practice README.md. If you do not have one, create a new folder and use Notepad to save a short README.md there.

[Community learning route](../index.md) · [Printable HTML](../handouts/04-copy-and-preview-changes.html)

## Keep the original in sight

Copying makes another file. Renaming changes the name of one file. Moving changes its location. Deleting removes a file; a terminal deletion should not be treated as a promise that the file will be in the Recycle Bin. We will first preview that last operation.

Use this lesson only with the small practice note. Do not experiment on application source or a folder containing work you have not backed up.

## 1. Read and copy

```powershell
Get-Location
Get-Content -LiteralPath ".\README.md"
Copy-Item -LiteralPath ".\README.md" -Destination ".\README-copy.md"
Get-ChildItem
```

You should now see README.md and README-copy.md. If a copy with that name already exists, stop and inspect it before choosing a different destination. A destination is where the result will go.

## 2. Rename the copy

```powershell
Rename-Item -LiteralPath ".\README-copy.md" -NewName "README-backup.md"
Get-ChildItem
Get-Content -LiteralPath ".\README-backup.md"
```

The copy has a new name but the same contents. The original README.md is still there. This local copy is useful for practice; it is not a backup against losing the whole disk.

## 3. Preview deletion

```powershell
Remove-Item -LiteralPath ".\README-backup.md" -WhatIf
Test-Path -LiteralPath ".\README-backup.md"
```

-WhatIf asks this PowerShell command to describe the action without performing it. The second command should still print True. Not every program supports -WhatIf; it is not a universal option you can add to any command.

## 4. Decide whether to remove the practice copy

You may keep it. If you want to practise removal, read it once more and remove only this named file:

```powershell
Get-Content -LiteralPath ".\README-backup.md"
Remove-Item -LiteralPath ".\README-backup.md"
Test-Path -LiteralPath ".\README-backup.md"
```

The last result should be False. README.md should remain. This command has no -Recurse option and does not ask to remove the project folder.

## If something goes wrong

File not found may simply mean the previous rename or deletion already happened. List the folder before repeating a command. Ctrl+C requests interruption of a running command; it cannot undo an operation that already completed.

## Your turn

Make another copy with a name you choose. Preview renaming it with Rename-Item and -WhatIf. Check that the name stays unchanged until you deliberately run the operation.

## Continue when you are ready

[Previous: Write and read your first Markdown file](03-write-your-first-readme.md) · [Next: Install and find your everyday tools](05-install-and-find-tools.md)

[Explore the related course](../../courses/introduction-to-version-control/index.html). You can finish this exercise without leaving this page.

[Video teaching script](../video-scripts/04-copy-and-preview-changes.md) · [Short community message](../messages/04-copy-and-preview-changes.md)
