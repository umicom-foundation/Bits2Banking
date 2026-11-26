<!--
Umicom Bits2Banking
File: content/simple-steps/apply/blockchain-ledgers.md

PURPOSE:
Give learners an additional practical case for Blockchain Technology and Distributed Ledgers — From First Principles.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Build a paper spending register

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A toy output-based ledger starts with one unspent output O9 worth 8 units. A transfer spends O9 and creates output O10 for 3 units and O11 for 5 units.

1. Draw the before and after unspent-output lists. Place a line from the spending transaction to the output it consumes.
2. Add a later attempt to spend O9 again. Write which output references can still be used in the exercise.

**Check your result.** The first transfer spends O9 and leaves O10 and O11 with a combined value of 8 units. The second attempt is refused because O9 is already spent.

[Step-by-step course guide](../course-guides/blockchain-ledgers.md) · [Full course](../../courses/blockchain-ledgers/index.html) · [Small projects by course](index.md) · [First practice case](../practice/blockchain-ledgers.md)
