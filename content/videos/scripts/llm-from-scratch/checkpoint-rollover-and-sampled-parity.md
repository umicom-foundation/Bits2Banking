# Video lesson — Checkpoint identity, rollover and sampled parity

**Bits to Banking · Umicom Foundation**  
**Author and narrator:** Sammy Hegab

## Narration

Imagine a window of four tokens: A, B, C and D. The model has learnt absolute positional embeddings for positions zero through three. When E arrives, the retained window becomes B, C, D and E. B is now at position zero rather than one. Even though its text is unchanged, its numerical representation differs. The decoder therefore rebuilds all Transformer-layer key and value rows at this boundary using the canonical full-context calculation.

The same principle applies when the model's weights change. Old cached rows belong to their source checkpoint. A new checkpoint with identical tensor shapes may produce different Q/K/V projections. The session checks an identity digest before using the store; on mismatch it rejects the inference step rather than attempting to guess whether reuse is safe.

We can now design two independent tests. First, compare every new K/V row and every vocabulary logit against the full reference decoder. Second, run exactly the same token sampling policy and seed on both implementations. The sampled token arrays must agree across prefix growth and repeated rollover. One kind of equality does not replace the other. Logits can drift without immediately changing greedy token choices.

The worked case is a one-token prompt, six-position context, three layers and eight emitted tokens. Five transitions append within the growing prefix; the next two transitions rebuild the window. Count the work and check the outputs before attempting a Release benchmark.

## Visual storyboard

1. Draw the active query as a single row and the historical K/V as a retained matrix.
2. Show the shape and index invariants using the concrete example from the narration.
3. Compare reference and incremental paths with identical inputs and checkpoint identity.
4. Conclude with the difference between tested numerical behaviour and measured execution speed.
