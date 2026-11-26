<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/developing-with-umicom-c/01-check-and-run.md

PURPOSE:
Build a habit of checking source before comparing an actual result.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check and run the recipe

![Umicom Foundation](../../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }
<a href="../../../assets/branding/umicom.ico"><img src="../../../assets/branding/umicom-icon.svg" alt="Umicom icon" width="28"></a>

Start with [the workshop setup](index.md). Work in the same PowerShell window.

1. Open [brew-time.uc](../../../labs/native/umicom-c-brew-time/brew-time.uc). Write the calculation as two steps. Multiply four by 60, then add 15. Keep the unit next to the answer.
2. Ask Umicom C to check the source. The check reads the file and verifies its grammar. It has no brew result to show.

   ~~~powershell
   $Source = Join-Path $Lab 'brew-time.uc'
   & $Uc check $Source
   $LASTEXITCODE
   ~~~

3. Run the source. Check for **Result: 255** and a count of executed instructions. In Umicom C, **return** gives the practice program's numeric answer. PowerShell's **LASTEXITCODE** reports whether the compiler command completed successfully.

   ~~~powershell
   & $Uc run $Source
   $LASTEXITCODE
   ~~~

4. Save a copy in the practice folder. Change the 4 to 3 and check and run the copy. Expect 195 seconds. Keep the original sample for the next lesson.

   ~~~powershell
   $Edited = Join-Path $Practice 'brew-time-edited.uc'
   if (-not (Test-Path -LiteralPath $Edited)) {
       Copy-Item -LiteralPath $Source -Destination $Edited
   }
   notepad $Edited
   ~~~

   Save the edit in Notepad before running the next commands.

   ~~~powershell
   & $Uc check $Edited
   & $Uc run $Edited
   ~~~

If the check points to a line in the file, open the file from that exact path and look for a missing operator, number or closing punctuation before running again.

[Workshop setup](index.md) · [Next step — Save and compare bytecode](02-save-and-compare.md)
