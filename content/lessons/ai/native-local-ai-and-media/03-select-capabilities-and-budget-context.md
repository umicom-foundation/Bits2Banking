<!--
Umicom Bits2Banking
File: content/lessons/ai/native-local-ai-and-media/03-select-capabilities-and-budget-context.md

PURPOSE:
Teach select capabilities and budget context.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original material; cited sources retain their own terms.
-->
![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Select capabilities and budget context

## What you will learn
Choose a runtime using capabilities, health and context capacity. Avoid silently turning a local request into a remote request.

## A catalogue is a description
UmiAiRuntimeDescriptor records identity, transport, capability bits, context capacity, output limit and health. It does not discover hardware by itself. A descriptor with available set to one is not proof that a server was contacted.

The current umi_ai_runtime_catalogue_select implementation filters unconfigured or unavailable entries, requires all requested capability bits, respects local_only and rejects insufficient context. Among remaining candidates it chooses the smallest sufficient context, then the runtime ID alphabetically. This is deterministic selection, not a speed or quality benchmark.

## Follow the offline lab
1. Read Descriptor in [offline.c](../../../../labs/native/local-ai-routing/offline.c).
2. Predict which of three fixtures will serve a local chat request requiring 1024 tokens.
3. Run the selection exercise after building the lab:
~~~powershell
.\build\btb-local-ai-routing.exe offline selection
~~~
4. Compare the complete output with “Selected lab.small; remote candidate excluded.”
5. Run capability, context and health to observe refusal or an alternative eligible local fixture.

The fixtures intentionally declare their health and capacity. No model is loaded. The capability exercise asks for embeddings; a chat-only fixture must not satisfy that request.

## Account for the complete prompt
The context window contains more than the last typed message. A practical budget includes system instructions, retained history, retrieved passages, formatting tokens and reserved output.

For a hypothetical 4096-token model, reserve 512 for output and 256 for formatting/margin. That leaves 3328 for all input. These are teaching numbers. Use the actual tokenizer and model metadata before claiming a prompt fits; character counts are not token counts.

Memory is a separate constraint. Weight storage, key/value cache, temporary tensors and backend overhead all matter. Free disk space does not establish sufficient RAM or VRAM. An estimate should show its assumptions and fail gracefully when the runtime rejects allocation.

## Exercise and answer
Why should a model with a large context limit not always win? A larger limit is not evidence of lower latency, adequate memory or higher quality. The current selector implements one predictable policy; a measured performance selector would require separate observations and rules.

## Diagnose refusals
When selection returns NOT_FOUND, inspect configured state, health, capability bits, context and local_only separately. Do not clear all constraints until something runs. Display the missing requirement and allow the user to change it deliberately.

[Course contents](index.md) · [Next lesson](04-own-providers-and-requests-in-c.md)
