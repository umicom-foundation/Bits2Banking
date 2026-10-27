# Mathematics for AI — Unit 254: Derive the LoRA factor-averaging counterexample

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Prerequisite:** arithmetic, fractions, basic vectors and Unit 253.

## Learning outcome

Calculate, check and interpret one quantity used in a native distributed-learning system. Separate mathematical assumptions, theoretical bounds, reserved metadata and actual measured performance.

## Step-by-step worked calculation

Let worker 1 have scalar A1=1,B1=1, worker 2 A2=−1,B2=−1. Each produces BᵢAᵢ=+1. Product average (1+1)/2=1. Factor averages Ā=(1−1)/2=0, B̄=(1−1)/2=0, so B̄Ā=0. Low-rank factors are non-unique; averaging components without considering their product can be wrong.

## Application to a C23 learning network

A robust implementation checks dimensions and integer bounds **before** modifying stored state. The existing Framework federated aggregation and new job-admission services treat sample counts, model vectors and transfer reservations as different units. None of the arithmetic presented here proves that remote training was carried out honestly.

## Independent exercise

**Question:** If factors are instead A1=2,B1=1 and A2=1,B2=2, what is the average product?

<details><summary>Reveal the complete solution</summary>
<p>Both products equal 2, so their average is 2. The factor averages equal 1.5×1.5=2.25, again different.</p>
</details>

## Units, assumptions and interpretation

Preserve byte versus bit, decimal MB versus binary MiB, sample count versus token count, and reported resource forecasts versus observed measurements. If the calculation describes a statistical model, state its independence assumptions; if it describes a rejected update, do not silently change the aggregation algorithm.

## Further study

[Related LLM Lesson 402](../10-native-ai/402-test-poisoning-and-abnormal-norms.md) · [Mathematics learning path](../../courses/maths-for-ai/federated-job-mathematics.html).

*Service to Many Leads to Greatness.*
