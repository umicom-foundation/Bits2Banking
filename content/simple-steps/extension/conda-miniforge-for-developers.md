<!--
Umicom Bits2Banking
File: content/simple-steps/extension/conda-miniforge-for-developers.md

PURPOSE:
Give learners an additional practical case for Conda and Miniforge for Umicom Developers.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Select an interpreter for one command

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A disposable course environment named umicom-env-lab already exists. The current PowerShell session has a different active environment.

1. Record the active name from conda env list. Run conda run --name umicom-env-lab python -c "import sys; print(sys.executable)" as shown in Create an environment and identify its interpreter.
2. Check conda env list again and compare the reported interpreter path with the prefix for umicom-env-lab.

**Check your result.** The one command reports a Python inside umicom-env-lab. The star in conda env list stays on the same previously active environment.

[Step-by-step course guide](../course-guides/conda-miniforge-for-developers.md) · [Full course](../../courses/conda-miniforge-for-developers/index.html) · [Extend a skill by course](index.md) · [First practice case](../practice/conda-miniforge-for-developers.md)
