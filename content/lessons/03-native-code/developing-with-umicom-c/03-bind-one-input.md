<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/developing-with-umicom-c/03-bind-one-input.md

PURPOSE:
Reuse one checked artifact with varying host arguments and a structural budget.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Bind one input and plan the budget

![Umicom Foundation](../../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }
<a href="../../../assets/branding/umicom.ico"><img src="../../../assets/branding/umicom-icon.svg" alt="Umicom icon" width="28"></a>

The recipe now receives the number of minutes from the tool that runs it. The tool supplies this number as a signed 32-bit integer. The practice recipe accepts minutes 1 through 60.

1. Open [brew-time-input.uc](../../../labs/native/umicom-c-brew-time/brew-time-input.uc). Read the input entry and identify the condition that keeps the initial minus-one result for a value outside the recipe.
2. Compile it once to a fresh input artifact. Ask the tool to report its path budget. The budget counts virtual machine instructions.

   ~~~powershell
   $InputArtifact = Join-Path $Practice 'brew-time-input.umcb'
   & $Uc compile-input (Join-Path $Lab 'brew-time-input.uc') $InputArtifact
   & $Uc budget-input $InputArtifact
   & $Uc check-input-fuel $InputArtifact 64
   ~~~

3. Use the same artifact with three inputs and check the change in the result.

   ~~~powershell
   & $Uc exec-input $InputArtifact 4 --max-steps 64
   & $Uc exec-input $InputArtifact 3 --max-steps 64
   & $Uc exec-input $InputArtifact 0 --max-steps 64
   $LASTEXITCODE
   ~~~

   Expect answers 255, 195 and minus one. The last value is the practice program's refusal to make that recipe. It still completes successfully, so the process exit is 0.

4. Try the value 2147483648. The command rejects an input outside the signed 32-bit range, and the program produces no result. Try a budget of one instruction with input 4. This time the tool can bind the value but stops during execution.

   ~~~powershell
   & $Uc exec-input $InputArtifact 2147483648
   $LASTEXITCODE
   & $Uc exec-input $InputArtifact 4 --max-steps 1
   $LASTEXITCODE
   ~~~

Use **exec-input** for this file. The ordinary **exec** command expects an artifact that can start without a host input. Using a different input with the right command leaves the saved artifact unchanged.

[Previous step — Save and compare bytecode](02-save-and-compare.md) · [Next step — Trace, pause and diagnose](04-trace-and-diagnose.md)
