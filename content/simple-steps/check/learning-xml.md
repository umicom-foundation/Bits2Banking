<!--
Umicom Bits2Banking
File: content/simple-steps/check/learning-xml.md

PURPOSE:
Give learners an additional practical case for Learning XML.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check two names with special characters

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A local room XML fixture needs to store the text Cedar in one case and West & East in the other.

1. Use the repair lesson to write both as element text, escaping the ampersand in the second case before parsing.
2. Check that both written fragments parse and that their parsed text matches the exact original input.

**Check your result.** The parsed texts are Cedar and West & East. The second file has an entity reference for the ampersand.

[Step-by-step course guide](../course-guides/learning-xml.md) · [Full course](../../courses/learning-xml/index.html) · [Acceptance checks by course](index.md) · [First practice case](../practice/learning-xml.md)
