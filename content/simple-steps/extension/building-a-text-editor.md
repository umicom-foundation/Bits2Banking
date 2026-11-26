<!--
Umicom Bits2Banking
File: content/simple-steps/extension/building-a-text-editor.md

PURPOSE:
Give learners an additional practical case for Building a Text Editor in C.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Consume the single undo state

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A disposable editor buffer starts empty. You want to check what remains available after using its one stored undo state.

1. Enter append desk, append top, undo and show on separate lines in a practice session.
2. Enter undo a second time, then show and discard. Keep the results of both show commands.

**Check your result.** Both show commands print TEXT: desk. The second undo is refused because the earlier undo already consumed the saved state.

[Step-by-step course guide](../course-guides/building-a-text-editor.md) · [Full course](../../courses/building-a-text-editor/index.html) · [Extend a skill by course](index.md) · [First practice case](../practice/building-a-text-editor.md)
