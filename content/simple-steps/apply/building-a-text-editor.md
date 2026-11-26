<!--
Umicom Bits2Banking
File: content/simple-steps/apply/building-a-text-editor.md

PURPOSE:
Give learners an additional practical case for Building a Text Editor in C.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Make a safe handoff between two documents

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A practice editor session holds unsaved text draft. A separate training file active.txt already contains the word current.

1. Attempt open active.txt and check the buffer before proceeding. Save the draft to a fresh practice file named draft-backup.txt.
2. Open active.txt again after the successful save, then use show. Inspect draft-backup.txt separately.

**Check your result.** The first open leaves draft in the buffer. After saving, show prints TEXT: current. draft-backup.txt contains draft.

[Step-by-step course guide](../course-guides/building-a-text-editor.md) · [Full course](../../courses/building-a-text-editor/index.html) · [Small projects by course](index.md) · [First practice case](../practice/building-a-text-editor.md)
