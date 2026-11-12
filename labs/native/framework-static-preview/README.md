# Read a static file through Framework

![Umicom](../../../content/assets/branding/umicom-wordmark.svg)

This laboratory calls the installed Framework preview session. It opens no listener. It parses a complete request, applies the same browser request gate used by the native host, reads a selected regular file through rooted storage, and measures the closed HTTP response.

## Prepare and build

1. Install a matching Framework SDK that contains `umicom/web/preview.h` and its web library. Use the same compiler family and architecture for the SDK and this client.
2. Put CMake, Ninja and the C23 compiler on PATH. Substitute your actual SDK prefix if it differs from the example below.
3. Run each command separately and stop on errors.

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
cmake -S labs/native/framework-static-preview -B build/static-preview -G Ninja -DCMAKE_PREFIX_PATH=C:/umicom/installed/applications -DBUILD_TESTING=ON
cmake --build build/static-preview --parallel 2
ctest --test-dir build/static-preview --output-on-failure --no-tests=error
& ".\build\static-preview\btb-static-preview.exe" "C:\umicom\Umicom-Bits2Banking\labs\native\framework-static-preview\site" GET /message.txt
```

<!-- Previous scope retained for review: Six tests were registered. -->
Eleven tests are registered: the original six inline cases, two owned-body text cases, two approved large assets, and a legacy SVG capacity refusal. For GET /message.txt, expect HTTP 200, representation-bytes 14, body-sent yes and a hexadecimal prefix 48 65 6c 6c 6f. These are expectations, not results from an executed qualification.

## Compare the responses

Run the executable again with HEAD /message.txt, GET /nested/note.txt, GET /absent.txt, GET /%2e%2e/message.txt and POST /message.txt. HEAD retains representation length but sends no body. The last three requests return deliberate 404, 403 and 405 responses. An HTTP refusal is a handled exchange, so this inspection program returns zero when it successfully produces that response. Parser or I/O failures return nonzero.

The fixture files use LF endings through the repository attributes. A changed line ending changes the exact representation size. Keep those bytes and the corresponding exact-size checks aligned deliberately; do not weaken a failing check without explaining the mismatch.

## Inspect approved artwork without a listener

Use the installed SDK's resource directory, exported as `UMICOM_FRAMEWORK_RESOURCE_ROOT` to CMake. With the prefix shown above and the default `share` data directory, the commands are:

```powershell
& ".\build\static-preview\btb-static-preview.exe" "C:\umicom\installed\applications\share\umicom\framework\resources\brand" GET /umicom-logo.svg --owned
& ".\build\static-preview\btb-static-preview.exe" "C:\umicom\installed\applications\share\umicom\framework\resources\brand" HEAD /umicom.ico --owned
```

Expect HTTP 200, the full file size and the source's hexadecimal prefix. Inspect the body before calling `UmiWebResponseBodyDestroy`. SVG uses `image/svg+xml` and ICO uses `image/vnd.microsoft.icon`. Without `--owned`, the large SVG should produce 413, demonstrating the preserved compatibility boundary.

The legacy output labels `wire-bytes` and `body-sent` describe the response that would be encoded. They are not network evidence. The new transport line explicitly states that no bytes were sent to a peer. Native socket delivery and browser appearance remain separate exercises.

The CMake target uses the installed Framework branding helper to attach the approved SVG and Windows ICO. It neither redraws the brand nor starts a GTK runtime. Terminal typography remains the terminal user's setting.

## Add a real local listener

After building or installing the matching native Umicom CLI, run:

```powershell
umicom preview --root "C:\umicom\Umicom-Bits2Banking\labs\native\framework-static-preview\site" --port 8080 --dry-run
umicom preview --root "C:\umicom\Umicom-Bits2Banking\labs\native\framework-static-preview\site" --port 8080
```

The first command only admits root/port syntax. The second binds 127.0.0.1. Open http://127.0.0.1:8080/message.txt in a browser, then stop with Ctrl+C in the server terminal. The selected fixture root has no index.html, so requesting / should return 404. No browser is opened automatically.

If umicom is not on PATH, use its full installed executable path. Keep the CLI outside directories that an installation command will replace. A standalone fallback is the existing Framework example:

```powershell
umicom-web-local-service-example --port 8080 --root "C:\umicom\Umicom-Bits2Banking\labs\native\framework-static-preview\site"
```

## Understand the boundary

UmiWebPreviewCreate owns the copied root, gate context, service and server. Start is a separate operation. Handle performs headless routing, while ServeNext performs one native exchange after Start. Destroy releases the server before its borrowed service. All operations belong to one owner thread.

<!-- Earlier inline-only explanation retained for review: The file policy accepts complete files smaller than 16 KiB. -->
The default lab command preserves the inline API and its limit of 16,383 bytes. Add --owned to select UmiWebPreviewHandleBody and receive a complete immutable body up to 1 MiB. Native umicom preview uses the owned-body path automatically. A URL ending in a slash requests index.html; directory listings are unavailable. Traversal, encoded separators, links and ambiguous portable paths are refused through the existing shared policy. Other ordinary files in the selected folder can be read, so use a dedicated export folder containing only intended content.

This host is for local development. There is no TLS, login, upload, remote deployment, public-host qualification or sandbox. Other local processes can form permitted headers; Host/Origin checks are not user authentication. Browser execution, native socket handling and platform-specific shutdown need their own qualification after the headless checks.

## Recover and extend

A package error means the SDK prefix or component needs attention. An undefined symbol commonly indicates mismatched headers and libraries. HTTP 404 means the chosen file was not found; 403 means a path or request gate was refused; 413 means the complete file exceeded the fixed preview limit. Startup failure may mean the chosen port is occupied. Try another explicit port and use that same port in the browser address.

Copy the fixture site into a separate practice folder before adding files. Inspect a text asset with a space in its name, percent-encode the space in the URL, and compare GET with HEAD. Preserve source revisions, SDK path, compiler, commands, actual output and skipped checks. Do not describe a headless response as a browser or deployment pass.

See [the C web server course](../../../content/lessons/05-engineering/building-a-web-server-in-c/index.md) for the complete sequence.
