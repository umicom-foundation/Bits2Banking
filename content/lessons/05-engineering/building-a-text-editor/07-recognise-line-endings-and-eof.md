<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-text-editor/07-recognise-line-endings-and-eof.md

PURPOSE:
Explain the lesson: Recognise line endings and end of file.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Recognise line endings and end of file

Text files may represent a line ending with one line-feed byte or with carriage return followed by line feed. The editor loads both forms into one internal representation.

## Setup recap

Read the loading loop in editor.c and the fixtures in test_load.c. A fixture is controlled input created for a check. These fixtures are written into a dedicated build-directory folder when the test runs.

The loader opens files in binary mode so the C runtime does not translate line endings before the code observes them.

## 1. Keep the input result as int

fgetc returns either an unsigned-character value represented as int, or EOF. EOF indicates that no next character was obtained. It does not belong in the text buffer.

The variable byte is therefore an int. Converting it to char before comparing with EOF could lose the distinction between a byte and the end marker.

## 2. Follow the carriage-return case

When byte is carriage return, the loader reads one more byte. That next byte must be line feed. The pair becomes a single line feed in the candidate.

```text
file bytes:   a b CR LF c
model bytes:  a b LF    c
```

A lone carriage return, including one immediately before EOF, is refused. The function does not silently guess what it means.

## 3. Separate end from failure

EOF can result from reaching the end or from a read error. After the loop, ferror distinguishes an error indication from an ordinary completed read.

The insertion validator also rejects embedded zero bytes and bytes outside the example's accepted ASCII range. An embedded zero would otherwise make string-based display stop before the recorded document length.

## Exercise and expected results

Prepare a table for LF text, CRLF text, lone CR, embedded zero, a file exactly at capacity and a file one byte too large. Record success or refusal and whether the previous document should change.

Exactly-at-capacity content succeeds because the model reserves another byte for its terminating zero. The capacity describes document bytes, not the total size of its storage array.

A non-ASCII character being refused is an intentional limitation of this lab. Supporting Unicode requires an explicit encoding and cursor policy, not removal of arbitrary checks.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/text-editor/test_load.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](06-load-into-a-private-candidate.md) · [Next lesson](08-check-failure-state-and-command-results.md)

