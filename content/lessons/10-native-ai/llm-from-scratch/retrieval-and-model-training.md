<!--
Umicom Bits2Banking
File: content/lessons/10-native-ai/llm-from-scratch/retrieval-and-model-training.md

PURPOSE:
Separate retrieval from model training

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
![Umicom](../../../assets/branding/umicom-logo.svg)

# Separate retrieval from model training

## Two different ways to use documents

Training changes model parameters by comparing predictions with targets and applying an optimization rule. Retrieval searches an existing collection and returns material that may help answer a question. A document can participate in either workflow, but a successful retrieval call does not show that a model learned anything. This module adds retrieval to your native AI knowledge without replacing the earlier decoder and checkpoint lessons.


Begin with C arrays, structures, pointers and status handling. The laboratory uses small original strings and hand-written vectors. No provider generates those vectors. This makes the arithmetic and ownership visible, but it cannot demonstrate semantic search quality. Read the laboratory README before compiling, then locate Lexical and Prepare in main.c.


## Observe a deterministic baseline

~~~c
size_t count = umi_ai_retrieval_rank(
    "target", chunks, 3U, results, 4U);
/* Read only results[0] through results[count - 1]. */
~~~


The lexical baseline searches for case-insensitive substring matches. In the example, one chunk contains target twice and another contains it once. The repeated match ranks first. This is useful for understanding how records become ordered candidates, although it is not a full language-aware search engine. Case folding uses the C locale rather than a complete Unicode linguistic model.


## Keep an explicit evidence boundary

A returned count describes how many result records were written. Zero can mean no match or refusal. The new validators let an application distinguish malformed input before requesting a rank. Do not display a green search-success message solely because a function returned zero; explain whether the input was admitted and whether any candidate matched.


Run the lexical scenario after qualifying the matching installed SDK. It first checks the expected order, then damages a later chunk in an isolated fixture and verifies that the previous output survives. A successful laboratory exit means its assertions held, including the expected refusal. It does not mean that the damaged chunk was accepted.


## Practice

Change the repeated text to a different word and predict the new order before running. Record the input strings, actual result IDs and Framework revision. Then write separate statements for storage admission, ranking behavior and model quality. Only the first two are exercised here; learned representations, answer generation and quality evaluation need their own data and experiments.


## Read and run the client

[Setup, expected output and troubleshooting](../../../../labs/native/framework-retrieval-ownership/README.md) · [C23 example source](../../../../labs/native/framework-retrieval-ownership/main.c).

## Continue learning

[Course contents](../../../courses/llm-from-scratch/index.html) · [Previous: Report checkpoint evidence clearly](report-checkpoint-evidence-and-limits.md) · [Next: Keep chunk identity and source ownership intact](retrieval-chunk-ownership.md)
