<!--
Umicom Bits2Banking
File: labs/framework/host-cache-budget/README.md

PURPOSE:
Explain synthetic host-memory budgeting and dense cache capacity.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../content/assets/branding/umicom-wordmark.svg)

# Plan a dense cache after fixed model costs

This C exercise starts with synthetic 8 GiB available memory, 6 GiB resident
weights, 512 MiB workspace, 256 MiB runtime overhead and a 512 MiB host reserve.
The remaining 768 MiB covers a dense cache costing 256 KiB per token across two
sequences. The requested 4096 tokens are reduced to 3072. No model is loaded,
no host memory is measured and no allocation is reserved by the planner.

Run each command separately and stop on errors:

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S labs/framework/host-cache-budget -B build/host-cache-budget -G Ninja -DUMICOM_FRAMEWORK_SOURCE=C:/umicom/Umicom-Applications/framework
cmake --build build/host-cache-budget --parallel 2
ctest --test-dir build/host-cache-budget --output-on-failure --no-tests=error
```

A passing exercise checks the 3072-token calculation and confirms that fixture,
stale and incomplete observations produce no cache plan. Add -V to CTest to
see the printed values. This project links source directly; it does not qualify
an installed Framework SDK or the memory behavior of an inference backend.

The shape describes dense key/value arrays with explicit layer, head, dimension
and element-byte counts. It is not a universal estimate for every GGUF model.
Quantized, sliding-window, recurrent or paged caches may use different layouts.
A mathematically fitting cache does not establish peak loading fit, GPU capacity,
future free RAM or permission to start an application.
