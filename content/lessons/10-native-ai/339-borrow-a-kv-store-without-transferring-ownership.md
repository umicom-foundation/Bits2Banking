# Lesson 339 — Borrow a K/V store without transferring ownership

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Implementation:** C23 and native Umicom Framework APIs  
**Prerequisite:** LLM Lesson 338; Mathematics Unit 199.

## Learning objective

Explain and test **borrow a k/v store without transferring ownership** within the bounded, educational native Transformer architecture.

## Technical explanation and worked example

Some Framework inference services accept an existing `UmiAiTrainingStackedKvStore *` rather than a pool lease. A pool may expose a narrow borrowed pointer to support them. A borrow is neither a clone nor a transfer of ownership: the pool remains responsible for destruction, and the borrowed pointer is valid only while the associated lease stays active.

C23 provides explicit pointers and conventional ownership contracts rather than automatic borrow checking. Handle validation before returning a pointer can reject stale leases, but it cannot stop a caller from storing that pointer in a long-lived object after release. Correct usage therefore depends on a caller-serialised lifecycle and a documented rule against retaining pointers across release or destruction.

**Worked scenario.** Borrow store A, synchronously propose one incremental token, and finish using the pointer. Only then may the owner release A. A later attempt to borrow using A's stale lease is rejected. Dereferencing the old pointer directly would be undefined behaviour and falls outside lease-based validation.

**Native walkthrough.** Find `StackedKvPoolBorrow` and `StackedKvStepPropose`. Record which function owns each pointer and which operation invalidates it. An application integration should pass the borrow only into a synchronous call and verify the model checkpoint first.

## Practise

**Question:** Why cannot generation validation protect a pointer dereferenced after release?

<details><summary>Reveal the worked answer</summary>

Because a raw pointer bypasses the pool API; the check runs only when a lease is presented to the pool.

</details>

## Explore the mathematics

[Mathematics Unit 199](../11-maths-for-ai/199-distinguish-reserved-capacity-from-occupied-tokens.md) develops a related calculation. Distinguish stated design, tested library contracts and measured runtime evidence.

## Continue learning

[Previous lesson](338-reset-release-and-cancel-a-session-safely.md) · [Next lesson](340-separate-raw-cache-payload-from-process-memory-overhead.md) · [Browser lesson](../../courses/llm-from-scratch/lessons/339-borrow-a-kv-store-without-transferring-ownership.html)

*Service to Many Leads to Greatness.*
