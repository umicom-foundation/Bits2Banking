<!--
Umicom Bits2Banking
File: content/lessons/05-ai/generative-ai-foundations/01-pixels-frames-and-models.md

PURPOSE:
Start with pixels, frames and generative models

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Start with pixels, frames and generative models

[Course contents](index.md)
A digital image is a grid of pixels. Each pixel stores channel values, often red, green and blue. A video is a timed sequence of frames, usually accompanied by audio and metadata. A generative model learns patterns that let it create new samples. Saving an image file and training such a model are very different operations.

A tensor is a multidimensional array of numbers. An image tensor might be described as height by width by channels, or channels by height by width; the loader and model must agree. A batch adds another dimension. A video adds time. The order is part of the contract, not something to guess because the total element count happens to match.

1. Draw a two-by-two image on paper. Give each pixel three channel values between 0 and 255.
2. Count twelve channel values: 2 × 2 × 3. At one byte per value, the raw pixel storage is twelve bytes. File headers and compression are separate.
3. Make four frames of that image. The raw channel count is forty-eight, before any model activations or training state.
4. Write the tensor order beside the example. Transposing dimensions changes interpretation even if storage size stays the same.

Diffusion models learn to reverse a controlled corruption process, often in a compressed latent representation. Autoregressive models predict pieces sequentially. Generative adversarial networks use competing generator and discriminator objectives. These are families of methods, not interchangeable file formats. This course uses diffusion as the main conceptual example while keeping model-specific training requirements explicit.


## Check

A PNG is an image container, not a tensor shape declaration. A video’s frame count does not reveal its duration without timing information. An inference pipeline that generates images from a prompt is not automatically a training pipeline.


## Continue learning

[Course contents](index.md) · [Next: Prepare image-caption pairs with provenance](02-caption-and-image-pairs.md)
