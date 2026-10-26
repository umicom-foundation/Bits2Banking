# Build a Native Multi-Layer Transformer — Reading Path

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Licence:** MIT  
**Level:** Progressive native C23 / AI engineering

This sequence moves from the earlier [capacity-planning lesson](119-plan-native-transformer-gpu-support.md) to a **real, bounded, multi-layer CPU decoder**, while preserving the original single-block model, published checkpoints and educational narratives. The training implementation is owned by Umicom Framework; these are teaching manuscripts, not application-local runtime code.

## Learning sequence

1. **[Compose a real multi-layer model](121-build-a-real-multi-layer-transformer.md)** — explore one engineering problem with a worked exercise.
2. **[Check shapes](122-verify-shapes-through-a-transformer-stack.md)** — explore one engineering problem with a worked exercise.
3. **[Initialise weights](123-initialise-independent-transformer-layers.md)** — explore one engineering problem with a worked exercise.
4. **[Test causality](124-test-multilayer-causal-invariance.md)** — explore one engineering problem with a worked exercise.
5. **[Backpropagate](125-backpropagate-through-several-transformer-blocks.md)** — explore one engineering problem with a worked exercise.
6. **[Mask response loss](126-supervise-only-reviewed-completion-tokens.md)** — explore one engineering problem with a worked exercise.
7. **[Inspect memory](127-measure-stacked-graph-memory-and-rewind.md)** — explore one engineering problem with a worked exercise.
8. **[Encode a checkpoint](128-encode-a-separate-stacked-model-checkpoint.md)** — explore one engineering problem with a worked exercise.
9. **[Continue SGD](129-restore-and-continue-deterministic-sgd.md)** — explore one engineering problem with a worked exercise.
10. **[Run a held-out experiment](130-run-held-out-stacked-training-experiments.md)** — explore one engineering problem with a worked exercise.
11. **[Generate tokens](131-understand-greedy-generation-and-context-rollover.md)** — explore one engineering problem with a worked exercise.
12. **[Qualify evidence](132-qualify-capacity-correctness-and-model-evidence.md)** — explore one engineering problem with a worked exercise.

## Foundations and links

Read the [mathematics companion](../11-maths-for-ai/stacked-transformer-mathematics.md) alongside these lessons. For background, see [native supervised training](126-supervise-only-reviewed-completion-tokens.md) and [the previous model-sizing introduction](103-differentiate-model-size-and-memory.md). Full educational examples use synthetic byte-token inputs and remain unsuitable for production financial decisions.

## Testable Framework interface

- `umicom/ai/training/stacked_decoder.h` — configuration, logits, selected-token SGD, memory and raw greedy generation.
- `umicom/ai/training/stacked_checkpoint.h` — strict standalone checkpoint codec.
- `umicom/ai/training/stacked_experiment.h` — deterministic training/evaluation orchestration with exact-source split checks.

The earlier [native generation performance lessons](67-measure-decoder-and-kv-cache-work.md) discuss cache semantics for the **single-block** educational decoder. Their measurements must not be presented as proof of cached multi-layer generation.
