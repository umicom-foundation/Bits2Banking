<!--
Umicom Bits2Banking
File: content/simple-steps/extension/llm-from-scratch.md

PURPOSE:
Give learners an additional practical case for LLM from Scratch.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Compare a less confident prediction

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

Use two classroom probability vectors for the correct first token. They assign probabilities 0.80 and 0.40 to it.

1. Write the negative log loss for each assigned probability using the lesson’s definition.
2. Compare the two numbers and record which prediction receives the larger penalty.

**Check your result.** The approximate losses are 0.223 and 0.916. The less confident correct prediction receives the larger loss.

[Step-by-step course guide](../course-guides/llm-from-scratch.md) · [Full course](../../courses/llm-from-scratch/index.html) · [Extend a skill by course](index.md) · [First practice case](../practice/llm-from-scratch.md)
