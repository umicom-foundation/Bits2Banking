<!--
Umicom Bits2Banking
File: content/simple-steps/compare/llm-from-scratch.md

PURPOSE:
Give learners an additional practical case for LLM from Scratch.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Compare two toy vocabulary policies

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

One toy vocabulary divides `doors` into `door` plus `s`. The other assigns `doors` a single entry.

1. Write both token sequences using the two separate mappings. Record each sequence length and mapping identity.
2. Decode both using their own maps and compare whether they recover the same word.

**Check your result.** The sequences have lengths two and one. They can both decode to `doors` using the appropriate mapping.

[Step-by-step course guide](../course-guides/llm-from-scratch.md) · [Full course](../../courses/llm-from-scratch/index.html) · [Compare two approaches by course](index.md) · [First practice case](../practice/llm-from-scratch.md)
