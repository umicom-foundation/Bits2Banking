<!--
Umicom Bits2Banking
File: content/simple-steps/course-guides/learning-odin.md

PURPOSE:
Provide practical first steps and a result to check for Learning Odin.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Learning Odin

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

1. Open `labs/languages/odin-activity/main.odin` and `bridge.h`. Match each declared argument and return type before the call. [Connect Odin values to the C contract](../../courses/learning-odin/lessons/02-connect-values-to-c.html)
2. Work out the C bridge results for −1, 0, 41, 999 and 1000 in that order. [Connect Odin values to the C contract](../../courses/learning-odin/lessons/02-connect-values-to-c.html)
3. Build the C archive and Odin client with the linked interoperability commands. Compare the client output with your predicted results. [Connect Odin values to the C contract](../../courses/learning-odin/lessons/02-connect-values-to-c.html)

**Check your result.** The expected bridge results are refusal, 1, 42, 1000 and refusal. The negative result represents refusal, so the caller should handle it as a separate case.

[Continue in the full course](../../courses/learning-odin/index.html) · [All course guides](index.md)
