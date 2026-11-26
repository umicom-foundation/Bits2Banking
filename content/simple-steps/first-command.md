<!--
Umicom Bits2Banking
File: content/simple-steps/first-command.md

PURPOSE:
Help readers identify the current PowerShell folder.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check your current folder

![Umicom Foundation](../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

1. Open **PowerShell 7** from Windows Start.
2. Type this command and press **Enter**.

   ```powershell
   Get-Location
   ```

3. Read the folder name under `Path`. Type the command again after moving to a new folder to confirm where you are.

Use this check before building or using Git. It tells you which folder your next command will work in.

[Install PowerShell 7](powershell-setup.md) · [Make a practice folder](work-folder.md) · [Full terminal lesson](../community/lessons/01-open-your-terminal.md)

<!-- Earlier demonstration code is retained for comparison. The active steps use an everyday task and check its result.

```powershell
Get-Location
```
-->
