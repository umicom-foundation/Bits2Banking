<!--
Umicom Bits2Banking
File: content/lessons/ai/native-local-ai-and-media/02-map-framework-and-applications.md

PURPOSE:
Teach map shared framework services to ai applications.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original material; cited sources retain their own terms.
-->
![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Map shared Framework services to AI applications

## What you will learn
Place reusable behavior in Framework and keep application clients small. Reusing one service also gives different applications the same failure and ownership rules.

## Start with the existing services
The inspected Framework tree already contains these contracts:

| Responsibility | Source contract | Application use |
| --- | --- | --- |
| Provider dispatch and policy | ai/runtime.h, ai/provider_registry.h, ai/policy.h | LLM and AI Chat submit a request through one dispatcher |
| Runtime descriptions and selection | ai/runtime_catalogue.h | Show model, capability, context and observed health |
| Source selection and reviewed jobs | ai_workspace/workspace.h | RAG prepares bounded evidence and preserves job state |
| Conversation records and privacy | ai/conversation_archive.h, ai/context_broker.h | Chat can retain explicit history and review context |
| Loopback inference transport | ai_workspace/providers.h | Send one request to a configured local chat server |
| Remote image/video requests | media_generation/seedream.h, media_generation/pixverse.h | Media reviews requests and retains receipts |
| Creative output and watermarking | creative_workspace/video_render.h | Compose and export branded media |

An interface in a header is a source contract, not a completed user journey. Read its implementation and application wiring before describing it as available to an end user.

## Keep the boundaries visible
A useful arrangement is:

~~~text
LLM / RAG / AI Chat / Media user workflows
                 |
Framework requests, policy, evidence, jobs and assets
                 |
Native model engine or explicitly selected adapter
                 |
Local weights / local service / separately approved remote service
~~~

Umicom's native training and generation code lives under ai/training. A transport adapter that calls another engine does not train or validate Umicom's model. Likewise, a remote image adapter written in C is native client code, but generation still happens remotely.

## Guided source reading
1. Open src/ai/runtime.c. Find the policy check before provider->generate.
2. Open include/umicom/ai_workspace/providers.h. Note the unsupported features of its loopback provider.
3. Open the LLM, RAG and Media module runtime.c files. Observe delegation to shared application runtime contracts.
4. Find adapters/gtk4/ai_workspace_panel_gtk4.c and creative_workspace_panel_gtk4.c. Trace a visible action to its shared service.
5. Record the exact SDK revision used for the lab.

**Exercise:** assign “store a prompt,” “draw a toolbar,” “parse a model response” and “decode model tensors” to their owners. Store/parse and model computation belong in reusable native services; the toolbar belongs in the relevant UI adapter.

**Recovery:** if installed headers and libraries disagree, fix the SDK selection. Copying a new header into an old installation can make compilation appear possible while linkage or ABI behavior remains incompatible.

[Course contents](index.md) · [Next lesson](03-select-capabilities-and-budget-context.md)
