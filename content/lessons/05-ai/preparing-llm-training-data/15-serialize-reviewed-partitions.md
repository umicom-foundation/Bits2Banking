<!--
Umicom Bits2Banking
File: content/lessons/05-ai/preparing-llm-training-data/15-serialize-reviewed-partitions.md

PURPOSE:
Turn reviewed partitions into complete JSONL buffers

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Turn reviewed partitions into complete JSONL buffers

[Course contents](index.md)
A partition assignment is a list of decisions: this row belongs to training, that row belongs to evaluation. A trainer normally needs the corresponding records, not just the decisions. In this lesson you will turn the reviewed assignment from lesson 14 into two complete JSONL strings by calling Umicom Framework from C. You will also see why producing valid text is different from saving a file, tokenizing it or training a model.


## 1. Understand the four objects you are handling

The input is the original sequence of JSONL bytes. A byte is one unit of computer storage; UTF-8 characters may occupy more than one byte. The membership array has one small integer for each input row: zero means training and one means evaluation. A result buffer is memory that your program provides for a selected side. A summary describes the successful result, including its row count and encoded length. Keep these objects separate so that a failed operation cannot accidentally replace the original dataset.

Imagine the input rows are note-a, note-b, note-a, note-c, in that order. If the reviewed membership is 0, 1, 0, 0, the training result contains rows 1, 3 and 4; evaluation contains row 2. Both note-a rows stay together. This particular membership illustrates the concept; it does not assert what every seed chooses. The real example obtains membership from the group partitioner rather than hard-coding a favorable assignment.


## 2. Read the function call

~~~c
char training[512];
UmiAiTrainingJsonlSelectionSummary selection;
UmiAiTrainingJsonlReport report;
UmiStatus status = UmiAiTrainingJsonlSelectionWrite(
    related, sizeof(related) - 1U,
    evaluation, partition.rows, 0U, NULL,
    training, sizeof(training), &selection, &report);
if (status != UMI_STATUS_OK) {
    return 1;
}
printf("Training: %zu rows, %zu bytes\n",
    selection.selectedRows, selection.outputBytes);
~~~

related is the character array introduced in the previous lesson. Its sizeof includes the final zero byte used to end a C string, so subtract one when describing the JSONL input. evaluation is the membership returned by JsonlPartition. partition.rows is the number of meaningful entries, not necessarily the capacity of the array. The 0U selects training; change that argument to 1U for evaluation. NULL means no cancellation token is supplied for this small synchronous exercise. training and sizeof(training) provide the destination and its capacity. The addresses written with & let Framework fill the summary and report.

The suffix U makes a numeric literal unsigned, which means it represents nonnegative values. It is not a unit such as bytes or rows; those meanings come from the parameter contract. %zu is the printf format for size_t, the C type used for lengths and counts. Do not replace it with %d when printing these fields.


## 3. Build and inspect the existing example

1. Complete lesson 14 and obtain a matching installed Framework SDK. This addition requires jsonl_selection.h and its corresponding implementation in Umicom::ai; an older library cannot be repaired by copying only a header.
2. Open examples/training_data/main.c in the Framework source. Find the four related records, the partition call and the two selection calls. The earlier validation and summary exercises remain in the file.
3. Open PowerShell in examples/training_data. Replace C:/SDK/Umicom with the real installed SDK prefix. Run the commands below separately and stop after an error.
4. Read the additional Selected JSONL output line. The example parses both resulting strings and checks that their row counts add to four. It does not print the complete dataset or save files.
5. Keep this result distinct from installed-package qualification on another computer. A focused source test does not establish that a separately installed SDK contains the same symbols or runtime dependencies.

~~~powershell
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S . -B build -G Ninja -DUMICOM_SDK_ROOT=C:/SDK/Umicom
cmake --build build --parallel 2
ctest --test-dir build --output-on-failure
~~~


## 4. Why are there two scans?

The service first validates the complete input and measures the selected encoded output. It then allocates exactly that output size plus one byte for the final zero terminator. A second scan writes into this private temporary buffer. Only after every fallible operation succeeds does Framework copy the result into your destination. This design trades another bounded parsing pass for a clear ownership guarantee: an allocation failure near the end cannot publish half of a dataset.

Allocation means asking the runtime for memory. Even a small allocation can fail, so a C function must handle the failure rather than assume that memory is unlimited. During export, temporary memory includes one maximum-size row buffer, the exact selected result and the bounded per-record parser/writer allocations. Your input and destination also occupy memory. This is a bounded synchronous operation for datasets up to the documented 16 MiB and 4096-row limits, not a streaming solution for a multi-terabyte training corpus.

