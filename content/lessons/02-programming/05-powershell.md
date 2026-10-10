# 5. PowerShell: your first commands and scripts

PowerShell is a command shell and scripting language widely used to manage Windows computers. Unlike many text-only shells, PowerShell can pass **objects** between commands. An object carries named properties: for example, a file has a name, size and modification time.

You can use PowerShell to explore a computer, organise project files, run compilers, inspect Git repositories and automate repeatable tasks.

## Create a working folder

Open PowerShell and enter the following commands one at a time:

```powershell
New-Item -ItemType Directory -Force -Path "$HOME\UmicomLearning" | Out-Null
Set-Location "$HOME\UmicomLearning"
Get-Location
Get-ChildItem
```

`$HOME` refers to your personal home directory. `New-Item` creates a directory, `Set-Location` enters it and `Get-ChildItem` lists its contents. `Out-Null` hides the success object from the first command.

Create and read a note:

```powershell
Set-Content -Path ".\notes.txt" -Value "Build the Umicom task board"
Get-Content -Path ".\notes.txt"
```

The expected output is:

```text
Build the Umicom task board
```

Add a second line without replacing the first:

```powershell
Add-Content -Path ".\notes.txt" -Value "Review the project backlog"
Get-Content -Path ".\notes.txt"
```

A path beginning `./` or `.\` is **relative** to the current folder. An **absolute** path, such as `C:\Users\...`, identifies a location independently of where the terminal is currently working.

## Copy, rename and remove practice files

Work only inside your `UmicomLearning` folder for this exercise:

```powershell
Copy-Item -LiteralPath ".\notes.txt" -Destination ".\notes-backup.txt"
Rename-Item -LiteralPath ".\notes-backup.txt" -NewName "notes-copy.txt"
Get-ChildItem
Remove-Item -LiteralPath ".\notes-copy.txt"
```

`Copy-Item` makes a second file; `Rename-Item` changes its name; `Remove-Item` deletes the selected practice file. Check `Get-ChildItem` before deleting anything, and do not use broad wildcard or recursive deletion commands in a real source tree without carefully reviewing what they would affect.

You can create and remove an **empty** temporary directory in the same practice location:

```powershell
New-Item -ItemType Directory -Path ".\temporary" | Out-Null
Remove-Item -LiteralPath ".\temporary"
```

## Inspect files with a pipeline

```powershell
Get-ChildItem -File |
    Select-Object Name, Length, LastWriteTime
```

The pipeline sends file objects into `Select-Object`, which chooses three properties to display. `Length` means file size in bytes. This is different from finding those words inside a file's text: the pipeline works with structured properties.

To locate notes by text, use:

```powershell
Select-String -Path ".\notes.txt" -Pattern "Umicom"
```

## Variables, decisions and loops

A **variable** stores a value under a name. Type these lines together:

```powershell
$taskCount = 3
$finishedCount = 1
$remaining = $taskCount - $finishedCount

if ($remaining -gt 0) {
    Write-Output "Remaining tasks: $remaining"
} else {
    Write-Output "All tasks are complete"
}
```

`-gt` means “greater than”. The code prints `Remaining tasks: 2`.

A **loop** repeats actions. For instance:

```powershell
$tasks = @("Write documentation", "Run tests", "Review changes")

foreach ($task in $tasks) {
    Write-Output "Task: $task"
}
```

The `@(...)` syntax creates an array here. Each item is stored in `$task` in turn.

## Make a reusable function

Rather than rewriting the same file check, define a function:

```powershell
function Test-NoteFile {
    param([string]$Path)

    if (Test-Path -LiteralPath $Path -PathType Leaf) {
        Write-Output "Found: $Path"
    } else {
        Write-Output "Missing: $Path"
    }
}

Test-NoteFile -Path ".\notes.txt"
```

The parameter `Path` allows the caller to choose which file to test. `-LiteralPath` prevents wildcard characters in a file name from being treated as patterns.

## Write a script you can reuse

Create a file named `check-tools.ps1` containing:

```powershell
$tools = @("git", "python", "cmake")

foreach ($tool in $tools) {
    $command = Get-Command $tool -ErrorAction SilentlyContinue
    if ($null -eq $command) {
        Write-Output "$tool : not found"
    } else {
        Write-Output "$tool : $($command.Source)"
    }
}
```

Save it in `UmicomLearning` and run it with:

```powershell
pwsh -NoProfile -File ".\check-tools.ps1"
```

If `pwsh` is not installed, Windows PowerShell can run a suitable local script with `powershell -NoProfile -File ".\check-tools.ps1"`, subject to your machine's execution policy. It is better to use a signed or locally reviewed script than to disable security settings for unknown code.

You should see one line per tool. Missing software is not a failure of the script: it is useful information before building a project.

**Next:** [Use Bash on Linux](06-bash.md).
