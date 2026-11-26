<!--
Umicom Bits2Banking
File: content/simple-steps/compare/conda-miniforge-for-developers.md

PURPOSE:
Give learners an additional practical case for Conda and Miniforge for Umicom Developers.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Compare two selected native tool paths

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A fictional clean native terminal resolves cmake to C:\msys64\ucrt64\bin\cmake.exe. The activated teaching environment resolves the same command to C:\Miniforge\envs\lab\Library\bin\cmake.exe.

1. Compare these two Get-Command results using Keep native C and Assembly builds separate.
2. Write which path matches the documented native toolchain and what should be verified before a native configure.

**Check your result.** The first path matches the UCRT64 tool location. The second selects a different executable and needs an explicit toolchain check before configure.

[Step-by-step course guide](../course-guides/conda-miniforge-for-developers.md) · [Full course](../../courses/conda-miniforge-for-developers/index.html) · [Compare two approaches by course](index.md) · [First practice case](../practice/conda-miniforge-for-developers.md)
