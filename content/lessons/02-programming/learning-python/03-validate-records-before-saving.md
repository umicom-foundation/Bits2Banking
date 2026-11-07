<!--
Umicom Bits2Banking
File: content/lessons/02-programming/learning-python/03-validate-records-before-saving.md

PURPOSE:
  Present "Validate records before saving" with source-based exercises.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Validate records before saving

A JSON file can be valid text and still contain unusable records. This lesson continues the existing Python notes lab by tracing its validation before storage. We will use the existing program; no extra script is needed.

Source to open: `Umicom-Bits2Banking/content/labs/python-notes/notes.py`.

## Setup recap

Use a text editor, this course and a checkout of the named source. A checkout is a folder containing a repository's files. This is a source-reading and reasoning lab; it needs no running service or account. Choose your own practice folder and keep the original example unchanged. The commands below display source rather than compile or execute it. Replace the example directory with your checkout location. The detailed terminal and editor guide explains how to obtain a checkout, open a terminal and prepare later executable exercises.

A terminal accepts commands. Set-Location (PowerShell) and cd (Bash) choose the folder in which subsequent commands work. Get-Content and sed display text. If a path is missing, locate the repository first instead of creating an empty replacement file.

### PowerShell

```powershell
Set-Location 'C:\umicom\Umicom-Bits2Banking'
Get-Content -LiteralPath 'content\labs\python-notes\notes.py'
```

### Bash

```bash
cd /path/to/umicom/Umicom-Bits2Banking
sed -n '1,200p' 'content/labs/python-notes/notes.py'
```

## Understand the idea

Parsing turns JSON text into values such as lists, dictionaries and numbers. Validation asks whether those values satisfy the application's rules. validate_notes requires a bounded list of dictionaries with unique positive integer identifiers and nonblank text. It deliberately checks type(identifier) is int because Python also treats booleans as instances of int in some type checks.

```text
file bytes → size limit → UTF-8 decode → JSON parse → record validation
records → validation → serialization + byte limit → write
```

## Work through the lab

1. Open validate_notes. Make columns headed shape, identifier, text and duplicate. Place each rejection condition in a column.
2. On paper trace [{"id":1,"text":"Read C"}]. Then trace two records sharing id 1, a record using true as its id, and a record with spaces as text.
3. Follow save_notes. Notice validation and the serialized byte-size check occur before write_text opens the destination.
4. Find the loader's MAX_FILE_BYTES + 1 read. Explain how one extra byte lets it detect oversized input without reading the entire file.

## Expected result

The first paper record is admitted; the duplicate identifier, boolean identifier and blank text cases are refused. Unknown extra fields in otherwise valid records are retained.

## If the result differs

A character count and UTF-8 byte count can differ. If a file is rejected after serialization, inspect byte size rather than shortening an unrelated field. The lab writes directly to one file and is not a concurrent or atomic database.

## Explain it yourself

Why should a failed validation leave the previous file unopened for writing?

<details>
<summary>Worked explanation</summary>

Opening a replacement file too early can truncate good data before discovering that the new records are invalid. This ordering protects against that specific error; atomic replacement and crash recovery require additional storage design.

</details>

## Use the idea in Umicom

Record inputs, expected outputs and refusal cases before extending the example. Reusable production behaviour belongs in Umicom Framework; applications translate user actions and show the service result. A traced example explains a contract. It does not establish that every application using a similar idea has been integrated or tested.

[HTML edition](../../../courses/learning-python/lessons/03-validate-records-before-saving.html)

[Terminal and editor setup guide](../../learning-c/terminal-to-visual-studio.md)

[Previous lesson](02-json-files-and-error-boundaries.md) · [Course contents](index.md)

[Next: Inspect a record before reading it](04-inspect-a-record-before-reading-it.md)
