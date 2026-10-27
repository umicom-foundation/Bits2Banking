# Mathematics for AI — Unit 248: Account for cancelled workers without fake zero deltas

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Prerequisite:** arithmetic, fractions, basic vectors and Unit 247.

## Learning outcome

Calculate, check and interpret one quantity used in a native distributed-learning system. Separate mathematical assumptions, theoretical bounds, reserved metadata and actual measured performance.

## Step-by-step worked calculation

Suppose the intended worker sample counts are A=100, B=200, C=300. C cancels. Completed weights are now 100/(100+200)=1/3 and 200/300=2/3. If ΔA=+0.4 and ΔB=−0.1, accepted mean=(100×0.4+200×−0.1)/300=(40−20)/300≈+0.066667. Erroneously adding 300 cancelled samples with zero delta gives 20/600≈+0.033333.

## Application to a C23 learning network

A robust implementation checks dimensions and integer bounds **before** modifying stored state. The existing Framework federated aggregation and new job-admission services treat sample counts, model vectors and transfer reservations as different units. None of the arithmetic presented here proves that remote training was carried out honestly.

## Independent exercise

**Question:** Explain the error caused by counting cancelled samples as zero-valued updates.

<details><summary>Reveal the complete solution</summary>
<p>The denominator is doubled without any C gradient; the resulting mean is halved, changing the algorithm.</p>
</details>

## Units, assumptions and interpretation

Preserve byte versus bit, decimal MB versus binary MiB, sample count versus token count, and reported resource forecasts versus observed measurements. If the calculation describes a statistical model, state its independence assumptions; if it describes a rejected update, do not silently change the aggregation algorithm.

## Further study

[Related LLM Lesson 396](../10-native-ai/396-reserve-claimed-transfer-bytes-before-admission.md) · [Mathematics learning path](../../courses/maths-for-ai/federated-job-mathematics.html).

*Service to Many Leads to Greatness.*
