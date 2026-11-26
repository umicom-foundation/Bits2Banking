<!--
Umicom Bits2Banking
File: content/simple-steps/check/conda-miniforge-for-developers.md

PURPOSE:
Give learners an additional practical case for Conda and Miniforge for Umicom Developers.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check interpreter and package ownership together

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

One recorded invocation uses the practice lab's Python and pip inside the same environment prefix. A second shows that Python path but a pip module reported from the base prefix.

1. Read the two pieces of evidence independently. Compare each's pip path against the prefix reported by the Python process.
2. Write whether these records are sufficient for a package-installation exercise. Record the symptom that needs investigation.

**Check your result.** The first passes the ownership check. The second fails because the pip module path is outside the selected interpreter's environment.

[Step-by-step course guide](../course-guides/conda-miniforge-for-developers.md) · [Full course](../../courses/conda-miniforge-for-developers/index.html) · [Acceptance checks by course](index.md) · [First practice case](../practice/conda-miniforge-for-developers.md)
