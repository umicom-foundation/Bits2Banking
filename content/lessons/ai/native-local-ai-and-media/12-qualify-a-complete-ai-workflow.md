<!--
Umicom Bits2Banking
File: content/lessons/ai/native-local-ai-and-media/12-qualify-a-complete-ai-workflow.md

PURPOSE:
Teach qualify a complete ai workflow.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original material; cited sources retain their own terms.
-->
![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Qualify a complete AI workflow

## What you will learn
Build an evidence-based acceptance plan for chat, retrieval and media without collapsing them into one “AI works” checkbox.

## Start with the native lab
Read [the lab instructions](../../../../labs/native/local-ai-routing/README.md) and prepare a matching installed Framework SDK. The CMake project is a consumer; it does not build or replace Framework.

1. Configure and compile the lab using the documented toolchain.
2. Run its seven offline cases and retain actual results.
3. Confirm that a wrong port fails before transport creation.
4. Run a separate live request only against your reviewed local service.
5. Record SDK, executable, engine and model identities.
6. Inspect actual errors instead of substituting fixture output.

The lab is authored source with unexecuted qualification commands. Expected output teaches the intended behavior; it is not a claim that a particular installation passed.

## Build an acceptance matrix
| Layer | Evidence to collect | What it does not establish |
| --- | --- | --- |
| Offline routing | Exact candidate and refusal outcomes | Live model availability |
| Local request | Bound endpoint, accepted response, finish reason | Answer correctness |
| RAG | Source revision, captured evidence, citations | That all retrieved facts are current |
| Image generation | Valid decoded image, settings and model identity | Quality on arbitrary prompts |
| Video generation | Job identity, validated frames/container and playback | Universal hardware compatibility |
| Export | Approved watermark and retained provenance | Model output rights for every source |

Use harmless evaluation prompts and public practice documents. Record missing optional features as unavailable, and skipped checks separately from passes.

## Capstone
Design a local assistant that explains a C source file, cites selected documentation and creates a storyboard for a short tutorial. The first version may produce reviewed text and a media brief; actual image/video generation requires independently qualified adapters.

Submit a component diagram, provider capability table, request lifecycle, source-selection policy, asset provenance format and failure matrix. Include cancel, restart, missing weights, oversized reply, invalid UTF-8, stale model identity and unsupported media settings.

## Suggested assessment
Award credit for a correctly bounded request, truthful capability display, preserved evidence, explicit error handling and reproducible observations. Do not award model-quality credit for constant fixtures or image-generation credit for an uploaded avatar.

**Knowledge check:** when is a job complete? Only when its own terminal contract is satisfied. A received job ID proves submission at most; a finished file still needs content and playback checks.

## Recovery and next work
Work from the first failing layer upward. Fix transport before judging model responses, and fix evidence capture before tuning prompts. Keep private logs and credentials outside public lessons. Extend shared Framework services once, then wire each application to the same qualified boundary.

[Course contents](index.md)
