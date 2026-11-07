<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/learning-gtk4/09-present-status-without-changing-the-model.md

PURPOSE:
Explain the lesson: Present status without changing the model.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Present status without changing the model

## Prepare
Build the existing Framework activity example with GTK4 enabled using its README. Keep `activity.c`, `activity.h` and `window.c` open side by side. These files separate the rule, its declaration and its presentation.

A **status** describes whether an operation succeeded and, if not, why it was refused. The window should not infer success merely because a click occurred.

## Follow the result
The callback calls `BtbActivityAdvance`. On `UMI_STATUS_OK` it formats the updated count. Otherwise it formats an explanation using Framework's `umi_status_text`. The label is updated after this decision.

The destination buffer is a fixed 96-byte local array. `g_snprintf` receives the buffer's capacity so formatting is bounded. A bounded message can still be truncated, so future longer messages need deliberate presentation requirements.

## Work through two cases
For count 9, the next value is 10 and the label reports it. For count 1000, the model returns capacity exceeded and preserves the count. The window presents a refusal instead of pretending the action succeeded.

**Exercise:** list information useful to a person and information useful to a developer. A person needs the outcome and a next action; a developer may need a status code and source identity. Avoid replacing helpful UI text with raw private logs.

## Investigate inconsistency
If the count changes after failure, inspect the model's output-preservation contract. If the model preserves it but the label claims success, inspect the status branch in the callback. Testing these separately identifies the responsible boundary.

## Extend
Propose a richer screen with a persistent count label and a separate status label. Keep that as a presentation exercise using the same model; do not move capacity rules into the widget code. Record layout and functional observations independently.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-activity/window.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](08-compose-widgets-in-a-container.md) · [Next lesson](10-separate-logic-and-window-checks.md)

