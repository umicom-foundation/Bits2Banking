<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/developing-with-umicom-c/04-trace-and-diagnose.md

PURPOSE:
Distinguish source, execution and budget failures before reading debugger state.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Trace, pause and diagnose

![Umicom Foundation](../../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }
<a href="../../../assets/branding/umicom.ico"><img src="../../../assets/branding/umicom-icon.svg" alt="Umicom icon" width="28"></a>

Use a trace to see a sequence of instructions. Use the debugger when you want to decide when to advance.

1. Trace [the recipe with a local adjustment](../../../labs/native/umicom-c-brew-time/brew-time-adjust.uc). Find the first store of seconds and the store after adding 15.

   ~~~powershell
   $Adjust = Join-Path $Lab 'brew-time-adjust.uc'
   & $Uc trace $Adjust --max-steps 64
   ~~~

2. Pause the same program with the debugger. Type **where** to see the next instruction. Type **line** and then **locals**. Repeat both commands. The first initialized slot should hold 240, then 255. Type **continue** to finish and see the completed result.

   ~~~powershell
   & $Uc debug $Adjust --max-steps 64
   ~~~

   A local slot is numbered storage for the running program. Use **step** when you want one instruction. The **line** command advances according to source coordinates, so separate your changes onto separate lines for this exercise.

3. Run the three failures below. Read the first diagnostic and record whether a complete result appeared. The sample files include [a missing operand](../../../labs/native/umicom-c-brew-time/brew-time-invalid.uc) and [a division by zero](../../../labs/native/umicom-c-brew-time/brew-time-zero-divisor.uc).

   ~~~powershell
   & $Uc check (Join-Path $Lab 'brew-time-invalid.uc')
   & $Uc trace (Join-Path $Lab 'brew-time-zero-divisor.uc')
   & $Uc run $Adjust --max-steps 1
   ~~~

4. Repair them separately. Copy the missing-operand file and put 60 after the multiplication sign. Copy the zero-divisor file and divide by 1. Repeat the budget-limited run with 64. Each successful repair should produce 255.

Use source changes to repair the first two examples. Use a larger instruction allowance for the third. When a run is incomplete, keep its diagnostic with the exact version of the source you ran.

[Previous step — Bind one input](03-bind-one-input.md) · [Next step — Try an edit before accepting it](05-preview-and-commit.md)
