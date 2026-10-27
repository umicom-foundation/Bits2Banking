# Mathematics for AI — Unit 209: Derive raw K/V payload per store

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Prerequisite:** Earlier arithmetic and K/V-memory units.

## Learning outcome

A cache stores keys and values for every supported layer, position and channel. By the end of this unit, you should be able to reproduce the calculation and state the limits of its interpretation.

## Step-by-step worked calculation

For 2 layers, 4 positions, 8 channels and four bytes per FP32 scalar: 2 × 2 × 4 × 8 × 4 = 512 bytes. Each store reserves this full capacity even before a token is loaded.

## How the mathematics maps to C23

Umicom Framework uses `size_t` for raw memory counts, checked multiplication before allocation, and `UmiStatus` codes to reject malformed or oversized requests. The K/V pool's `reservedRawKvBytes` counts active leases, `idleRawKvBytes` counts reset retained stores, and `physicalRawKvBytes` counts their combined capacity. These are **raw payload** measurements; operating-system RSS and allocator overhead are separate. A numerical capacity result alone is not evidence of a faster or safer production deployment.

## Exercise

**Question:** If context doubles to 8 positions with everything else fixed, how many raw bytes are reserved?

<details><summary>Reveal the full calculation</summary>
<p>1,024 bytes.</p>
</details>

## Investigation

Write the calculation again after changing exactly one input. Check units (bytes versus MiB), distinguish current from peak values, and specify whether the result is a proven identity, a bounded estimate or an actual timing measurement.

## Continue learning

[Previous unit](208-build-a-bounded-session-memory-evidence-table.md) · [Next unit](210-prove-active-plus-idle-equals-physical-payload.md) · [Mathematics learning path](../../courses/maths-for-ai/kv-reuse-mathematics.html)

*Service to Many Leads to Greatness.*
