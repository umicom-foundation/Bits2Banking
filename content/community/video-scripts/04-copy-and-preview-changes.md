# Video script: Copy, rename and preview a deletion

**Aim:** Keep a practice copy and understand what a file command will change.

**Preparation:** PowerShell and a practice README.md. If you do not have one, create a new folder and use Notepad to save a short README.md there. Use a separate practice folder and hide notifications or personal account details before recording.

[Lesson and exact commands](../lessons/04-copy-and-preview-changes.md)

## Opening words

Next, we will take this topic one step at a time: copy, rename and preview a deletion. Follow one step at a time. Pause the video whenever you need a little more time.

## Scene 1

Place the original and copy side by side in the folder listing. Read the contents of each before renaming.

## Scene 2

Run Remove-Item with -WhatIf and point to True from Test-Path. This is the key moment: the command described an action but did not perform it.

## Scene 3

Explain that removal is optional. If demonstrating it, use only the copy, then prove the original remains.

## Walkthrough and pauses

### Keep the original in sight

**Say:** Copying makes another file. Renaming changes the name of one file. Moving changes its location. Deleting removes a file; a terminal deletion should not be treated as a promise that the file will be in the Recycle Bin. We will first preview that last operation.

**Say:** Use this lesson only with the small practice note. Do not experiment on application source or a folder containing work you have not backed up.

### 1. Read and copy

**On screen — type one line at a time:**

```powershell
Get-Location
Get-Content -LiteralPath ".\README.md"
Copy-Item -LiteralPath ".\README.md" -Destination ".\README-copy.md"
Get-ChildItem
```

Pause. Read the result before continuing.

**Say:** You should now see README.md and README-copy.md. If a copy with that name already exists, stop and inspect it before choosing a different destination. A destination is where the result will go.

### 2. Rename the copy

**On screen — type one line at a time:**

```powershell
Rename-Item -LiteralPath ".\README-copy.md" -NewName "README-backup.md"
Get-ChildItem
Get-Content -LiteralPath ".\README-backup.md"
```

Pause. Read the result before continuing.

**Say:** The copy has a new name but the same contents. The original README.md is still there. This local copy is useful for practice; it is not a backup against losing the whole disk.

### 3. Preview deletion

**On screen — type one line at a time:**

```powershell
Remove-Item -LiteralPath ".\README-backup.md" -WhatIf
Test-Path -LiteralPath ".\README-backup.md"
```

Pause. Read the result before continuing.

**Say:** -WhatIf asks this PowerShell command to describe the action without performing it. The second command should still print True. Not every program supports -WhatIf; it is not a universal option you can add to any command.

### 4. Decide whether to remove the practice copy

**Say:** You may keep it. If you want to practise removal, read it once more and remove only this named file:

**On screen — type one line at a time:**

```powershell
Get-Content -LiteralPath ".\README-backup.md"
Remove-Item -LiteralPath ".\README-backup.md"
Test-Path -LiteralPath ".\README-backup.md"
```

Pause. Read the result before continuing.

**Say:** The last result should be False. README.md should remain. This command has no -Recurse option and does not ask to remove the project folder.

### If something goes wrong

**Say:** File not found may simply mean the previous rename or deletion already happened. List the folder before repeating a command. Ctrl+C requests interruption of a running command; it cannot undo an operation that already completed.

### Your turn

**Say:** Make another copy with a name you choose. Preview renaming it with Rename-Item and -WhatIf. Check that the name stays unchanged until you deliberately run the operation.

## Closing words

Before moving on, try the exercise once more in your own practice folder. If the result is different, compare the command and current location with the lesson. You can come back to this step at any time.
