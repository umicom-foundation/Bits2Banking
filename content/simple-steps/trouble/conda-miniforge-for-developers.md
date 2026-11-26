<!--
Umicom Bits2Banking
File: content/simple-steps/trouble/conda-miniforge-for-developers.md

PURPOSE:
Give learners an additional practical case for Conda and Miniforge for Umicom Developers.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Find where pip is running

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

After opening a new PowerShell window, python -m pip --version reports a path outside the practice environment that was active in the previous window.

1. In the new window run conda env list. Find the star marking the selected environment and the path of your disposable practice environment.
2. Activate the practice environment by name. Run conda env list and python -m pip --version again if pip is installed there.

**Check your result.** The star moves to the named environment. When pip is installed in the sample environment, its reported module path starts inside that environment's listed directory.

[Step-by-step course guide](../course-guides/conda-miniforge-for-developers.md) · [Full course](../../courses/conda-miniforge-for-developers/index.html) · [Troubleshoot by course](index.md) · [First practice case](../practice/conda-miniforge-for-developers.md)
