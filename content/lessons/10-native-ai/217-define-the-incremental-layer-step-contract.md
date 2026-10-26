# Lesson 217 — Define the incremental layer-step contract

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Language:** Native C23 · **Level:** Building beyond the introductory Transformer.

**Learning objective:** Separate immutable trained weights, retained keys/values and the one new token from which logits will be predicted.

## 1. The engineering question

A growing prefix does not move the absolute positions of earlier tokens. For a model with learned absolute embeddings, this is the only phase in which old key/value projections can be reused without positional rebasing. The proposed step must read but not mutate the existing store. Publishing new rows belongs to a later transaction.

## 2. Work through a concrete example

For context capacity 6, a cache holding three tokens may propose a fourth row at position 3. When six tokens are retained, a proposal is refused: the seventh token would evict the oldest and reassign every surviving learned position.

## 3. How Umicom Framework implements the idea

The new C23 boundary `UmiAiTrainingStackedKvStepPropose` accepts a borrowed stacked decoder, an immutable KV-store view and a token ID. It stages per-layer K/V and last-position logits. The store is not changed. The caller may compare those bytes with the canonical decoder before appending.

The relevant public contract is `umicom/ai/training/stacked_kv_step.h`. The native implementation and numerical tests belong to Umicom Framework; this manuscript does not introduce an alternative application-local training or inference service. The training tape owns mathematical operators and tensor lifetimes, while consumers use explicit C23 handles and status results.

## 4. Check the mathematical foundation

For a step-by-step explanation of the arithmetic, read [Mathematics Unit 113](../11-maths-for-ai/113-count-multilayer-qkv-tensor-shapes.md). Keep tensor **shape**, **absolute position**, **model checkpoint identity** and **actual executed work** distinct when describing a cache.

## 5. Practice and verify

**Question:** Given context length 8 and seven retained tokens, identify the position of a proposed next token. What changes when eight tokens are already retained?

<details>
<summary>Reveal the worked explanation</summary>

At seven retained tokens the new position is 7 (positions begin at zero). At eight retained tokens the context is full; eviction must trigger a complete reference rebuild rather than an incremental proposal.

</details>

## 6. Limits and responsible interpretation

This contract does not accelerate an already-full window or authenticate model publishers. Inference must be serialised with model training and destruction.

A passing test in an isolated demonstration is not a production integration result. Evaluate against the actual Framework checkout and document any numerical or timing limitations before making deployment claims.

## Continue learning

[Previous lesson](216-design-the-next-incremental-attention-reference.md) · [Next lesson](218-prove-unchanged-prefix-positions.md) · [Browser learning path](../../courses/llm-from-scratch/incremental-attention-learning-path.html)

*Service to Many Leads to Greatness.*