All rows are validated, including unselected rows. Otherwise a malformed evaluation row might disappear silently when exporting training data, making two exports disagree about what the dataset contains. The membership count must match exactly. Every membership value must be zero or one. The overall UmiStatus determines success; a report whose parsing stage is COMPLETE can still accompany a later capacity, count or allocation failure.


## 5. Distinguish bytes from meaning

The exporter preserves each selected record’s decoded source_id, prompt and completion values and keeps their input order. It writes field names in a consistent order, separates records with LF and appends one C string terminator. Original spaces, CRLF line endings and JSON escape spellings can change. For example, a source written as a Unicode escape for the letter a is emitted as the same decoded a. Comparing the raw input and output byte-for-byte is therefore the wrong test for value preservation.

The outputBytes field includes the LF at the end of each record, but excludes the final zero terminator. Capacity includes that terminator. If the encoded dataset contains 200 bytes, the destination needs at least 201 bytes. A zero-row selection produces an empty C string and a zero byte count. A subsequent training workflow should normally reject an empty training set; the serializer itself does not decide that policy.


## 6. Practice failure recovery

1. In a learning copy of the example, reduce the training destination capacity to one byte. The call must fail when training contains records. Do not print the uninitialized buffer after failure. Restore its original size.
2. Initialize a destination with a recognizable marker before a deliberately invalid call. Verify that the marker is unchanged. This demonstrates preservation, not a usable new dataset.
3. Change a completion in an unselected row to a number. Export must still reject the input because every row is checked. Restore the string before proceeding.
4. Use a membership count that is one less than the row count. The call must refuse it. Supplying a shorter count does not mean silently selecting the first part of the dataset.
5. After a successful partition, reorder input rows without reordering membership. Explain why a serializer cannot infer that you paired the wrong decisions with the new order. Restore the exact reviewed input before calling it again.


## 7. Keep the two sides private until both succeed

One successful call publishes one memory result. Two calls are not one atomic transaction. If training serialization succeeds and evaluation serialization fails, the application must not advertise that both results are ready. The example retains both private buffers until both calls succeed, then checks them. For real file publication, use a separate reviewed workflow with explicit destinations and recovery behavior. Never open a valuable file with a truncating write merely because the first buffer was produced successfully.

The source, membership and output objects remain owned by the caller. They must be valid, separate objects and unchanged by other threads until the call returns. The function does not retain their pointers. Temporary selected text is cleared before release, but that does not erase the original file, every parser allocation, operating-system caches or your output buffers. Clear and free your own data when its lifetime ends according to your application’s needs.


## 8. Decide what comes after serialization

JSONL is a storage convention, not a complete training method. A model-specific adapter may convert prompt/completion pairs into a chat template. A tokenizer turns the resulting text into token IDs. A training collator groups examples and creates attention masks and loss labels. A trainer computes predictions, compares them with targets and updates weights. Evaluation measures behavior on data kept out of those updates. None of these model operations occurs in this exercise.

A vector database instead stores searchable representations, usually embeddings computed from text or other data. In retrieval-augmented generation, matching passages are retrieved and added to a model’s context. That can be useful without changing model weights. You do not need to convert every training document into a vector database first. Choose the workflow based on whether you need better retrieval of changing knowledge, a learned response pattern, a new task or another measurable outcome.

Before moving on, explain in your own words what would be lost if you shuffled membership independently of the rows. Explain why successful JSON validation does not prove that an answer is correct or licensed for training. Finally, write down the model, tokenizer, template, source policy and evaluation plan you would need before replacing this tiny exercise with a real training run.


## A complete preparation chain

| Step | Input | Output | What it proves |
| --- | --- | --- | --- |
| Review sources | Documents and permissions | Approved source records | A documented review decision |
| Partition groups | Validated rows and source IDs | Membership for each row | The requested exact-ID group rule |
| Serialize sides | Same rows plus membership | Canonical JSONL buffers | Complete schema-valid selected output |
| Tokenize | Model-formatted text | Token IDs and masks | A model-specific encoding |
| Train and evaluate | Tokens, model and settings | Measured model results | Only the outcomes actually tested |

[Previous: Turn reviewed source IDs into a reproducible partition](14-partition-jsonl-by-source.md)

[Next: Choose which predictions contribute to loss](16-choose-which-predictions-contribute-to-loss.md)
