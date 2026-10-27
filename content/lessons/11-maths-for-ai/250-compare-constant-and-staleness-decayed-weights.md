# Mathematics for AI — Unit 250: Compare ordinary weights with illustrative stale-update decay

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Prerequisite:** arithmetic, fractions, basic vectors and Unit 249.

## Learning outcome

Calculate, check and interpret one quantity used in a native distributed-learning system. Separate mathematical assumptions, theoretical bounds, reserved metadata and actual measured performance.

## Step-by-step worked calculation

A research staleness policy may downweight old updates: w(τ)=exp(−λτ), where τ counts checkpoint-version age and λ>0 is a chosen coefficient. With λ=ln(2) and τ=0,1,2, weights are 1,0.5,0.25. Normalise them by total 1.75: probabilities 4/7, 2/7, 1/7. This is a *proposed* weighted rule, not the current Umicom FedAvg implementation.

## Application to a C23 learning network

A robust implementation checks dimensions and integer bounds **before** modifying stored state. The existing Framework federated aggregation and new job-admission services treat sample counts, model vectors and transfer reservations as different units. None of the arithmetic presented here proves that remote training was carried out honestly.

## Independent exercise

**Question:** What unnormalised weight is assigned at τ=3 under the same policy?

<details><summary>Reveal the complete solution</summary>
<p>exp(−3ln2)=1/8=0.125. The policy must still be validated for quality and fairness.</p>
</details>

## Units, assumptions and interpretation

Preserve byte versus bit, decimal MB versus binary MiB, sample count versus token count, and reported resource forecasts versus observed measurements. If the calculation describes a statistical model, state its independence assumptions; if it describes a rejected update, do not silently change the aggregation algorithm.

## Further study

[Related LLM Lesson 398](../10-native-ai/398-detect-duplicate-contributors-and-stale-models.md) · [Mathematics learning path](../../courses/maths-for-ai/federated-job-mathematics.html).

*Service to Many Leads to Greatness.*
