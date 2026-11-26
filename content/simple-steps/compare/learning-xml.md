<!--
Umicom Bits2Banking
File: content/simple-steps/compare/learning-xml.md

PURPOSE:
Give learners an additional practical case for Learning XML.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Compare parsing success with record acceptance

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A local XML fragment has a closed room element, but the training rule requires an id attribute that the element omits.

1. Apply the syntax checks from the course first and give parsing its own outcome. Then apply the training record rule to the parsed element.
2. Add id R7 in a practice copy and trace the same two stages again.

**Check your result.** Both fragments parse. The missing-id fragment fails the record rule and the R7 fragment is accepted.

[Step-by-step course guide](../course-guides/learning-xml.md) · [Full course](../../courses/learning-xml/index.html) · [Compare two approaches by course](index.md) · [First practice case](../practice/learning-xml.md)
