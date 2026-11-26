<!--
Umicom Bits2Banking
File: content/simple-steps/course-guides/building-a-text-editor.md

PURPOSE:
Provide practical first steps and a result to check for Building a Text Editor in C.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Building a Text Editor in C

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

1. Open the course’s console editor example. Locate the model’s insert, erase and undo operations. [Plan a small editor with a testable model](../../courses/building-a-text-editor/lessons/01-plan-a-small-editor.html)
2. Use the worked editing session for `abcdef`. Apply `erase 1 3` to remove three bytes beginning at position one. [Insert and erase text without losing the tail](../../courses/building-a-text-editor/lessons/02-insert-and-erase-text.html)
3. Type `undo` in the console editor and inspect the restored text using `show`. [Insert and erase text without losing the tail](../../courses/building-a-text-editor/lessons/02-insert-and-erase-text.html)

**Check your result.** The deletion leaves `aef`. Undo restores `abcdef` with the original tail.

[Continue in the full course](../../courses/building-a-text-editor/index.html) · [All course guides](index.md)
