<!--
Umicom Bits2Banking
File: content/simple-steps/check/learning-visual-studio.md

PURPOSE:
Give learners an additional practical case for Learning Visual Studio for Umicom development.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check whether a failed debug build can be launched as current

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A practice session contains one successful build fixture and one with a compile error. Both still show an executable in the output folder.

1. Use the guide’s debugging and deliberate failure sections to define which build result is required before launching the intended current executable.
2. Apply the check to both records. Pair each with its own configure and build outcome before considering the executable path.

**Check your result.** The successful current build permits the debug launch. The failed build does not qualify a current launch even though an earlier executable exists.

[Step-by-step course guide](../course-guides/learning-visual-studio.md) · [Full course](../../courses/learning-visual-studio/index.html) · [Acceptance checks by course](index.md) · [First practice case](../practice/learning-visual-studio.md)
