<!--
Umicom Bits2Banking
File: content/lessons/04-web/learning-javascript/11-check-browser-and-native-boundaries.md

PURPOSE:
Explain the lesson: Check the browser and native boundaries separately.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check the browser and native boundaries separately

## Prepare
Use the existing activity adapter host tests and the browser activity lab. The host tests need a C23 toolchain and matching Framework SDK; the browser build uses Emscripten and a local HTTP server. Follow each README's setup for its destination.

A native test and a browser workflow answer different questions. Both are valuable because code can be correct at one boundary and disconnected at another.

## Build a check map
- Shared C model: first/last accepted count and failure preservation.
- Integer bridge: negative input and rejected results.
- Generated module: exported function available after initialization.
- Browser: action enabled, listener invoked and result displayed.

## Exercise the visible path
1. Load the served page.
2. Wait for Ready.
3. Activate the button once; expect 1.
4. Activate twice more; expect 3.
5. Reach the same action using keyboard navigation.
6. Reload and record the in-memory reset.

Separately exercise a missing module in a disposable copy. Expect a useful message and no available action.

## Exercise
A host bridge test passes, but the browser console says the export is undefined. Where should you investigate? Expected answer: the export/build/loading boundary before altering the model's count rule.

## Record and recover
Write expected and observed results with source revision, compiler, browser and server root. Keep unexecuted or unavailable checks marked as such. If generated outputs are stale, rebuild them using the documented command and retry; editing generated JavaScript can conceal the real source problem.

These checks establish the small example. They do not demonstrate a complete browser port of every Framework library or native GUI component.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/web/framework-activity/README.md). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](10-events-closures-and-current-state.md)

