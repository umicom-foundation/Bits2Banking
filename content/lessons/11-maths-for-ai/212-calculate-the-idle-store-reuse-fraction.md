# Mathematics for AI — Unit 212: Calculate the idle-store reuse fraction

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Prerequisite:** Earlier arithmetic and K/V-memory units.

## Learning outcome

A reuse ratio counts lifecycle events rather than wall-clock speed. By the end of this unit, you should be able to reproduce the calculation and state the limits of its interpretation.

## Step-by-step worked calculation

A pool observes 12 acquisitions: 9 reuse an idle store and 3 allocate new stores. Reuse fraction = 9/12 = 0.75 = 75%. All 12 still require their own prompt and model work.

## How the mathematics maps to C23

Umicom Framework uses `size_t` for raw memory counts, checked multiplication before allocation, and `UmiStatus` codes to reject malformed or oversized requests. The K/V pool's `reservedRawKvBytes` counts active leases, `idleRawKvBytes` counts reset retained stores, and `physicalRawKvBytes` counts their combined capacity. These are **raw payload** measurements; operating-system RSS and allocator overhead are separate. A numerical capacity result alone is not evidence of a faster or safer production deployment.

## Exercise

**Question:** Out of 20 acquisitions, 6 are cold allocations. Find the reuse percentage.

<details><summary>Reveal the full calculation</summary>
<p>(20 − 6)/20 × 100% = 70%.</p>
</details>

## Investigation

Write the calculation again after changing exactly one input. Check units (bytes versus MiB), distinguish current from peak values, and specify whether the result is a proven identity, a bounded estimate or an actual timing measurement.

## Continue learning

[Previous unit](211-admit-warm-stores-under-a-raw-budget.md) · [Next unit](213-bound-hypothetical-allocation-savings.md) · [Mathematics learning path](../../courses/maths-for-ai/kv-reuse-mathematics.html)

*Service to Many Leads to Greatness.*
