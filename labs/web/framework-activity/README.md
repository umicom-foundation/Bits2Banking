# Browser screen calling the shared C model

HTML supplies the button. JavaScript connects it to a WebAssembly build of the existing C activity source. No activity-count rule is reimplemented in JavaScript.

## Build

Install and activate the Emscripten SDK using its official installation instructions. Confirm `emcc --version` works in the same terminal. From the Bits2Banking checkout, run:

~~~powershell
emcc -std=c23 -Wall -Wextra -Wconversion -Wshadow labs/native/framework-activity/activity.c labs/native/activity-adapters/bridge.c -I C:/umicom/Umicom-Applications/framework/include --no-entry -sMODULARIZE=1 -sEXPORT_ES6=1 -sEXPORTED_FUNCTIONS=_BtbActivityNext -o labs/web/framework-activity/activity.js
~~~

On Bash use the same command and substitute the real Framework include path. Use `-std=c2x` only if your installed Emscripten compiler has not renamed the draft mode. The build produces `activity.js` and its WebAssembly companion beside the page. Do not commit those generated files.

This first lab uses Framework status declarations. It does not link an installed desktop Framework library. [Emscripten's C interoperation guide](https://emscripten.org/docs/porting/connecting_cpp_and_javascript/Interacting-with-code.html) explains exported functions and runtime loading.

## Open through HTTP

Serve this lab folder with an existing local static HTTP server. For example, if PHP is already installed:

~~~powershell
php -S 127.0.0.1:8088 -t labs/web/framework-activity
~~~

Keep the terminal open and visit `http://127.0.0.1:8088/`. The button stays disabled until the module is loaded. Press it three times and expect 3. Stop the server with Ctrl+C. Opening the HTML as a `file:` URL can fail module loading; it is not the supported route for this exercise.

## Inspect failures

Use the browser's Network panel. Both `activity.js` and its `.wasm` companion must load successfully. An HTML error document returned under either filename is not a module. Check the Console for the actual load error; the page shows a concise recovery message.

Reloading resets the in-memory value. The browser does not access a native desktop folder automatically. Persistence and permissions need a separate design.

## Observe the single source

The click handler calls `module._BtbActivityNext(current)`. The underscore is the generated export name. The C bridge returns -1 on rejection; the handler leaves the displayed count intact. Test model boundaries with the native adapter checks and browser behavior separately.

