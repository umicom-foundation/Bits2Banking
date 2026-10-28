# Native LLM Engineering — Lesson 478: Model idempotent submission and replay rejection

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Licence:** MIT · **Language:** UK English  
**Study route:** Native LLM Engineering · **Method:** reason → compute → test → qualify

## Learning objective

Networks retry after timeouts, creating repeated delivery. A coordinator must connect authenticated round and sequence numbers to exactly one outstanding local ticket.

By the end of the lesson, a learner should be able to distinguish what the method mathematically establishes from what its security or distributed-systems context still requires. The objective is to explain the mechanism, reproduce the worked argument and recognise an invalid inference.

## Mechanism and architecture

Networks retry after timeouts, creating repeated delivery. A coordinator must connect authenticated round and sequence numbers to exactly one outstanding local ticket. Consider the boundaries of **data identity**, **computation**, **trust** and **governance** independently. When several computers contribute to a model or ledger, the system must identify the exact input revision, define the legal operation, check the output against an independently fixed reference and record which entity has authority to accept the transition.

A hash or signature secures a *statement about bytes and keys*; a numerical test constrains a *calculation*; a protocol governs *who may decide*; and an independent benchmark measures *whether the model is useful*. These statements are complementary, not interchangeable. A transparent experiment separates claims from measured outcomes.

## Worked case

Two copies of the same result carry one round identifier and sequence. The first may commit; the second must not add its samples again.

**Interpretation.** The worked result is a defined calculation or carefully bounded scenario. It does not assert an observed speedup, network finality, legal authorisation or a trained production model. When interpreting a number, state its denominator, units, assumptions and the exact predicate being checked.

## Practical native engineering exercise

Trace FederatedWire message sequence, AuthOpen and FederatedJobComplete boundaries.

A safe experiment uses **synthetic or explicitly authorised inputs**, checks every buffer bound, preserves independent reference results and records both expected-success and deliberate-rejection cases. Implement reusable operations in Umicom Framework C23/Assembly first; an application or course laboratory consumes the published API rather than maintaining a second implementation of its mathematics or hashing.

## Independent exercise

**Question:** Show why numerical validation alone cannot prevent double counting.

<details><summary>Reveal a worked answer</summary>

A perfectly finite duplicate vector could otherwise enter the mean twice and alter sample weights; one-use ticket transitions prevent that.

</details>

## Security, scientific and governance limits

A copied HMAC-valid message can still be a replay unless stateful freshness is checked.

The small experiments in this course do not establish a deployed blockchain, secure multiparty computation, real Internet-scale learning, a signed identity infrastructure or superior model quality unless a separate qualification specifically measures that property. **Honest negative results are valuable evidence.**

## Primary research and technical reading

- [FedAvg, McMahan et al.](https://proceedings.mlr.press/v54/mcmahan17a.html)
- [NIST Blockchain Technology Overview](https://csrc.nist.gov/pubs/ir/8202/final)

## Continue learning

- [Previous lesson](477-check-model-base-identity-before-admission.md)
- [Next lesson](479-compare-hmac-and-public-key-signatures.md)
- [Browser lesson](../../courses/llm-from-scratch/lessons/478-model-idempotent-submission-and-replay-rejection.html)
- [Complete study route](../../courses/llm-from-scratch/federated-evidence-and-trusted-anchors.html)

*Service to Many Leads to Greatness.*
