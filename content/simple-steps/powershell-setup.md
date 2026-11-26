<!--
Umicom Bits2Banking
File: content/simple-steps/powershell-setup.md

PURPOSE:
Install and check the supported PowerShell setup for the starter route.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Step 1. Install PowerShell 7

![Umicom Foundation](../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

Use these steps on a Windows computer. PowerShell lets you work with the computer by typing commands. Type each command and press Enter.

1. Open **Start**, search for **PowerShell**, and open the app. **Windows PowerShell** can run the installation commands.

2. Check which version is open.

   ```powershell
   $PSVersionTable.PSVersion
   ```

   If the `Major` column shows `7`, go to [Step 2](system-checks.md).

3. Check that Windows can find its software installer.

   ```powershell
   winget --version
   ```

   If a version appears, run the next command. If Windows cannot find `winget`, use the installer on the official download page. [Microsoft's PowerShell installation guide](https://learn.microsoft.com/en-us/powershell/scripting/install/installing-powershell-on-windows)

4. Install PowerShell 7. Read any prompt before you confirm it.

   ```powershell
   winget install --id Microsoft.PowerShell --exact --source winget
   ```

5. When the installer finishes, close the window. Open **Start**, search for **PowerShell 7**, and open it. Run the version check from step 2 again. Continue when `Major` shows `7`.

## Update an existing PowerShell 7 installation

1. Open PowerShell 7 and note your current version.

   ```powershell
   $PSVersionTable.PSVersion
   ```

2. If you installed PowerShell with WinGet, check whether it offers an update for that package.

   ```powershell
   winget list --id Microsoft.PowerShell --exact --upgrade-available
   ```

3. If the list shows an update, use the same package ID. Read the installer prompts before confirming them.

   ```powershell
   winget upgrade --id Microsoft.PowerShell --exact
   ```

4. When the update finishes, close the terminal window. Open **PowerShell 7** again and compare the version with the one you noted.

If WinGet offers no update, leave the current installation in place. If you installed with another method, use that method to update it. If the current window shows version 5.1, follow the installation steps above to open PowerShell 7 alongside it. [Microsoft's PowerShell installation and update guide](https://learn.microsoft.com/en-us/powershell/scripting/install/install-powershell-on-windows)

[Guide overview](index.md) · [Next: Step 2. Check your computer](system-checks.md)

[Full lesson on opening and using PowerShell](../community/lessons/01-open-your-terminal.md)
