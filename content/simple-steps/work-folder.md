<!--
Umicom Bits2Banking
File: content/simple-steps/work-folder.md

PURPOSE:
Create and verify a practice folder for the first project.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Step 3. Make a practice folder

![Umicom Foundation](../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

Give the projects from this guide a place in your Windows user folder. The first project will go in a folder called `coffee-timer`.

1. Open PowerShell 7. Make the main practice folder.

   ```powershell
   New-Item -ItemType Directory -Path "$env:USERPROFILE\Bits2Banking-Practice" -Force
   ```

   `$env:USERPROFILE` gives PowerShell the path to your Windows user folder. You should see `Bits2Banking-Practice` in the output. You can run this command again if the folder already exists.

2. Move into it.

   ```powershell
   Set-Location -LiteralPath "$env:USERPROFILE\Bits2Banking-Practice"
   ```

3. Make the project folder and move into it. `.` means the folder you are in now.

   ```powershell
   New-Item -ItemType Directory -Path '.\coffee-timer' -Force
   Set-Location -LiteralPath '.\coffee-timer'
   ```

4. Check where you are.

   ```powershell
   Get-Location
   ```

   The path should end in `Bits2Banking-Practice\coffee-timer`. You will return to this folder when you write the first C program.

If PowerShell says it cannot find the practice folder, run step 1 again. Then follow the remaining steps in order.

[Previous: Step 2. Check your computer](system-checks.md) · [Next: Step 4. Set up the C tools](toolchain.md)

[Full lesson on creating and checking folders](../community/lessons/02-make-a-practice-folder.md)
