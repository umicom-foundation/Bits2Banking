<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/developing-with-umicom-c/08-embed-and-test.md

PURPOSE:
Build a minimal C23 host and check ordinary and refused compiler work.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Call the compiler and runtime from C23

![Umicom Foundation](../../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }
<a href="../../../assets/branding/umicom.ico"><img src="../../../assets/branding/umicom-icon.svg" alt="Umicom icon" width="28"></a>

A host can compile and run practice source directly in memory. The host owns instruction storage, the execution result and diagnostic storage. It checks the returned status before it uses any output.

1. Open [the host source](../../../labs/native/umicom-c-brew-time/brew-time-sdk.c). Identify the instruction array, the compile count, the result and the diagnostic. Find where the host stops when a source or runtime check fails.
2. Configure this teaching project against the same Umicom C source checkout used in the workshop. Run one line at a time and stop after a failure.

   ~~~powershell
   $LabBuild = Join-Path $Practice 'sdk-client'
   cmake -S $Lab -B $LabBuild -G Ninja -DCMAKE_C_COMPILER=C:/msys64/ucrt64/bin/gcc.exe "-DUMICOM_C_SOURCE=$UcSource"
   cmake --build $LabBuild --parallel 2
   ctest --test-dir $LabBuild --output-on-failure --no-tests=error
   ~~~

3. Check that all the tests pass. The host checks the normal result, a source refusal and a short budget that leaves the caller's result storage unchanged. The command checks compare the saved artifact, a typed preview and an input-bound run.
4. Edit a copy of the teaching project. Change the recipe time and its expected result together. Rebuild and rerun the checks so you know the test is exercising the new value. Keep the refusal cases too. A successful result does not tell you what the host does after failure.

This exercise uses the source targets exported by Umicom C. An independent project with the matching installed SDK can request the **Compiler** and **Runtime** components and link their namespaced targets. Review the [Umicom C repository and SDK documentation](https://github.com/umicom-foundation/umicom-c) for package versions and installation.

[Previous step — Inspect and link native x64 output](07-link-a-constant.md) · [Next step — Display a number and a Boolean](09-print-and-return.md)
