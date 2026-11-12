<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-text-editor/11-select-source-words-and-lines.md

PURPOSE:
Teach select source words and physical lines without changing text.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-logo.svg)

# Select source words and physical lines without changing text

<!-- The original local lab references are retained for source review. Published manuscripts use repository URLs because labs is outside the site content root.
[Course contents](index.md) · [Complete source](../../../../labs/native/shared-editor/buffer.c) · [Build and run](../../../../labs/native/shared-editor/README.md)
-->
[Course contents](index.md) · [Complete source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/shared-editor/buffer.c) · [Build and run](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/shared-editor/README.md)

A selection is a range in the current document, described by an offset and a byte count. Selecting a word or line should not rewrite the document. Framework provides UmiEditorSourceSelectionAt for this read-only calculation, so a course client does not need a second UTF-8 scanner.

## 1. Keep the units explicit

The caret and returned range both count UTF-8 bytes. The caret must already be on a complete scalar boundary and must not fall between CR and LF. The service accepts a stable borrowed text view and supports inputs up to its documented 8 MiB limit. An application must respect that bound before offering this particular operation on a larger source.

~~~c
UmiEditorSourceSelection selected = {0};
UmiStatus status = UmiEditorSourceSelectionAt(
    &view, 11U, UMI_EDITOR_SELECT_SOURCE_WORD, &selected);
~~~

For the fixture from the previous lesson, byte 11 is inside note. The result begins at offset 9 and contains four bytes. It is a slice into the existing view, not a newly allocated string. In general the next byte is still part of the original document, so do not print the slice with an unbounded %s operation. Compare or copy exactly selected.byte_count bytes.

## 2. Choose the line policy

LINE_CONTENT selects a physical line without its ending. LINE_WITH_ENDING includes the complete ending. At caret 3 in the fixture, content is the seven bytes before CRLF, while the second policy includes nine bytes. This distinction matters for commands such as copying a line, duplicating it or removing it without accidentally joining unrelated lines.

The final LF leaves an empty last line. Selecting its content at offset 14 succeeds with offset 14 and a zero byte count. Empty selection is not an error. Similarly, an empty document has an empty line. Code that treats every zero-length range as failure will incorrectly reject normal caret positions.

## 3. Understand what a source word means

The source-word policy groups ASCII letters, digits and underscore, together with non-ASCII bytes at validated boundaries. It prefers a word at the caret, then one immediately before it. This is a convenience for source text, not a linguistic word-break algorithm. It does not promise correct human-language segmentation, grapheme navigation or language-specific tokenisation.

An IDE may later layer language-server tokens or another approved segmentation service on top. That extension should retain the distinction between byte ranges and user-perceived characters. Do not advertise a token convenience as complete Unicode editing simply because it accepts non-ASCII input.

## 4. Check refusals without editing

selection-refusals starts with an output range containing sentinels. A caret between CR and LF must fail and preserve both values. It then places malformed UTF-8 after an ordinary ASCII prefix. The source-selection operation validates the text and rejects the malformed suffix even though the requested caret is at the beginning. This is deliberately different from the prefix-scanning position conversion discussed earlier.

~~~powershell
& .\build\shared-editor\shared-editor.exe selection
& .\build\shared-editor\shared-editor.exe selection-refusals
~~~

An invalid caret is an INVALID_ARGUMENT error. Malformed UTF-8 reaches the shared position scanner and produces PARSE_ERROR. The lab checks that distinction explicitly. Both failures preserve the output range, but their causes and corrective actions differ: repair the requested coordinate or repair/reject the encoded input.

## Exercise and worked explanation

Select the note line using both line modes in a practice copy. Content should begin at 9 with four bytes; including its final LF should give five. Explain why copying four bytes with memcpy does not automatically make a C string. Add a terminator in a destination with at least five bytes of capacity, or retain an explicit slice length throughout the caller.

## Connect the range to a document

A computed range is meaningful only for the text revision that was inspected. If the document changes before an asynchronous action completes, the old byte range can point somewhere else. The next lesson introduces captured document edit plans, which check identity and revisions before applying an edit. This selection calculation itself performs no history operation, disk save or UI selection update.


[Previous lesson](10-resolve-unicode-positions.md) · [Next lesson](12-capture-and-apply-document-edits.md)
