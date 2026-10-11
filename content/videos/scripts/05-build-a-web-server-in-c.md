# Build a web server in C — video script

**Duration:** approximately 18–22 minutes

## Opening: 0:00–2:00

**Narration**

“When we open a website, our browser sends a request to another program. The program receives that request, finds the correct page and returns its contents. That second program is called a web server. In this lesson we will follow a real request through a web server written in C and use it to display the Bits to Banking website.”

**On screen**

Open the Bits to Banking homepage in a browser. Highlight the address `127.0.0.1:8765`. Show the diagram of a browser, socket, C request handler, file and response in the matching written lesson.

## HTTP and sockets: 2:00–6:00

**Narration**

“A socket is a connection endpoint provided by the operating system. The web server opens a listening socket on a particular address and port. In this case, the address is 127.0.0.1, which means this computer. We deliberately do not expose the server to the Internet.”

“When the browser asks for `/`, the server interprets that path as a request for `index.html`. The response contains a status code, a content type and the number of bytes being sent. These are not decorative labels; they tell the browser whether a request succeeded and how to handle the result.”

**Demonstration**

Display `GET / HTTP/1.1`, `Host: 127.0.0.1:8765`, `HTTP/1.1 200 OK` and `Content-Type: text/html`. Explain `200` and `404` with the actual server.

## Read the source: 6:00–11:00

**Narration**

“We keep the reusable networking and file-serving logic in Umicom Framework. The educational website does not need to write a second socket library. The public header declares the operations; the implementation handles them; and a small command-line program selects the action.”

“First the server checks the HTTP method. Then it validates the Host and requested path. The file opener must stay under the selected website directory. Only after these checks can the server read bytes and send them to the browser.”

**On screen**

Open `framework/include/umicom/education/site.h`, `framework/src/education/site_preview.c` and `framework/tools/umicom-education/main.c`. Show the path conversion and the streaming loop. Explain that the complete file is sent in bounded chunks rather than copied into one large fixed array.

## Build, test and launch: 11:00–16:00

**Narration**

“CMake describes the targets we want to build. Ninja asks the compiler to build the affected files. CTest runs executable checks. Passing a compiler check means the source compiled. Passing a test means a documented behaviour was exercised. We need both, and we still inspect the running server.”

**On screen**

Run the exact PowerShell configure, build and CTest commands from the [written server lesson](../../lessons/05-engineering/39-build-a-c-web-server.md). Run `umicom-education build --repo ...` and explain that MkDocs still performs HTML generation. Run `umicom-education serve --repo ... --port 8765`, then open the site in the browser.

## Investigate a failure: 16:00–19:00

**Narration**

“A web address is untrusted text. A malicious path might try to read `.git/config` or escape the approved directory using `../`. Our server refuses those requests. This is one reason we write tests for failures as well as successful requests.”

**Demonstration**

Request a missing page, a dot-file and a normal CSS file. Show the status codes. Explain that a local teaching server is not a production web platform: it has no TLS, public authentication or load-balancing infrastructure.

## Closing: 19:00–22:00

**Narration**

“You have now watched a C program accept an HTTP request, validate it and send back a real page. As you continue learning, investigate how the operating system creates sockets, how TCP transports bytes, and how Umicom Framework lets different applications reuse the same services. The source code and the full explanation are linked from the Bits to Banking lesson.”

**On screen**

Display the written lesson, Framework source repository and next lesson on building and booting Umicom Kernel. End with the project's community values and an invitation to explain one newly learned concept to someone else.
