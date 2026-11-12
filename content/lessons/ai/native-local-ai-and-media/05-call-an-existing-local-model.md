<!--
Umicom Bits2Banking
File: content/lessons/ai/native-local-ai-and-media/05-call-an-existing-local-model.md

PURPOSE:
Teach call an existing local model through framework.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original material; cited sources retain their own terms.
-->
![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Call an existing local model through Framework

## What you will learn
Send one reviewed prompt from C to a trusted local service, and identify the limits of that integration.

## The actual transport
UmiAiWorkspaceLocalProviderCreate targets http://127.0.0.1:&lt;port&gt;/v1/chat/completions. The inspected contract supports ports 1024–65535 and timeouts 100–60000 milliseconds. Its optional libcurl/json-c implementation disables proxies and redirects, bounds response size, validates decoded data and rejects tool-bearing replies. It requests a complete response with streaming disabled.

An OpenAI-compatible route is a protocol description. It does not imply every server supports the same parameters, response fields or error behavior. A service that forwards requests elsewhere is not private merely because its listening address is loopback.

## Prepare deliberately
1. Install and qualify a matching Framework SDK with the optional local HTTP provider.
2. Start a trusted server separately using its own documented workflow and an approved model.
3. Confirm the actual model ID, port, model license, runtime revision and destination behavior.
4. Read local.c. Notice the explicit command acknowledgement and the absence of automatic fallback.
5. Use a harmless prompt; command-line arguments may appear in shell history or process inspection.

After adapting the port and model ID to that server:
~~~powershell
.\build\btb-local-ai-routing.exe local --send-reviewed-prompt 8080 "your-installed-model-id" "Explain what a C pointer stores."
~~~

This command sends a request. It does not launch a server, install dependencies or download a model. The lab uses temperature 0.2, at most 128 output tokens and a 30-second deadline. Those choices keep the exercise bounded, not deterministically correct.

## Interpret results
A zero exit status means the adapter accepted the returned response. Read its finish reason: a length-limited answer may be incomplete. It is not a correctness score. The client escapes ASCII terminal control bytes before display; a richer UI needs its own reviewed Unicode and markup policy.

Exit 3 reports a missing optional provider in the installed Framework. Exit 2 reports invalid command input. Other failures report the Framework status and must not be presented as a successful answer.

## Exercise and recovery
Try the offline invalid-port check before the live exercise. It must reject 70000 before provider creation. Then plan how to distinguish connection refusal, timeout, unsupported model and malformed JSON.

**Answer:** test these layers separately. Do not install Conda to repair an absent C SDK component. Conda can support separate Python experiments, but this native client does not require a Python environment.

[Course contents](index.md) · [Next lesson](06-stream-cancel-and-display-text.md)
