# Mathematics for AI — Unit 252: Compute random challenge detection probability

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Prerequisite:** arithmetic, fractions, basic vectors and Unit 251.

## Learning outcome

Calculate, check and interpret one quantity used in a native distributed-learning system. Separate mathematical assumptions, theoretical bounds, reserved metadata and actual measured performance.

## Step-by-step worked calculation

Assume each independent random challenge has probability p=0.1 of inspecting a dishonest step. With replacement and n=5 independent choices, P(detection)=1−(1−p)^n=1−0.9^5=1−0.59049=0.40951, or 40.951%. The independent-uniform assumption is essential; adaptive adversaries invalidate it.

## Application to a C23 learning network

A robust implementation checks dimensions and integer bounds **before** modifying stored state. The existing Framework federated aggregation and new job-admission services treat sample counts, model vectors and transfer reservations as different units. None of the arithmetic presented here proves that remote training was carried out honestly.

## Independent exercise

**Question:** If there are 10 independent challenges instead, how should detection probability be expressed?

<details><summary>Reveal the complete solution</summary>
<p>1−0.9^10≈0.65132156, or 65.132%. Passing still does not prove every step honest.</p>
</details>

## Units, assumptions and interpretation

Preserve byte versus bit, decimal MB versus binary MiB, sample count versus token count, and reported resource forecasts versus observed measurements. If the calculation describes a statistical model, state its independence assumptions; if it describes a rejected update, do not silently change the aggregation algorithm.

## Further study

[Related LLM Lesson 400](../10-native-ai/400-model-local-sgd-epochs-and-sync-barriers.md) · [Mathematics learning path](../../courses/maths-for-ai/federated-job-mathematics.html).

*Service to Many Leads to Greatness.*
