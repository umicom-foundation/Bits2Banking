# Distributed Learning — Lesson 016: Budget model-update communication

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Level:** Beginner–intermediate · **Prerequisites:** Distributed Learning Lessons 001–012.

## Learning objective

Describe **budget model-update communication** in your own words and work through a small numerical or lifecycle experiment.

## Understand the idea

A slow Internet connection can make frequent gradient exchanges much more expensive than local computation. Budget data in **bytes**, convert correctly to bits for Mbps, and label estimates rather than calling them observations. Low-rank adapters reduce payload compared with full dense updates but have their own compatibility constraints.

Three notions must always stay distinct: *training* changes model parameters, *coordination* decides which work may proceed, and *verification* evaluates what evidence can be trusted. A blockchain may eventually record decisions, but neither transactions nor hashes replace backpropagation.

## Classroom walkthrough

A 64 KiB update means 65,536 bytes = 524,288 bits. At an ideal 10 Mbps it takes at least 52.4288 ms to serialise, before latency and overhead.

## Practical native C23 connection

The existing Umicom Framework owns training arithmetic and its new federated-job interface accounts for local assignments. The distributed-learning laboratory links the real Framework interfaces; no Python trainer is added to Umicom. All examples use synthetic IDs and synthetic deltas. Real training, signed network messages and end-to-end quality certification are separate research stages.

## Exercise

**Question:** Why is a 52 ms estimate not proof of a 52 ms observed network transfer?

<details><summary>Show the explained answer</summary>
<p>It omits RTT, framing, congestion, TLS, retransmissions and processing.</p>
</details>

## Suggested demonstration

Sketch the lifecycle: *propose → inspect permission → admit → local work → submit → independently check → aggregate → evaluate*. Mark where it is appropriate to refuse a task and where a failure must leave model weights unchanged. Write one example of a negative result worth reporting.

## Further reading

- [DiLoCo — Distributed Low-Communication Training](https://arxiv.org/abs/2311.08105)

[Course learning route](../../courses/distributed-learning/rounds-and-verification.html) · [Native learning job laboratory](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/distributed-learning/federated-job/README.md)

*Service to Many Leads to Greatness.*
