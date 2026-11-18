<!--
Umicom Bits2Banking
File: labs/framework/budget-observations/README.md

PURPOSE:
Explain finite telemetry values and reproducible source-linked checks.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../content/assets/branding/umicom-wordmark.svg)

# Observe a budget without claiming to enforce memory

This small C exercise uses `UmiPerformanceMemoryBudget` to store synthetic measurements, refuses an invalid measurement without overwriting the prior record, and checks the final usable sequence. The comparison accepts only finite nonnegative used/limit values. It captures no process memory, starts no model and reserves no RAM.

Run each command separately and stop on an error:

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S labs/framework/budget-observations -B build/budget-observations -G Ninja -DUMICOM_FRAMEWORK_SOURCE=C:/umicom/Umicom-Applications/framework
cmake --build build/budget-observations --parallel 2
ctest --test-dir build/budget-observations --output-on-failure --no-tests=error
```

A passing test checks the synthetic 512 MiB observation, rejection of infinity as a limit, unchanged state after NaN input, and refusal after the last sequence. To see its messages, add `-V` to the CTest command. If the source and headers disagree, stop and reconcile the Framework checkout rather than running a stale executable. This project deliberately links source; it does not qualify an installed SDK.

Use integer byte counts in model memory planning when exact accounting matters. A double-precision telemetry field cannot represent every large integer exactly. Record measurement status separately from the numeric sample; unknown memory is neither zero nor infinity. Keep model-specific admission, process limits and runtime monitoring as explicit separate responsibilities.
