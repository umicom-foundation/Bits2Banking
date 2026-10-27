# Mathematics for AI — Unit 253: Compare verification GPU-seconds with training cost

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Prerequisite:** arithmetic, fractions, basic vectors and Unit 252.

## Learning outcome

Calculate, check and interpret one quantity used in a native distributed-learning system. Separate mathematical assumptions, theoretical bounds, reserved metadata and actual measured performance.

## Step-by-step worked calculation

Suppose one worker reports a 120 GPU-second task, and a verifier runs 6 challenges costing 0.8 GPU-seconds each. Audit cost=6×0.8=4.8 GPU-seconds, representing (4.8/120)×100=4% of the claimed training duration. If false-negative risk remains large, the 4% cost may still be poor value.

## Application to a C23 learning network

A robust implementation checks dimensions and integer bounds **before** modifying stored state. The existing Framework federated aggregation and new job-admission services treat sample counts, model vectors and transfer reservations as different units. None of the arithmetic presented here proves that remote training was carried out honestly.

## Independent exercise

**Question:** How many 0.8-second challenges fit in a 10%-of-training audit budget?

<details><summary>Reveal the complete solution</summary>
<p>0.10×120=12 seconds, so at most 15 whole challenges. This budget alone determines no security guarantee.</p>
</details>

## Units, assumptions and interpretation

Preserve byte versus bit, decimal MB versus binary MiB, sample count versus token count, and reported resource forecasts versus observed measurements. If the calculation describes a statistical model, state its independence assumptions; if it describes a rejected update, do not silently change the aggregation algorithm.

## Further study

[Related LLM Lesson 401](../10-native-ai/401-quantify-non-iid-client-drift.md) · [Mathematics learning path](../../courses/maths-for-ai/federated-job-mathematics.html).

*Service to Many Leads to Greatness.*
