<!--
Umicom Bits2Banking
File: content/lessons/ai/native-local-ai-and-media/09-plan-video-jobs-and-exports.md

PURPOSE:
Teach plan video generation jobs and exports.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original material; cited sources retain their own terms.
-->
![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Plan video generation jobs and exports

## What you will learn
Represent long-running generation and distinguish a job receipt, decoded frames and a playable exported video.

## Video has several stages
A video model may accept text, an input image or earlier frames. Its supported resolution, frame count, frame rate and conditioning differ from an image model. Generation can produce frames or a provider-owned job, while encoding turns frames and audio into a container. These are separate operations.

The inspected PixVerse contract prepares create/status requests and retains job identity. A confirmed creation is not a completed video. The remote adapter's behavior is useful source material for receipt handling, but it does not supply local video inference.

## Specify the job states
Use an explicit sequence such as reviewed → queued → running → completed, with failed, cancelled and interrupted outcomes. These names describe a proposed local media adapter, not a new API already provided by this course.

1. Capture prompt, model/weight identity, seed and dimensions before submission.
2. Assign a stable local operation ID; keep any provider job ID separately.
3. Display progress only from actual backend observations.
4. Bound queued work so one application cannot exhaust memory.
5. Check output frames or returned asset identity.
6. Encode and export through shared creative-workspace services.
7. Decode or play the resulting file as a separate qualification step.

A 1920×1080 RGB frame occupies 6,220,800 bytes before padding. One hundred twenty such frames occupy 746,496,000 bytes, about 712 MiB. This simple calculation excludes model weights, tensors, audio and encoder memory; it is not a total VRAM estimate. Stream frames through bounded storage where the backend permits it.

## Preserve branding and provenance
Framework's video-render contract has UmiVideoRenderApplyWatermark for a trusted SVG. It describes required rendering support and rejects a missing supported branded render instead of silently using an unbranded fallback. General SDK preparation remains compatible with unbranded callers, so application wiring matters.

Retain model identity, prompt, source asset rights, settings and operation ID beside the output. A generated clip and an edited clip should not lose their origin simply because both are MP4 files.

## Exercise and answer
A request times out after a server accepted it. Should the application submit the same prompt again? No automatic resubmission: the first job may still exist. Preserve its receipt or uncertainty and query status when the protocol supports it.

## Recovery
After a crash, inspect recorded operation identity and partial files before resuming. A successful encoder exit is useful evidence but does not prove correct duration, audio, visual content or playback. Validate those properties independently.

[Course contents](index.md) · [Next lesson](10-manage-personas-and-conversations.md)
