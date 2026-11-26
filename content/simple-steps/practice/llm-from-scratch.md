<!--
Umicom Bits2Banking
File: content/simple-steps/practice/llm-from-scratch.md

PURPOSE:
Give learners an additional practical case for LLM from Scratch.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Read a short vocabulary without shifting IDs

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

Define IDs 0, 1 and 2 as `start`, `room` and `open` in a toy model exercise.

1. Write the IDs for the phrase `room open`. Decode them using the same map.
2. Add a new word to the end of a copy of the vocabulary. Repeat the encoding of the original phrase.

**Check your result.** The phrase is 1 then 2. Appending a new entry preserves those earlier identities.

[Step-by-step course guide](../course-guides/llm-from-scratch.md) · [Full course](../../courses/llm-from-scratch/index.html) · [Practice by course](index.md)
