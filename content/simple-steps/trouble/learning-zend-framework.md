<!--
Umicom Bits2Banking
File: content/simple-steps/trouble/learning-zend-framework.md

PURPOSE:
Give learners an additional practical case for Learning Zend Framework.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Find why a title shows an entity name

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A local title intended to show `Hall & garden` instead appears as `Hall &amp; garden` on the screen.

1. Write down the raw title, the template value and the displayed text. Find where the exercise handles HTML text.
2. Follow only one display conversion through the local template. Check that the unchanged value still belongs in your input record.

**Check your result.** The displayed text has one ampersand. The input field still contains `Hall & garden`.

[Step-by-step course guide](../course-guides/learning-zend-framework.md) · [Full course](../../courses/learning-zend-framework/index.html) · [Troubleshoot by course](index.md) · [First practice case](../practice/learning-zend-framework.md)
