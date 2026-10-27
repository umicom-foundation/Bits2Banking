# Mathematics for AI — Unit 246: Calculate a two-parameter sample-weighted FedAvg delta

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Prerequisite:** arithmetic, fractions, basic vectors and Unit 245.

## Learning outcome

Calculate, check and interpret one quantity used in a native distributed-learning system. Separate mathematical assumptions, theoretical bounds, reserved metadata and actual measured performance.

## Step-by-step worked calculation

Take two workers: n1=100, Δ1=(+0.20,−0.40), n2=300, Δ2=(−0.10,+0.20). Sum=400 samples. First coordinate (100×0.20+300×−0.10)/400=(20−30)/400=−0.025. Second (100×−0.40+300×0.20)/400=(−40+60)/400=+0.05. The weighted mean is (−0.025,+0.05).

## Application to a C23 learning network

A robust implementation checks dimensions and integer bounds **before** modifying stored state. The existing Framework federated aggregation and new job-admission services treat sample counts, model vectors and transfer reservations as different units. None of the arithmetic presented here proves that remote training was carried out honestly.

## Independent exercise

**Question:** What would an unweighted mean of the same two vectors be?

<details><summary>Reveal the complete solution</summary>
<p>((0.20−0.10)/2,(−0.40+0.20)/2)=(+0.05,−0.10); different from sample-weighted FedAvg.</p>
</details>

## Units, assumptions and interpretation

Preserve byte versus bit, decimal MB versus binary MiB, sample count versus token count, and reported resource forecasts versus observed measurements. If the calculation describes a statistical model, state its independence assumptions; if it describes a rejected update, do not silently change the aggregation algorithm.

## Further study

[Related LLM Lesson 394](../10-native-ai/394-admit-workers-through-scoped-tickets.md) · [Mathematics learning path](../../courses/maths-for-ai/federated-job-mathematics.html).

*Service to Many Leads to Greatness.*
