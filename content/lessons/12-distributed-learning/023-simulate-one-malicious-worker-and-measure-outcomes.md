# Distributed Learning — Lesson 023: Measure a malicious worker without real victim data

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Level:** Beginner–intermediate · **Prerequisites:** Distributed Learning Lessons 001–012.

## Learning objective

Describe **measure a malicious worker without real victim data** in your own words and work through a small numerical or lifecycle experiment.

## Understand the idea

Use a synthetic experiment to separate malformed submissions from adversarially *plausible* submissions. NaN vectors and enormous norms are easy to reject. A malicious but finite low-norm vector may still degrade a model. Proper evaluation measures both harmful accepted updates and honest rejected updates.

Three notions must always stay distinct: *training* changes model parameters, *coordination* decides which work may proceed, and *verification* evaluates what evidence can be trusted. A blockchain may eventually record decisions, but neither transactions nor hashes replace backpropagation.

## Classroom walkthrough

With a norm bound 2.5, delta (3,4) is rejected because its norm is 5. A deliberately reversed delta (−0.1,0) passes the norm but may harm quality.

## Practical native C23 connection

The existing Umicom Framework owns training arithmetic and its new federated-job interface accounts for local assignments. The distributed-learning laboratory links the real Framework interfaces; no Python trainer is added to Umicom. All examples use synthetic IDs and synthetic deltas. Real training, signed network messages and end-to-end quality certification are separate research stages.

## Exercise

**Question:** Why is a valid finite norm not enough to establish trust?

<details><summary>Show the explained answer</summary>
<p>Direction, data provenance and model usefulness are not tested by magnitude alone.</p>
</details>

## Suggested demonstration

Sketch the lifecycle: *propose → inspect permission → admit → local work → submit → independently check → aggregate → evaluate*. Mark where it is appropriate to refuse a task and where a failure must leave model weights unchanged. Write one example of a negative result worth reporting.

## Further reading

- [Proof of Learning (PoLe)](https://arxiv.org/abs/2007.15145)

[Course learning route](../../courses/distributed-learning/rounds-and-verification.html) · [Native learning job laboratory](../../../labs/native/distributed-learning/federated-job/README.md)

*Service to Many Leads to Greatness.*
