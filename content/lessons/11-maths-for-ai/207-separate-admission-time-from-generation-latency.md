# Mathematics for AI — Unit 207: Separate admission time from generation latency

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Prerequisite:** Basic arithmetic and the preceding mathematics units.

## Learning objective

Decompose measured time into independently interpretable phases.

## Step-by-step derivation

An end-to-end measurement may include admission `t_a`, prefill `t_p`, decoding `t_d` and release `t_r`: `t_total=t_a+t_p+t_d+t_r` if those phases are executed sequentially without overlapping tasks. Suppose measured values are `0.2, 1.0, 2.9, 0.1` ms respectively: total 4.2 ms. A pool reducing admission by 0.1 ms could still have unchanged or worse overall generation due to different decode timings. Report the measurement boundary.

## Check your understanding

**Exercise:** For `0.1+0.7+3.0+0.2` ms, what is total latency?

<details><summary>Show the worked solution</summary>

4.0 milliseconds.

</details>

## Native C23 connection

Use the Framework's existing checked `InferenceMemoryPlan`, `StackedKvStore` and `StackedKvPool` contracts. Arithmetic estimates do not themselves prove safe allocation, neural accuracy or measured latency.

## Continue learning

[Previous unit](206-estimate-the-limits-of-shared-prefix-savings.md) · [Next unit](208-build-a-bounded-session-memory-evidence-table.md) · [Browser unit](../../courses/maths-for-ai/lessons/207-separate-admission-time-from-generation-latency.html)

*Service to Many Leads to Greatness.*
