# Open PowerShell and find your place

Open a terminal, identify the shell and find the folder it is using.

**Before you start:** A Windows computer and a normal user account. You do not need Git, a compiler or an administrator window.

[Community learning route](../index.md) · [Printable HTML](../handouts/01-open-your-terminal.html)

## First, let us separate two names

Windows Terminal is the window. It can hold several tabs. PowerShell is a shell: the program in a tab that reads your commands and returns results. You may also see Command Prompt or a Linux shell in another tab. They do not all understand the same commands.

Windows PowerShell is the older Windows shell. PowerShell 7 is the newer edition and starts with pwsh. Both can exist on the same computer. The commands in this first lesson work in either. A command is an instruction you type; the prompt is the text already on screen showing where you can type. Do not copy the prompt.

## 1. Open a window

1. Open the Start menu and type PowerShell.
2. Open PowerShell, or Windows PowerShell if that is the only choice. A normal window is enough.
3. Click after the prompt. Type the following line and press Enter.

```powershell
$PSVersionTable.PSVersion
```

You should see a version table with Major and Minor columns. Major 7 means PowerShell 7. Major 5 usually means Windows PowerShell 5.1. The dollar sign starts a variable name. PSVersionTable is information PowerShell already keeps about itself; .PSVersion selects its version entry.

## 2. Check your location

```powershell
Get-Location
Get-ChildItem
```

Type each command separately. Get-Location prints your current folder. Get-ChildItem lists what is inside it. A folder is also called a directory. Listing a folder does not open or change its files. Your result will differ from someone else’s because it is your computer.

PowerShell commands often have a verb and a noun: Get means read information, and Location means the current place. Later you will use Set-Location to change that place.

## 3. Try a useful shortcut

```powershell
pwd
Get-Help Get-ChildItem -Examples
```

pwd is a short name, called an alias, for Get-Location in PowerShell. Get-Help asks for help. -Examples is an option that asks for examples rather than every detail. Press the Up Arrow to recall a command, but read it before pressing Enter. Clear-Host clears the visible screen; it does not delete files.

## If your screen looks different

If $PSVersionTable is not recognised, check which shell the tab is running. A Command Prompt tab does not understand PowerShell variables. Open PowerShell from Start and try again. If help is incomplete, continue with Get-Location and Get-ChildItem; local help files are not required for these commands.

## Your turn

Write down the shell version and the current folder. Close the terminal and open it again. Check the folder once more. Do not assume a new tab starts in the folder you used last time.

## Continue when you are ready

[Next: Make a folder for your practice work](02-make-a-practice-folder.md)

[Explore the related course](../../courses/introduction-to-programming/index.html). You can finish this exercise without leaving this page.

[Video teaching script](../video-scripts/01-open-your-terminal.md) · [Short community message](../messages/01-open-your-terminal.md)
