<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-text-editor/10-resolve-unicode-positions.md

PURPOSE:
Teach resolve exact utf-8 offsets and utf-16 positions.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-logo.svg)

# Resolve exact UTF-8 offsets and UTF-16 positions

<!-- The original local lab references are retained for source review. Published manuscripts use repository URLs because labs is outside the site content root.
[Course contents](index.md) · [Complete source](../../../../labs/native/shared-editor/buffer.c) · [Build and run](../../../../labs/native/shared-editor/README.md)
-->
[Course contents](index.md) · [Complete source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/shared-editor/buffer.c) · [Build and run](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/shared-editor/README.md)

A position can mean a byte offset, a Unicode scalar position, a UTF-16 code-unit count or a screen column. These numbers agree for simple ASCII and diverge for other text. Treating them as interchangeable can select half of a character or apply a diagnostic to the wrong location.

## The fixture

buffer.c contains A, an e-acute character, a grinning face, CRLF, the word note and a final LF. Its C literal uses hexadecimal UTF-8 bytes so that the example does not depend on the compiler guessing the source-file encoding. The document contains 14 bytes before its terminating zero.

~~~c
static const char sample[] = "A\xc3\xa9\xf0\x9f\x98\x80\r\nnote\n";
~~~

## 1. Count each representation

A occupies one UTF-8 byte and one UTF-16 code unit. The e-acute character occupies two UTF-8 bytes and one UTF-16 code unit. The supplementary grinning-face character occupies four UTF-8 bytes and two UTF-16 code units. Thus byte offset 7, immediately before CRLF, corresponds to UTF-16 column 4 on line zero. These are encoding positions, not measurements of how wide a font draws the characters.

| UTF-8 offset | Zero-based line | UTF-16 column |
| --- | --- | --- |
| 0 | 0 | 0 |
| 1 | 0 | 1 |
| 3 | 0 | 2 |
| 7 | 0 | 4 |
| 9 | 1 | 0 |
| 13 | 1 | 4 |
| 14 | 2 | 0 |

## 2. Resolve through Framework

UmiEditorTextViewPositionAt converts a byte offset to a protocol position. UmiEditorTextViewResolvePosition performs the reverse operation. They borrow a stable buffer view and allocate nothing. Keep all calls on the owning thread or otherwise prevent concurrent mutation. The scenario checks both directions for every row instead of checking only one convenient ASCII position.

~~~c
UmiEditorTextPosition position = {99U, 99U};
size_t offset = SIZE_MAX;
UmiStatus status = UmiEditorTextViewPositionAt(&view, 7U, &position);
if (status == UMI_STATUS_OK)
    status = UmiEditorTextViewResolvePosition(&view, position, &offset);
~~~

This excerpt assumes the valid view established earlier in buffer.c. On success the expected values are line zero, column four and offset seven. Always check status before using outputs. The sentinel values make an accidental use of an unchanged output easier to notice during a failure investigation.

## 3. Refuse positions that split an encoding

Offsets 2, 4, 5 and 6 fall inside multibyte UTF-8 sequences. Offset 8 lies between CR and LF. UTF-16 column 3 lies between the two units representing the supplementary character. Exact conversion refuses these positions; it does not round them to a nearby character. The position-refusals scenario also checks an offset beyond the buffer and confirms that output sentinels remain unchanged.

The service recognises LF, CRLF and standalone CR line endings. End of buffer is a valid position. A final newline creates a valid empty final line. The conversion validates the scanned prefix, so successfully resolving the beginning of a file does not certify an unvisited malformed suffix.

## Run the two observations

~~~powershell
& .\build\shared-editor\shared-editor.exe positions
& .\build\shared-editor\shared-editor.exe position-refusals
~~~

## Exercise and worked explanation

Predict the result at byte offset 9 before running the scenario: it is the start of line one, column zero. Now explain why the editor Go To command can have a different policy. The coordinator navigation contract uses one-based byte columns and permits clamping, while these protocol conversion functions require exact zero-based UTF-16 positions. A client must choose the contract required by its input rather than hide the difference in a generic column variable.

## Troubleshooting

If the expected rows fail, preserve the exact fixture bytes, compiler identity and selected SDK prefix. Check whether an editor converted the CRLF escape into unrelated source text or a different binary was launched. Font appearance cannot repair an encoding-offset error.


[Previous lesson](09-own-a-shared-text-buffer.md) · [Next lesson](11-select-source-words-and-lines.md)
