# Checkpoint-bound KV capture and absolute-position rebuilds

**Sammy Hegab · Umicom Foundation**  
**Format:** Narration with a four-token sliding-window animation.

## Audience and outcome

Students should leave able to explain why checkpoint identity matters, why positional rebasing invalidates a K/V cache, and how the Framework handles a complete replacement without partial state changes.

## Opening scene — One letter moves

Place four labelled cards on screen: A, B, C and D. Positions underneath them read 0, 1, 2 and 3. Now insert E and slide the cards left: B, C, D and E. B has moved from position one to zero; D has moved from position three to two.

In Umicom's currently trained stacked decoder, each absolute position has a learned embedding. The representation of B depends on which embedding is added to B. Because B's position changes, its query and key projections may change too. Upper-layer keys can change further because the hidden states passing between Transformer blocks change.

## Explain the Framework ownership

The K/V store owns copies of projection rows; it cannot invent their values. The canonical decoder is the only authority for the model's actual projection mathematics. The capture first verifies the model's approved checkpoint identity, computes a fresh reference for the shifted full context, and submits all layers and positions to the cache owner's `ReplaceRolled` operation. The store refuses any inconsistent token shift, invalid shape or non-finite component.

## Calculate the accepted replacement

For two Transformer layers, context length four and four channels, a full replacement accepts eight token-layer rows for keys and eight corresponding value rows. Each K and V tensor has `2×4×4=32` floats. Together they need 256 raw FP32 bytes. The old projection values are not retained as if their positional meanings were unchanged.

## Integrity versus identity

Explain why a 32-byte SHA-256 digest may detect mismatched checkpoint bytes but does not itself certify the publisher. If model weights change after a cache was built, the borrowed capture becomes stale and must be rejected. Verification of publisher authority is a separate security procedure.

## Further study

A rotary-position model might support different retention semantics, but it requires separately identified training and numerical qualification. It is not acceptable to relabel this existing learned-absolute checkpoint and assume compatibility.

## Practice

If a model has three layers and a six-token window, how many token-layer K/V row pairs must be refreshed after a full rollover? **Eighteen**. Ask why a mere pointer shift is wrong: it does not recompute the new positional mathematics or revised upper-layer states.

[Read Lesson 211](../../../lessons/10-native-ai/211-rebuild-all-layers-after-absolute-position-rollover.md).
