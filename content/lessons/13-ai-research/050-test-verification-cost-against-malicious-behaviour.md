# AI Research Frontiers — Lesson 050: Test verification cost against malicious behaviour

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Licence:** MIT · **Language:** UK English  
**Study route:** AI Research Frontiers · **Method:** reason → compute → test → qualify

## Learning objective

Proof-of-learning research must demonstrate detection under an explicit adversarial model. Compare cheap format checks, selected recomputation and independent hold-out testing.

By the end of the lesson, a learner should be able to distinguish what the method mathematically establishes from what its security or distributed-systems context still requires. The objective is to explain the mechanism, reproduce the worked argument and recognise an invalid inference.

## Mechanism and architecture

Proof-of-learning research must demonstrate detection under an explicit adversarial model. Compare cheap format checks, selected recomputation and independent hold-out testing. Consider the boundaries of **data identity**, **computation**, **trust** and **governance** independently. When several computers contribute to a model or ledger, the system must identify the exact input revision, define the legal operation, check the output against an independently fixed reference and record which entity has authority to accept the transition.

A hash or signature secures a *statement about bytes and keys*; a numerical test constrains a *calculation*; a protocol governs *who may decide*; and an independent benchmark measures *whether the model is useful*. These statements are complementary, not interchangeable. A transparent experiment separates claims from measured outcomes.

## Worked case

A policy catches 70 of 100 malicious updates but rejects 8 of 200 honest ones: true-positive rate 70%, honest false-rejection rate 4%.

**Interpretation.** The worked result is a defined calculation or carefully bounded scenario. It does not assert an observed speedup, network finality, legal authorisation or a trained production model. When interpreting a number, state its denominator, units, assumptions and the exact predicate being checked.

## Practical native engineering exercise

Define negative tests before implementing any contributor-scoring mechanism.

A safe experiment uses **synthetic or explicitly authorised inputs**, checks every buffer bound, preserves independent reference results and records both expected-success and deliberate-rejection cases. Implement reusable operations in Umicom Framework C23/Assembly first; an application or course laboratory consumes the published API rather than maintaining a second implementation of its mathematics or hashing.

## Independent exercise

**Question:** Is this sufficient to justify rewards?

<details><summary>Reveal a worked answer</summary>

Not without stated attack severity, economic incentives, uncertainty and costs of wrongly accepting harmful results.

</details>

## Security, scientific and governance limits

Unobserved attacks cannot be claimed detected; adversaries can adapt to disclosed tests.

The small experiments in this course do not establish a deployed blockchain, secure multiparty computation, real Internet-scale learning, a signed identity infrastructure or superior model quality unless a separate qualification specifically measures that property. **Honest negative results are valuable evidence.**

## Primary research and technical reading

- [DiLoCo research](https://arxiv.org/abs/2311.08105)
- [LoRA research](https://arxiv.org/abs/2106.09685)
- [NIST Blockchain Technology Overview](https://csrc.nist.gov/pubs/ir/8202/final)

## Continue learning

- [Previous lesson](049-pre-register-fedavg-versus-local-sgd-comparisons.md)
- [Next lesson](051-avoid-non-iid-evaluation-leakage.md)
- [Browser lesson](../../courses/ai-research/lessons/050-test-verification-cost-against-malicious-behaviour.html)
- [Complete study route](../../courses/ai-research/verifiable-learning-research-methods.html)

*Service to Many Leads to Greatness.*
