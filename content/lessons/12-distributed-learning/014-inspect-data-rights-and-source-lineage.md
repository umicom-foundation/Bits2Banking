# Distributed Learning — Lesson 014: Understand why a data hash is not a licence

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Level:** Beginner–intermediate · **Prerequisites:** Distributed Learning Lessons 001–012.

## Learning objective

Describe **understand why a data hash is not a licence** in your own words and work through a small numerical or lifecycle experiment.

## Understand the idea

A file hash fingerprints exact bytes. It cannot tell whether a researcher may copy, share or train on those bytes. For public experiments, use synthetic or explicitly approved datasets. A privacy review is needed before involving financial, educational or healthcare records.

Three notions must always stay distinct: *training* changes model parameters, *coordination* decides which work may proceed, and *verification* evaluates what evidence can be trusted. A blockchain may eventually record decisions, but neither transactions nor hashes replace backpropagation.

## Classroom walkthrough

Two students download an identical PDF. Both get the same SHA-256 digest. One holds training permission; the other may only read it. The digest does not distinguish their legal rights.

## Practical native C23 connection

The existing Umicom Framework owns training arithmetic and its new federated-job interface accounts for local assignments. The distributed-learning laboratory links the real Framework interfaces; no Python trainer is added to Umicom. All examples use synthetic IDs and synthetic deltas. Real training, signed network messages and end-to-end quality certification are separate research stages.

## Exercise

**Question:** Is a freely accessible online banking manual automatically authorised for AI training?

<details><summary>Show the explained answer</summary>
<p>No. Review copyright, licence, contractual restrictions and the proposed usage separately from file identity.</p>
</details>

## Suggested demonstration

Sketch the lifecycle: *propose → inspect permission → admit → local work → submit → independently check → aggregate → evaluate*. Mark where it is appropriate to refuse a task and where a failure must leave model weights unchanged. Write one example of a negative result worth reporting.

## Further reading

- [DataComp-LM: Designing a Benchmark for Language Model Data](https://arxiv.org/abs/2406.11794)

[Course learning route](../../courses/distributed-learning/rounds-and-verification.html) · [Native learning job laboratory](../../../labs/native/distributed-learning/federated-job/README.md)

*Service to Many Leads to Greatness.*
