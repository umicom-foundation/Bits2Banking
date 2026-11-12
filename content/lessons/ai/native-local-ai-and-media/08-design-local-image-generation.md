<!--
Umicom Bits2Banking
File: content/lessons/ai/native-local-ai-and-media/08-design-local-image-generation.md

PURPOSE:
Teach design a local image generation adapter.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original material; cited sources retain their own terms.
-->
![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Design a local image generation adapter

## What you will learn
Define a real image-generation boundary and distinguish it from a chat request or image upload.

## A separate inference pipeline
Text-to-image generation typically includes text conditioning, repeated numerical denoising steps and a decoder that produces pixels. A text model's chat endpoint does not implement those stages. The model family, weight files, tokenizer/encoder, dimensions and backend must be compatible.

The upstream [stable-diffusion.cpp project](https://github.com/leejet/stable-diffusion.cpp) is a C/C++ diffusion engine worth examining as an optional interoperability reference. Calling such an engine through C would still use an external implementation. It would not become an original all-C Umicom inference engine. No dependency or model is installed by this course.

## Reuse the existing media boundary
Umicom's Seedream adapter already separates a draft, immutable review plan, execution and owned validated image result. It calls a remote service. A local implementation should reuse common image surfaces, jobs, provenance and export services while defining its own backend contract; changing the remote adapter's URL is not enough.

A proposed local image draft should describe model identity, positive/optional negative conditioning, seed, dimensions, sampler, steps and output policy. Reject unsupported combinations explicitly. A seed helps repeat an experiment; it does not promise identical pixels across hardware, kernels or backend revisions.

## Build a staged design
1. Review the draft without starting inference.
2. Resolve approved model files and verify their identities.
3. Estimate memory with visible assumptions and reserve bounded resources.
4. Run on a worker that supports progress and cancellation.
5. Validate dimensions, channel format and decoded pixel extent.
6. Transfer the image into an existing UmiMediaImageSurface owner.
7. Apply the approved Umicom identity through the shared export workflow and inspect the saved output.

A byte buffer is not automatically a valid image. Check multiplication when calculating row size and total bytes; reject dimensions whose allocation would overflow.

## Exercise
Write a contract table for “512×512 RGB, fixed seed, 20 steps.” Mark every value as a teaching assumption until a selected backend admits it. Add failures for missing weights, unsupported dimensions, cancellation after a step and invalid output.

**Expected result:** no output asset is marked complete merely because a progress value reaches 100 percent.

## Recovery
Keep partial output separate from accepted assets. Never retry an unknown remote operation automatically. Local cancellation also needs cleanup: release buffers and report whether any newly created partial file remains. Actual quality, GPU compatibility and watermark appearance require separate executed checks.

[Course contents](index.md) · [Next lesson](09-plan-video-jobs-and-exports.md)
