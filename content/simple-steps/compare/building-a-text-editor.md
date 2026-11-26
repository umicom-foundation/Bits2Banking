<!--
Umicom Bits2Banking
File: content/simple-steps/compare/building-a-text-editor.md

PURPOSE:
Give learners an additional practical case for Building a Text Editor in C.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Compare two line endings in a loaded document

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

One scratch file contains A followed by LF and B. Another contains A followed by CRLF and B. The course editor opens each into a clean buffer.

1. Write the input bytes for both files in hex. Use Recognise line endings and end of file to trace the loading loop.
2. Write the bytes inserted into the editor in both cases. Keep the source file sizes in their own column.

**Check your result.** The inputs are 41 0A 42 and 41 0D 0A 42. Both buffers contain 41 0A 42 with length three. Their original files have lengths three and four.

[Step-by-step course guide](../course-guides/building-a-text-editor.md) · [Full course](../../courses/building-a-text-editor/index.html) · [Compare two approaches by course](index.md) · [First practice case](../practice/building-a-text-editor.md)
