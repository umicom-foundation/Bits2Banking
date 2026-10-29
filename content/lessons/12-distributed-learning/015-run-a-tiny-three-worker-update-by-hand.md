# Distributed Learning — Lesson 015: Carry out the three-worker FedAvg classroom exercise

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Level:** Beginner–intermediate · **Prerequisites:** Distributed Learning Lessons 001–012.

## Learning objective

Describe **carry out the three-worker fedavg classroom exercise** in your own words and work through a small numerical or lifecycle experiment.

## Understand the idea

Start with θ=1.000. All three workers start from the same value, train locally in a conceptual experiment, and submit deltas. FedAvg weights contributions by admitted sample counts and computes an aggregated *candidate*, not automatically a better model.

Three notions must always stay distinct: *training* changes model parameters, *coordination* decides which work may proceed, and *verification* evaluates what evidence can be trusted. A blockchain may eventually record decisions, but neither transactions nor hashes replace backpropagation.

## Classroom walkthrough

A: 100 samples, +0.05; B: 250, −0.01; C: 150, +0.08. Total 500. Weighted delta=(5−2.5+12)/500=0.029. Proposed θ=1.029.

## Practical native C23 connection

The existing Umicom Framework owns training arithmetic and its new federated-job interface accounts for local assignments. The distributed-learning laboratory links the real Framework interfaces; no Python trainer is added to Umicom. All examples use synthetic IDs and synthetic deltas. Real training, signed network messages and end-to-end quality certification are separate research stages.

## Exercise

**Question:** What happens to the denominator if C never submits?

<details><summary>Show the explained answer</summary>
<p>Use only A+B accepted samples: 350, not 500. A dropout is not a zero-valued trained update.</p>
</details>

## Suggested demonstration

Sketch the lifecycle: *propose → inspect permission → admit → local work → submit → independently check → aggregate → evaluate*. Mark where it is appropriate to refuse a task and where a failure must leave model weights unchanged. Write one example of a negative result worth reporting.

## Further reading

- [Federated Averaging — McMahan et al., AISTATS 2017](https://proceedings.mlr.press/v54/mcmahan17a.html)

[Course learning route](../../courses/distributed-learning/rounds-and-verification.html) · [Native learning job laboratory](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/distributed-learning/federated-job/README.md)

*Service to Many Leads to Greatness.*
