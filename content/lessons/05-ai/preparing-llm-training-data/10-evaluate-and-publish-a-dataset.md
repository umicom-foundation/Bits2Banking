<!--
Umicom Bits2Banking
File: content/lessons/05-ai/preparing-llm-training-data/10-evaluate-and-publish-a-dataset.md

PURPOSE:
Evaluate changes and publish a reproducible dataset package

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Evaluate changes and publish a reproducible dataset package

[Course contents](index.md)
Evaluation asks whether a model change helps the intended task without unacceptable regressions. A lower training loss alone cannot answer that. Use examples the training process did not consume, and record how you score them. For a coding assistant, valid syntax, behavior and source attribution may matter separately.

1. Keep a baseline model and run the same held-out cases before fine-tuning.
2. Define observable criteria: factual correctness, required output format, valid citations, refusal of unknown facts where appropriate, latency and memory.
3. Compare the candidate with the baseline using the same decoding settings and environment. Record failures as well as successes.
4. Inspect examples manually, especially where an aggregate score hides a serious error.
5. Package the reviewed dataset, schema, source permissions, split membership, transformation manifest, checksums and a short dataset card describing scope and limits.
6. Keep private or restricted originals separate from any public release. Publish only what its permissions allow.

A dataset card explains what the examples represent, how they were collected or authored, what preprocessing occurred, and what uses remain unsupported. A checksum helps detect byte changes. It does not establish legal permission, correctness or privacy. Keep those review results as separate fields.

A final test set should not become a tuning set through repeated inspection and adjustment. If you use its results to choose settings, acknowledge that and reserve new independent evaluation. Finance data may also need chronological and entity separation; medical examples need domain review. The grouped splitter is useful infrastructure, not a complete evaluation policy.


## Capstone

Create a six-record invented corpus with four source groups. Explain its schema, make a two-way grouped partition, validate every row, and write a dataset card. Then describe the additional work needed before any real model training. Success in this course is a traceable, inspected preparation workflow, not a claim to have trained a production assistant.


## Continue learning

[Previous: Choose a fine-tuning method and save recoverable state](09-fine-tuning-adapters-and-checkpoints.md) · [Course contents](index.md)

[Next: Validate training records with native Framework code](11-read-jsonl-with-native-framework.md)
