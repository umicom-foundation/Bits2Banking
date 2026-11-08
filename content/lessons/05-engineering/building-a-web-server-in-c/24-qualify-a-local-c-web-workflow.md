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

## Read the source

[labs/native/framework-http-contracts/README.md](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-http-contracts/README.md). Use the matching local revision when working offline.

## Continue learning

[Course contents](index.md) · [Previous: Connect parser state to the transport owner](23-connect-stream-state-to-transport-ownership.md) · [Next lesson](25-select-a-static-document-root.md)
