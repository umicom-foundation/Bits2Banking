# Lesson 273 — Reject stale checkpoint-bound caches

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Course:** Building an LLM from Scratch · Native C23

**Learning objective:** Enforce model identity across the lifetime of an incremental inference session.

## 1. Concept and motivation

A K/V cache is valid only for the model parameters that produced its rows. The same tensor dimensions do not imply compatible weights. In an educational decoder with a mutable training tape, even a successful SGD step invalidates every previously captured projection. Checkpoint identity is therefore part of the cache contract rather than optional metadata.

## 2. Worked example

Suppose two models both have two layers, eight channels and context six, but their token-embedding weights differ. A cache from model A can be copied into the shape of model B without a memory error; its values are still mathematically invalid. A content digest prevents treating equal shapes as identical checkpoints.

## 3. Native Framework implementation and evidence

Capture the canonical SHA-256 identity at session creation, verify it before and after proposals and check that the store retains the same digest. On mismatch return a failure without modifying caller outputs or advancing token generation.

## 4. Mathematical companion

Read [Mathematics Unit 154 — Compute absolute-plus-relative error](../11-maths-for-ai/154-compute-absolute-plus-relative-error.md). Check each numerical assumption against the example above before running a program.

## 5. Exercise

**Question:** Does SHA-256 equality certify that a checkpoint is safe or authorised for deployment?

<details>
<summary>Reveal the worked answer</summary>

No. It binds the bytes of a checkpoint. Provenance, signature, review and release trust require separate evidence.

</details>

## 6. Interpretation

Content identity is necessary for cache compatibility but is not a trust decision.

## Continue learning

[272 — Rebuild the cache at learned-absolute-position rollover](272-rebuild-cache-on-absolute-position-rollover.md) · [274 — Verify greedy and sampled sequence parity](274-verify-greedy-and-sampled-sequence-parity.md) · [Browser learning path](../../courses/llm-from-scratch/integrated-attention-learning-path.html)
