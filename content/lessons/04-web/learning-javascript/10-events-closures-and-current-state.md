<!--
Umicom Bits2Banking
File: content/lessons/04-web/learning-javascript/10-events-closures-and-current-state.md

PURPOSE:
Explain the lesson: Follow state retained by an event handler.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Follow state retained by an event handler

## Prepare
Open the browser activity source. For execution, follow the README's Emscripten command and HTTP-server setup. Locate `let current = 0` and the click listener.

An **event handler** is a function called when an event occurs. A **closure** is a function together with access to variables in its surrounding scope. Here the listener can read and update `current`.

## Trace successive presses
1. Before the first click, current is 0.
2. C returns 1; the handler assigns current = 1.
3. The next click reads 1, not the original 0.
4. C returns 2; the handler displays it.

The listener is registered once after module setup. The page does not register another listener on every press.

## Exercise
Imagine accidentally calling `addEventListener` again inside the click handler. Predict why later presses might trigger repeated work. Expected explanation: several registered handlers could respond to one event. This is a wiring defect, even if each C call is individually correct.

## Check the lifecycle
Reloading creates a new page/module session and the example begins at 0. It has no durable project storage. A value retained by a closure should not be described as a saved file.

## Diagnose
If one click advances more than once, count handler invocations and inspect initialization paths. If it always returns to 1, check whether state is recreated before each call. Use an isolated learning value for diagnostics.

For a larger Umicom web client, shared services own operations and durable data. Browser listeners adapt user actions to those services; they should not create competing hidden copies of the domain model.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/web/framework-activity/page.js). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](09-translate-results-into-dom-updates.md) · [Next lesson](11-check-browser-and-native-boundaries.md)

