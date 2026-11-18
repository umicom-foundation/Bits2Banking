<!--
Umicom Bits2Banking
File: content/lessons/05-ai/generative-ai-foundations/07-video-timing-and-clip-groups.md

PURPOSE:
Prepare video clips with timing and group identity

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Prepare video clips with timing and group identity

[Course contents](index.md)
Video adds time. Frame rate describes how often frames are presented, but some files use variable timing. A clip has duration, spatial dimensions, frame timestamps and sometimes audio. A list of unrelated images is not automatically a coherent video dataset.

1. Keep the original video and record its source and permissions.
2. Decode a short clip with a tool that exposes timing. Record frame timestamps, dimensions and color handling.
3. Choose a documented sampling policy, such as a supported fixed frame rate and clip length. Explain how variable-rate input is resampled.
4. Keep all clips and extracted frames from the same source recording in one leakage group.
5. Pair the clip with a caption describing action over time, and review that caption against the entire clip.
6. Validate any audio alignment separately; removing or resampling video frames can break synchronization.

~~~text
Frame index       0       1       2       3
Presentation time 0 ms    40 ms   80 ms   120 ms
This example uses 25 frames per second.
Four frames span sample times through 120 ms; container duration
and final-frame display interval must be handled explicitly.
~~~

A video trainer may require a fixed frame count, stride and resolution. The model’s temporal architecture determines supported shapes. Adding a time dimension multiplies data and activation costs, and attention can grow faster than linearly with the number of positions. Do not multiply an image memory estimate by frame count and call it a measured training budget.


## Exercise

Two ten-second clips overlap by five seconds. Should one be training and the other validation? Usually no, because they share source content. Assign them the same source group. The Framework grouped splitter can preserve assigned groups, but it cannot infer overlap from filenames or timestamps.


## Continue learning

[Previous: Plan and evaluate a small image-training experiment](06-plan-an-image-training-experiment.md) · [Course contents](index.md) · [Next: Evaluate motion and temporal coherence](08-temporal-coherence-and-video-evaluation.md)
