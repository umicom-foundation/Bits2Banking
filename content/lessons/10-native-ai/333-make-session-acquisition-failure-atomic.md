# Lesson 333 — Make session acquisition failure atomic

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Implementation:** C23 and native Umicom Framework APIs  
**Prerequisite:** LLM Lesson 332; Mathematics Unit 201.

## Learning objective

Explain and test **make session acquisition failure atomic** within the bounded, educational native Transformer architecture.

## Technical explanation and worked example

Acquisition touches multiple resources: a free slot, a memory budget, a store allocation and a returned lease. A partial failure is dangerous if any resource is made visible before all prerequisites are met. The safe order is: validate arguments; check available slot and budget; allocate the canonical store; inspect its reserved bytes; commit the slot, counters and lease together.

If the store constructor reports out-of-memory, nothing should be reserved. If the planner and actual store disagree, the candidate allocation is destroyed without publishing a session. The public output lease stays untouched on every rejection. In C, local staging and one final publication point are often simpler than rolling back a half-mutated object graph.

**Worked scenario.** An allocator fails after the pool identifies slot 1. The old active count is 1 and reserved bytes are 512. The expected state after failure is still 1 active session and 512 reserved bytes; no observable lease points to slot 1.

**Native walkthrough.** Trace the conditions preceding the assignment to `slot->store` in `StackedKvPoolAcquire`. Then inspect the `budget` and `rejections` CTest cases. Confirm that no failure occurs after any of the count increments without a compensating action.

**Subtle point.** Failure-atomic API output does not mean allocator failure is impossible. It means the caller can retry without repairing hidden partial state.

## Practise

**Question:** Which operation should happen last in a successful acquisition?

<details><summary>Reveal the worked answer</summary>

The public lease publication, after creating and validating the canonical store and committing its reservation.

</details>

## Explore the mathematics

[Mathematics Unit 201](../11-maths-for-ai/201-prove-reservation-accounting-across-a-release.md) develops a related calculation. Distinguish stated design, tested library contracts and measured runtime evidence.

## Continue learning

[Previous lesson](332-prevent-stale-handles-with-generation-stamped-leases.md) · [Next lesson](334-prefill-a-prompt-and-append-without-moving-its-positions.md) · [Browser lesson](../../courses/llm-from-scratch/lessons/333-make-session-acquisition-failure-atomic.html)

*Service to Many Leads to Greatness.*
