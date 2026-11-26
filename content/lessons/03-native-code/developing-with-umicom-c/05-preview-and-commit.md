<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/developing-with-umicom-c/05-preview-and-commit.md

PURPOSE:
Try and reject typed session edits while keeping the last accepted value visible.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Try an edit before accepting it

![Umicom Foundation](../../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }
<a href="../../../assets/branding/umicom.ico"><img src="../../../assets/branding/umicom-icon.svg" alt="Umicom icon" width="28"></a>

A line session keeps the values from accepted submissions. A preview lets you try a change and then return to the accepted state. An atomic block applies one submitted sequence as a whole.

1. Open [the typed preview file](../../../labs/native/umicom-c-brew-time/brew-time-preview.ucs). Find the changes to the Boolean include_pour value. Read the first assignment with the preview prefix and the second assignment without it.
2. Run the file with the typed profile. Look for a preview acknowledgement. The first return still gives 255. The later accepted change gives 240.

   ~~~powershell
   & $Uc script --typed (Join-Path $Lab 'brew-time-preview.ucs')
   ~~~

3. Run [a complete block](../../../labs/native/umicom-c-brew-time/brew-time-script.ucs) and [a block with a zero divisor](../../../labs/native/umicom-c-brew-time/brew-time-script-error.ucs). Check the exit status immediately. The first prints just 255. The second reports a division diagnostic and prints no accepted result.

   ~~~powershell
   & $Uc script --block (Join-Path $Lab 'brew-time-script.ucs')
   $LASTEXITCODE
   & $Uc script --block (Join-Path $Lab 'brew-time-script-error.ucs')
   $LASTEXITCODE
   ~~~

4. Send [the rollback example](../../../labs/native/umicom-c-brew-time/brew-time-rollback.stdin) through standard input. The bad submission tentatively assigns 2 before the division fails. The prompt continues after it, prints 255 from the last accepted state and exits with failure once input ends.

   ~~~powershell
   Get-Content -LiteralPath (Join-Path $Lab 'brew-time-rollback.stdin') | & $Uc script --stdin
   $LASTEXITCODE
   ~~~

When reproducing a named-file error, stop at the reported line and correct it before retrying. The file reader stops at the first rejected submission. Standard input can continue and still return a failure status for the session.

[Previous step — Trace, pause and diagnose](04-trace-and-diagnose.md) · [Next step — Classify two language regions](06-classify-source.md)
