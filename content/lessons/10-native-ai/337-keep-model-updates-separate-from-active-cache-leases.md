# Lesson 337 — Keep model updates separate from active cache leases

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Implementation:** C23 and native Umicom Framework APIs  
**Prerequisite:** LLM Lesson 336; Mathematics Unit 197.

## Learning objective

Explain and test **keep model updates separate from active cache leases** within the bounded, educational native Transformer architecture.

## Technical explanation and worked example

The pool's config contains a frozen store checkpoint digest. A successful `CheckIdentity` only proves that the offered digest matches the pool and the store. It does **not** watch for model training operations. A live decoder may change after the pool was created. Therefore the caller must verify the model identity at every inference boundary that consumes retained K/V.

One robust application architecture has a model catalogue publish immutable generation objects. Active inference requests borrow one generation. A new checkpoint is introduced as a new generation and routed to new sessions; existing ones either finish on the original model or are cancelled. Mixing live weights and old K/V is invalid even if the underlying C buffer survives.

**Worked scenario.** Generation A uses digest `A0…` and serves two leases. The model is updated to generation B, digest `B1…`. Session A may be kept only if the original model A is still available and fixed. Passing session A's store to model B must be rejected by the canonical identity verifier.

**Native walkthrough.** Trace `StackedModelIdentityCapture` and `Verify` in Framework, then `StackedKvPoolCheckIdentity`. Compare their responsibilities. One deals with a live decoder; the other checks pool/store record agreement.

**Avoid false assurance.** A matching SHA-256 content digest does not establish publication approval, authenticity or permission to train.

## Practise

**Question:** What extra check is necessary beyond `PoolCheckIdentity` before inference?

<details><summary>Reveal the worked answer</summary>

Verify that the actual live decoder still matches the expected frozen checkpoint using the canonical model identity service.

</details>

## Explore the mathematics

[Mathematics Unit 197](../11-maths-for-ai/197-derive-one-fp32-kv-reservation.md) develops a related calculation. Distinguish stated design, tested library contracts and measured runtime evidence.

## Continue learning

[Previous lesson](336-isolate-independent-inference-conversations.md) · [Next lesson](338-reset-release-and-cancel-a-session-safely.md) · [Browser lesson](../../courses/llm-from-scratch/lessons/337-keep-model-updates-separate-from-active-cache-leases.html)

*Service to Many Leads to Greatness.*
