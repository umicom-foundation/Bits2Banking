# Distributed Learning — Lesson 078: Test a Byzantine-worker poisoning attempt

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Licence:** MIT · **Language:** UK English  
**Study route:** Distributed Learning · **Method:** reason → compute → test → qualify

## Learning objective

An adversarial worker may submit a numerically finite, correctly framed and authenticated update that harms held-out performance. Integrity checks do not address objective misuse.

By the end of the lesson, a learner should be able to distinguish what the method mathematically establishes from what its security or distributed-systems context still requires. The objective is to explain the mechanism, reproduce the worked argument and recognise an invalid inference.

## Mechanism and architecture

An adversarial worker may submit a numerically finite, correctly framed and authenticated update that harms held-out performance. Integrity checks do not address objective misuse. Consider the boundaries of **data identity**, **computation**, **trust** and **governance** independently. When several computers contribute to a model or ledger, the system must identify the exact input revision, define the legal operation, check the output against an independently fixed reference and record which entity has authority to accept the transition.

A hash or signature secures a *statement about bytes and keys*; a numerical test constrains a *calculation*; a protocol governs *who may decide*; and an independent benchmark measures *whether the model is useful*. These statements are complementary, not interchangeable. A transparent experiment separates claims from measured outcomes.

## Worked case

A delta of +0.03 stays below max-norm 0.1 but decreases validation accuracy from 91% to 82%.

**Interpretation.** The worked result is a defined calculation or carefully bounded scenario. It does not assert an observed speedup, network finality, legal authorisation or a trained production model. When interpreting a number, state its denominator, units, assumptions and the exact predicate being checked.

## Practical native engineering exercise

Use the existing numeric aggregator and independent evaluation evidence.

A safe experiment uses **synthetic or explicitly authorised inputs**, checks every buffer bound, preserves independent reference results and records both expected-success and deliberate-rejection cases. Implement reusable operations in Umicom Framework C23/Assembly first; an application or course laboratory consumes the published API rather than maintaining a second implementation of its mathematics or hashing.

## Independent exercise

**Question:** What should a quality gate do in this toy example?

<details><summary>Reveal a worked answer</summary>

Reject or quarantine the update if a pre-registered regression threshold is violated, retaining the negative result.

</details>

## Security, scientific and governance limits

Non-IID honest updates can also lower a global metric; define false-rejection policies fairly.

The small experiments in this course do not establish a deployed blockchain, secure multiparty computation, real Internet-scale learning, a signed identity infrastructure or superior model quality unless a separate qualification specifically measures that property. **Honest negative results are valuable evidence.**

## Primary research and technical reading

- [FedAvg paper](https://proceedings.mlr.press/v54/mcmahan17a.html)
- [Secure Aggregation, Bonawitz et al.](https://arxiv.org/abs/1611.04482)

## Continue learning

- [Previous lesson](077-keep-forked-round-histories-visible.md)
- [Next lesson](079-handle-delayed-acknowledgements-without-double-counting.md)
- [Browser lesson](../../courses/distributed-learning/lessons/078-test-a-byzantine-worker-poisoning-attempt.html)
- [Complete study route](../../courses/distributed-learning/anchored-contributions-and-governance.html)

*Service to Many Leads to Greatness.*
