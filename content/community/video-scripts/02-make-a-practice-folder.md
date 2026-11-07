# Video script: Make a folder for your practice work

**Aim:** Create a practice folder and move into it without touching product source.

**Preparation:** PowerShell on Windows. Open it from Start. Get-Location shows your current folder. Use a separate practice folder and hide notifications or personal account details before recording.

[Lesson and exact commands](../lessons/02-make-a-practice-folder.md)

## Opening words

Next, we will take this topic one step at a time: make a folder for your practice work. Follow one step at a time. Pause the video whenever you need a little more time.

## Scene 1

Draw three nested boxes labelled user folder, Umicom-Practice and notes-practice. Explain that a path describes this route.

## Scene 2

Create the folders one line at a time. Show the location after each move, then list src, include, tests and docs.

## Scene 3

Move up once and return. Pause for the learner to create docs/drawings and explain their result aloud.

## Walkthrough and pauses

### Choose a place you can find again

**Say:** We will keep the exercises in a folder called Umicom-Practice inside your user folder. Your user folder holds files belonging to your Windows account. The example uses its location from Windows, so you do not have to copy someone else’s user name.

**Say:** A path is an address for a file or folder. An absolute path starts from a drive, such as C:\Users\Alex. A relative path starts from your current folder. . means the current folder; .. means its parent.

### 1. Create your practice folder

**On screen — type one line at a time:**

```powershell
Set-Location $env:USERPROFILE
Get-Location
New-Item -ItemType Directory -Path "Umicom-Practice"
```

Pause. Read the result before continuing.

**Say:** $env:USERPROFILE reads the user-folder path from your environment. An environment value is a setting made available to programs. Set-Location moves into that folder. New-Item creates something; -ItemType Directory says it must be a folder. Quotes keep the path together as one value.

### 2. Enter the folder

**On screen — type one line at a time:**

```powershell
Set-Location "Umicom-Practice"
Get-Location
Get-ChildItem
```

Pause. Read the result before continuing.

**Say:** The location should end in Umicom-Practice. An empty listing is fine: we have not created files yet. If New-Item said the folder already exists, do not remove it. List it first and use a new name if it contains work you want to keep.

### 3. Add a project folder

**On screen — type one line at a time:**

```powershell
New-Item -ItemType Directory -Path "notes-practice"
Set-Location "notes-practice"
New-Item -ItemType Directory -Path "src", "include", "tests", "docs"
Get-ChildItem
```

Pause. Read the result before continuing.

**Say:** src will hold source code, include will hold shared declarations, tests will hold checks, and docs will hold explanations. These are conventions: names people agree to use. Empty folders are useful while working, but Git will later record files rather than empty folders on their own.

### 4. Leave and return

**On screen — type one line at a time:**

```powershell
Set-Location ..
Get-Location
Set-Location ".\notes-practice"
```

Pause. Read the result before continuing.

**Say:** .. moves one level up. .\notes-practice selects the project under the current folder. Check Get-Location whenever you are unsure. Typing cd instead of Set-Location also works in PowerShell.

### If a command fails

**Say:** Path not found normally means the spelling or current folder differs from the example. Run Get-Location and Get-ChildItem before trying again. Access denied may mean you selected a protected folder. Use a folder you own; these exercises do not need administrator access.

### Your turn

**Say:** Create a folder called drawings inside docs. Return to the project folder and list docs to check it. Keep this practice project for the next lesson.

## Closing words

Before moving on, try the exercise once more in your own practice folder. If the result is different, compare the command and current location with the lesson. You can come back to this step at any time.
