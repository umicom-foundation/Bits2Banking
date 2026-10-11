# Build and inspect a lightweight web server in C

A **web server** is a program that receives requests using protocols such as HTTP and sends responses containing webpages, images, stylesheets or other files. Your web browser is an HTTP client. It asks for a page; the server finds the corresponding resource and sends it back.

This lesson uses a native C23 preview server from Umicom Framework to serve the actual Bits to Banking website on your own computer. Unlike a one-line sample that responds with a fixed string, this application can stream generated HTML, CSS, JavaScript, illustrations and book files.

## 1. Understand one HTTP request

When your browser visits `http://127.0.0.1:8765/`, the address has three important parts:

- `http` is the protocol.
- `127.0.0.1` is the **loopback address**, referring to your own computer.
- `8765` is the **port**, an identifier that helps your operating system send the connection to the correct listening program.

The browser might send:

```http
GET / HTTP/1.1
Host: 127.0.0.1:8765
```

`GET` asks for a representation of the resource `/`. The server maps `/` to `index.html` and might respond:

```http
HTTP/1.1 200 OK
Content-Type: text/html; charset=utf-8
Content-Length: 32
Connection: close
```

The response is followed by file bytes. `200` means the request succeeded. `404` means the requested resource does not exist. The MIME type tells the browser how to interpret the bytes.

## 2. Trace the complete path

```text
Browser
   │ HTTP GET /lessons/
   ▼
127.0.0.1:8765  →  socket listener
   │
   ▼
C request parser → method + Host + URL checks
   │
   ▼
Safe path resolution → lessons/index.html
   │
   ▼
Open regular file beneath approved site root
   │
   ▼
Send response headers, then file in fixed-size chunks
   │
   ▼
Browser renders the completed page
```

A **socket** is an operating-system endpoint used to send and receive network data. The code accepts one local connection, reads a bounded request header, chooses a file and sends the result. It does not run a web browser or interpret JavaScript; the browser does that.

## 3. Find the real C code

The implementation belongs to the reusable Umicom Framework, not to a second network stack inside Bits to Banking:

- `framework/include/umicom/education/site.h` — the public C contract.
- `framework/src/education/site_preview.c` — HTTP request handling, rooted file opening and streamed responses.
- `framework/src/education/site_content.c` — publishing existing book content and official branding.
- `framework/tools/umicom-education/main.c` — the command-line interface.
- `framework/tests/education/` — path and publication tests.

