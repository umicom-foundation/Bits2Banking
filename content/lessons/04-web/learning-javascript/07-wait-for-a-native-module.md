<!--
Umicom Bits2Banking
File: content/lessons/04-web/learning-javascript/07-wait-for-a-native-module.md

PURPOSE:
Explain the lesson: Wait for a compiled C module.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Wait for a compiled C module

## Prepare
Activate Emscripten, compile the browser activity lab using its README, and serve the folder over HTTP. Open `page.js` in an editor. The generated `activity.js` file is a build output; do not edit it to change the application rule.

A **promise** represents work whose result may arrive later. `await` waits within this module's flow for that work to complete.

## Read the two waits
~~~javascript
const { default: createActivityModule } = await import("./activity.js");
const module = await createActivityModule();
~~~
The first obtains the module factory. The second waits for that factory's initialization. Only afterward does the example enable its button.

The **factory** is a function that creates the usable module instance. Emscripten's [interoperation guide](https://emscripten.org/docs/porting/connecting_cpp_and_javascript/Interacting-with-code.html) explains the generated C-call boundary.

## Trace without a browser
Write loading, imported, initialized and ready on a line. Put button enabling after initialized. Then imagine the import failing: the flow moves into the error handler and never reaches ready.

**Exercise:** why is enabling the button before initialization unreliable? Expected answer: the click may arrive before the exported C function is available.

## Inspect failure
In a disposable served copy, omit a generated module output and reload. Expect visible recovery guidance and an unavailable button. Restore the output, reload and record the result. Do not claim this check ran merely because the catch block exists.

## Keep the boundary small
JavaScript owns browser events and presentation. The C model still decides the accepted transition. Adding a second JavaScript count rule would create two implementations to maintain and compare.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/web/framework-activity/page.js). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](05-publish-a-checked-action-result.md) · [Next lesson](08-catch-module-load-failures.md)

