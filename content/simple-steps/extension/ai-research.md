<!--
Umicom Bits2Banking
File: content/simple-steps/extension/ai-research.md

PURPOSE:
Give learners an additional practical case for AI Research Frontiers — Architectures, Training, Data and Native Kernels.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Size a score matrix without running a model

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

Compare 256 and 512 tokens in an illustration that stores every dense attention score for four heads at two bytes per score.

1. Use the state-space comparison lesson's full square matrix. Multiply token count by itself, then by four heads.
2. Convert to bytes by multiplying by two. Record the memory ratio for the score arrays in isolation.

**Check your result.** The arrays hold 524,288 and 2,097,152 bytes. Doubling tokens makes this illustrated storage four times as large.

[Step-by-step course guide](../course-guides/ai-research.md) · [Full course](../../courses/ai-research/index.html) · [Extend a skill by course](index.md) · [First practice case](../practice/ai-research.md)
