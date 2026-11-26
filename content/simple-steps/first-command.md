<!--
Umicom Bits2Banking
File: content/simple-steps/first-command.md

PURPOSE:
Help a Windows learner find their current folder using one command.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Find your current folder

![Umicom Foundation](../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A folder holds files and other folders. Let’s find the folder PowerShell is looking at.

1. On Windows, open **Start**. Type **PowerShell**, then open it.
2. Type this line. Press **Enter**.

```powershell
Get-Location
```

Look under `Path`. That is the name of the folder PowerShell is using. It might look like `C:\Users\Alex`. Your computer will show its own folder name.

**Try it.** Run the same command again. Did you see the same folder?

If Windows says it doesn’t know `Get-Location`, open **PowerShell** from Start and try again.

## Copy to WhatsApp

```text
Bits2Banking • Find your folder
1. On Windows, open Start and search for PowerShell. Open it.
2. Type Get-Location and press Enter.
3. Look under Path. That is your current folder.
Reply “found it” or tell us which step you got stuck on.
```

[Make a practice folder next](../community/lessons/02-make-a-practice-folder.md) · [Learning in Simple Steps](index.md)
