# Mathematics for AI — Unit 215: Measure the peak physical-memory watermark

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Prerequisite:** Earlier arithmetic and K/V-memory units.

## Learning outcome

Peak is the largest observed physical payload, not a cumulative sum of allocations. By the end of this unit, you should be able to reproduce the calculation and state the limits of its interpretation.

## Step-by-step worked calculation

Physical bytes over five observation points are [512,1024,512,1536,512]. The maximum is 1,536 bytes. Total acquisitions could be much larger than five without raising this watermark.

## How the mathematics maps to C23

Umicom Framework uses `size_t` for raw memory counts, checked multiplication before allocation, and `UmiStatus` codes to reject malformed or oversized requests. The K/V pool's `reservedRawKvBytes` counts active leases, `idleRawKvBytes` counts reset retained stores, and `physicalRawKvBytes` counts their combined capacity. These are **raw payload** measurements; operating-system RSS and allocator overhead are separate. A numerical capacity result alone is not evidence of a faster or safer production deployment.

## Exercise

**Question:** Find the peak of [0,512,1024,1024,512] bytes.

<details><summary>Reveal the full calculation</summary>
<p>1,024 bytes.</p>
</details>

## Investigation

Write the calculation again after changing exactly one input. Check units (bytes versus MiB), distinguish current from peak values, and specify whether the result is a proven identity, a bounded estimate or an actual timing measurement.

## Continue learning

[Previous unit](214-combine-session-slot-and-memory-ceilings.md) · [Next unit](216-count-reset-fp32-elements-and-state.md) · [Mathematics learning path](../../courses/maths-for-ai/kv-reuse-mathematics.html)

*Service to Many Leads to Greatness.*
