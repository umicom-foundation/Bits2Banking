<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-qt/11-serve-and-observe-the-web-build.md

PURPOSE:
Serve and observe the generated web application

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Serve and observe the generated web application

## Before starting

Finish the Wasm build and locate its generated application HTML. This exercise uses the single-threaded kit from lesson 10, a browser and Python 3 for a temporary local development server. Use a new terminal for the server so its output stays visible. No public hosting or account is needed.

## Serve the complete directory

A browser application must load its companion resources. Serve the generated directory over local HTTP rather than opening one file with a file URL. In the following command the relative build-wasm path is resolved from the lab directory.

~~~powershell
python -m http.server 8000 --bind 127.0.0.1 --directory build-wasm
~~~

## Follow the request

Open http://127.0.0.1:8000/ in the browser, then choose the generated application HTML. In developer tools, inspect Network before refreshing. The application page and its requested companions should load successfully. A missing Wasm response is a deployment-path problem; it is not evidence that UmiLocalProfileNameBytes rejected a name. Keep the browser console available for initialization errors.

## Repeat the same workflow

Enter Alice_7 and activate Check name. Record whether the result is Accepted name: alice_7. Replace the field with ../../other, activate Check name again and confirm the old success is replaced by a refusal. Try keyboard Enter, paste, browser zoom and a narrow window. Record the actual browser, kit and source revision. A screenshot helps explain a layout problem but cannot establish which C library was linked.

## Diagnose and recover

If the page loads but the application remains blank, inspect the first console error and failed request. If a resource is missing, compare the build directory with the served directory. If browser state appears stale, reload with cache disabled and compare resource names. Multithreaded kits need additional server headers; this simple server is not the threaded-kit setup. Stop the server with Ctrl+C when finished.

## Exercise and worked answer

A learner copies only the HTML file to a new folder and receives 404 responses. What should be repaired first? Restore the complete generated resource set and serve the correct root. Rebuilding the name validator would not restore missing JavaScript or Wasm files. Once loading works, repeat the input workflow and retain the new observations separately.

## Reference

[Qt WebAssembly running and deployment reference](https://doc.qt.io/qt-6/wasm.html). Consult the documentation for the exact kit you install.

## Read the source

[labs/framework/qt-profile/README.md](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/framework/qt-profile/README.md). Use the matching local revision when working offline.

## Continue learning

[Course contents](../../../courses/learning-qt/index.html) · [Previous: Build the Qt form for a browser](10-build-the-browser-application.md) · [Next: Separate browser validation from server authority](12-browser-boundaries-and-trust.md)
