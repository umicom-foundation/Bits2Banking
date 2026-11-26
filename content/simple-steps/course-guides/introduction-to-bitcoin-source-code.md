<!--
Umicom Bits2Banking
File: content/simple-steps/course-guides/introduction-to-bitcoin-source-code.md

PURPOSE:
Provide practical first steps and a result to check for Introduction to Bitcoin Source Code.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Introduction to Bitcoin Source Code

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

1. Use the lesson’s linked Bitcoin Core v28.0 source. Write down the tag so someone else can inspect the same files. [A source map and a fixed version](../../lessons/14-blockchain-ledgers/introduction-to-bitcoin-source-code/01-a-source-map-and-a-fixed-version.md)
2. Read `src/primitives/transaction.h`. Draw how an input refers to an earlier transaction and output position. [Inputs, outputs and data types](../../lessons/14-blockchain-ledgers/introduction-to-bitcoin-source-code/02-inputs-outputs-and-data-types.md)
3. Read `CheckTransaction` in `src/consensus/tx_check.cpp`. Mark which collection the function checks for emptiness first and which rule checks outputs. [Reading rejection paths](../../lessons/14-blockchain-ledgers/introduction-to-bitcoin-source-code/03-reading-rejection-paths.md)

**Check your result.** Your notes name the tag, the input reference fields and a source location for the empty-output rule.

[Continue in the full course](../../courses/introduction-to-bitcoin-source-code/index.html) · [All course guides](index.md)
