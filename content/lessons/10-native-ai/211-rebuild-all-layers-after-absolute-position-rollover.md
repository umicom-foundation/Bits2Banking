# Lesson 211 — Rebuild every layer after learned-position rollover

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Language:** C23  
**Scope:** Educational native model engineering; not production deployment.

**Learning objective:** Understand the exact point where positional rebasing makes old KV rows invalid.

## Why this matters

A finite context cannot grow indefinitely. Once C tokens are retained, the next token forces an eviction. Under the current learned absolute positions, every surviving token moves left by one index. Its token embedding is now combined with a **different positional embedding**, which changes the input to the first Transformer block. The effect may propagate through every upper layer.

The existing storage owner deliberately exposes `ReplaceRolled` rather than silently shifting its K/V rows. The capture constructs the shifted token sequence, executes a fresh canonical full-context trace, and supplies newly calculated K/V rows for **all layers and all positions**. Only after validation does the complete replacement become visible.

RoPE and relative-position architectures have different invariants; they are not a licence to change the semantics of this already trained learned-absolute checkpoint. Nor does a single-block rotary demonstration qualify upper-layer cache reuse in a deep network.

## Work through the numbers and tensor shapes

For context four, old IDs `[A,B,C,D]` become `[B,C,D,E]` after the new token E arrives. Position of B changes from 1 to 0; position of D changes from 3 to 2. With three layers, the full replacement accepts `3 × 4 = 12` fresh token-layer K/V rows. The number of retained tokens stays four; the number of complete rebuilds increases by one.

In a two-layer four-token example with a two-token prefill, two safe appends and one rollover: admitted rows are `2×2 + 2 + 2 + 2×4 = 16`. Four store operations never imply that only 16 token-layer rows were computed. Four canonical observations actually compute `4×2×4=32` rows.

## Where the implementation lives

The reusable implementation belongs to `Umicom-Applications/framework`. Use the public `umicom/ai/training/stacked_projection_trace.h` or `umicom/ai/training/stacked_kv_capture.h` interfaces, depending on the task. The trace observes the **original** decoder through its established Transformer projection hook; the existing cache store handles K/V row ownership. No C23 neural-network computations belong in the Bits2Banking course. Run the Framework CTest cases for numerical qualification on the actual model before interpreting these services as integrated.

## Limitations and engineering evidence

The current observation pipeline performs a **complete canonical Transformer forward** for each observed prompt state. A smaller number of rows accepted into a store is not proof of fewer operations, lower latency or more accurate generated text. SHA-256 identifies checkpoint bytes but does not authenticate a publisher. No generated output should be executed as source code or treated as financial advice.

## Practice

**Question:** Why must the cache not preserve token D's original key when D moves from position 3 to 2?

<details><summary>Reveal the worked explanation</summary>

Its positional embedding changes, so the key is no longer generally the one the canonical decoder calculates at position 2. All surviving positions are recalculated in the current model family.

</details>

## Continue studying

[Previous lesson](210-verify-existing-rows-before-appending.md) · [Next lesson](212-distinguish-stored-rows-from-computed-rows.md) · [View the browser lesson](../../courses/llm-from-scratch/lessons/211-rebuild-all-layers-after-absolute-position-rollover.html) · [K/V projection learning path](kv-projection-observation-study-route.md).

*Service to Many Leads to Greatness.*
