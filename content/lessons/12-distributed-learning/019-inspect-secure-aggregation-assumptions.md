# Distributed Learning — Lesson 019: Compare secure aggregation and inspecting individual updates

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Level:** Beginner–intermediate · **Prerequisites:** Distributed Learning Lessons 001–012.

## Learning objective

Describe **compare secure aggregation and inspecting individual updates** in your own words and work through a small numerical or lifecycle experiment.

## Understand the idea

Secure aggregation can hide individual worker values while recovering their aggregate sum. That limits what a central verifier can inspect. It also does not guarantee that a worker’s hidden contribution was benign. Any system claiming both per-worker fraud detection and hidden individual deltas must explain what information is revealed and to whom.

Three notions must always stay distinct: *training* changes model parameters, *coordination* decides which work may proceed, and *verification* evaluates what evidence can be trusted. A blockchain may eventually record decisions, but neither transactions nor hashes replace backpropagation.

## Classroom walkthrough

Three participants submit concealed values a, b, c. The coordinator obtains a+b+c but should not learn individual a from a secure-sum protocol under its stated threat assumptions.

## Practical native C23 connection

The existing Umicom Framework owns training arithmetic and its new federated-job interface accounts for local assignments. The distributed-learning laboratory links the real Framework interfaces; no Python trainer is added to Umicom. All examples use synthetic IDs and synthetic deltas. Real training, signed network messages and end-to-end quality certification are separate research stages.

## Exercise

**Question:** Does secure aggregation alone prevent poisoning?

<details><summary>Show the explained answer</summary>
<p>No. Concealment of individual contributions and resistance to malicious values are distinct properties.</p>
</details>

## Suggested demonstration

Sketch the lifecycle: *propose → inspect permission → admit → local work → submit → independently check → aggregate → evaluate*. Mark where it is appropriate to refuse a task and where a failure must leave model weights unchanged. Write one example of a negative result worth reporting.

## Further reading

- [Practical Secure Aggregation — Bonawitz et al.](https://arxiv.org/abs/1611.04482)

[Course learning route](../../courses/distributed-learning/rounds-and-verification.html) · [Native learning job laboratory](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/distributed-learning/federated-job/README.md)

*Service to Many Leads to Greatness.*
