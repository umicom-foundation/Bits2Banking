<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/40-one-model-several-interfaces.md

PURPOSE:
Explain the lesson: Plan one C model for several interfaces.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Plan one C model for several interfaces

## Before you begin

You need a text editor and the Bits2Banking checkout. Read `labs/native/framework-activity/activity.h`, then `activity.c`. A function declaration tells a caller how to ask for work. Its contract also explains which inputs are accepted and what changes on success or failure.

## Separate the decisions

Our activity records completed exercises. A button, browser page and phone screen can all request the next count. The rule accepts a count below 1000 and writes the next value. A null result pointer or an excessive count is rejected. The caller must inspect the returned status before presenting success.

The screen chooses labels and receives input. The model decides whether the update is valid. Framework supplies the shared status vocabulary. The small activity rule belongs to this educational application; a production service shared by multiple Umicom products belongs in Framework.

~~~text
Desktop button ─┐
Browser click ──┼─> input adapter ─> activity rule ─> result ─> screen
Phone tap ──────┘
~~~

An adapter translates between representations. It should not quietly invent a different maximum or accept a failure as success.

## Make a boundary map

1. Write the input: an existing count.
2. Write the output: a status and, on success, a next count.
3. Write the unchanged state on failure.
4. Name the UI state owner. Each window or page owns its displayed value.
5. Identify the files used by every interface: the same `activity.c` and header.

## Trace a refusal

Suppose the screen shows 1000. The user presses Complete exercise. The rule returns a capacity status. The screen keeps 1000 and explains that the limit has been reached. It must not show 1001 first and try to repair the display later.

## Practice and check

Draw the path for a keyboard shortcut. It should reach the same rule as the button. Then propose a Reset action. Specify its input, output, ownership and tests before adding a second operation. Reset is a new rule, not a reason to bypass validation in the UI.

## When results disagree

If two screens show different answers, compare the actual compiled source and adapter conversions. Sharing a filename is insufficient when each project copied and changed its own file. Keep a source revision and build configuration with the result.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-activity/activity.h). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Next lesson](41-signed-values-at-a-platform-boundary.md)


[Previous lesson](39-trace-an-event-to-a-framework-rule.md)
