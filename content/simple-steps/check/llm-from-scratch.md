<!--
Umicom Bits2Banking
File: content/simple-steps/check/llm-from-scratch.md

PURPOSE:
Give learners an additional practical case for LLM from Scratch.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check a repeatable toy token round trip

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

Use the course vocabulary exercise with a known phrase and a phrase containing its out-of-vocabulary example.

1. Record what the encoder accepts from the known phrase. Encode then decode using the original vocabulary identity.
2. Exercise the unknown input separately and check the documented fallback identifier or refusal result.

**Check your result.** The known phrase round trips using the recorded tokens. The unknown observation uses the chosen fallback or refusal and has no invented token ID.

[Step-by-step course guide](../course-guides/llm-from-scratch.md) · [Full course](../../courses/llm-from-scratch/index.html) · [Acceptance checks by course](index.md) · [First practice case](../practice/llm-from-scratch.md)
