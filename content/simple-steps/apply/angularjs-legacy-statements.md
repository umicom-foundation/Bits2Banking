<!--
Umicom Bits2Banking
File: content/simple-steps/apply/angularjs-legacy-statements.md

PURPOSE:
Give learners an additional practical case for AngularJS and Legacy Statement Screens.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Write a migration handoff for a statement screen

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A maintainer will replace a legacy statement view. The C producer's version 1 snapshot displays posted row 21 at 725 cents and pending row 24 at 350 cents.

1. Write a short handoff naming the one-way report input, the version, the signed-cent fields and the key used in ngRepeat.
2. Draft the expected view for the supplied snapshot and for an admitted empty snapshot, using the course's exact empty-state text.

**Check your result.** The handoff calls for displayed rows 21 and 24 with a posted total of 725 cents. The admitted empty snapshot reads No entries in this statement.

[Step-by-step course guide](../course-guides/angularjs-legacy-statements.md) · [Full course](../../courses/angularjs-legacy-statements/index.html) · [Small projects by course](index.md) · [First practice case](../practice/angularjs-legacy-statements.md)
