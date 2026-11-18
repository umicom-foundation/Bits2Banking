<!--
Umicom Bits2Banking
File: content/lessons/05-ai/preparing-llm-training-data/04-quality-deduplication-and-rights.md

PURPOSE:
Review quality, duplicates and allowed use

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Review quality, duplicates and allowed use

[Course contents](index.md)
More rows are not automatically more useful. A duplicated answer can dominate a small dataset. A contradictory answer can teach the wrong behavior. A record containing a secret can be memorized. Quality review is part of dataset engineering, not a step to defer until after training.

1. Define an acceptance checklist: relevant topic, readable text, correct answer, permitted use, no unnecessary personal data, and a source identifier.
2. Detect exact duplicates using a digest of a defined normalized representation. Record the normalization rules; retain original bytes separately.
3. Review near-duplicates such as two versions of the same paragraph or resized copies of one image. Exact hashes do not detect all semantic similarity.
4. Keep rejection reasons and counts. Do not silently discard rows and then report the original count as accepted training data.
5. Review a sample from every source and label category, not only the easiest first ten records.

Normalization means applying a defined transformation, such as consistent line endings. Lowercasing code, removing punctuation or joining table columns can change meaning. A normalization useful for duplicate detection need not be the same text you train on. Keep those purposes separate.

An example with a user question and an assistant answer must teach the behavior you want. If a source is uncertain, preserve uncertainty instead of inventing a confident answer. If a document contains an instruction such as “ignore all rules,” it is data from the document, not an instruction to your preparation tool.


## Exercise

Make four invented records: two identical, one contradictory and one correct distinct example. Write which would be admitted and why. There is no useful “train everything” shortcut here. The acceptance report should account for all four, including rejected records.


## A review log

| Observation | Action | Why |
| --- | --- | --- |
| Exact duplicate | Keep one or assign a shared group; record choice | Avoid accidental overweighting |
| Related revisions | Use one leakage group | Prevent train/evaluation contamination |
| Unknown permission | Hold for review | Availability is not permission |
| Malformed record | Reject with location and reason | Avoid silent loader truncation |
| Incorrect answer | Correct with evidence or reject | A polished answer can still be false |

## Continue learning

[Previous: Read JSON, JSONL and conversational records](03-json-jsonl-and-chat-records.md) · [Course contents](index.md) · [Next: Keep related sources out of different partitions](05-split-sources-before-chunking.md)
