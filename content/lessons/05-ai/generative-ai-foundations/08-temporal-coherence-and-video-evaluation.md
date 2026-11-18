<!--
Umicom Bits2Banking
File: content/lessons/05-ai/generative-ai-foundations/08-temporal-coherence-and-video-evaluation.md

PURPOSE:
Evaluate motion and temporal coherence

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Evaluate motion and temporal coherence

[Course contents](index.md)
Temporal coherence means that related content remains consistent across time. A frame can look good by itself while a video flickers, changes identity or violates motion continuity. Video evaluation therefore needs more than selecting one attractive thumbnail.

1. Define motion requirements, such as a ball moving continuously left to right, and appearance requirements, such as retaining its color.
2. Create held-out prompts and reference cases that test stationary scenes, camera motion, subject motion and occlusion separately.
3. Review the entire generated clip at its intended timing, then inspect frames around visible failures.
4. Record flicker, identity drift, inconsistent geometry, repeated/frozen frames and caption mismatch as separate observations.
5. Compare with a fixed baseline and retain failed examples. If audio is generated or preserved, evaluate synchronization and content separately.

A seed identifies a random initialization choice within an implementation. It is useful metadata, not a quality label. Different seeds reveal different failures. Comparing one favored seed from a candidate with one poor baseline seed is a biased experiment. Metrics can help summarize results, but their assumptions and sensitivity must be understood.

A native Media application should keep generation job state, cancellation, preview ownership and output provenance separate from model quality claims. A job reaching completed means an operation finished under its contract; it does not mean the resulting scene is accurate, safe for a specific use or visually coherent.


## Practice

Write an evaluation sheet with five prompts and three criteria per prompt. Define what counts as a failure before viewing the candidate outputs. Then explain which criteria can be measured automatically and which need human review. Do not claim an automated score measures a concept it was not designed to measure.


## Continue learning

[Previous: Prepare video clips with timing and group identity](07-video-timing-and-clip-groups.md) · [Course contents](index.md) · [Next: Bound memory and recover image/video training work](09-memory-checkpoints-and-recovery.md)
