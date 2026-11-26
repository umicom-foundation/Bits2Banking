<!--
Umicom Bits2Banking
File: content/simple-steps/apply/automated-testing-with-umicom.md

PURPOSE:
Give learners an additional practical case for Automated Testing with Umicom Framework.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Draw a read-only adapter worksheet

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A fictional test reads a seeded account total of 1,750 cents. The adapter supports read and write, but the fixture owner authorizes only read.

1. Write the intended operation, permission mask, capability mask and expected amount in a one-page workflow plan.
2. Add a proposed correction that would write 200 cents. Mark where the workflow gate should refuse it and include a final read to verify the seed.

**Check your result.** The read is allowed and expects 1,750 cents. The proposed write fails at permission and leaves the final read at 1,750 cents.

[Step-by-step course guide](../course-guides/automated-testing-with-umicom.md) · [Full course](../../courses/automated-testing-with-umicom/index.html) · [Small projects by course](index.md) · [First practice case](../practice/automated-testing-with-umicom.md)
