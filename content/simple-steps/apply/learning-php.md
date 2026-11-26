<!--
Umicom Bits2Banking
File: content/simple-steps/apply/learning-php.md

PURPOSE:
Give learners an additional practical case for Learning PHP.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Show a list of names as plain text

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A local PHP report displays the fictional name `Room <West>` from its record list.

1. Use the output validation lesson to choose an HTML escaping step at the point where the name enters the page.
2. Place the escaped value inside one list item. Inspect the rendered text and the HTML source in a scratch copy.

**Check your result.** The browser displays `Room <West>` as text. The source represents the angle brackets as `&lt;` and `&gt;` and creates no West element.

[Step-by-step course guide](../course-guides/learning-php.md) · [Full course](../../courses/learning-php/index.html) · [Small projects by course](index.md) · [First practice case](../practice/learning-php.md)
