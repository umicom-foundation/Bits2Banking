<!--
Umicom Bits2Banking
File: content/simple-steps/check/angularjs-legacy-statements.md

PURPOSE:
Give learners an additional practical case for AngularJS and Legacy Statement Screens.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check that repeated keys cannot enter the view

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

Two version 1 snapshots both declare two rows. The first lists ascending IDs 41 and 42. The second uses ID 41 twice. The fixture's cents and states are otherwise valid.

1. Trace the native producer's ascending-ID rule before passing either snapshot to a view. Write the admission outcome for each index.
2. Check the predicted displayed keys for the admitted version. Record whether the invalid candidate can replace that result.

**Check your result.** The first snapshot admits two keys, 41 and 42. The repeated key is refused on its second row and cannot replace the valid snapshot.

[Step-by-step course guide](../course-guides/angularjs-legacy-statements.md) · [Full course](../../courses/angularjs-legacy-statements/index.html) · [Acceptance checks by course](index.md) · [First practice case](../practice/angularjs-legacy-statements.md)
