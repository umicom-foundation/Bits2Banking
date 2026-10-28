# Distributed Learning — Lesson 082: Budget selective verification under WAN constraints

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Licence:** MIT · **Language:** UK English  
**Study route:** Distributed Learning · **Method:** reason → compute → test → qualify

## Learning objective

Remote verification cost includes downlink/uplink bytes, RTT, CPU time and possible sampled replay. A short proof is useful only if the required source of truth is independently known.

By the end of the lesson, a learner should be able to distinguish what the method mathematically establishes from what its security or distributed-systems context still requires. The objective is to explain the mechanism, reproduce the worked argument and recognise an invalid inference.

## Mechanism and architecture

Remote verification cost includes downlink/uplink bytes, RTT, CPU time and possible sampled replay. A short proof is useful only if the required source of truth is independently known. Consider the boundaries of **data identity**, **computation**, **trust** and **governance** independently. When several computers contribute to a model or ledger, the system must identify the exact input revision, define the legal operation, check the output against an independently fixed reference and record which entity has authority to accept the transition.

A hash or signature secures a *statement about bytes and keys*; a numerical test constrains a *calculation*; a protocol governs *who may decide*; and an independent benchmark measures *whether the model is useful*. These statements are complementary, not interchangeable. A transparent experiment separates claims from measured outcomes.

## Worked case

Four 320-byte Merkle paths consume 1,280 bytes, but the underlying 4×2-MiB model deltas are about 8 MiB if each must be downloaded.

**Interpretation.** The worked result is a defined calculation or carefully bounded scenario. It does not assert an observed speedup, network finality, legal authorisation or a trained production model. When interpreting a number, state its denominator, units, assumptions and the exact predicate being checked.

## Practical native engineering exercise

Benchmark proof generation versus full payload transfer under stated link characteristics.

A safe experiment uses **synthetic or explicitly authorised inputs**, checks every buffer bound, preserves independent reference results and records both expected-success and deliberate-rejection cases. Implement reusable operations in Umicom Framework C23/Assembly first; an application or course laboratory consumes the published API rather than maintaining a second implementation of its mathematics or hashing.

## Independent exercise

**Question:** When is it valid to claim that Merkle proofs reduce communication?

<details><summary>Reveal a worked answer</summary>

When the use case only requires selected membership checks rather than transferring all original update contents.

</details>

## Security, scientific and governance limits

Sample coverage, attack detection and cache validation remain separate.

The small experiments in this course do not establish a deployed blockchain, secure multiparty computation, real Internet-scale learning, a signed identity infrastructure or superior model quality unless a separate qualification specifically measures that property. **Honest negative results are valuable evidence.**

## Primary research and technical reading

- [FedAvg paper](https://proceedings.mlr.press/v54/mcmahan17a.html)
- [Secure Aggregation, Bonawitz et al.](https://arxiv.org/abs/1611.04482)

## Continue learning

- [Previous lesson](081-design-data-provenance-commitments-safely.md)
- [Next lesson](083-separate-consensus-voting-from-evaluation-voting.md)
- [Browser lesson](../../courses/distributed-learning/lessons/082-budget-selective-verification-under-wan-constraints.html)
- [Complete study route](../../courses/distributed-learning/anchored-contributions-and-governance.html)

*Service to Many Leads to Greatness.*
