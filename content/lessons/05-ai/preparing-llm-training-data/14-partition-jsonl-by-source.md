<!--
Umicom Bits2Banking
File: content/lessons/05-ai/preparing-llm-training-data/14-partition-jsonl-by-source.md

PURPOSE:
Turn reviewed source IDs into a reproducible partition

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Turn reviewed source IDs into a reproducible partition

[Course contents](index.md)
An evaluation set is a collection of examples kept out of training so that you can measure behavior on material the model did not train on. A partition is the assignment of each example to a side. If two examples came from the same original document, placing one on each side can leak very similar information into evaluation. The earlier source-splitting lesson explained the idea. This lesson applies it directly to JSONL records through Umicom Framework’s native C service.


## 1. Identify the source before thinking about random numbers

Imagine three notes called note-a, note-b and note-c. You turn note-a into two question-and-answer rows, and the other notes into one row each. There are four rows but only three source groups. A source_id identifies the original group you chose. It is not a claim that Framework checked the document, a filename that the service opens, or a cryptographic proof of ownership. Decide those identities before generating chunks and keep them stable in your reviewed dataset.

~~~jsonl
{"source_id":"note-a","prompt":"a1","completion":"one"}
{"source_id":"note-b","prompt":"b1","completion":"two"}
{"source_id":"note-a","prompt":"a2","completion":"three"}
{"source_id":"note-c","prompt":"c1","completion":"four"}
~~~

The short prompts and completions above make the grouping visible; they are not useful language-model training examples. JSONL means that each physical line contains one complete JSON value. Our teaching schema accepts exactly source_id, prompt and completion as strings. The real newline separates records. An escaped newline inside a string is part of that field and does not create an extra row.


## 2. Read the C call one argument at a time

~~~c
unsigned char evaluation[4] = {0};
UmiAiTrainingJsonlPartitionSummary partition;
UmiAiTrainingJsonlReport report;
UmiStatus status = UmiAiTrainingJsonlPartition(
    related, sizeof(related) - 1U,
    1U, 42U, NULL,
    evaluation, sizeof(evaluation), &partition, &report);
if (status != UMI_STATUS_OK) {
    /* Do not use a new assignment: none was published. */
    return 1;
}
/* evaluation[i] is 0 for training or 1 for evaluation. */
~~~

related is the C character array containing the four lines. sizeof(related) includes its final zero terminator, so subtracting one passes only the JSONL bytes. The first 1U selects one source group for evaluation. 42U is the seed: an integer that makes the shuffle reproducible. NULL means that this small synchronous exercise has no cancellation token. evaluation is your output array, and sizeof(evaluation) is its capacity in bytes. The two addresses beginning with & let the function fill your summary and parser report. Check the returned status before reading a newly produced result.

A membership byte belongs to the row at the same position in the input. The two note-a rows must receive the same byte. Do not sort the input afterward while keeping the old byte array without the matching row identities. The summary reports the row count, source group count, training row count and evaluation row count. It does not retain prompt text, source strings or a model.


## 3. Build the existing SDK example

1. Use the setup from lesson 11 and select a matching installed Umicom Framework SDK. This extension needs jsonl_partition.h and the corresponding implementation in the AI library.
2. Open Framework examples/training_data/main.c. Find the related array and compare it with the four records above. The example keeps its earlier parser, writer and summary demonstrations.
3. From examples/training_data, configure, build and test with the commands below. Replace C:/SDK/Umicom with your real SDK prefix. Run each command separately and stop on failure.
4. Expect the existing record-validation messages followed by a Source partition line reporting training and evaluation row counts and confirming that related rows stayed together. The counts sum to four.
5. If the header is missing or a symbol cannot be linked, the selected SDK is too old or incomplete for this example. Rebuild and qualify the matching SDK through its normal process; do not bypass package identity checks.

~~~powershell
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S . -B build -G Ninja -DUMICOM_SDK_ROOT=C:/SDK/Umicom
cmake --build build --parallel 2
ctest --test-dir build --output-on-failure
~~~

These commands build an installed-package consumer. Focused tests of Framework source files are a separate form of evidence and cannot establish that your installed SDK contains the same code, exports or runtime dependencies. The exercise performs no training, uploads or dataset-file changes.


## 4. Understand the stable part of a seeded result

Framework decodes the source strings, sorts exact names into numeric ranks and calls its existing group splitter. It does not replace strings with a short hash, so a hash collision cannot accidentally combine unrelated names. Reordering rows or repeating an existing source does not change which groups are selected when the set of source names, seed and requested evaluation-group count stay the same. Adding or removing a source changes that set and may change the assignment. A seed alone is not a complete experiment record.

For reproducibility, record the dataset revision, the source-group policy, the actual assignment and the splitting algorithm version alongside the seed. A source named a and a JSON escape that decodes to the same a are one identity. Uppercase A is different. Unicode text that looks identical can have different byte representations; this API does not normalize them for you. Normalize and review identifiers consistently before calling it if your dataset requires that rule.


## 5. Observe rejection without a partial assignment

1. In a separate learning copy, make the second completion a number instead of a string. The parser should reject that row. Membership and summary outputs remain unchanged. The report identifies parser progress.
2. Restore the string. Reduce output capacity from four bytes to three. All records may parse, but the operation must refuse to publish an assignment that cannot fit.
3. Restore capacity. Set the requested evaluation group count to three. There are only three groups, so none would remain for training; the request must be rejected.
4. Restore one evaluation group. Reorder the four rows and check the assignment by source identity, not by old row position.
5. Repeat note-a many times. Observe that the group count remains three while the row counts change. Explain why a one-third group holdout need not contain one-third of the rows.


## 6. Decide what this operation does not establish

A complete parser report means parsing finished, not that a later grouping operation necessarily succeeded. Always use UmiStatus as the overall result. Output stays unchanged on allocation failure, invalid group counts, insufficient capacity and observed cancellation. Temporary source names are bounded and cleared before release. Sorting and the bounded splitter are synchronous; cancellation is checked around them, not inside every comparison.

This method does not detect near-duplicate documents with different IDs, balance label distributions, hold out future dates or evaluate a model. For time-dependent financial examples, a chronological holdout may be more appropriate than a shuffled group split. For videos, keep related frames and clips together according to a reviewed source policy. For image collections, inspect repeated subjects and near-duplicates. Choose the evaluation design for the question you want to answer before choosing a convenient random split.

Before continuing, explain why two rows with identical prompt text but different source IDs can still leak information across sides. Then explain why a syntactically valid, perfectly partitioned file can contain incorrect or unlicensed answers. A reliable training workflow combines structural checks, provenance review, an appropriate evaluation design and measured model behavior.


## Keep the units separate

| Quantity | In this example | Meaning |
| --- | --- | --- |
| Rows | 4 | Individual question-and-answer records |
| Source groups | 3 | Original-note identities |
| Evaluation groups | 1 | How many entire groups are held out |
| Evaluation rows | 1 or 2 depending on selected group | An outcome, not the requested group count |
| Model tokens | Not measured | Requires the selected model tokenizer |

[Previous: Inspect a local JSONL file before choosing a trainer](13-inspect-a-local-jsonl-file.md)

[Next: Turn reviewed partitions into complete JSONL buffers](15-serialize-reviewed-partitions.md)
