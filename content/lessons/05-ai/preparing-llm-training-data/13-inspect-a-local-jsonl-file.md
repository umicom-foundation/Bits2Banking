<!--
Umicom Bits2Banking
File: content/lessons/05-ai/preparing-llm-training-data/13-inspect-a-local-jsonl-file.md

PURPOSE:
Inspect a local JSONL file before choosing a trainer

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Inspect a local JSONL file before choosing a trainer

[Course contents](index.md)

## What you will practise

Earlier lessons introduced JSONL records and counted their decoded bytes. Now you will save two original examples in a real file and inspect that file through the native Umicom command. A command-line interface, or CLI, is a program you operate by typing a command and its arguments. An argument supplies a value such as a filename. This exercise validates one small teaching schema; it does not choose a model, tokenize text, build a vector database, change weights or send your data to a provider.


## 1. Check the command you are about to use

Use a matching Umicom Framework build that includes training-data inspect. In PowerShell, Get-Command identifies the executable selected by your current PATH. PATH is the list of directories searched for programs. If the command is not found, use the full path to the Umicom executable in your reviewed build or installed package. Do not assume that an older executable contains the command simply because its file is named umicom.exe. Run help before inspecting data.

~~~powershell
Get-Command umicom -ErrorAction Stop
umicom training-data --help
~~~


## 2. Create a small practice file

Choose a new practice directory, for example C:\umicom-learning\training. Make it in File Explorer. Open a plain-text editor and create corpus.jsonl inside it. JSONL means JSON Lines: one complete JSON object occupies each physical line. Copy the two lines below exactly, without Markdown fences. Save as UTF-8 without a byte-order mark, commonly called a BOM. A BOM is an optional encoding marker used by some editors; this strict reader rejects it. Avoid blank lines. A final line ending is allowed.

~~~json
{"source_id":"guide-1","prompt":"What is a compiler?","completion":"A program that translates source code."}
{"source_id":"guide-1","prompt":"","completion":"These two examples came from one teaching note."}
~~~


## 3. Identify every field

source_id names the original source group. Both examples came from the same invented teaching note, so both use guide-1. A different line is not automatically a different independent source. prompt is the input text presented before an answer; it may be empty in this teaching schema. completion is the desired answer text and must be nonempty. All three values are strings enclosed in double quotes. The reader accepts exactly these fields, rejects repeated keys and refuses extra fields. This is an explicit Framework teaching contract, not a universal format accepted by every fine-tuning service.


## 4. Inspect the file by its absolute path

An absolute path identifies a file from the filesystem root. On this Windows example it begins with C:\. Put quotes around paths, especially those containing spaces. The inspector requires an ordinary absolute local path and does not search directories, recurse through documents or accept a URL. It reads the selected file and leaves its bytes unchanged.

~~~powershell
umicom training-data inspect "C:\umicom-learning\training\corpus.jsonl"
~~~


## 5. Read the summary

Expect two rows, one source group, a largest group of two rows and one empty prompt. A row is an accepted record; a source group identifies related records. Prompt and completion sizes are measured after JSON escapes have been decoded into UTF-8 text. Byte counts are storage measurements. A model token is an element produced by that model's tokenizer, which may represent a word fragment or another unit. You cannot infer a model's exact token count or context-window fit from these byte totals. Use the selected model's tokenizer after preparing and reviewing the data.


## 6. Observe a controlled failure

Make a separate copy called broken.jsonl so the original remains available. In its second line replace the completion string with the number 42. Inspect broken.jsonl. The command should refuse it, reporting one accepted row and failed line 2. It must not print a successful aggregate summary for this incomplete dataset. The progress report explains where parsing stopped; it does not mean that training on the first row occurred. Restore the quoted string and inspect again.

1. Copy corpus.jsonl to a distinct broken.jsonl file.
2. Change only the second completion value to a number.
3. Run inspection and record the reported accepted-row count and failed line.
4. Restore the string value, rerun and explain why the result changes.


## 7. Recognise the bounds

The input file is limited to 16 MiB, meaning 16 times 1,048,576 bytes. A scan accepts at most 4,096 records. A decoded source ID is limited to 128 bytes; each prompt and completion is limited to 4,096 bytes. The raw JSON in a record may occupy at most 32,768 bytes. Escapes can use more raw bytes than their decoded text. A single LF or CRLF line ending is excluded from that record limit but included in the whole-file size. These bounds limit the operation's storage and work; they do not make an arbitrarily large document suitable for a model.


## 8. Know what happens to memory

Framework's platform service opens the selected regular file and checks its size before allocating its input buffer. The summary service then validates records and retains only bounded source IDs while calculating group counts. The successfully read input buffer is cleared before release. This does not erase the original file, operating-system caches or every intermediate allocation in the process. Cancellation is checked before reading and while parsing, but the synchronous file read itself is not interruptible. An interactive application should run this service on a worker so a slow filesystem does not block its interface.


## 9. Connect the CLI to your own C application

The CLI is a thin presentation layer over UmiAiTrainingJsonlInspectFile, declared in umicom/ai/training/jsonl_file.h. A C caller provides a summary object and a separate progress report. On failure, the summary remains unchanged; the report is initialized and describes progress when available. The caller must check the returned UmiStatus before using the summary. Reuse this service instead of writing another JSON parser in Umicom Media, Studio or a new application. The service does not retain the caller's objects after it returns.


## 10. Choose the next operation deliberately

A successful inspection proves the records meet this schema and its limits. It does not establish that the answers are correct, licensed, representative, free of sensitive content or independent of evaluation data. Review those questions separately. For retrieval, choose a chunking and embedding pipeline with source references. For supervised fine-tuning, choose the exact trainer, tokenizer, chat template and loss-mask convention. For continued pretraining, a text corpus may be more appropriate than question-answer pairs. A vector database stores representations for retrieval; it is not a replacement for a trainer's tokenized examples.


## Check your understanding

Explain why both rows have the same source ID. Describe how a newline escaped inside a JSON string differs from a physical line ending. Explain why inspection can fail after accepting one row while still leaving the summary unchanged. Finally, decide whether your intended application needs retrieval, fine-tuning or both, and list the additional evidence needed before starting either operation.


## Common results and what to do

| Result | Meaning | Next step |
| --- | --- | --- |
| Unknown command | The selected executable lacks this entry point | Check Get-Command and choose a matching build |
| Usage error, exit 2 | Arguments do not match inspect plus one file | Use help; no --train option exists |
| Input refused, exit 1 | Admission or record validation failed | Check absolute path, file type, encoding, bounds and failed line |
| Schema accepted, exit 0 | All records satisfy the strict teaching schema | Review quality and choose a model-specific conversion |

[Previous: count bytes and groups](12-count-bytes-rows-and-source-groups.md)

[Next: Turn reviewed source IDs into a reproducible partition](14-partition-jsonl-by-source.md)
