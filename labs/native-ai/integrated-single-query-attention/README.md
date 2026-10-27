# Practical lab: verify a cached decoder against the reference

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Language:** C23

## Learning goal

Show that eliminating unused historical query rows does not alter the newest query's forward result. Use the reusable Umicom Framework interfaces; this laboratory does not ship a second tensor engine or an application-local attention implementation.

## Experiment A — Attention row arithmetic

Take a two-row, one-head example with `q=[1,0]`, `K=[[1,0],[0,1]]` and `V=[[2,4],[6,8]]`. Compute `softmax([1/sqrt(2),0])` by hand, then compare the weighted output with the final row of the canonical tape's multi-head operator. Record the full vector, not the largest entry alone.

## Experiment B — Multi-layer decoder

Create a model with context six and layer counts one, two and three. Start from a one-token prompt. For each growing-prefix append, record the current cached K/V shapes and compare all new projection elements plus all 260 vocabulary logits against the canonical decoder. Use the Framework-owned `UmiAiTrainingStackedDecoderTraceProjections` oracle and the existing `UmiAiTrainingStackedKvStepPropose` proposal API.

## Experiment C — Boundary conditions

Continue until the first full-window rollover and a second rollover. The model has learnt absolute positions, so evicting the oldest token requires canonical reconstruction of all K/V layers. Repeat with a changed model checkpoint and confirm that the old cache is rejected. Test undersized output arrays and confirm that outputs remain unchanged.

## Interpretation questions

- Which calculation reports query rows and which reports scored keys?
- Which scenarios depend on learned-absolute-position semantics?
- Why does matching the sampled token fail to prove full-logit parity?
- What additional evidence is needed before making latency claims?

The relevant C23 test implementations live in Umicom Framework under `tests/ai_training`. This reader exercise reuses their public contracts without copying them into the educational repository.
