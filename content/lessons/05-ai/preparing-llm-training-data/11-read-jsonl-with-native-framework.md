<!--
Umicom Bits2Banking
File: content/lessons/05-ai/preparing-llm-training-data/11-read-jsonl-with-native-framework.md

PURPOSE:
Validate training records with native Framework code

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Validate training records with native Framework code

[Course contents](index.md)
A data reader is a gate between an editable file format and a program. In this lesson the gate accepts a small, documented JSON Lines schema. It checks structure and bounds; it cannot decide whether an answer is true, whether a source is licensed or whether examples will improve a model. Those remain separate review steps.


## 1. Read one complete example

~~~json
{"source_id":"compiler-note","prompt":"What does a compiler do?","completion":"It translates source code into another executable form."}
~~~

The outer braces describe one object. The quoted names are keys. Each colon connects a key to its value. Commas separate fields. source_id records which original source produced this example; prompt is the model input; completion is the desired continuation. This teaching reader requires exactly these three string fields. It permits an empty prompt, but source_id and completion must contain at least one byte. A whitespace-only answer still requires human quality review.


## 2. Follow the memory ownership

~~~c
UmiAiTrainingPair pair;
UmiStatus status = UmiAiTrainingPairRead(
    json, json_length, NULL, &pair);
if (status != UMI_STATUS_OK) {
    /* Do not use pair: a failed read leaves it unchanged. */
    return 1;
}
/* pair now owns copies of the three decoded strings. */
~~~

json_length is a byte count, excluding a C string terminator. &pair passes the address of caller-owned storage. NULL means no cancellation token in this example. UmiStatus is an explicit result code. Test it before using output. The parser does not retain your input and does not return pointers into temporary JSON storage. If you use the multi-row visitor instead, each callback receives a borrowed pair that lasts only until that callback returns.


## 3. Build the provided consumer

1. Obtain a matching installed Framework SDK containing jsonl_pairs.h and the corresponding AI library. Follow the earlier SDK setup course if you do not yet have a compiler, CMake or Ninja.
2. Open the Framework examples/training_data directory. Read main.c before running commands. Its two original records are embedded in the program; it does not inspect your folders.
3. Set UMICOM_SDK_ROOT to the actual installed prefix. Run the commands below separately, stopping on an error.
4. Expect two accepted records, then a separate demonstration that rejects line 2 after one accepted row. No model is trained.
5. Read the example README for toolchain compatibility and a missing-header or undefined-symbol recovery path. Installed package qualification is distinct from focused source tests.

~~~powershell
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S . -B build -G Ninja -DUMICOM_SDK_ROOT=C:/SDK/Umicom
cmake --build build --parallel 2
ctest --test-dir build --output-on-failure
~~~


## 4. Try a controlled failure

In a separate learning copy, change a completion value from a quoted string to the number 42. Predict which line will fail before compiling. After the rejection, check acceptedRows, consumedBytes, failedLine and stage. The callback for an earlier valid line has already run. A visitor cannot reverse arbitrary actions performed by your callback; collect a candidate dataset and approve it only after the complete scan succeeds if your workflow requires all-or-nothing publication.


## 5. Explain the limits

Blank lines, a byte-order mark, duplicate decoded keys, unknown fields, malformed Unicode and multiline objects are rejected. Escaped \n inside a string decodes to a newline within the value. A decoded newline does not create another record. None of these checks finds near-duplicate documents or replaces a tokenizer, chat template, train/evaluation split or training objective.


## Check your understanding

1. Explain why a valid JSON object can still fail this schema.
2. Explain why a byte count does not tell you how many model tokens are present.
3. Explain why related rows need the same source group before partitioning.
4. Name the owner of the input bytes, a single-read output pair and a visitor callback pair.
5. Describe how your application would avoid publishing the first row if the second row is invalid.


## Reader limits and their meaning

| Limit | Purpose |
| --- | --- |
| 4,096 decoded bytes per prompt or completion | Bounds output records; it is not a model context limit |
| 128 source-ID bytes | Keeps provenance identifiers bounded |
| 32,768 bytes per physical line | Bounds parsing work and owned JSON input |
| 4,096 rows and 16 MiB per scan | Bounds one review operation; partition larger work deliberately |
| LF or CRLF records, optional final LF | Makes physical line numbers predictable |

[Previous: Evaluate changes and publish a reproducible dataset package](10-evaluate-and-publish-a-dataset.md)

## 6. Prepare a record in C

The example constructs a UmiAiTrainingPair and calls UmiAiTrainingPairWrite.
Framework escapes newlines inside strings and adds one real LF after the record.
The returned count includes LF and excludes NUL; capacity includes NUL.
Both caller output and count remain unchanged on failure. Read the result back
with UmiAiTrainingPairRead and compare the decoded answer. This checks the
representation contract, not model accuracy. Escaping can expand control-heavy
text beyond the line limit; revise the example deliberately instead of silently
truncating it. No dataset file is opened, replaced or uploaded by this API.

## Continue practice

[Next: Count bytes, rows and source groups before tokenization](12-count-bytes-rows-and-source-groups.md)
