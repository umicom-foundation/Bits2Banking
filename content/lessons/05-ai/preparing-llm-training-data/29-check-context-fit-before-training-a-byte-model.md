<!--
Umicom Bits2Banking
File: content/lessons/05-ai/preparing-llm-training-data/29-check-context-fit-before-training-a-byte-model.md

PURPOSE:
Check context fit before training a byte model

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Check context fit before training a byte model

[Previous lesson](28-find-repeated-pairs-across-training-and-evaluation.md)

[Course contents](index.md)

## What this lesson answers

A dataset can be well-formed and still contain examples that are too long for a model. Before training, you need to know how examples become token positions, which positions contribute to the learning objective, and what happens when they do not fit. This lesson uses the small native Umicom byte decoder to make those quantities concrete. It does not ask you to download a large model or start a paid service. You will inspect three synthetic records, calculate the expected totals, run a C SDK example, and decide how to investigate overlong records.


## A short vocabulary


| Term | Meaning |
| --- | --- |
| Context length | The number of token positions reserved for one processed example. |
| Token | An integer identifier presented to the model; its meaning depends on the tokenizer. |
| BOS and EOS | Reserved beginning-of-sequence and end-of-sequence markers. |
| Prediction row | One input position paired with the next token that it should predict. |
| Selected row | A prediction included in the learning objective. |
| Padding | Unused positions filled consistently so examples have the requested shape. |
| Truncation | Removing part of an example to make it shorter. It changes the data and requires an explicit policy. |


## Do not choose a storage format by guessing

JSONL is a convenient storage format: each physical line contains one JSON object. A vector database is an index for retrieving similar items; it is not a mandatory format for fine-tuning. A dictionary or key/value object describes fields but does not define the model objective. For this exercise, each object has exactly source_id, prompt and completion strings. The reader validates that teaching schema. A later conversion maps the strings into the selected model format. Other trainers may require role-based message arrays, images plus captions, or different fields.


## Write three original records

These tiny strings are deliberate arithmetic fixtures, not useful instruction-tuning data. An empty prompt is permitted. Every completion is nonempty. The IDs identify three independent source examples for this exercise. In real work, preserve meaningful source identities so related chunks can stay in one partition; a source ID supplied by an author is not proof of permission to train on it.

~~~json
{"source_id":"one","prompt":"p","completion":"c"}
{"source_id":"two","prompt":"","completion":"xyz"}
{"source_id":"three","prompt":"long","completion":"reply"}
~~~


## Understand this tokenizer before counting

Umicom’s teaching byte tokenizer assigns an ID to each byte and reserves additional IDs for special markers. A UTF-8 letter can occupy more than one byte, so it may occupy several tokens in this format. The current native decoder has a maximum context of 32 rows. Those two facts belong to this implementation. They are not claims about the tokenization or context capacity of a pretrained model such as one loaded from a GGUF file. Always use that model’s actual tokenizer and prompt template when preparing its training data.


## Derive the extra row

The prepared stream is BOS, prompt bytes, completion bytes, EOS. Inputs and targets are adjacent elements: each input predicts the following token. If there are P prompt bytes and C completion bytes, the stream contains P + C + 2 tokens. There is one fewer adjacent pair than tokens, so it creates P + C + 1 prediction rows. The last prediction is EOS. Completion-only supervision selects C + 1 rows, including that final prediction. Prompt targets are excluded from the objective, but prompt inputs can still influence later predictions.

~~~text
Stream:  BOS   p   c   EOS
Inputs:  BOS   p   c
Targets:   p   c   EOS
Selected:  0   1     1
~~~


## Calculate the fixture by hand

Choose context length four. Records one and two fit; record three does not. The first fitting record needs one padding row and the second needs none. The longest requirement is ten, the shortest is three, and all records together require seventeen rows before any fit decision. This last sum is not the number of rows the fitting subset contributes.


