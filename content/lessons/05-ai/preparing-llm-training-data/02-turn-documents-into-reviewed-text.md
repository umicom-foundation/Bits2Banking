<!--
Umicom Bits2Banking
File: content/lessons/05-ai/preparing-llm-training-data/02-turn-documents-into-reviewed-text.md

PURPOSE:
Turn documents into reviewed text without losing provenance

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Turn documents into reviewed text without losing provenance

[Course contents](index.md)
A dataset is a collection of examples used by a program. Provenance is a record of where each example came from and what happened to it. Begin with material you own or have permission to use. This course supplies invented examples so you can learn without collecting personal or proprietary records.

1. Create separate raw, reviewed and reports folders inside an empty practice directory. Raw means unchanged originals; reviewed means text approved for the next step.
2. Copy a small document you created into raw. Record a stable source identifier, a content digest and its usage permission in a manifest. A digest is a compact fingerprint of bytes, not a privacy guarantee.
3. Extract readable text into reviewed using a format-appropriate tool. A scanned PDF may need optical character recognition, or OCR, which guesses text from pixels.
4. Compare the extraction with the original. Check reading order, headings, table columns, code indentation, equations, accents and repeated page headers.
5. Keep a record of corrections and the extraction tool/version. Never overwrite the only original.

UTF-8 is a way to encode Unicode characters as bytes. A text file containing accented names is not necessarily one byte per character. A PDF is a structured container; feeding its binary bytes as ordinary training text creates noise. HTML may contain navigation, scripts and repeated menus that are not the teaching content you want.

~~~text
source_id: handbook-demo
source_revision: authored-example-1
permission: original teaching text
raw_file: raw/handbook.txt
reviewed_file: reviewed/handbook.txt
group_id: 100
review_state: accepted
~~~

These labels illustrate metadata. They are not a required trainer schema. Keep source identity outside the prose unless the chosen task intentionally teaches citations. A path in a record must be resolved against a defined dataset root; do not allow an imported record to request arbitrary files on the computer.


## Exercise and answer

Imagine OCR changes “do not delete” into “do delete.” A valid UTF-8 file and a passing JSON parser would not catch that meaning change. Human comparison or task-specific checks remain necessary. Mark uncertain passages for review rather than converting uncertainty into an authoritative answer.


## Continue learning

[Previous: Choose retrieval, fine-tuning or training from scratch](01-choose-retrieval-or-training.md) · [Course contents](index.md) · [Next: Read JSON, JSONL and conversational records](03-json-jsonl-and-chat-records.md)
