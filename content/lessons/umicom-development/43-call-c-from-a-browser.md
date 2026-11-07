<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/43-call-c-from-a-browser.md

PURPOSE:
Explain the lesson: Call the shared C model from a browser.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Call the shared C model from a browser

## Before you begin

A browser runs a page containing HTML, styles and program code. WebAssembly is a binary instruction format that a supporting browser can execute. Emscripten compiles supported C code into that format and creates JavaScript loading code.

Use the existing `labs/web/framework-activity/README.md` for the exact Emscripten command. Install and activate the Emscripten SDK first. Use a local HTTP server to open the page; the README includes a command using an existing PHP installation.

## Understand three files

The authored `index.html` supplies the button and output. The authored `page.js` waits for the generated module. The generated `activity.js` loads `activity.wasm`. Generated outputs are ignored by Git so a source review does not accidentally include a machine's build products.

## Wait before enabling input

~~~javascript
const module = await createActivityModule();
button.disabled = false;
~~~

Loading is asynchronous: the browser may still be downloading bytes while the page is visible. A button enabled too soon could call a function that does not exist yet. The example begins disabled and reports an initialization error if loading fails.

## Follow one request

1. The user clicks Complete exercise.
2. JavaScript calls the exported `_BtbActivityNext`.
3. The C bridge calls the same activity rule used by the desktop lab.
4. JavaScript updates the output only for a nonnegative result.

The underscore is part of this generated export interface. It is not a new name for the C source function.

## Lab and expected result

Build from the repository root using the README. Serve the lab directory and open the local address. Expect the button to enable after loading, then 0 to become 1. Temporarily serve a copy without its WebAssembly file and verify that an explanatory status appears.

## Troubleshooting

An unavailable export usually means the build omitted the function from its export list. A network error suggests the server path or missing output file. The browser developer console helps distinguish these causes. This example uses Framework status declarations; it does not demonstrate that every native Framework service can execute in a browser.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/web/framework-activity/page.js). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](42-desktop-events-and-state.md) · [Next lesson](44-mobile-bindings-without-duplicated-rules.md)

