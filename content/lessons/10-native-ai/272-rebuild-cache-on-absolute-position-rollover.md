# Lesson 272 — Rebuild the cache at learned-absolute-position rollover

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Course:** Building an LLM from Scratch · Native C23

**Learning objective:** Understand why evicting a token changes surviving upper-layer cached states.

## 1. Concept and motivation

A learned absolute-position decoder represents each surviving token using the sum of its token embedding and a position-specific vector. When a full window evicts its oldest token, every surviving token moves to a new position index. Its lower-layer state changes, which propagates to the K/V projections of every higher layer. Simply dropping the oldest cache row would reuse projections calculated for the wrong input state.

## 2. Worked example

For a four-position window `[A,B,C,D]`, appending E produces `[B,C,D,E]`. B had position 1 and now has position 0. Even if B is unchanged text, its input vector is different. Every layer’s cached projections must be rebuilt before the next sample.

## 3. Native Framework implementation and evidence

Retain the canonical full-context projection trace for each rollover and invoke the established store replacement transaction. When the prefix is not full, position indices do not move and the one-query path is applicable.

## 4. Mathematical companion

Read [Mathematics Unit 155 — Track window-rollover position indices](../11-maths-for-ai/155-track-window-rollover-position-indices.md). Check each numerical assumption against the example above before running a program.

## 5. Exercise

**Question:** Would a ring buffer alone make cache eviction numerically correct?

<details>
<summary>Reveal the worked answer</summary>

No. A ring buffer can maintain storage order but cannot recompute positional embeddings, causal history or layer-specific hidden states.

</details>

## 6. Interpretation

Do not assume RoPE-style cache strategies apply unchanged to learned absolute positions.

## Continue learning

[271 — Preserve failure-atomic cache proposals](271-preserve-atomic-cache-proposals.md) · [273 — Reject stale checkpoint-bound caches](273-reject-stale-checkpoint-caches.md) · [Browser learning path](../../courses/llm-from-scratch/integrated-attention-learning-path.html)
