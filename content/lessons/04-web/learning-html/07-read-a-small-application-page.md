<!--
Umicom Bits2Banking
File: content/lessons/04-web/learning-html/07-read-a-small-application-page.md

PURPOSE:
Explain the lesson: Read a small application page.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Read a small application page

## Start with the files
Open the browser activity lab's `index.html` in a text editor. You can study the markup without a compiler. To run the C-backed interaction, follow that lab's README: activate Emscripten, compile the shared C sources and serve the folder through a local HTTP server.

HTML describes the document's structure. A **tag** marks the beginning or end of an element, such as a heading or button. An **attribute** supplies extra information on that element.

## Read from outside inward
1. `<!doctype html>` requests the normal HTML document mode.
2. `<html lang="en">` identifies the document's language.
3. `<head>` holds metadata, including the title and character encoding.
4. `<body>` contains the visible document.
5. `<main>` identifies its central content.

The page contains a heading, a count, an action and a status message. It does not implement the activity rule; that remains in C.

## Make a content map
Write a four-row table: heading explains the page; output shows the count; button requests a completion; status explains readiness or failure. This is the smallest useful workflow map for the example.

**Exercise:** change only the page title in a disposable copy. Predict which browser surface will change and which heading will remain unchanged. Expected answer: the document title and visible heading are separate elements.

## Recover from confusion
If a page appears blank, first check that you opened or served the intended file. If text appears but the action stays disabled, inspect module loading using the JavaScript lesson. An HTML structure problem and a C module failure occur at different layers.

Keep working code, generated WebAssembly output and course explanation distinct so learners can see which source controls each result.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/web/framework-activity/index.html). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](06-identifiers-links-and-relative-paths.md) · [Next lesson](08-use-real-buttons-and-outputs.md)

