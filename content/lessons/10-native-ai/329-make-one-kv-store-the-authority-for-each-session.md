# Lesson 329 — Make one K/V store the authority for each session

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Implementation:** C23 and native Umicom Framework APIs  
**Prerequisite:** LLM Lesson 328; Mathematics Unit 197.

## Learning objective

Explain and test **make one k/v store the authority for each session** within the bounded, educational native Transformer architecture.

## Technical explanation and worked example

A KV cache stores projections, not model weights. Each token contributes a **key** and a **value** vector at every Transformer layer. The established `UmiAiTrainingStackedKvStore` owns these vectors, including their model identity and retained token rows. Adding a session pool must not introduce a second packed-tensor implementation: the pool owns *stores*, whereas each store owns *rows*. This is composition with an explicit ownership hierarchy.

There are three different lifetimes. A decoder checkpoint may survive several requests. A pool may survive multiple conversations. A per-session store should survive only one active lease, although the session may reset its rows to begin another prompt. The K/V store's `Destroy` operation releases the vectors; the pool's `Release` operation must call it exactly once. A copied cache pointer is not a second owner.

**Worked scenario.** Two users each request four context positions in a two-layer, eight-channel FP32 model. Each store reserves `2 (K and V) × 2 layers × 4 positions × 8 channels × 4 bytes = 512 bytes`. The pool owns two independent 512-byte stores. One user's append cannot mutate the other's rows, even if they use the same checkpoint.

**Native walkthrough.** Identify the two ownership levels in `stacked_kv_pool.h`: the opaque pool and its generation-stamped lease. Read `StackedKvStorePrefill`, `Append` and `ReplaceRolled` before attempting to write any session scheduler. The original store must continue to enforce position and row rules.

**Failure to investigate.** If a pool copies the underlying K/V arrays into its own side buffer, which component becomes authoritative after a context rollover? A single owner prevents that ambiguity.

## Practise

**Question:** Why does a lease not own the raw K/V buffer?

<details><summary>Reveal the worked answer</summary>

Because a lease is an identity/permission-to-address record; the pool owns a real store, and the existing K/V store owns its allocated projections.

</details>

## Explore the mathematics

[Mathematics Unit 197](../11-maths-for-ai/197-derive-one-fp32-kv-reservation.md) develops a related calculation. Distinguish stated design, tested library contracts and measured runtime evidence.

## Continue learning

[Previous lesson](328-complete-a-bounded-memory-admission-capstone.md) · [Next lesson](330-bind-all-active-caches-to-a-frozen-model-identity.md) · [Browser lesson](../../courses/llm-from-scratch/lessons/329-make-one-kv-store-the-authority-for-each-session.html)

*Service to Many Leads to Greatness.*
