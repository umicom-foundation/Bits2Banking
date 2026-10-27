# Mathematics for AI — Unit 214: Combine session-slot and memory ceilings

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Prerequisite:** Earlier arithmetic and K/V-memory units.

## Learning outcome

The admitted physical-store count is bounded by both maximum slots and available raw payload. By the end of this unit, you should be able to reproduce the calculation and state the limits of its interpretation.

## Step-by-step worked calculation

For 6 slots, 512 bytes per store and a 2,048-byte limit, floor(2048/512)=4 physical stores fit. Therefore at most min(6,4)=4 can be resident regardless of the idle policy.

## How the mathematics maps to C23

Umicom Framework uses `size_t` for raw memory counts, checked multiplication before allocation, and `UmiStatus` codes to reject malformed or oversized requests. The K/V pool's `reservedRawKvBytes` counts active leases, `idleRawKvBytes` counts reset retained stores, and `physicalRawKvBytes` counts their combined capacity. These are **raw payload** measurements; operating-system RSS and allocator overhead are separate. A numerical capacity result alone is not evidence of a faster or safer production deployment.

## Exercise

**Question:** If the budget rises to 4,096 bytes but the slot maximum remains six, how many stores can exist?

<details><summary>Reveal the full calculation</summary>
<p>min(6, floor(4096/512)) = 6.</p>
</details>

## Investigation

Write the calculation again after changing exactly one input. Check units (bytes versus MiB), distinguish current from peak values, and specify whether the result is a proven identity, a bounded estimate or an actual timing measurement.

## Continue learning

[Previous unit](213-bound-hypothetical-allocation-savings.md) · [Next unit](215-measure-the-peak-physical-memory-watermark.md) · [Mathematics learning path](../../courses/maths-for-ai/kv-reuse-mathematics.html)

*Service to Many Leads to Greatness.*
