# Distributed Learning — Lesson 013: Bind one worker to one training round

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Level:** Beginner–intermediate · **Prerequisites:** Distributed Learning Lessons 001–012.

## Learning objective

Describe **bind one worker to one training round** in your own words and work through a small numerical or lifecycle experiment.

## Understand the idea

A learning worker receives a specific model version, shard and task. A local **ticket** records the assignment’s lifetime, whereas an authenticated remote identity requires separate cryptography. Keeping the two separate makes it possible to cancel a task without pretending to revoke someone’s public key.

Three notions must always stay distinct: *training* changes model parameters, *coordination* decides which work may proceed, and *verification* evaluates what evidence can be trusted. A blockchain may eventually record decisions, but neither transactions nor hashes replace backpropagation.

## Classroom walkthrough

Imagine a student given worksheet 7. Returning the answer to worksheet 6 is not acceptable just because the student is registered. Similarly a correct-shaped delta labelled with the wrong base checkpoint must be refused.

## Practical native C23 connection

The existing Umicom Framework owns training arithmetic and its new federated-job interface accounts for local assignments. The distributed-learning laboratory links the real Framework interfaces; no Python trainer is added to Umicom. All examples use synthetic IDs and synthetic deltas. Real training, signed network messages and end-to-end quality certification are separate research stages.

## Exercise

**Question:** Write three identifiers that belong in a worker assignment.

<details><summary>Show the explained answer</summary>
<p>Worker identity, shared base-checkpoint identity and authorised dataset-shard identity; include a unique round or job identifier.</p>
</details>

## Suggested demonstration

Sketch the lifecycle: *propose → inspect permission → admit → local work → submit → independently check → aggregate → evaluate*. Mark where it is appropriate to refuse a task and where a failure must leave model weights unchanged. Write one example of a negative result worth reporting.

## Further reading

- [Federated Averaging — McMahan et al., AISTATS 2017](https://proceedings.mlr.press/v54/mcmahan17a.html)

[Course learning route](../../courses/distributed-learning/rounds-and-verification.html) · [Native learning job laboratory](../../../labs/native/distributed-learning/federated-job/README.md)

*Service to Many Leads to Greatness.*
