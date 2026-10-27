# Mathematics for AI — Unit 255: Quantify non-IID domain skew between two workers

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Prerequisite:** arithmetic, fractions, basic vectors and Unit 254.

## Learning outcome

Calculate, check and interpret one quantity used in a native distributed-learning system. Separate mathematical assumptions, theoretical bounds, reserved metadata and actual measured performance.

## Step-by-step worked calculation

Worker A has 90 finance and 10 code examples; worker B has 10 finance and 90 code examples. A finance proportion=0.90; B finance proportion=0.10. Their total-variation distance for this two-category distribution is 0.5(|0.9−0.1|+|0.1−0.9|)=0.8. Pooled data are 100 finance and 100 code examples, a 0.5/0.5 mixture.

## Application to a C23 learning network

A robust implementation checks dimensions and integer bounds **before** modifying stored state. The existing Framework federated aggregation and new job-admission services treat sample counts, model vectors and transfer reservations as different units. None of the arithmetic presented here proves that remote training was carried out honestly.

## Independent exercise

**Question:** Does an aggregate 50% finance mixture imply the individual workers are IID?

<details><summary>Reveal the complete solution</summary>
<p>No. Each worker is strongly skewed (90/10 versus 10/90) even though the pooled mixture is balanced.</p>
</details>

## Units, assumptions and interpretation

Preserve byte versus bit, decimal MB versus binary MiB, sample count versus token count, and reported resource forecasts versus observed measurements. If the calculation describes a statistical model, state its independence assumptions; if it describes a rejected update, do not silently change the aggregation algorithm.

## Further study

[Related LLM Lesson 403](../10-native-ai/403-separate-digest-identity-signatures-and-usefulness.md) · [Mathematics learning path](../../courses/maths-for-ai/federated-job-mathematics.html).

*Service to Many Leads to Greatness.*
