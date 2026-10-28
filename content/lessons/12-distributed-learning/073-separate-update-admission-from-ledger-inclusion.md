# Distributed Learning — Lesson 073: Separate update admission from ledger inclusion

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Licence:** MIT · **Language:** UK English  
**Study route:** Distributed Learning · **Method:** reason → compute → test → qualify

## Learning objective

FederatedJob admits authorised assignments and FederatedRound computes weighted updates. Merkle inclusion commits to an already accepted list; it should not decide who is authorised to participate.

By the end of the lesson, a learner should be able to distinguish what the method mathematically establishes from what its security or distributed-systems context still requires. The objective is to explain the mechanism, reproduce the worked argument and recognise an invalid inference.

## Mechanism and architecture

FederatedJob admits authorised assignments and FederatedRound computes weighted updates. Merkle inclusion commits to an already accepted list; it should not decide who is authorised to participate. Consider the boundaries of **data identity**, **computation**, **trust** and **governance** independently. When several computers contribute to a model or ledger, the system must identify the exact input revision, define the legal operation, check the output against an independently fixed reference and record which entity has authority to accept the transition.

A hash or signature secures a *statement about bytes and keys*; a numerical test constrains a *calculation*; a protocol governs *who may decide*; and an independent benchmark measures *whether the model is useful*. These statements are complementary, not interchangeable. A transparent experiment separates claims from measured outcomes.

## Worked case

A worker submits a finite update but lacks rights to its declared shard. The update must not be included as accepted solely because its SHA-256 digest is valid.

**Interpretation.** The worked result is a defined calculation or carefully bounded scenario. It does not assert an observed speedup, network finality, legal authorisation or a trained production model. When interpreting a number, state its denominator, units, assumptions and the exact predicate being checked.

## Practical native engineering exercise

Compare the Framework federated job, wire and evidence-anchor interfaces.

A safe experiment uses **synthetic or explicitly authorised inputs**, checks every buffer bound, preserves independent reference results and records both expected-success and deliberate-rejection cases. Implement reusable operations in Umicom Framework C23/Assembly first; an application or course laboratory consumes the published API rather than maintaining a second implementation of its mathematics or hashing.

## Independent exercise

**Question:** List the checks performed before producing an accepted-receipt digest.

<details><summary>Reveal a worked answer</summary>

Verify worker identity, shard permission, base checkpoint, one-use ticket, numeric shape, applicable policy and held-out evaluation gate.

</details>

## Security, scientific and governance limits

Identity and use permission are not properties of a Merkle tree.

The small experiments in this course do not establish a deployed blockchain, secure multiparty computation, real Internet-scale learning, a signed identity infrastructure or superior model quality unless a separate qualification specifically measures that property. **Honest negative results are valuable evidence.**

## Primary research and technical reading

- [FedAvg paper](https://proceedings.mlr.press/v54/mcmahan17a.html)
- [Secure Aggregation, Bonawitz et al.](https://arxiv.org/abs/1611.04482)

## Continue learning

- [Previous lesson](072-complete-an-audited-three-worker-experiment.md)
- [Next lesson](074-give-each-training-round-an-immutable-identity.md)
- [Browser lesson](../../courses/distributed-learning/lessons/073-separate-update-admission-from-ledger-inclusion.html)
- [Complete study route](../../courses/distributed-learning/anchored-contributions-and-governance.html)

*Service to Many Leads to Greatness.*
