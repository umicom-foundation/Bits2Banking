<!--
Umicom Bits2Banking
File: content/simple-steps/compare/build-a-bank-application-in-c.md

PURPOSE:
Give learners an additional practical case for Build a Banking Application in C.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Compare an interruption before and after a commit

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A paper database adapter moves 80 cents from one fictional account to another. One trial stops before commit. The other commits both updates and the journal row, then loses its reply.

1. Draw the transaction boundary and put the interruption marker in the appropriate place for each trial.
2. Write the expected next observation using the original request reference. Count the committed journal records in the two trials.

**Check your result.** The pre-commit stop has zero committed journal rows. The committed trial has one row and its reference can identify the stored result after the lost reply.

[Step-by-step course guide](../course-guides/build-a-bank-application-in-c.md) · [Full course](../../courses/build-a-bank-application-in-c/index.html) · [Compare two approaches by course](index.md) · [First practice case](../practice/build-a-bank-application-in-c.md)
