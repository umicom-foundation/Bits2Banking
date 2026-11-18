<!--
Umicom Bits2Banking
File: content/lessons/05-ai/preparing-llm-training-data/03-json-jsonl-and-chat-records.md

PURPOSE:
Read JSON, JSONL and conversational records

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Read JSON, JSONL and conversational records

[Course contents](index.md)
JSON represents values using objects, arrays, strings, numbers, true, false and null. An object contains named fields between braces. An array contains ordered values between square brackets. JSONL stores one complete JSON value per line. It is convenient for processing records incrementally, but a file extension alone does not establish a valid schema.

~~~jsonl
{"id":"demo-1","group_id":100,"text":"A byte contains eight bits."}
{"id":"demo-2","group_id":200,"text":"A compiler translates a source program."}
~~~

1. Save these two lines as corpus.jsonl in a text editor using UTF-8. Keep each record on one line.
2. Identify the three field names in the first object. id is a string; group_id is a number; text is a string.
3. If a string needs a newline, encode it as \n within the JSON string rather than inserting a physical line break into the record. Escape an embedded quotation mark as \".
4. Open the file with a JSONL-aware validator or parse each line separately. A single JSON parser applied to the whole file may reject two adjacent objects because they are not one JSON document.

Continued pretraining may consume a text field. A supervised chat trainer may consume a messages array with role and content. A preference trainer may need chosen and rejected alternatives. Do not rename fields by guesswork: read the selected trainer’s documented format and validate a tiny batch before a long run.

~~~jsonl
{"messages":[{"role":"user","content":"How many bits are in a byte?"},{"role":"assistant","content":"Eight bits."}]}
~~~

This is a common conversational representation, not a universal model file. The tokenizer’s chat template later turns roles and content into the token sequence expected by that model. A schema can include metadata that the loader ignores, or accidentally train on metadata if a formatting function concatenates every field. Inspect the final formatted sample.


## Check

A dictionary is an in-memory name/value collection in some languages. A JSON object is a serialized representation. Neither is a vector database. The two formats solve storage and structure problems; they do not decide what the model should learn.


## Further reading

- [TRL dataset formats source documentation](https://github.com/huggingface/trl/blob/main/docs/source/dataset_formats.md)

## Continue learning

[Previous: Turn documents into reviewed text without losing provenance](02-turn-documents-into-reviewed-text.md) · [Course contents](index.md) · [Next: Review quality, duplicates and allowed use](04-quality-deduplication-and-rights.md)
