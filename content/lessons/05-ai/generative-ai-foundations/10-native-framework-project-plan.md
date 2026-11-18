<!--
Umicom Bits2Banking
File: content/lessons/05-ai/generative-ai-foundations/10-native-framework-project-plan.md

PURPOSE:
Build a native generative-AI project in verifiable stages

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Build a native generative-AI project in verifiable stages

[Course contents](index.md)
A native implementation should be developed as a set of tested contracts. Replacing a user interface or a Python launcher does not implement a model architecture. Start with data and resource management, then numerical primitives, compatible model loading, inference and training. Each stage needs evidence before the next product claim.

1. Implement and verify dataset manifests, source grouping, bounded decoding and deterministic preprocessing.
2. Verify tensor shapes, numeric operations and gradients against small known examples. Use independent reference values, not a test that repeats the same formula incorrectly.
3. Add architecture-specific weight loading with explicit shape, dtype and version checks. Reject unsupported formats honestly.
4. Implement inference for a narrowly defined model and compare outputs or intermediate values under documented tolerances.
5. Add optimizer and checkpoint state for training, then verify a tiny controlled learning task and restart behavior.
6. Integrate thin Media/LLM clients using shared Framework jobs, memory budgets and resource ownership. Qualify cancellation and failure before long runs.

A useful project can begin with a tiny model and original geometric data. Define success as a measured behavior, such as learning a controlled reconstruction task, before promising general image generation. Keep training code original, respect external formats and licenses, and document any external reference tool used for comparison.


## Capstone

Prepare a project specification containing dataset schema, source permissions, group split, shapes, memory budget, target architecture, evaluation cases and checkpoint contract. Mark every unimplemented stage. That specification is a practical starting point for native Framework development; it is not a claim that all competing frameworks’ features already exist.


## Keep capabilities and evidence separate

| Implemented building block in this continuation | Still separate work |
| --- | --- |
| Grouped C training/evaluation partition | Duplicate detection, chronological policy and large streaming split |
| Beginner datasets and native ABI examples | Production diffusion/video training engine |
| Small focused regression checks | Full application, installed SDK and GPU qualification |

## Continue learning

[Previous: Bound memory and recover image/video training work](09-memory-checkpoints-and-recovery.md) · [Course contents](index.md)

[Continue to the native exercise](11-run-a-native-denoising-experiment.md)
