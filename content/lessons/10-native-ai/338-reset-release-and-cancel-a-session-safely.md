# Lesson 338 — Reset, release and cancel a session safely

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Implementation:** C23 and native Umicom Framework APIs  
**Prerequisite:** LLM Lesson 337; Mathematics Unit 198.

## Learning objective

Explain and test **reset, release and cancel a session safely** within the bounded, educational native Transformer architecture.

## Technical explanation and worked example

Reset and release are not synonyms. Reset clears the currently retained K/V rows inside an active store while preserving the lease and its full reserved capacity. Release destroys the store, frees the raw payload allocation and invalidates the lease. Destroying the pool releases all remaining stores and invalidates all borrowed pointers.

Cancellation is a request-level decision. A token generator should stop any pending operation before releasing its store. This bounded C23 service is caller-serialised; it is not a thread-safe cancellation scheduler. An application supervising concurrent workers must establish ownership barriers so that one worker cannot still use a borrowed pointer while another releases its lease.

**Worked scenario.** A two-layer, four-position store reserves 512 bytes. Reset changes retained tokens from three to zero, but `reservedRawKvBytes` remains 512. Release changes active sessions by one and reduces reserved bytes by 512. A second release with the old lease must return `INVALID_STATE`.

**Native walkthrough.** Compare `StackedKvStoreReset` with `StackedKvStoreDestroy`. Run the lifecycle test and verify that a reset session can prefill a new prompt while its lease generation stays the same. Verify that reacquisition uses a different generation.

## Practise

**Question:** Which operation reduces the pool’s raw reserved K/V bytes?

<details><summary>Reveal the worked answer</summary>

Release, because it destroys the owned store. Reset clears rows without freeing its reserved allocation.

</details>

## Explore the mathematics

[Mathematics Unit 198](../11-maths-for-ai/198-convert-a-budget-into-admitted-session-count.md) develops a related calculation. Distinguish stated design, tested library contracts and measured runtime evidence.

## Continue learning

[Previous lesson](337-keep-model-updates-separate-from-active-cache-leases.md) · [Next lesson](339-borrow-a-kv-store-without-transferring-ownership.md) · [Browser lesson](../../courses/llm-from-scratch/lessons/338-reset-release-and-cancel-a-session-safely.html)

*Service to Many Leads to Greatness.*
