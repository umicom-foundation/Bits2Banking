<!--
Umicom Bits2Banking
File: labs/native/local-ai-routing/README.md

PURPOSE:
Explain the original native routing lab and owner-run qualification.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original material; cited sources retain their own terms.
-->
![Umicom](../../../content/assets/branding/umicom-wordmark.svg)

# Local AI routing through the installed Framework SDK

This original C23 learning client exercises Framework routing, policy and provider ownership. Its optional live mode calls the existing Framework loopback provider. It does not contain a model engine, download weights or generate images/video.

Read the [paired course](../../../content/courses/native-local-ai-and-media/index.html) before the live exercise. Source and seven offline regression cases are authored; configure, compilation, CTest and live model behavior remain unexecuted for this lab.

## Prepare one matching SDK

1. Qualify and install Framework separately with its AI and AI workspace components. Keep headers and libraries from the same source revision and toolchain.
2. The live path also needs Framework's optional libcurl/json-c local-provider support. The program reports its absence rather than substituting a fixture.
3. Review the approved server and weights independently. Do not change vendor revisions just to run a lesson.
4. Run each command separately and stop on errors. Adjust the installation prefix if your qualified SDK uses a different location.

~~~powershell
Set-Location "C:\umicom\Umicom-Bits2Banking\labs\native\local-ai-routing"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug -DCMAKE_PREFIX_PATH="C:/umicom/installed/framework"
cmake --build build
ctest --test-dir build --output-on-failure
.\build\btb-local-ai-routing.exe offline selection
~~~

The expected CTest result is seven passing cases, all without contacting a model. This expectation is not executed evidence. The installed branding helper supplies approved SVG resources and embeds the Windows ICO. Inspect actual resources and icon appearance during qualification; this console client does not require GTK runtime deployment.

## Understand each offline case

| Case | Observation checked |
| --- | --- |
| selection | The smallest sufficient local chat fixture wins; the remote fixture is excluded |
| capability | Chat-only fixtures cannot satisfy embeddings |
| context | No fixture can accept 9000 requested context tokens |
| health | An unavailable small fixture is skipped for the available larger one |
| dispatch | Exactly one callback returns an explicitly labelled constant fixture answer |
| policy | The default policy rejects the remote fixture before invoking it |
| invalid-port | Port 70000 is rejected before provider creation |

The fixtures' model capacities and health are supplied data, not probed hardware. Catalogue selection does not load a model or guarantee sufficient memory. The six scenario checks compare status, stdout and stderr; ownership checks in dispatch/policy also verify one destroy callback. Checks remain active in release builds.

## Send one reviewed local request

This is a separate, deliberate action. First start a trusted service yourself and verify that it supports the required route and response schema. Replace the example model identifier with the actual supported identifier. Use a public practice prompt: shell history and process inspection can expose command arguments.

~~~powershell
.\build\btb-local-ai-routing.exe local --send-reviewed-prompt 8080 "your-installed-model-id" "Explain what a C pointer stores."
~~~

The request goes only to http://127.0.0.1:8080/v1/chat/completions through Framework. The provider disables redirects and proxies; the server itself must also be trusted not to forward the prompt elsewhere. This lab never launches the service. It requests a maximum of 128 output tokens with temperature 0.2 and a 30-second deadline.

The current transport does not support streaming, model downloads, credentials, external hosts or tool execution. It validates responses and can reject incompatible server output. It uses a borrowed cancellation token, but this single synchronous CLI does not install an interactive cancel handler. UI cancellation is separate work.

Exit zero means the returned response passed the adapter contract. It is not a factual-quality score. Exit 2 is invalid command input, exit 3 is absent optional transport, and exit 1 covers an observed contract or request failure. Other Framework failures are printed as numeric status values; compare them with the SDK's status header.

## Read the source in order

- main.c admits offline mode or the explicit live invocation.
- offline.c uses the existing catalogue, provider registry and runtime policy.
- local.c validates arguments, prepares a request, creates the existing local provider, transfers its ownership, generates once and destroys in the correct order.
- lab.h contains only teaching-client declarations.

Requests use static storage because this is a serial, single-process exercise. Production GUI operations need independent lifetime-managed state. Model output is not interpreted as HTML; ASCII terminal control bytes are escaped on display. The prompt's command acknowledgement is an affordance, not an authentication system.

## Troubleshoot one layer at a time

- Unknown component or target: select a complete matching installed SDK. Do not copy isolated headers into an older installation.
- Missing local provider: qualify Framework with its optional transport dependencies; installing a Python environment does not add a C component to the SDK.
- Connection refusal: verify the already-running service and port. Never silently switch to a cloud.
- Parse error: inspect a sanitized server response and its actual compatibility with Framework's codec.
- Timeout: record the outcome; do not assume the server stopped computing.
- Wrong output: distinguish transport success, model finish reason and answer quality.
- Resource load failure: inspect the SDK runtime-library path and staged branding resources.

No Framework implementation is copied into this lab. The Python reference project's source, prompts and artwork are not redistributed. Production service improvements should be authored once in Framework; the learning client remains thin.
