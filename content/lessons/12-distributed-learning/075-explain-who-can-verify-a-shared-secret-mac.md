# Distributed Learning — Lesson 075: Explain who can verify a shared-secret MAC

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Licence:** MIT · **Language:** UK English  
**Study route:** Distributed Learning · **Method:** reason → compute → test → qualify

## Learning objective

HMAC recipients holding the same key can verify integrity, but either holder could have produced the MAC. Independent public audit needs different attribution machinery.

By the end of the lesson, a learner should be able to distinguish what the method mathematically establishes from what its security or distributed-systems context still requires. The objective is to explain the mechanism, reproduce the worked argument and recognise an invalid inference.

## Mechanism and architecture

HMAC recipients holding the same key can verify integrity, but either holder could have produced the MAC. Independent public audit needs different attribution machinery. Consider the boundaries of **data identity**, **computation**, **trust** and **governance** independently. When several computers contribute to a model or ledger, the system must identify the exact input revision, define the legal operation, check the output against an independently fixed reference and record which entity has authority to accept the transition.

A hash or signature secures a *statement about bytes and keys*; a numerical test constrains a *calculation*; a protocol governs *who may decide*; and an independent benchmark measures *whether the model is useful*. These statements are complementary, not interchangeable. A transparent experiment separates claims from measured outcomes.

## Worked case

A trainer and coordinator share K. A third-party investigator sees HMAC(K,message) but cannot tell which endpoint generated it.

**Interpretation.** The worked result is a defined calculation or carefully bounded scenario. It does not assert an observed speedup, network finality, legal authorisation or a trained production model. When interpreting a number, state its denominator, units, assumptions and the exact predicate being checked.

## Practical native engineering exercise

Read existing Framework HMAC and detached attestation services.

A safe experiment uses **synthetic or explicitly authorised inputs**, checks every buffer bound, preserves independent reference results and records both expected-success and deliberate-rejection cases. Implement reusable operations in Umicom Framework C23/Assembly first; an application or course laboratory consumes the published API rather than maintaining a second implementation of its mathematics or hashing.

## Independent exercise

**Question:** How would asymmetric signing change the evidence claim?

<details><summary>Reveal a worked answer</summary>

With registered public keys and protected private keys, a valid signature can attribute a statement to the private-key holder under the governance assumptions.

</details>

## Security, scientific and governance limits

Neither primitive automatically certifies useful learning, legitimate training data or secrecy of the message body.

The small experiments in this course do not establish a deployed blockchain, secure multiparty computation, real Internet-scale learning, a signed identity infrastructure or superior model quality unless a separate qualification specifically measures that property. **Honest negative results are valuable evidence.**

## Primary research and technical reading

- [FedAvg paper](https://proceedings.mlr.press/v54/mcmahan17a.html)
- [Secure Aggregation, Bonawitz et al.](https://arxiv.org/abs/1611.04482)

## Continue learning

- [Previous lesson](074-give-each-training-round-an-immutable-identity.md)
- [Next lesson](076-reject-revoked-workers-before-applying-deltas.md)
- [Browser lesson](../../courses/distributed-learning/lessons/075-explain-who-can-verify-a-shared-secret-mac.html)
- [Complete study route](../../courses/distributed-learning/anchored-contributions-and-governance.html)

*Service to Many Leads to Greatness.*
