<!--
Umicom Bits2Banking
File: content/simple-steps/extension/first-csharp-statements.md

PURPOSE:
Give learners an additional practical case for First C# Statements.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check a large pending amount beside posted amounts

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A fictional C# fixture has states posted, pending and posted, and amounts 500, int.MaxValue and -120.

1. Follow TryPostedTotal row by row and write the posted subtotal after each row. Include the pending row in the array.
2. Add the case to Main with the existing Check helper, using pending excluded as its name, or trace the comparison on paper.

**Check your result.** The subtotals are 500, 500 and 380. The call returns true with total 380, and the helper reports Pass: pending excluded.

[Step-by-step course guide](../course-guides/first-csharp-statements.md) · [Full course](../../courses/first-csharp-statements/index.html) · [Extend a skill by course](index.md) · [First practice case](../practice/first-csharp-statements.md)
