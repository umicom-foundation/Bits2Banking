# Mathematics for AI — Unit 218: Compare warm and cold median latencies

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Prerequisite:** Earlier arithmetic and K/V-memory units.

## Learning outcome

Latency comparisons need comparable workloads and an explicit timing boundary. By the end of this unit, you should be able to reproduce the calculation and state the limits of its interpretation.

## Step-by-step worked calculation

Sort cold admission durations [0.14,0.11,0.12,0.13,0.10] ms: median = 0.12 ms. Sort warm [0.07,0.05,0.05,0.06,0.05] ms: median = 0.05 ms. The median *admission* difference is 0.07 ms, not necessarily a generation-time difference.

## How the mathematics maps to C23

Umicom Framework uses `size_t` for raw memory counts, checked multiplication before allocation, and `UmiStatus` codes to reject malformed or oversized requests. The K/V pool's `reservedRawKvBytes` counts active leases, `idleRawKvBytes` counts reset retained stores, and `physicalRawKvBytes` counts their combined capacity. These are **raw payload** measurements; operating-system RSS and allocator overhead are separate. A numerical capacity result alone is not evidence of a faster or safer production deployment.

## Exercise

**Question:** For [3,7,5,1,9] ms, what is the median?

<details><summary>Reveal the full calculation</summary>
<p>Sort [1,3,5,7,9]; the median is 5 ms.</p>
</details>

## Investigation

Write the calculation again after changing exactly one input. Check units (bytes versus MiB), distinguish current from peak values, and specify whether the result is a proven identity, a bounded estimate or an actual timing measurement.

## Continue learning

[Previous unit](217-analyse-lease-generation-across-slot-reuse.md) · [Next unit](219-compute-idle-trimming-with-live-leases.md) · [Mathematics learning path](../../courses/maths-for-ai/kv-reuse-mathematics.html)

*Service to Many Leads to Greatness.*
