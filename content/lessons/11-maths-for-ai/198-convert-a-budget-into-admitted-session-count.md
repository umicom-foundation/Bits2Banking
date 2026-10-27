# Mathematics for AI — Unit 198: Convert a budget into admitted session count

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Prerequisite:** Basic arithmetic and the preceding mathematics units.

## Learning objective

Use integer floor division to compute an upper bound on complete reservations.

## Step-by-step derivation

If each session needs `R` bytes and the raw budget is `M` bytes, the budget-limited concurrency is `floor(M/R)`. With `M=1024` and `R=512`, at most two sessions fit even when `maximumSessions=3`. More generally, `admitted=min(maximumSessions, floor(M/R))` when a finite budget exists. A zero-budget-ceiling flag is an API convention, not a zero-byte allocation. Always check that `R > 0` before division.

## Check your understanding

**Exercise:** If the budget is 1,500 bytes with 512 bytes per session, how many complete stores fit?

<details><summary>Show the worked solution</summary>

Two; `floor(1500/512)=2`, with 476 bytes unreserved.

</details>

## Native C23 connection

Use the Framework's existing checked `InferenceMemoryPlan`, `StackedKvStore` and `StackedKvPool` contracts. Arithmetic estimates do not themselves prove safe allocation, neural accuracy or measured latency.

## Continue learning

[Previous unit](197-derive-one-fp32-kv-reservation.md) · [Next unit](199-distinguish-reserved-capacity-from-occupied-tokens.md) · [Browser unit](../../courses/maths-for-ai/lessons/198-convert-a-budget-into-admitted-session-count.html)

*Service to Many Leads to Greatness.*
