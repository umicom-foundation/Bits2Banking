# Lesson 209 — Prefill real K/V rows from an unpadded prompt

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Language:** C23  
**Scope:** Educational native model engineering; not production deployment.

**Learning objective:** Observe an entire context yet store only the valid prefix token rows.

## Why this matters

Prefill is the first acquisition of a model's K/V state. For a short prompt of length P, the current stacked decoder still expects a full context of C tokens. The capture therefore fills the remaining positions with BOS on the **right** and reads the K/V projections for all layers. Only the first P rows are admitted into the existing `UmiAiTrainingStackedKvStore`.

This is correct because causal attention prevents real prefix tokens from attending to later padding. However, the underlying calculation still evaluated C rows per layer; the storage owner merely retains P rows per layer. Never describe this as saving C−P rows of **executed** Transformer computation.

Each source row must be copied from `[layer][C][channel]` into compact `[layer][P][channel]` before calling StorePrefill. Skipping that repacking step would associate a later layer's padding rows with valid tokens. The Framework stages and validates the entire operation before exposing the result.

## Work through the numbers and tensor shapes

Take `C=8`, `P=3`, `L=2`, `channels=4`. One canonical trace computes `8 × 2 = 16` token-layer rows. The K/V owner accepts only `3 × 2 = 6` token-layer rows, occupying `2 × 3 × 2 × 4 × 4 = 192` bytes of meaningful K/V data, although its reserved capacity may cover all eight positions.

The last real token's logits come from row index `P−1=2`. The right-padding row index `C−1=7` answers a different question and must not be used to sample the next response token.

## Where the implementation lives

The reusable implementation belongs to `Umicom-Applications/framework`. Use the public `umicom/ai/training/stacked_projection_trace.h` or `umicom/ai/training/stacked_kv_capture.h` interfaces, depending on the task. The trace observes the **original** decoder through its established Transformer projection hook; the existing cache store handles K/V row ownership. No C23 neural-network computations belong in the Bits2Banking course. Run the Framework CTest cases for numerical qualification on the actual model before interpreting these services as integrated.

## Limitations and engineering evidence

The current observation pipeline performs a **complete canonical Transformer forward** for each observed prompt state. A smaller number of rows accepted into a store is not proof of fewer operations, lower latency or more accurate generated text. SHA-256 identifies checkpoint bytes but does not authenticate a publisher. No generated output should be executed as source code or treated as financial advice.

## Practice

**Question:** Why does the capture publish logits from position P−1 instead of position C−1?

<details><summary>Reveal the worked explanation</summary>

Only positions zero through P−1 belong to the real prompt. Later rows are right-side BOS padding. A causal decoder's logits at the last real token are the appropriate continuation distribution for this policy.

</details>

## Continue studying

[Previous lesson](208-bind-the-capture-to-a-frozen-checkpoint.md) · [Next lesson](210-verify-existing-rows-before-appending.md) · [View the browser lesson](../../courses/llm-from-scratch/lessons/209-prefill-real-kv-rows-from-an-unpadded-prompt.html) · [K/V projection learning path](kv-projection-observation-study-route.md).

*Service to Many Leads to Greatness.*
