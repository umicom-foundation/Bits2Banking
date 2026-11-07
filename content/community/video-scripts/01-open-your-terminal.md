# Video script: Open PowerShell and find your place

**Aim:** Open a terminal, identify the shell and find the folder it is using.

**Preparation:** A Windows computer and a normal user account. You do not need Git, a compiler or an administrator window. Use a separate practice folder and hide notifications or personal account details before recording.

[Lesson and exact commands](../lessons/01-open-your-terminal.md)

## Opening words

Next, we will take this topic one step at a time: open powershell and find your place. Follow one step at a time. Pause the video whenever you need a little more time.

## Scene 1

Show the Start menu and open a normal PowerShell window. Pause before typing: point to the prompt and explain that it is already supplied by the shell.

## Scene 2

Type the version command slowly. Read the Major value. Show Get-Location, then Get-ChildItem, explaining a folder and a file as they appear.

## Scene 3

Clear the screen and run pwd. Ask the learner to pause, reopen PowerShell and find their own location.

## Walkthrough and pauses

### First, let us separate two names

**Say:** Windows Terminal is the window. It can hold several tabs. PowerShell is a shell: the program in a tab that reads your commands and returns results. You may also see Command Prompt or a Linux shell in another tab. They do not all understand the same commands.

**Say:** Windows PowerShell is the older Windows shell. PowerShell 7 is the newer edition and starts with pwsh. Both can exist on the same computer. The commands in this first lesson work in either. A command is an instruction you type; the prompt is the text already on screen showing where you can type. Do not copy the prompt.

### 1. Open a window

**Show each action:**

1. Open the Start menu and type PowerShell.
2. Open PowerShell, or Windows PowerShell if that is the only choice. A normal window is enough.
3. Click after the prompt. Type the following line and press Enter.

**On screen — type one line at a time:**

```powershell
$PSVersionTable.PSVersion
```

Pause. Read the result before continuing.

**Say:** You should see a version table with Major and Minor columns. Major 7 means PowerShell 7. Major 5 usually means Windows PowerShell 5.1. The dollar sign starts a variable name. PSVersionTable is information PowerShell already keeps about itself; .PSVersion selects its version entry.

### 2. Check your location

**On screen — type one line at a time:**

```powershell
Get-Location
Get-ChildItem
```

Pause. Read the result before continuing.

**Say:** Type each command separately. Get-Location prints your current folder. Get-ChildItem lists what is inside it. A folder is also called a directory. Listing a folder does not open or change its files. Your result will differ from someone else’s because it is your computer.

**Say:** PowerShell commands often have a verb and a noun: Get means read information, and Location means the current place. Later you will use Set-Location to change that place.

### 3. Try a useful shortcut

**On screen — type one line at a time:**

```powershell
pwd
Get-Help Get-ChildItem -Examples
```

Pause. Read the result before continuing.

**Say:** pwd is a short name, called an alias, for Get-Location in PowerShell. Get-Help asks for help. -Examples is an option that asks for examples rather than every detail. Press the Up Arrow to recall a command, but read it before pressing Enter. Clear-Host clears the visible screen; it does not delete files.

### If your screen looks different

**Say:** If $PSVersionTable is not recognised, check which shell the tab is running. A Command Prompt tab does not understand PowerShell variables. Open PowerShell from Start and try again. If help is incomplete, continue with Get-Location and Get-ChildItem; local help files are not required for these commands.

### Your turn

**Say:** Write down the shell version and the current folder. Close the terminal and open it again. Check the folder once more. Do not assume a new tab starts in the folder you used last time.

## Closing words

Before moving on, try the exercise once more in your own practice folder. If the result is different, compare the command and current location with the lesson. You can come back to this step at any time.
