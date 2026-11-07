<!--
Umicom Bits2Banking
File: content/lessons/04-web/learning-html/05-buttons-status-and-a-loading-page.md

PURPOSE:
Explain the lesson: Make a loading page understandable.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Make a loading page understandable

## What the page must explain

A browser page can appear before its program is ready. The Umicom activity example loads a compiled C module. A visitor needs to know whether the page is loading, ready, or unable to continue. Those are different states, even when the number on screen is still zero.

HTML gives content meaning. A button represents an action. An output represents a calculated result. A paragraph with a status role can announce a change to assistive technology without moving keyboard focus.

## Setup recap

Open the [browser activity lab guide](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/web/framework-activity/README.md). Reading its HTML needs only an editor. Running the complete page needs the generated JavaScript and WebAssembly files and a local HTTP server. The guide explains the C build and serving commands. Do not open the page by double-clicking it and assume that module loading will behave like an HTTP site.

## Read the initial state

~~~html
<button id="complete" type="button" disabled>Complete exercise</button>
<p id="message" role="status">Loading the C module…</p>
~~~

The disabled attribute is present in the document itself. Before any JavaScript runs, the page already refuses an action it cannot perform. JavaScript removes the disabled state only after the C module has loaded.

The id is a unique name used to find an element. The words inside the button are its accessible name. A title tooltip alone would not provide the same clear visible instruction.

## Lab

1. Read index.html and locate the button, output and message.
2. Serve the built lab using its guide.
3. Press Tab until the enabled button receives focus; activate it with the keyboard.
4. Check that the displayed count changes once.
5. In a disposable lab copy, temporarily move the generated activity.js file aside.
6. Reload. Expect an explanation of the load failure and a disabled button.
7. Restore the generated file and reload.

Do not overwrite your source file while exploring a failed-load case. The generated module is a separate artifact.

## Exercise and explanation

Would a clickable paragraph be an equally good button? It would need extra keyboard, focus and accessibility behaviour. A native button supplies those semantics. Use the element whose meaning matches the action.

## Connection to Umicom

The browser owns labels and focus. The existing C model decides whether a count can advance. The page should communicate the model's result without silently inventing a second policy. This lab uses temporary state; it does not save course progress.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/web/framework-activity/index.html). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](04-follow-a-form-to-a-c-service.md) · [Next lesson](06-identifiers-links-and-relative-paths.md)

