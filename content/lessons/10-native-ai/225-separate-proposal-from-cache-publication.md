# Lesson 225 — Separate a proposal from cache publication

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Language:** Native C23 · **Level:** Building beyond the introductory Transformer.

**Learning objective:** Understand failure-atomic staging across neural computation, sampling and cache mutation.

## 1. The engineering question

A candidate can be mathematically valid yet fail before it should become visible. For that reason, the Framework computes the new K/V rows and vocabulary logits first. It can then qualify the result and sample a token before committing the proposed rows to the store.

## 2. Work through a concrete example

If a proposed token has invalid dimensions or a non-finite logit, outKeys, outValues and outLastLogits keep their earlier bytes; the store remains unchanged. A successful `StackedKvStoreAppend` accepts both arrays atomically.

## 3. How Umicom Framework implements the idea

The distinction between `KvStepPropose` and `StackedKvStoreAppend` matches the Framework’s existing failure-atomic design. The sampled token is published only after the resulting store transition has succeeded.

The relevant public contract is `umicom/ai/training/stacked_kv_step.h`. The native implementation and numerical tests belong to Umicom Framework; this manuscript does not introduce an alternative application-local training or inference service. The training tape owns mathematical operators and tensor lifetimes, while consumers use explicit C23 handles and status results.

## 4. Check the mathematical foundation

For a step-by-step explanation of the arithmetic, read [Mathematics Unit 121](../11-maths-for-ai/121-separate-projection-work-from-attention-work.md). Keep tensor **shape**, **absolute position**, **model checkpoint identity** and **actual executed work** distinct when describing a cache.

## 5. Practice and verify

**Question:** If sampling fails after K/V calculation but before StoreAppend, which data structures should remain unchanged?

<details>
<summary>Reveal the worked explanation</summary>

The caller’s sampled output, sampling RNG and persistent KV store remain unchanged. Temporary tape results have already been discarded.

</details>

## 6. Limits and responsible interpretation

These contracts do not make the model thread-safe. Callers must still serialize training, inference and destruction.

A passing test in an isolated demonstration is not a production integration result. Evaluate against the actual Framework checkout and document any numerical or timing limitations before making deployment claims.

## Continue learning

[Previous lesson](224-preserve-residual-and-feed-forward-order.md) · [Next lesson](226-verify-every-vocabulary-logit.md) · [Browser learning path](../../courses/llm-from-scratch/incremental-attention-learning-path.html)

*Service to Many Leads to Greatness.*
