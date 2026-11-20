<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-web-server-in-c/24-qualify-a-local-c-web-workflow.md

PURPOSE:
Qualify the parser, exchange and local host separately

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Qualify the parser, exchange and local host separately

## Prepare

Collect the matching Framework and Bits2Banking revisions and local changes. Use the lab README for configure/build commands and the Framework local-service guide for the optional loopback host. Do not treat source examples or expected outputs as completed runs.

## Build the evidence in layers

First inspect and build the shared web component and C teaching clients. Run the five lab programs and the focused stream, frame and exchange checks. Then, if authorized for your environment, start the actual local host with an explicit port and observe it in a browser. Each step answers a different question.

## Record boundaries as well as success

Include a partial body, a binary body, a duplicate Content-Length, a size refusal, a short transfer and a post-dispatch write failure. For the local host, record resource/route responses and stopping behaviour. Keep skipped or unavailable checks separate from passes.

~~~text
Source + SDK identity | command | expected | actual | evidence
Stream fixture       | focused CTest | partition decisions | not run | pending
C teaching client    | btb-http-stream | owned A/NUL/B | not run | pending
Exchange fixture     | focused CTest | dispatch/delivery | not run | pending
Loopback host        | explicit launch | page/API response | not run | pending
~~~

## Explain a correction

Choose one observed mismatch and write the symptom, evidence, likely cause, repair and next check. If the SDK header was newer than its archive, describe a dependency mismatch. If a browser cannot connect because the process is stopped, describe a transport condition. Do not label either as a parser repair without supporting evidence.

## Exercise and worked answer

The stream tests pass and the teaching program prints its expected body, but no server was launched. What can the report claim? The recorded source passed those executed in-memory checks on that environment. Native socket behaviour, browser interaction and deployment remain unverified. A complete record makes those next steps explicit.

## Continue responsibly

Further web work can extend static-file delivery, application input policies, concurrency and reviewed deployment. Reuse existing Framework services before adding new protocol logic. The current subset still has no chunked input, protocol upgrades, persistent connections or production hosting qualification.

## Compare a native route with a separate application worker

The [loopback server lab](https://github.com/umicom-foundation/Bits2Banking/tree/main/labs/native/http-loopback-server) has its own native C23 route demonstration. Build it using its README, then start the lab on your machine with `--port 8765 --routes`. Use another port in both commands if 8765 is busy.

~~~powershell
& ".\output\learning-build\http-loopback-server\btb-http-server.exe" --port 8765 --routes
~~~

From a second PowerShell window, read the response and stop the lab with Ctrl+C when you finish.

~~~powershell
Invoke-RestMethod -Uri "http://127.0.0.1:8765/api/status" |
    Select-Object service, state, scope
~~~

Expect `bits2banking-routes`, `ready` and `loopback`. Trace the route in `learning_routes.c`. The compiled C program handles the request on your computer, and the client receives JSON. The endpoint only describes the lab route. A deployment readiness check also needs to prove that each required dependency can serve a request.

A reverse proxy receives the browser's HTTP request and forwards it to a separate service. The deployment needs a rule for which service owns each route, how it starts and how failed requests are reported.

| Application | Example hosting boundary | What to verify |
| --- | --- | --- |
| C, D or FreeBASIC | A compiled executable serving HTTP behind a proxy, or a C handler built and registered in the web server | The built program matches the host platform and responds on the configured route. |
| PHP | A PHP-FPM worker pool reached through FastCGI | The proxy reaches the intended pool and the pool can read the deployed script. |
| Python | An ASGI server running the Python application behind an HTTP proxy | The runtime can import and start the application with its deployed dependencies. |
| Java | A Java deployment in a server such as WildFly, reached over HTTP | The runtime accepted the deployment and the expected application path responds. |

For a design exercise, choose one worker, draw the request path and describe what the proxy should report while that worker starts, responds or is stopped. The loopback C lab exercises the local HTTP route. The worker examples describe separate deployments to study. Code that needs to run inside a standard browser requires a browser-supported format, such as JavaScript or WebAssembly with the host interfaces it uses. See [Apache FastCGI proxying](https://httpd.apache.org/docs/2.4/mod/mod_proxy_fcgi.html), [ASGI](https://asgi.readthedocs.io/en/latest/), [WildFly administration](https://docs.wildfly.org/38/Admin_Guide.html) and [WebAssembly on MDN](https://developer.mozilla.org/en-US/docs/WebAssembly).

## Check a native bytecode request

Umicom C writes a bytecode file containing instructions for its virtual
machine. Some bytes are zero. An HTTP client must send the complete file and
declare its media type so the native service can distinguish it from text.

1. Configure Umicom Applications with `-DUMICOM_LOCAL_WEB_CVM_PREVIEW=ON`
   and a compatible Umicom C SDK. Build `umicom-web-studio-local-service`.
2. Save `int main(void) { return 40 + 2; }` as `answer.uc`. Run
   `umicom-c compile answer.uc answer.umcb`. Start the local demo with
   `umicom-web-studio-local-service --port 8765` in its own terminal.
3. Send the artifact from the folder where you built it.

```powershell
curl.exe --fail --header 'Content-Type: application/vnd.umicom.c-bytecode' --data-binary '@answer.umcb' http://127.0.0.1:8765/api/cvm/preview
```

Expect value `42` and an instruction count in JSON. Repeat with a different
media type and expect HTTP 415. These responses qualify what your local
server accepted and returned. The machine executes on the server and the
client receives the computed result. Stop the demo with Ctrl+C.

## Read the source

[labs/native/framework-http-contracts/README.md](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-http-contracts/README.md). Use the matching local revision when working offline.

## Continue learning

[Course contents](index.md) · [Previous: Connect parser state to the transport owner](23-connect-stream-state-to-transport-ownership.md) · [Next lesson](25-select-a-static-document-root.md)
