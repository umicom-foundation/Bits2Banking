<!--
Umicom Bits2Banking
File: content/simple-steps/compare/learning-android.md

PURPOSE:
Give learners an additional practical case for Android Development.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Compare an Android package with the C library it contains

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

The course's JNI-enabled build produces an APK and compiles the training C model into a shared library for a selected ABI.

1. Inspect the package listing with the course tooling and find the packaged library for the chosen ABI.
2. Record which artifact Android installs and which component supplies the native model code.

**Check your result.** The APK is the installable package. Its selected ABI entry contains the shared library for the C model.

[Step-by-step course guide](../course-guides/learning-android.md) · [Full course](../../courses/learning-android/index.html) · [Compare two approaches by course](index.md) · [First practice case](../practice/learning-android.md)
