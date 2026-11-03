# Start and stop a local service safely

A server is more than a callback. Its listener, service and borrowed context must remain alive together. Follow the example's complete startup and shutdown order.

## 1. Understand the ownership order

The service owns routing behavior. The server uses that service while it handles a connection. The request gate also borrows an access-policy value containing the chosen port. Destroying a borrowed object while a request is active would leave the request with invalid storage.

 <svg viewbox="0 0 700 110" role="img" aria-label="The service and handler contexts stay alive until serving has finished; shutdown releases the server before the service." style="width:100%;max-width:700px"><title>The service and handler contexts stay alive until serving has finished; shutdown releases the server before the service.</title><rect x="10" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="115" y="53" text-anchor="middle" fill="white" font-size="17">Create service + routes</text><path d="M220 47h18l-7 -6m7 6l-7 6" fill="none" stroke="#287b78" stroke-width="3"></path><rect x="240" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="345" y="53" text-anchor="middle" fill="white" font-size="17">Serve on owner thread</text><path d="M450 47h18l-7 -6m7 6l-7 6" fill="none" stroke="#287b78" stroke-width="3"></path><rect x="470" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="575" y="53" text-anchor="middle" fill="white" font-size="17">Destroy server, then service</text></svg>

The service and handler contexts stay alive until serving has finished; shutdown releases the server before the service.

1. Choose the port and prepare the configuration.
2. Create the service and install the request gate.
3. Register the selected routes or static-file fallback.
4. Create and start the server.
5. Serve one connection at a time from its owner thread.
6. After the active call returns, destroy the server and then the service.

Read [`local_service.c`](https://github.com/umicom-foundation/umicom-framework/blob/main/examples/web/local_service.c) alongside [`server.h`](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/web/server.h). A handler must not start, stop or destroy its own server. Keep blocking serving work out of a GTK4 event callback so the application's window can continue responding.

## 2. Prepare the optional Windows exercise

First complete [Umicom Framework Development](../../../courses/umicom-development/index.html) and its toolchain setup. You need the Framework checkout, a prepared UCRT64 compiler, CMake and Ninja. Reading this course requires none of those installations.

The following commands configure the existing standalone Framework preset and build only the example target plus its declared dependencies. They do not build all application executables or all test executables. Use a separate build directory when another build is active. Run one stage at a time and stop on an error.

```text
Set-Location "C:\umicom\Umicom-Applications\framework"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
New-Item -ItemType Directory -Force "C:\umicom\_local\logs\web-service"
cmake --preset windows-ucrt64-debug -B ".\build\web-service-learning" -DUMICOM_BUILD_LEARNING_EXAMPLES=ON -DBUILD_TESTING=OFF 2>&1 | Tee-Object "C:\umicom\_local\logs\web-service\configure.log"
cmake --build ".\build\web-service-learning" --target umicom-web-local-service-example --parallel 2 2>&1 | Tee-Object "C:\umicom\_local\logs\web-service\build.log"
& ".\build\web-service-learning\bin\umicom-web-local-service-example.exe" --port 8080 2>&1 | Tee-Object "C:\umicom\_local\logs\web-service\run.log"
```

The target is declared in `cmake/UmicomLocalWebService.cmake`, uses C23 and links `Umicom::web`. Configuration can still require dependencies from the selected Framework composition. The command does not claim that an unprepared machine has them. `BUILD_TESTING=OFF` means this exercise does not register a test suite; do not describe its manual browser checks as a CTest pass.

## 3. Observe one request

1. Keep the server terminal open.
2. Open exactly `http://127.0.0.1:8080/` in a browser.
3. Expect the heading “Umicom local web service.”
4. Select the health link and compare its JSON with lesson 1.
5. Return to the home page, enter a short message and submit the form. Expect encoded plain text, not a saved record.
6. Return to the terminal and press Ctrl+C to stop.

If the port is occupied, choose 8081 and use that same port in the browser. A missing executable means the build did not produce the expected target; inspect its log before trying random paths. A 403 may indicate a different Host or Origin; compare the exact printed address.

## 4. Explain cancellation without assuming instant interruption

The example's signal handler only sets `stop_requested`, a `sig_atomic_t` flag. It performs no socket, allocation or logging work in the signal handler. The owner loop checks that flag between calls.

`UmiWebServerServeNext` receives separate accept-wait and exchange limits. The example passes 100 milliseconds and 3,000 milliseconds. Socket waits are bounded, but a synchronous C handler must return before the loop can continue. A deadline is not permission to forcibly free an object still used by a callback.

## 5. Keep the local boundary explicit

The native example listens on `127.0.0.1`, serves one connection at a time and installs a gate checking the selected Host, Origin and fetch metadata. This reduces unwanted cross-origin access; it does not authenticate a user or prevent another local process from making requests.

Public hosting needs a separate reviewed design for encrypted transport, authentication, authorization, concurrency and operations. Changing an address alone does not provide those features. A browser client can use an appropriate host service; browser code cannot simply become a native listening socket.

## Exercise

Why destroy the server before the service?

<details>

<summary>Explanation</summary>

The server borrows the service while dispatching. Finish serving first, then release the borrower, then the borrowed object. Keeping that order prevents a server from referencing a destroyed service.

</details>

---

[Read this lesson in HTML](../../../courses/building-a-web-server-in-c/lessons/03-own-the-server-lifetime.html) · [Learning sequence](../../../start/learning-sequence.md)
