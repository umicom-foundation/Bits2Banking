# Episode 53 — Stream website files and follow Umicom service boundaries

**Running time:** approximately 11–15 minutes with demonstrations.  
**Companion reading:** [Chapters 154–156](../../lessons/05-engineering/154-stream-static-files-and-head.md).  
**Source:** [`labs/native/http-loopback-server`](https://github.com/umicom-foundation/Bits2Banking/tree/main/labs/native/http-loopback-server).

## Opening — The file does not have to fit in memory (0:00–1:45)

**On screen:** Show a large file icon, a labelled 8 KiB buffer and a browser. Then display the [streaming diagram](../../assets/diagrams/static-streaming-and-head.svg).

**Narration:**

When we first created a small HTTP server, we prepared the whole response in one C character array. That approach works for a short message, but what should happen if the file is 100 kilobytes, one megabyte, or larger? Should the programme allocate memory for the entire file before sending anything?

Not necessarily. A better teaching example is streaming. We read a small part of the file, send those exact bytes, then read the next part. The buffer can remain the same size regardless of how many total bytes we are sending, up to the file-size limit we deliberately chose.

There are several details we must get right. Network calls may transfer fewer bytes than requested. A file can end unexpectedly. And a browser can close its connection while the server is still sending. We need to inspect real return values rather than assume success.

## In the editor — Count bytes, not characters (1:45–4:15)

**On screen:** Open `static_files.h` and `tcp_server.c` and find `BTB_STATIC_STREAM_BYTES` and `BtbSendStaticFile()`.

**Narration:**

The lesson uses a fixed 8 KiB working buffer. The open file record also contains its expected total size, stored in a 64-bit unsigned integer. We do not use `strlen()` for file content because a binary file can contain zero bytes and because UTF-8 characters may occupy more than one byte.

Inside the streaming loop, the programme calculates how many bytes remain. It asks the native file reader for no more than the buffer capacity. The reader returns the actual byte count. The sender then tries to transmit those bytes. If `send()` accepts only part of them, our existing `BtbSendAll()` helper keeps track of the accepted part and continues with the remainder.

This distinction is central to reliable I/O programming. A successful function call does not always mean the entire requested transfer happened in one step. The contract tells us what actually happened, and the caller must honour that result.

The file is admitted as a regular, read-only file. The socket receives its own short timeouts and the entire client operation is given a ten-second time budget. These bounds prevent the educational programme from waiting without limit. They are not a guarantee of predictable performance or public-service resilience.

## Demonstration — A file larger than the buffer (4:15–6:45)

**On screen:** Configure the HTTP laboratory and run the static-file test.

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
ctest --test-dir ".\output\learning-build\http-loopback-server" `
    -R "bits2banking.http.static_files" --output-on-failure
```

**Narration:**

This test creates a file containing 151,241 bytes inside a temporary test directory. That is much larger than the 8 KiB buffer. The test opens it through the same native file API, reads successive chunks and compares every byte against the expected pattern. It finishes only when the number of bytes read equals the declared size.

Think about what this proves and what it does not. It demonstrates that our file API can read that test file in bounded chunks, that its byte count is coherent and that it closes resources correctly. It does not yet prove that every possible browser, network error or Windows path race has been handled. Those require additional tests and stronger platform-specific work.

## Demonstration — HTTP GET and HEAD (6:45–8:45)

**On screen:** Start the server with the sample site in one terminal. In the second, use `curl.exe`.

```powershell
curl.exe -i "http://127.0.0.1:8765/assets/site.css"
curl.exe -I "http://127.0.0.1:8765/assets/site.css"
```

**Narration:**

The first command requests GET. Look for the response headers, a blank line and the returned stylesheet. The second uses HEAD. It should contain the same status and Content-Length but no stylesheet body.

Why would we support HEAD? A client may need to inspect the size or media type of a resource before deciding whether to download it. Implementing HEAD also teaches us to separate response metadata from response content. Our old all-in-one buffer cannot simply be copied unchanged for every method.

Now request a missing file and a disallowed traversal path. These should not produce a successful response, even though the server itself remains running. A refusal is often correct behaviour.

## Source comparison — Framework and Kernel (8:45–12:45)

**On screen:** Show the source links in [Chapter 156](../../lessons/05-engineering/156-follow-static-files-through-umicom.md), opening the Framework HTTP example and the Kernel VFS header in separate editor panes.

**Narration:**

Our laboratory is an ordinary process. It relies on Windows or Linux for sockets, file handles and access to persistent storage. That is different from the native Umicom Kernel, which is responsible for privileged mechanisms such as process services, virtual filesystem interfaces and physical-device ownership.

Look first at Umicom Framework's `examples/web/local_service.c`. It demonstrates HTTP routes through shared Framework interfaces. Then open `include/umicom/web/static_files.h`. The established Framework service has a different preview limit and its own rooted-file rules. Our educational streaming implementation is not a replacement for that production-oriented source. We are learning the responsibilities involved so that we can understand and improve those services responsibly.

Next open Umicom Kernel's `include/umicom/kernel/vfs.h`. Notice that a filename, a filesystem node, an open-file description and a descriptor are separate concepts. The kernel does not give a user application a pointer to arbitrary device memory merely because the application knows a filename.

In `kernel/user_files.c`, the native research implementation associates admitted file-service operations with an actual scheduled task. The original Kernel and the GNU Linux-libre-based Umicom OS distribution are separate development tracks. Our C23 HTTP exercise runs on a normal desktop operating system; it does not claim to run on the native Kernel.

These distinctions matter. Reusing an architectural idea does not mean copying private implementation logic across repositories. It means understanding the contract and choosing a clear owner for each responsibility.

## Closing — Prepare the next lesson (12:45–14:00)

**On screen:** Return to the three stages: request parsing, rooted file selection, streaming response.

**Narration:**

We can now describe a complete, bounded, read-only HTTP file response. We know where a URL becomes a permitted filesystem request, where a file handle is owned, how bytes are sent and why failed work must not be reported as a complete success.

Next we will advance from static files to more structured HTTP routing and service composition. The learning material and executable code are available in Bits2Banking, with source links to the Umicom Framework and Kernel projects. Practise the tests yourself, then explain one of the boundaries to a fellow learner. Teaching reinforces understanding, and useful knowledge becomes more valuable when we share it.
