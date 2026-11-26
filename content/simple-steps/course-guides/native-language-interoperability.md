<!--
Umicom Bits2Banking
File: content/simple-steps/course-guides/native-language-interoperability.md

PURPOSE:
Provide practical first steps and a result to check for Native languages working together through C.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Native languages working together through C

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

1. Open the bridge header and list the argument, result and status the callers share. [Prepare one shared C boundary](../../courses/native-language-interoperability/lessons/01-prepare-a-shared-boundary.html)
2. Follow a normal value and a negative value through the C implementation. Mark which path writes a result. [Follow the C contract and its failure path](../../courses/native-language-interoperability/lessons/02-follow-the-c-contract.html)
3. Run the C++ caller exercise with the same values and compare its status and output with the C version. [Call C from C++ without changing ownership](../../courses/native-language-interoperability/lessons/03-call-c-from-cpp.html)

**Check your result.** A valid call from either language gives the same result. The negative input follows the C contract’s refusal path.

[Continue in the full course](../../courses/native-language-interoperability/index.html) · [All course guides](index.md)
