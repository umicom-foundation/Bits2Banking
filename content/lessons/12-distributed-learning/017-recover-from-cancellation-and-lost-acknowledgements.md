# Distributed Learning — Lesson 017: Recover safely from dropout and repeated messages

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Level:** Beginner–intermediate · **Prerequisites:** Distributed Learning Lessons 001–012.

## Learning objective

Describe **recover safely from dropout and repeated messages** in your own words and work through a small numerical or lifecycle experiment.

## Understand the idea

A sender might time out after the coordinator accepted its update. The subsequent retry must not count as another worker. A one-use local ticket helps prevent accidental replay in one process; network idempotency must also bind a signed job and contribution ID to durable state.

Three notions must always stay distinct: *training* changes model parameters, *coordination* decides which work may proceed, and *verification* evaluates what evidence can be trusted. A blockchain may eventually record decisions, but neither transactions nor hashes replace backpropagation.

## Classroom walkthrough

A 100-sample update is accepted once, but the worker sends it a second time because the first ACK was lost. Correct total accepted samples remain 100 rather than 200.

## Practical native C23 connection

The existing Umicom Framework owns training arithmetic and its new federated-job interface accounts for local assignments. The distributed-learning laboratory links the real Framework interfaces; no Python trainer is added to Umicom. All examples use synthetic IDs and synthetic deltas. Real training, signed network messages and end-to-end quality certification are separate research stages.

## Exercise

**Question:** Should a retry count twice if its bytes are identical?

<details><summary>Show the explained answer</summary>
<p>No. The coordinator should return the prior outcome or reject the replay without changing the aggregation.</p>
</details>

## Suggested demonstration

Sketch the lifecycle: *propose → inspect permission → admit → local work → submit → independently check → aggregate → evaluate*. Mark where it is appropriate to refuse a task and where a failure must leave model weights unchanged. Write one example of a negative result worth reporting.

## Further reading

- [Federated Averaging — McMahan et al., AISTATS 2017](https://proceedings.mlr.press/v54/mcmahan17a.html)

[Course learning route](../../courses/distributed-learning/rounds-and-verification.html) · [Native learning job laboratory](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/distributed-learning/federated-job/README.md)

*Service to Many Leads to Greatness.*
