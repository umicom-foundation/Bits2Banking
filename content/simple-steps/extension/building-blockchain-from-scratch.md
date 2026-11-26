<!--
Umicom Bits2Banking
File: content/simple-steps/extension/building-blockchain-from-scratch.md

PURPOSE:
Give learners an additional practical case for Building Blockchain from Scratch.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Resume a replay from an earlier checkpoint

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A classroom ledger snapshot starts with 20 units before events 7 and 8. The accepted records debit 3 and 5 units respectively. A later record 9 is still only a proposal.

1. Replay events 7 and 8 in order. Record the resulting balance and the last accepted sequence after each.
2. Write the new checkpoint using the balance and last sequence. Keep the later proposal in its own column.

**Check your result.** Event 7 leaves 17 units and event 8 leaves 12. The new checkpoint contains balance 12 and sequence 8. Event 9 remains outside the replay.

[Step-by-step course guide](../course-guides/building-blockchain-from-scratch.md) · [Full course](../../courses/building-blockchain-from-scratch/index.html) · [Extend a skill by course](index.md) · [First practice case](../practice/building-blockchain-from-scratch.md)
