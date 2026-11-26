<!--
Umicom Bits2Banking
File: content/simple-steps/course-guides/preparing-llm-training-data.md

PURPOSE:
Provide practical first steps and a result to check for Preparing Data for LLM Training.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Preparing Data for LLM Training

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

1. Write one task that the system should learn or look up. Choose retrieval or training based on whether the facts will change. [Choose retrieval, fine-tuning or training from scratch](../../courses/preparing-llm-training-data/lessons/01-choose-retrieval-or-training.html)
2. Make raw, reviewed and reports folders. Use a document you authored and record which copy produced each reviewed line. [Turn documents into reviewed text without losing provenance](../../courses/preparing-llm-training-data/lessons/02-turn-documents-into-reviewed-text.html)
3. Save a tiny JSONL dataset and keep records with the same source group together when assigning training and evaluation examples. [Keep related sources out of different partitions](../../courses/preparing-llm-training-data/lessons/05-split-sources-before-chunking.html)

**Check your result.** Every reviewed row points back to a source, and related records appear in one data partition only.

[Continue in the full course](../../courses/preparing-llm-training-data/index.html) · [All course guides](index.md)
