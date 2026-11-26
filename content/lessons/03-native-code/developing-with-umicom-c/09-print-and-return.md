<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/developing-with-umicom-c/09-print-and-return.md

PURPOSE:
Separate typed display lines, return values and process exit codes.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Display a number and a Boolean

![Umicom Foundation](../../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }
<a href="../../../assets/branding/umicom.ico"><img src="../../../assets/branding/umicom-icon.svg" alt="Umicom icon" width="28"></a>

Open [brew-time-print.uc](../../../labs/native/umicom-c-brew-time/brew-time-print.uc). The program displays a number and a Boolean value. A Boolean means true or false. The last statement returns the numeric result to the caller.

1. Run the example from the [workshop shell](index.md). Check that the displayed number and true appear before the completed result.

   ~~~powershell
   $PrintSource = Join-Path $Lab 'brew-time-print.uc'
   & $Uc run $PrintSource
   $LASTEXITCODE
   ~~~

   The two display lines are `255` and `true`. The subsequent `Result: 255` is the finished calculation. The process exit is 0.

2. Save the program as bytecode. Run the saved artifact with the same Umicom C tool. Look for the same two display lines and the same result.

   ~~~powershell
   $PrintArtifact = Join-Path $Practice 'brew-time-print.umcb'
   & $Uc compile $PrintSource $PrintArtifact
   & $Uc exec $PrintArtifact
   ~~~

3. Ask the source interpreter to write a separate JSON record for each event. Read just the print records and compare their value types. Keep the original source with these records because the offsets refer to its exact bytes.

   ~~~powershell
   $Events = & $Uc interpret $PrintSource --jsonl | ForEach-Object { $_ | ConvertFrom-Json }
   $Events | Where-Object event -eq 'print' | Format-Table valueType, value, sourceOffset, sourceEnd
   ~~~

   Expect an integer with value 255 and a Boolean with value True.

4. Edit a copy of the source and change only the Boolean initializer to false. Run the copy. The second display line changes to false and the numeric result remains 255. Then decide whether the flag should also control the arithmetic in a future version of your recipe.

If a different host reports that output support is required, check whether that host handles typed output for the saved bytecode. Use the native first run above to compare an ordinary numeric result with the two display lines.

[Previous step — Call the compiler and runtime](08-embed-and-test.md) · [Next step — Inspect and collect objects](10-inspect-objects.md)
