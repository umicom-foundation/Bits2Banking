<!--
Umicom Bits2Banking
File: content/simple-steps/apply/conda-miniforge-for-developers.md

PURPOSE:
Give learners an additional practical case for Conda and Miniforge for Umicom Developers.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Record what a teammate needs to recreate an environment

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A course environment uses Python 3.12, pip and packaging from conda-forge. A colleague needs both the requested setup and what was observed on one practice machine.

1. Write the package requests and channel as a small environment specification using the course example.
2. Draft a separate installed-package record header. Add columns for package, version, build and channel, then name the interpreter-version check to run after recreation.

**Check your result.** The specification lists Python 3.12, pip and packaging from conda-forge. The inventory has separate version, build and channel fields and the next check is python --version.

[Step-by-step course guide](../course-guides/conda-miniforge-for-developers.md) · [Full course](../../courses/conda-miniforge-for-developers/index.html) · [Small projects by course](index.md) · [First practice case](../practice/conda-miniforge-for-developers.md)
