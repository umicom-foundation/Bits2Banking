# Distributed Learning — Lesson 018: Understand what makes an update stale

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Level:** Beginner–intermediate · **Prerequisites:** Distributed Learning Lessons 001–012.

## Learning objective

Describe **understand what makes an update stale** in your own words and work through a small numerical or lifecycle experiment.

## Understand the idea

Worker A starts from checkpoint 8 and finishes after checkpoint 9 has already been released. The update may be genuine yet unsuitable for direct addition to checkpoint 9. Research systems define explicit staleness windows, downweighting or rejection policies and test convergence under them.

Three notions must always stay distinct: *training* changes model parameters, *coordination* decides which work may proceed, and *verification* evaluates what evidence can be trusted. A blockchain may eventually record decisions, but neither transactions nor hashes replace backpropagation.

## Classroom walkthrough

With a strict same-base policy, a delta labelled checkpoint 8 is rejected from a round pinned to checkpoint 9, even when the tensor shapes match.

## Practical native C23 connection

The existing Umicom Framework owns training arithmetic and its new federated-job interface accounts for local assignments. The distributed-learning laboratory links the real Framework interfaces; no Python trainer is added to Umicom. All examples use synthetic IDs and synthetic deltas. Real training, signed network messages and end-to-end quality certification are separate research stages.

## Exercise

**Question:** Why is checking only parameter count insufficient?

<details><summary>Show the explained answer</summary>
<p>Identical shapes do not ensure compatible base parameter values, optimiser context or training ancestry.</p>
</details>

## Suggested demonstration

Sketch the lifecycle: *propose → inspect permission → admit → local work → submit → independently check → aggregate → evaluate*. Mark where it is appropriate to refuse a task and where a failure must leave model weights unchanged. Write one example of a negative result worth reporting.

## Further reading

- [DiLoCo — Distributed Low-Communication Training](https://arxiv.org/abs/2311.08105)

[Course learning route](../../courses/distributed-learning/rounds-and-verification.html) · [Native learning job laboratory](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/distributed-learning/federated-job/README.md)

*Service to Many Leads to Greatness.*