The Framework already has an established [Web Server API](https://github.com/umicom-foundation/umicom-framework/tree/main/include/umicom/web) and a [local service example](https://github.com/umicom-foundation/umicom-framework/blob/main/examples/web/local_service.c). Its current static-file response body is deliberately limited to less than 16 KiB. This preview utility uses a streaming file sender for larger MkDocs output. Integrating the streaming mechanism into the existing web-service architecture is a later engineering task; there is no reason to duplicate it inside every application.

## 4. Configure and build on Windows

Open PowerShell in the Umicom Applications repository:

```powershell
Set-Location "C:\umicom\Umicom-Applications"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"

cmake -S ".\framework\tools\umicom-education" `
      -B ".\build\umicom-education" `
      -G Ninja `
      -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" `
      -DBUILD_TESTING=ON

cmake --build ".\build\umicom-education" --parallel 2

ctest --test-dir ".\build\umicom-education" --output-on-failure
```

This builds the native command and focused tests without reconfiguring or deleting your main `windows-ucrt64-all-debug` build. A successful test run verifies path validation, input publication and the CLI's documented help. Network behaviour also needs the separate HTTP checks below.

The command is named `umicom-education.exe`, not `umicom.exe`: it is a separately built Framework-owned tool while we validate this capability. It can later become part of the existing Umicom command's subcommand catalogue without replacing any current commands.

## 5. Prepare the website files in C

Set the path to the new executable for this PowerShell session:

```powershell
Set-Location "C:\umicom\Umicom-Applications"

$Education = ".\build\umicom-education\bin\umicom-education.exe"
$Books = "C:\umicom\Umicom-Bits2Banking"

& $Education doctor --repo $Books
& $Education prepare --repo $Books
& $Education verify --repo $Books
```

`doctor` checks the repository and brand directory. `prepare` copies the original Islam volume and official Umicom branding into the website tree without altering the original manuscripts. It preserves different published files unless an explicit `--refresh` is requested. `verify` checks for the expected published assets.

The existing Python and PowerShell preparation programs are retained so you can compare results; there is no need to delete them.

## 6. Generate the website

Run:

```powershell
& $Education build --repo $Books
```

This command starts the existing MkDocs renderer as a child process and checks its exit result. Python and MkDocs are **still required for generating the HTML**; the C command does not pretend to implement Markdown, PDF or Word conversion yet.

When the build succeeds, the generated site lives under `C:\umicom\Umicom-Bits2Banking\site`. It contains an `index.html` file and the assets used by its pages.

## 7. Start the C web server

```powershell
& $Education serve --repo $Books --port 8765
```

The server displays:

```text
Serving read-only site at http://127.0.0.1:8765/
Folder: C:\umicom\Umicom-Bits2Banking/site
Stop with Ctrl+C.
```

Open `http://127.0.0.1:8765/` in your browser. You should see the compiled Bits to Banking website, including the Umicom logo, its chapters and links to the relevant Umicom repositories. Stop the server with **Ctrl+C** when finished.

If the port is occupied, choose another unused port such as `8766`. Ports below 1024 are deliberately refused by this learning tool.

## 8. Inspect responses without a browser

Keep the server running in one terminal. Open another PowerShell terminal:

```powershell
Invoke-WebRequest "http://127.0.0.1:8765/" -Method Head
Invoke-WebRequest "http://127.0.0.1:8765/" -Method Get
```

The `HEAD` request asks for the same response headers without downloading the response body. Look at the status code, Content-Type and Content-Length. A request to `/missing-page.html` should receive `404 Not Found`.

## 9. Why a file server must check paths

Suppose someone sends a URL such as `/.git/config`. A poorly designed server might reveal its Git configuration. If a URL contains `../`, it might try to climb above the website directory and read an unrelated file. Symbolic links may also point outside the approved site root.

The Framework-owned example rejects dot-prefixed path segments, ambiguous separators, directory traversal, control characters and device-name patterns. On POSIX systems, it opens each path relative to an already opened directory, rejecting symbolic links. On Windows, it checks reparse-point attributes for the local preview. It also checks the HTTP `Host` header to avoid serving files to an unexpected hostname.

The important rule is not simply “remove `..` from a string”. **Only normal files inside the explicitly selected site root may be served.** A URL is untrusted input, not a filesystem instruction.

The Windows adapter in this first edition uses narrow Win32 file paths and assumes the trusted local site tree is not concurrently manipulated by an adversary. Full Unicode path handling and hardened Windows handle-relative traversal remain follow-on tasks. Neither this preview nor a socket example should be exposed as an Internet-facing production server.

## 10. Why we do not rewrite the complete web server in Assembly

Assembly operates at the instruction-set level. Network connections, HTTP parsing, path security, file ownership and operating-system calls are easier to review and port in C. Assembly may be justified for a *small, measured operation*, such as a byte scanner or checksum, once there is a proven performance problem.

An Assembly helper cannot bypass the protocol rules or ownership checks established by its C caller. Its calling convention, input bounds and return value must be documented and tested against an equivalent C implementation. This is the approach used by Umicom Framework's Assembly learning exercises.

### Exercises

1. Start the native server and record the `Content-Type` for a `.css` file.
2. Request `/missing-page.html` and explain `404`.
3. Request `/.git/config`; explain why it is forbidden.
4. Compare a small HTML file with a generated file larger than 16 KiB. Both should stream through the native preview without truncation.
5. Follow `UmicomEducationResolveUrlPath()` from the URL through the result returned to its caller. Which invalid inputs does it reject before any file is opened?

Continue with [HTTP byte scanning in C and Assembly](42-http-and-assembly.md), [Safer C](../03-native-code/36-safer-c-programming.md), then [Umicom Kernel first boot](../06-umicom/40-boot-umicom-kernel.md).
