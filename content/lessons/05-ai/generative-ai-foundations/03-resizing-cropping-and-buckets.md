<!--
Umicom Bits2Banking
File: content/lessons/05-ai/generative-ai-foundations/03-resizing-cropping-and-buckets.md

PURPOSE:
Resize and batch images without silently changing the task

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Resize and batch images without silently changing the task

[Course contents](index.md)
A model often expects dimensions compatible with its architecture. Resizing changes resolution; cropping removes part of an image; padding adds a border. These operations produce different training examples. Aspect ratio is width divided by height, so forcing every picture into a square can distort shapes.

1. Record original dimensions and orientation.
2. Choose the model’s supported size and alignment rules. Do not assume every model accepts every multiple of eight.
3. Choose a documented policy: crop, pad or resize while preserving ratio. Preview the result next to the caption.
4. Group similar aspect ratios or sizes into buckets if the trainer supports them. A bucket is a collection with compatible shapes, not a replacement for source-group splitting.
5. Apply augmentation only to training data under a recorded policy. Keep evaluation preprocessing stable.

An augmentation intentionally changes an example, such as a crop or color adjustment. It is useful only when the task’s meaning remains valid. Flipping an image of written text or directional machinery can invalidate the caption. Cropping a person out of an image described as “a person beside a bicycle” breaks the pair.

~~~text
Original: width 1200, height 800, ratio 1.5
Square crop: retains 800 × 800 before resizing; removes side content
Padded square: adds space to reach a square canvas
Stretched square: changes the shapes
These are different datasets even when saved at 512 × 512.
~~~


## Check

Review a sample from every transformation path, including portrait, landscape and unusually small inputs. A decoder succeeding does not prove a crop preserved the target. Record rejected examples and do not present a transformed dataset’s row count as a count of independent original sources.


## Continue learning

[Previous: Prepare image-caption pairs with provenance](02-caption-and-image-pairs.md) · [Course contents](index.md) · [Next: Understand a denoising objective before training](04-noise-denoising-and-loss.md)
