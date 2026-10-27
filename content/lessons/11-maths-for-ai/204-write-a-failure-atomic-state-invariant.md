# Mathematics for AI — Unit 204: Write a failure-atomic state invariant

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Prerequisite:** Basic arithmetic and the preceding mathematics units.

## Learning objective

Formalise what should remain constant after a rejected operation.

## Step-by-step derivation

Let `S=(active, reserved, leased slots, generation values)` denote pool state and `O` a caller-owned output lease. A rejected acquisition should satisfy `S_after=S_before` and `O_after=O_before`. For a rejected K/V rollover, retained rows and contents also remain unchanged. This is stronger than checking only a status code; tests should snapshot counters and selected K/V values on both sides of a rejection.

## Check your understanding

**Exercise:** If the first two counters match after a failed acquisition, is failure atomicity fully established?

<details><summary>Show the worked solution</summary>

Not necessarily; the slot state and output lease must also remain unchanged.

</details>

## Native C23 connection

Use the Framework's existing checked `InferenceMemoryPlan`, `StackedKvStore` and `StackedKvPool` contracts. Arithmetic estimates do not themselves prove safe allocation, neural accuracy or measured latency.

## Continue learning

[Previous unit](203-index-layer-major-stored-projections.md) · [Next unit](205-count-projected-rows-at-a-full-window-rollover.md) · [Browser unit](../../courses/maths-for-ai/lessons/204-write-a-failure-atomic-state-invariant.html)

*Service to Many Leads to Greatness.*
