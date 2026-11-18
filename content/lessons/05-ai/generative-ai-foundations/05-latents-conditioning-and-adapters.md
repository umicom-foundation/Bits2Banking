<!--
Umicom Bits2Banking
File: content/lessons/05-ai/generative-ai-foundations/05-latents-conditioning-and-adapters.md

PURPOSE:
Understand latents, conditioning and image adapters

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Understand latents, conditioning and image adapters

[Course contents](index.md)
A latent is an internal representation, often smaller than raw pixels. A learned encoder may map an image into latents, and a decoder maps latents back to pixels. Text conditioning supplies information derived from a caption or prompt. These components must be compatible; combining arbitrary downloaded files is not a valid training configuration.

1. Identify the base architecture and exact component revisions: text encoder, tokenizer, image encoder/decoder if present, denoiser and scheduler configuration.
2. Read which components the training method updates and which remain frozen. Frozen means their parameters are not being optimized in that run.
3. Choose full fine-tuning or a compatible adapter method based on the task and available resources.
4. Check input scaling, color space, latent scaling and text formatting with a small inspected batch.
5. Save enough configuration to reconstruct the same pipeline when loading the result.

LoRA can train a low-rank update to selected layers. An adapter does not contain all base-model parameters. Its target layer names, rank and architecture matter. A small adapter file can still require a large base model and substantial activation memory. An image adapter is not automatically compatible with a video model merely because both are called diffusion models.


## Check

If a loader accepts an adapter file but the output is poor, investigate base revision, target modules, scaling and preprocessing as well as dataset quality. File loading success is only one check. Record the exact component set before comparing two runs.


## A model is often a compatible component set

| Artifact | What it contributes |
| --- | --- |
| Tokenizer and text encoder | Prompt representation |
| Image encoder/decoder | Pixel/latent conversion when used |
| Denoiser | Learned prediction at a specified noise level |
| Scheduler configuration | Noise and sampling rules |
| Adapter | Architecture-specific learned updates |

## Continue learning

[Previous: Understand a denoising objective before training](04-noise-denoising-and-loss.md) · [Course contents](index.md) · [Next: Plan and evaluate a small image-training experiment](06-plan-an-image-training-experiment.md)
