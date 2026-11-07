<!--
Umicom Bits2Banking
File: content/lessons/04-web/learning-javascript/08-catch-module-load-failures.md

PURPOSE:
Explain the lesson: Keep module loading inside the error boundary.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Keep module loading inside the error boundary

## Set up
Use the browser activity lab with its compiled outputs and a local HTTP server. Open developer tools before reloading. The README explains both compilation and serving; a text editor suffices to follow the control flow.

An **exception** interrupts the ordinary path of execution. A `try` block identifies work whose errors will be handled by the associated `catch`.

## Inspect the preserved implementation
The source retains a former static import as an explanatory comment. The active code uses a dynamic import inside `try`. This means a missing generated module can be handled by the page's visible recovery path.

The `catch` displays guidance but does not claim that the module is ready. The button began disabled, so an unsuccessful setup leaves the action unavailable.

## Make a failure table
List these cases:
- Generated JavaScript missing.
- WebAssembly companion missing.
- Server returns an HTML error document.
- Initialization succeeds.

For each case predict whether the button should be enabled. Only the last has enough evidence to offer the action.

## Exercise
Why is a text message more useful than a silent loading spinner forever? Expected answer: it explains that progress stopped and identifies a recovery action.

## Diagnose accurately
Check the detailed browser console message and failed request URL. The short page message is for the person using the lab; the developer tools help identify the cause. Do not log credentials or arbitrary project content to make the message more detailed.

After repairing the server root or generated outputs, reload and observe again. A successful import alone does not prove that the button listener or C function behaves correctly; check the full press-to-result path afterward.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/web/framework-activity/page.js). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](07-wait-for-a-native-module.md) · [Next lesson](09-translate-results-into-dom-updates.md)

