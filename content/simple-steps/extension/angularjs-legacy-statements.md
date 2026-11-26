<!--
Umicom Bits2Banking
File: content/simple-steps/extension/angularjs-legacy-statements.md

PURPOSE:
Give learners an additional practical case for AngularJS and Legacy Statement Screens.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Use one stable key in two templates

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A fictional report snapshot contains row 101 for 400 cents and row 103 for 900 cents. The view inserts a newly admitted row 102 between them.

1. Write the AngularJS track by expression and the modern Angular track expression from Plan a host migration.
2. Trace the row keys before and after insertion. Record which identity is added and which earlier row moves in the list.

**Check your result.** The keys change from 101 and 103 to 101, 102 and 103. Only 102 is new. Row 103 moves from the second to the third position and keeps key 103.

[Step-by-step course guide](../course-guides/angularjs-legacy-statements.md) · [Full course](../../courses/angularjs-legacy-statements/index.html) · [Extend a skill by course](index.md) · [First practice case](../practice/angularjs-legacy-statements.md)
