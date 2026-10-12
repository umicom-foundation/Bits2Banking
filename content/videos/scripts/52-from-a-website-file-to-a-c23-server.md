# Episode 52 — From a website file to a C23 server

**Running time:** approximately 10–14 minutes with the live build and browser demonstrations.  
**Companion reading:** [Chapter 152](../../lessons/05-engineering/152-serve-a-static-website-in-c23.md) and [Chapter 153](../../lessons/05-engineering/153-safe-http-paths-and-mime-types.md).  
**Source:** [`labs/native/http-loopback-server`](https://github.com/umicom-foundation/Bits2Banking/tree/main/labs/native/http-loopback-server).

## Opening — A website is made of files (0:00–1:30)

**On screen:** Show `sample_site/index.html` and `sample_site/assets/site.css` in the editor. Do not start with slides or an unexplained diagram.

**Narration:**

A web page can look complicated in the browser, but its foundation is straightforward. A file named `index.html` describes the document, and a stylesheet describes the appearance. The browser cannot read arbitrary files on a remote machine. Instead, it sends an HTTP request to a web server, which selects a resource, reads its bytes and sends a response.

Today we are extending the C23 web server developed in our earlier lesson. It already knows how to listen for TCP connections, check HTTP request headers and return a fixed HTML or JSON message. We will not replace those useful components. We will add one carefully defined new capability: serving files from a chosen directory, without giving the browser access to the rest of the computer.

That small requirement opens several important questions. What is an HTTP path? What is the difference between a URL and a Windows filename? What does the file type mean to a browser? And what happens if the request contains an unsafe path such as two dots?

## Demonstration — Build the same existing server (1:30–3:30)

**On screen:** Open PowerShell in `C:\umicom\Umicom-Bits2Banking`. Enter the following commands one at a time.

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\http-loopback-server" `
    -B ".\output\learning-build\http-loopback-server" `
    -G Ninja `
    -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" `
    -DBUILD_TESTING=ON
cmake --build ".\output\learning-build\http-loopback-server" --parallel 2
ctest --test-dir ".\output\learning-build\http-loopback-server" --output-on-failure
```

**Narration:**

CMake reads our build configuration. Ninja then asks the C compiler to compile the changed source files and link the executable. Notice that the library is shared by the demonstration programme and the test programmes. We do not maintain a special parser for tests that differs from the one the server uses.

The earlier GET, HEAD and header-validation tests still run. We have added tests for static paths and file access. If any test fails, we stop and read its error. Passing tests is useful evidence about the cases we exercised; it is not a promise that the server is secure against every possible network input.

## Demonstration — Choose the document root (3:30–5:30)

**On screen:** In the same PowerShell session, resolve the supplied sample site folder and start the server.

```powershell
$Root = (Resolve-Path ".\labs\native\http-loopback-server\sample_site").Path
& ".\output\learning-build\http-loopback-server\btb-http-server.exe" `
    --port 8765 --root $Root
```

**Narration:**

This command introduces the document root. It is the only directory whose contents may be returned to a browser. We use an absolute path so changing the shell's working directory cannot silently change what the server serves.

Now the server listens at `127.0.0.1`, the computer's local loopback address. Open the browser and enter `http://127.0.0.1:8765/`. The requested URL path is just a slash. The file router chooses `index.html`. The returned HTML references `assets/site.css`, so the browser sends a second request for the stylesheet. The result is a formatted page, but no new application logic was needed inside the HTML file.

Open `/health` as well. This is the same fixed JSON endpoint from our previous lesson. The new file-serving feature was added without removing the original function.

## Walk through the code — Trust boundaries (5:30–8:45)

**On screen:** Use the [static site request-path diagram](../../assets/diagrams/static-site-request-path.svg), then show `main.c`, `http.c`, `static_files.c` and `tcp_server.c` in that order.

**Narration:**

In `main.c`, the command-line parser reads `--root` and asks the static-file service to open that directory. That is an owned resource. The main function closes it only after the server has stopped. The folder is not just an unchecked string copied into every request.

In `tcp_server.c`, the connection handler reads the incoming bytes. HTTP request framing belongs to `http.c`. It checks that the method is GET or HEAD, that the Host header names our local address and that there is no unsupported request body. A browser's request target is still untrusted data at this stage.

The next check lives in `static_files.c`. A path such as `/assets/site.css` can become two directory components beneath our root. A path such as `/../private.txt` must be refused. We also reject the percent-encoded version of those two dots, encoded slashes, hidden metadata, invalid Windows device names and filesystem links that could redirect the read.

This is an important distinction in software engineering. Parsing a syntactically correct request does not grant authority to read a file. The file service makes its own decision based on the selected root and the real file handle.

On Linux the native implementation opens path components relative to the root descriptor and uses `O_NOFOLLOW`. On Windows it checks reparse points and the resolved final path. These two platforms provide different APIs, but the public lesson contract remains the same: read one admitted regular file beneath the selected directory.

## Demonstration — MIME and error responses (8:45–11:15)

**On screen:** Open a second PowerShell window. Issue requests while the server is running.

```powershell
curl.exe -I "http://127.0.0.1:8765/assets/site.css"
curl.exe -i "http://127.0.0.1:8765/does-not-exist.txt"
curl.exe --path-as-is -i "http://127.0.0.1:8765/%2e%2e/private.txt"
```

**Narration:**

The first request uses HEAD. The server describes the stylesheet, including `Content-Type: text/css`, without sending the stylesheet body. A missing file produces 404 Not Found. The attempt to escape above the document root produces 403 Forbidden.

The MIME type matters because a browser uses it to decide how to interpret the bytes. HTML and CSS are different media types. An unknown extension is returned as ordinary binary content, not executed as code. That is why this server does not run PHP or other scripts it finds in the folder.

One more useful experiment: change the HTML heading in the sample file and refresh the page. The server reads the file each time. You do not need to recompile the C application for an ordinary HTML edit.

## Closing — Continue learning (11:15–13:00)

**On screen:** Show the chapter links and the live repository source in the Bits2Banking website.

**Narration:**

We have taken a small but genuine step. Our C23 application now handles a network request, validates it, chooses one file under a selected root and returns the file with an appropriate content type. The earlier routes still work, and the tests now include more failure cases.

In the next episode we will look more closely at the transfer itself. We will serve a file much larger than our working buffer, compare GET and HEAD, and investigate what should happen when a client disconnects before the response is complete.

You can follow the code and practical exercises in Bits2Banking, and compare the educational implementation with the authoritative Umicom Framework web services. Study the code, experiment with one change at a time, and share what you have learned with someone else.
