# Distributed Learning — Lesson 020: Read signed receipts without overclaiming what they prove

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Level:** Beginner–intermediate · **Prerequisites:** Distributed Learning Lessons 001–012.

## Learning objective

Describe **read signed receipts without overclaiming what they prove** in your own words and work through a small numerical or lifecycle experiment.

## Understand the idea

Hashes identify bytes; signatures authenticate a signer’s claim under a key policy. Replay or attestation attempts to test execution, and independent held-out evaluation attempts to measure usefulness. These are four different questions. An audit record should state which checks have actually passed.

Three notions must always stay distinct: *training* changes model parameters, *coordination* decides which work may proceed, and *verification* evaluates what evidence can be trusted. A blockchain may eventually record decisions, but neither transactions nor hashes replace backpropagation.

## Classroom walkthrough

A worker signs “update hash H came from me”. This can verify the signature and message integrity. It does not verify a single gradient or guarantee the updated model is more useful.

## Practical native C23 connection

The existing Umicom Framework owns training arithmetic and its new federated-job interface accounts for local assignments. The distributed-learning laboratory links the real Framework interfaces; no Python trainer is added to Umicom. All examples use synthetic IDs and synthetic deltas. Real training, signed network messages and end-to-end quality certification are separate research stages.

## Exercise

**Question:** What independent test addresses usefulness?

<details><summary>Show the explained answer</summary>
<p>An appropriate held-out model evaluation with a predeclared acceptance threshold.</p>
</details>

## Suggested demonstration

Sketch the lifecycle: *propose → inspect permission → admit → local work → submit → independently check → aggregate → evaluate*. Mark where it is appropriate to refuse a task and where a failure must leave model weights unchanged. Write one example of a negative result worth reporting.

## Further reading

- [Proof of Learning (PoLe)](https://arxiv.org/abs/2007.15145)

[Course learning route](../../courses/distributed-learning/rounds-and-verification.html) · [Native learning job laboratory](../../../labs/native/distributed-learning/federated-job/README.md)

*Service to Many Leads to Greatness.*