| Record | Prompt bytes | Completion bytes | Required prediction rows | Selected rows if it fits |
| --- | --- | --- | --- | --- |
| one | 1 | 1 | 3 | 2 |
| two | 0 | 3 | 4 | 4 |
| three | 4 | 5 | 10 | 6 |


## Keep the denominators visible

Here fittingValidRows plus fittingPaddingRows equals fittingRecords times contextLength: 7 + 1 = 2 times 4. Selected rows are a subset of valid rows, not an additional allocation. Never present a percentage without explaining which records or positions form its denominator.


| Summary field | Expected value | What it includes |
| --- | --- | --- |
| records | 3 | Every valid record in the completed scan |
| fittingRecords | 2 | Examples requiring at most four rows |
| overlongRecords | 1 | Examples requiring more than four rows |
| firstOverlongLine | 3 | One-based location of the first overlong record |
| requiredRows | 17 | All examples, including the overlong one |
| fittingValidRows | 7 | Only real prediction rows in fitting examples |
| fittingSelectedRows | 6 | Only objective-selected rows in fitting examples |
| fittingPaddingRows | 1 | Only unused positions in fitting examples |


## Build the SDK consumer

1. Obtain an installed Framework SDK containing jsonl_context.h and its matching Umicom::ai implementation. A header copied into an older SDK cannot provide a missing library function.
2. Open PowerShell in the SDK training_data example directory. Keep the existing main.c example and the new context.c example together with their CMakeLists.txt.
3. Use a compiler and runtime compatible with the installed SDK. For a UCRT64 package, select the matching UCRT64 tools.
4. Replace C:/SDK/Umicom below with the absolute path of your actual installed package. Run each command separately and stop on an error.

~~~powershell
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S . -B build -G Ninja -DUMICOM_SDK_ROOT=C:/SDK/Umicom
cmake --build build --target umicom-sdk-training-context --parallel 2
ctest --test-dir build -R sdk.training-data.context --output-on-failure
& .\build\bin\umicom-sdk-training-context.exe
~~~


## Read the output without overclaiming

The example prints context four, three records, two fitting records, one overlong record at line three, seventeen total required rows, seven fitting valid rows, six fitting selected rows and one fitting padding row. Its final line says that inspection only was performed. No text is truncated and no model is trained. A successful test of current source objects is separate from successful resolution of an installed SDK package. If the linker reports an undefined function, confirm that the selected package contains the implementation instead of weakening the example.


## Inspect your saved file with the native CLI

1. Create a learning folder and save the three records shown earlier as corpus.jsonl using UTF-8 without a byte-order mark. Keep one object on each physical line. A newline inside a JSON string must be escaped, not inserted as a new physical record.
2. Use an absolute path beginning with a drive letter on Windows. A relative path depends on the current directory and is refused by this service.
3. Use a current Framework CLI that lists the context subcommand in training-data help. A source edit does not automatically rebuild your installed executable.
4. Run the command below, then inspect its exit status immediately. The number four is a context length, not a batch size or a memory budget.

~~~powershell
umicom training-data --help
umicom training-data context "C:\umicom-learning\training\corpus.jsonl" 4
$LASTEXITCODE
~~~


## Interpret success and refusal correctly

Exit zero means that the full inspection completed. The fixture still has one overlong record; zero does not approve it for training. Exit one means that file admission or parsing failed. Exit two means the command usage or context argument was invalid. The command prints only aggregate counters and numeric progress, not the path, source IDs or text. The file is not rewritten. The context accepts decimal integers from one through thirty-two; do not use a sign, decimal point, hexadecimal prefix or surrounding spaces. If a later record is malformed, no partial complete summary is printed.


## File buffers have a lifetime too

The C file service UmiAiTrainingJsonlInspectContextFile reuses the same in-memory inspection after a bounded regular-file read. Its owned input buffer is cleared and freed after inspection. That does not erase the original file, operating-system caches or every parser temporary. The synchronous read is not interruptible by its cancellation token; cancellation is checked before reading and during parsing. An interactive application should call it on a worker, keep the borrowed path and output objects alive, and report completion on the appropriate interface thread.


