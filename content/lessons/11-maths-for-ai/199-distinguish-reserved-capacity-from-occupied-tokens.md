# Mathematics for AI — Unit 199: Distinguish reserved capacity from occupied tokens

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Prerequisite:** Basic arithmetic and the preceding mathematics units.

## Learning objective

Relate physically allocated K/V space to the number of valid cached rows.

## Step-by-step derivation

A store may reserve `T` positions but only have `t` valid positions, with `0 ≤ t ≤ T`. Its occupied fraction is `t/T`. With context 4 and a two-token prefill, the occupied fraction is 50%, while the reserved raw bytes remain 512. Replacing raw reservation with `512 × 0.5 = 256` would understate the allocation. A pool's total reserved memory is computed from active stores, not the sum of retained token rows.

## Check your understanding

**Exercise:** At one retained token in a four-token store, what fraction is occupied?

<details><summary>Show the worked solution</summary>

25% occupied, while the full 512-byte capacity remains reserved.

</details>

## Native C23 connection

Use the Framework's existing checked `InferenceMemoryPlan`, `StackedKvStore` and `StackedKvPool` contracts. Arithmetic estimates do not themselves prove safe allocation, neural accuracy or measured latency.

## Continue learning

[Previous unit](198-convert-a-budget-into-admitted-session-count.md) · [Next unit](200-explain-generation-counters-and-the-aba-hazard.md) · [Browser unit](../../courses/maths-for-ai/lessons/199-distinguish-reserved-capacity-from-occupied-tokens.html)

*Service to Many Leads to Greatness.*
