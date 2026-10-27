# Lesson 334 — Prefill a prompt and append without moving its positions

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Implementation:** C23 and native Umicom Framework APIs  
**Prerequisite:** LLM Lesson 333; Mathematics Unit 202.

## Learning objective

Explain and test **prefill a prompt and append without moving its positions** within the bounded, educational native Transformer architecture.

## Technical explanation and worked example

Prefill and append have different shape contracts. `Prefill` takes ordered prompt token IDs and `[layer][token][channel]` K/V arrays; `Append` takes the next ID and a `[layer][channel]` slice for each projection. The pool delegates both to the original store. It does not recompute the Transformer mathematics and it never changes the checkpoint digest.

With learned absolute positions, a growing prefix assigns the first token position 0 and each append the next free position. Earlier keys and values remain valid *only while those positions and their causal prefixes are unchanged*. Moving every old row left by one position would invalidate the model's learned position representation.

**Worked scenario.** Two layers and eight channels give 16 key floats and 16 value floats for a one-token append. For a two-token prefill the supplied arrays each contain 32 floats. Supplying 31 key floats should be rejected without publishing any row. A full cache must reject append even though the caller supplies a correctly sized vector.

**Native walkthrough.** After acquiring a lease, call `PoolPrefill`, inspect `retainedTokens`, then append. Read the final token's K and V and verify they match the supplied layer-major slice. Repeat with an invalid length and check that retained rows do not change.

## Practise

**Question:** Why should an append to a full context be rejected?

<details><summary>Reveal the worked answer</summary>

Because it requires context eviction and learned-position recomputation, which are defined by a different full-rollover operation.

</details>

## Explore the mathematics

[Mathematics Unit 202](../11-maths-for-ai/202-check-multiplication-before-it-overflows-size-t.md) develops a related calculation. Distinguish stated design, tested library contracts and measured runtime evidence.

## Continue learning

[Previous lesson](333-make-session-acquisition-failure-atomic.md) · [Next lesson](335-rebuild-complete-kv-layers-at-learned-position-rollover.md) · [Browser lesson](../../courses/llm-from-scratch/lessons/334-prefill-a-prompt-and-append-without-moving-its-positions.html)

*Service to Many Leads to Greatness.*