## Follow the native C ownership boundary

This fragment uses the records string from the complete context.c example. sizeof minus one excludes the final C string terminator, not a JSONL data byte. NULL means no cancellation token was supplied. The input is borrowed for the synchronous call and remains unchanged. The summary and progress report are separate caller-owned objects. The shared parser temporarily owns decoded record storage; the audit keeps only fixed-size counters, not a second corpus or token matrix.

~~~c
#include "umicom/ai/training/jsonl_context.h"

UmiAiTrainingJsonlContextSummary summary;
UmiAiTrainingJsonlReport report;
UmiStatus status = UmiAiTrainingJsonlInspectContext(
    records, sizeof records - 1, 4, NULL, &summary, &report);
if (status == UMI_STATUS_OK) {
    /* Review summary.overlongRecords before selecting a training policy. */
}
~~~


## Count decoded bytes, not escape spelling

The JSON spelling backslash-u-0-0-e-9 occupies six source characters, but after decoding it represents the character é, which occupies two UTF-8 bytes. A rocket emoji occupies four UTF-8 bytes. With that letter as prompt and that emoji as completion, this native byte format needs 2 + 4 + 1 = 7 rows. It fits context seven exactly and is overlong at six. Raw JSON length would give the wrong answer. A subword tokenizer might produce a different count again.


## Overlong is not the same as malformed

A valid record needing ten rows can be inspected even when the chosen context is four. The audit counts it and continues. A malformed JSON object is different: the scan returns an error and does not publish any new summary. The progress report may say that earlier records were accepted before the failure, but that does not make the prefix a complete approved dataset. Correct or explicitly exclude the bad input in a reviewed preparation step, then rescan the intended full dataset.


## Choose a policy deliberately

1. Locate the first overlong example and inspect whether its prompt and answer are coherent.
2. Check whether the chosen model and tokenizer are appropriate; do not enlarge context past documented limits.
3. If a document can be divided into independent examples, preserve source provenance and keep related pieces in the same partition.
4. If truncation is necessary, define which content may be removed and how incomplete answers are prevented. Do not silently truncate inside a reader.
5. Recheck the distribution after conversion. A dataset with many discarded long answers may teach a different task than intended.
6. Evaluate the resulting model on separately held-out sources; fit alone does not measure learning quality.


## Why fit does not prove memory safety

A context-fit check establishes a shape condition, not an allocation budget for every operation. Attention matrices, parameters, gradients, optimizer state, batches and temporary buffers all consume memory. The native teaching decoder also has tensor and vocabulary limits. Increasing context may increase some costs quadratically. Use the existing capacity planning and bounded allocation services, then measure an actual workload. Rewriting a program in C does not automatically prevent leaks, invalid pointer access or excessive model memory use.


## Boundary exercises

1. Change the selected context to three. Predict the fitting record count, valid-row total and padding total before running.
2. Use context one. Explain why every nonempty completion is overlong even though the inspector can successfully finish the scan.
3. Put malformed JSON after a valid record. Explain why the caller must not read a newly computed complete summary.
4. Explain why converting documents into vectors does not remove the need for tokenizer-specific training preparation.
5. Describe which held-out source groups you would use to assess whether a fine-tuned model improved, rather than memorized its training examples.


## What remains outside this exercise

This lesson does not train or fine-tune a production model, implement a pretrained tokenizer, upload data, certify training rights or establish a memory benchmark. It supplies an inspectable C preparation step and a complete small SDK consumer. For an actual fine-tuning run, combine reviewed provenance, model-specific formatting, leakage checks, explicit masks, resource admission and evaluation evidence.


[Next: Stream records without retaining the whole file](30-stream-records-without-retaining-the-whole-file.md)
