<!--
Umicom Bits2Banking
File: content/lessons/05-ai/preparing-llm-training-data/12-count-bytes-rows-and-source-groups.md

PURPOSE:
Count bytes, rows and source groups before tokenization

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Count bytes, rows and source groups before tokenization

[Course contents](index.md)
Before choosing a model, inspect what you actually have. A row is one example. A source group links examples that came from the same independent document, recording or other origin. A byte is one unit of stored data. A token is an item produced by a particular model tokenizer. These counts answer different questions; substituting one for another can produce poor evaluation splits or incorrect memory estimates.


## Work through three records on paper

~~~jsonl
{"source_id":"note-a","prompt":"p","completion":"c"}
{"source_id":"note-b","prompt":"","completion":"xyz"}
{"source_id":"note-a","prompt":"uv","completion":"cd"}
~~~

1. Draw one box per row. There are three boxes.
2. Label two boxes note-a and one note-b. There are two source groups, and the largest contains two rows.
3. Count the prompt bytes: p has 1, the empty string has 0, and uv has 2. The total is 3 and the longest is 2.
4. Count completion bytes: 1 + 3 + 2 = 6. The longest completion has 3 bytes.
5. Choose note-b for evaluation. You selected half the source groups, but only one third of the rows. Choosing note-a instead would put two thirds of the rows in evaluation.

A random group split preserves the group boundary; it does not promise an exact row percentage or balanced topics. If rows from one source are split apart, closely related passages can appear in both training and evaluation. That can make a model seem better at generalizing than it is. A grouping rule must be chosen before chunking, and must follow actual provenance rather than a different invented ID for each chunk.


## Use the shared native summary

~~~c
#include "umicom/ai/training/jsonl_summary.h"

UmiAiTrainingJsonlSummary summary = {0};
UmiAiTrainingJsonlReport report;
UmiStatus status = UmiAiTrainingJsonlSummarize(
    jsonl_bytes, byte_length, NULL, &summary, &report);
if (status == UMI_STATUS_OK) {
    /* summary.rows, sourceGroups and byte counts are complete. */
} else {
    /* summary is unchanged; report explains parsing progress. */
}
~~~

This is an API fragment: jsonl_bytes and byte_length stand for your readable input span. The complete runnable example is the Framework SDK examples/training_data project from the preceding lesson. It validates embedded original examples, prints two rows and two groups, then checks that malformed data cannot replace the previous complete summary. Use that project's existing CMake instructions and matching SDK. Merely copying a new header does not update an older library.

1. Open the SDK example main.c and locate UmiAiTrainingJsonlSummarize. Read the status check before the printing code.
2. Build the example with the matching SDK as described in lesson 11. Stop if configuration or compilation fails.
3. Run it and look for: Dataset: 2 rows; 2 source groups; largest group 1 rows.
4. Find the separate malformed-input example. Explain why report.failedLine can be 2 while the previous summary remains unchanged.
5. In a separate practice copy, assign the same source_id to both valid records. Update the example's expected sourceGroups to 1 and largestSourceGroupRows to 2. Rebuild and verify the changed prediction. Do not alter the library test expectations to hide unrelated failures.


## Understand Unicode and temporary storage

The letter é encoded as UTF-8 occupies two bytes even though it is one Unicode scalar. An emoji such as 🚀 occupies four UTF-8 bytes. The JSON escape text \u00e9 has six ASCII bytes in the file, but the decoded prompt contains two bytes. The summary counts decoded text, not escape spelling. A model may tokenize either example into one or several tokens; run its actual tokenizer after formatting its exact chat template.

The service copies only bounded source IDs for sorting, then clears and frees that temporary storage. It does not accumulate prompts or completions into another corpus. Identical decoded source IDs belong to one group, so a and \u0061 coincide. A and a remain different, and canonically equivalent Unicode spellings are not normalized automatically. This is grouping, not text deduplication, rights verification, training or a vector database.


## Recover from a refusal

On malformed JSON, inspect the reported line and correct the source record. On a capacity error, check whole-input, line, decoded-field and row limits separately. Do not silently truncate an answer. LF and Windows CRLF delimiters have the same record-size allowance; delimiter bytes still count toward the whole input size. Cancellation leaves the summary unchanged. Record the dataset identity, grouping rule and tokenizer version before using the counts in an experiment.


## Check your understanding

Why can 50% of source groups mean 33% of rows? Why does counting UTF-8 bytes not establish a model context length? Answers: groups have different sizes, and tokenization depends on the selected vocabulary and template. Neither changing JSON into a dictionary nor putting it in a vector database performs a training update.


## Continue practice

[Previous: Validate training records with native Framework code](11-read-jsonl-with-native-framework.md)

[Next: inspect a local file](13-inspect-a-local-jsonl-file.md)
