<!--
Umicom Bits2Banking
File: content/lessons/04-web/learning-html/08-use-real-buttons-and-outputs.md

PURPOSE:
Explain the lesson: Use a real button and a named output.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Use a real button and a named output

## Prepare
Open the existing browser activity example in an editor. For interaction, compile its C bridge through the documented Emscripten command and serve it over HTTP. Use a browser with developer tools and keyboard navigation.

A button is an action control. An output presents a calculated result. The example uses those elements directly:
~~~html
<output id="completed">0</output>
<button id="complete" type="button" disabled>Complete exercise</button>
~~~
The `id` connects each element to JavaScript's lookup. It must be unique within the document.

## Follow the initial state
The button begins disabled because the compiled C module is not ready yet. After loading succeeds, JavaScript enables it. This prevents an action from trying to call a function that does not yet exist.

## Inspect and operate
1. Find the button in the browser's element inspector.
2. Check its disabled state during loading.
3. Once ready, reach it with Tab.
4. Activate it using the keyboard.
5. Observe the count and status message.

**Exercise:** explain why a styled paragraph with a click listener is a poor starting substitute. Expected answer: it would require additional keyboard, focus and semantic behaviour that a native button already supplies.

## Keep identities consistent
If `id="completed"` changes, update its JavaScript selector together. A missing element lookup can cause an error before the C call. Do not repair that by changing the C count function.

## Extend carefully
A future form can introduce labels and validation for inputs. Keep this example's action separate from implicit form submission by retaining `type="button"`. Record keyboard and pointer results separately; a pointer-only check misses an important way people use a page.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/web/framework-activity/index.html). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](07-read-a-small-application-page.md) · [Next lesson](09-status-messages-and-page-language.md)

