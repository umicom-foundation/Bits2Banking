<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/developing-with-umicom-c/02-save-and-compare.md

PURPOSE:
Separate operation identity from output identity in a portable artifact.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Save and compare bytecode

![Umicom Foundation](../../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }
<a href="../../../assets/branding/umicom.ico"><img src="../../../assets/branding/umicom-icon.svg" alt="Umicom icon" width="28"></a>

Bytecode stores instructions for the Umicom virtual machine. A disassembly lists those instructions in a form you can read.

1. Compile the original recipe to a new filename. Check that the file exists before reading it.

   ~~~powershell
   $Source = Join-Path $Lab 'brew-time.uc'
   $Artifact = Join-Path $Practice 'brew-time.umcb'
   & $Uc compile $Source $Artifact
   Get-Item -LiteralPath $Artifact
   ~~~

2. Inspect and disassemble the saved program. Find the multiply before the add. Execute the artifact and compare its 255-second result with the source run.

   ~~~powershell
   & $Uc inspect-bytecode $Artifact
   & $Uc disassemble $Artifact
   & $Uc exec $Artifact
   ~~~

3. Open [the spelling variation](../../../labs/native/umicom-c-brew-time/brew-time-spelling.uc) and [the direct constant](../../../labs/native/umicom-c-brew-time/brew-time-constant.uc). Compare each against the original. Read the report and capture the exit code immediately after each command.

   ~~~powershell
   & $Uc compare-operations $Source (Join-Path $Lab 'brew-time-spelling.uc')
   $LASTEXITCODE
   & $Uc compare-operations $Source (Join-Path $Lab 'brew-time-constant.uc')
   $LASTEXITCODE
   ~~~

   The spelling variation gives **operations=same** and exits 0. The direct constant gives **operations=different** and exits 1. Both source files produce 255 when executed. The comparison describes operation sequences and omits execution. An unreadable or invalid input exits 2.

Use a fresh output name after changing the recipe. Compilation preserves an existing output file. Keep the tool that made the artifact with your project notes so you can later check compatibility with the runtime that will load it.

[Previous step — Check and run the recipe](01-check-and-run.md) · [Next step — Bind one input](03-bind-one-input.md)
