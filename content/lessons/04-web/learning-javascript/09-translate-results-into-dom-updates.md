<!--
Umicom Bits2Banking
File: content/lessons/04-web/learning-javascript/09-translate-results-into-dom-updates.md

PURPOSE:
Explain the lesson: Translate C results into document updates.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Translate C results into document updates

## Prepare
Build and serve the browser activity lab using its README. Inspect `page.js`, `bridge.c` and `activity.c`. The **DOM**, or document object model, is the browser's object representation of the HTML page.

## Follow the success branch
The click handler calls `module._BtbActivityNext(current)`. A nonnegative result becomes the current count. The example then uses:
~~~javascript
output.textContent = String(current);
~~~
`String` creates text from the number. `textContent` assigns text to the element. It does not ask the browser to interpret the result as HTML markup.

## Follow refusal
If the returned value is negative, the handler changes only its message. The displayed count remains the previous accepted value.

Trace 999 -> 1000 -> refusal. Write three columns: old count, returned result, new visible count. Expected last row: 1000, -1, 1000.

## Exercise
Suppose an input label contains characters such as `<` and `>`. Which kind of assignment would preserve their meaning as text? Expected answer: a text assignment, rather than treating the label as HTML. This example displays a number, but the presentation distinction becomes important for future user-supplied content.

## Troubleshoot
If a press reaches C but nothing changes visually, inspect the element selector, result branch and text assignment. If the returned result is already wrong, inspect the C contract and input.

Keep presentation formatting out of the activity rule. The same C result can be displayed by GTK, Android, iPhone or the browser with different local widgets while preserving the same operation.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/web/framework-activity/page.js). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](08-catch-module-load-failures.md) · [Next lesson](10-events-closures-and-current-state.md)

