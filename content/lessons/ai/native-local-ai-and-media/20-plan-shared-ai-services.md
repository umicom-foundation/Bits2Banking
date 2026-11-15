<!--
Umicom Bits2Banking
File: content/lessons/ai/native-local-ai-and-media/20-plan-shared-ai-services.md

PURPOSE:
Teach plan reusable AI services for Media and LLM applications.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original material; cited sources retain their own terms.
-->
![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Plan reusable AI services for Media and LLM applications

Use the previous lessons to decide where shared behavior belongs. Framework should own reusable model, transport, storage and job contracts. Media, Studio, Trader and LLM should compose those services according to their own workflows. A lesson or a capability table is a design input, not evidence that an integration is available.

## Start from inspected Framework services

- local_models/manager.h already defines local model management contracts. Extend it only after comparing required model and runner identity rules.
- ai/retrieval.h, ai/chunk.h and ai/rag.h already separate ranking, source identity and prompt composition. Use them for the first deterministic retrieval lab.
- media_generation/pixverse.h already models prepared requests and uncertain remote creation. Study its ownership rules without treating its provider protocol as interchangeable with Runway.
- creative_workspace/workspace.h already owns project persistence and revision-aware edits. Media import should use that boundary instead of updating independent UI state and disk files separately.
- Installed SDK exports already let an independent application link selected services. The archive target packages those configured exports; it does not add provider capabilities.

## Useful next capabilities

1. ComfyUI adapter: reviewed graph identity, node capability discovery, bounded request/reply handling, progress reconciliation and explicit cancellation scope.
2. Runway adapter: provider-version-specific drafts, durable task IDs, bounded polling, uncertainty after timeout and controlled asset retrieval.
3. Retrieval evaluation: a fixed question corpus, expected source identities, ranking metrics and citation provenance.
4. Tensor runtime adapters: explicit element types and shapes, checked byte sizes, backend capability probing and output ownership.
5. Shared media provenance: model and source-asset identities, generation settings, imported byte digests, branded export and playback checks.

These are proposed work items. This continuation adds SDK packaging and educational material; it does not claim that those provider adapters, a diffusion engine, video inference or a universal compiler are complete. Prioritize a vertical slice that can be qualified from request review through a verified result.

## One end-to-end lab

1. Select one locally controlled model service and one tiny reviewed input.
2. Prepare a draft without I/O. Assert that invalid dimensions, unknown model identity and oversized text are refused.
3. Execute through a fixture transport first. Simulate acceptance, malformed replies, timeout and cancellation races.
4. Persist the observed receipt using shared storage. Restart the client and reconcile that same operation.
5. Import a valid output into a project. Reject an output that escapes the chosen destination or fails format checks.
6. Export with the approved Umicom SVG watermark, then inspect the actual rendered file and playback behavior.

## Evidence to keep

Record code revision, SDK identity, runtime/model digest, test inputs, environment and observed outcomes. Keep passes, failures and skipped coverage separate. Measure latency and memory on the selected hardware; do not infer performance from a different machine or from a synthetic transport.

## Review question

Can every application mark image generation available because the common Framework package installed successfully? No. Installation establishes file availability only. The chosen adapter, model, device, output pipeline and application interaction each need their own qualification.

[Course contents](index.md) · [Previous lesson](19-language-translation-and-runtime-contracts.md)
