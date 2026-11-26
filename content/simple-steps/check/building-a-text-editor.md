<!--
Umicom Bits2Banking
File: content/simple-steps/check/building-a-text-editor.md

PURPOSE:
Give learners an additional practical case for Building a Text Editor in C.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check a valid line ending and a refused replacement

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

The editor owns a clean current document holding the word saved. Two separate loads use byte sequences 41 0D 0A 42 and 41 0D 42 in disposable files.

1. Use the loading loop to follow the byte after the carriage return in each input.
2. Record the load result and buffer content after each attempt, starting from saved every time.

**Check your result.** The CRLF file returns BTB_EDIT_OK and loads bytes 41 0A 42. The lone CR returns BTB_EDIT_INVALID and keeps the exact text saved.

[Step-by-step course guide](../course-guides/building-a-text-editor.md) · [Full course](../../courses/building-a-text-editor/index.html) · [Acceptance checks by course](index.md) · [First practice case](../practice/building-a-text-editor.md)
