# Native LLM Engineering — Lesson 477: Check model base identity before admission

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Licence:** MIT · **Language:** UK English  
**Study route:** Native LLM Engineering · **Method:** reason → compute → test → qualify

## Learning objective

Every worker update must declare the same immutable base checkpoint expected by the aggregation round. Combining updates from different bases without an explicit transform makes the arithmetic ill-defined.

By the end of the lesson, a learner should be able to distinguish what the method mathematically establishes from what its security or distributed-systems context still requires. The objective is to explain the mechanism, reproduce the worked argument and recognise an invalid inference.

## Mechanism and architecture

Every worker update must declare the same immutable base checkpoint expected by the aggregation round. Combining updates from different bases without an explicit transform makes the arithmetic ill-defined. Consider the boundaries of **data identity**, **computation**, **trust** and **governance** independently. When several computers contribute to a model or ledger, the system must identify the exact input revision, define the legal operation, check the output against an independently fixed reference and record which entity has authority to accept the transition.

A hash or signature secures a *statement about bytes and keys*; a numerical test constrains a *calculation*; a protocol governs *who may decide*; and an independent benchmark measures *whether the model is useful*. These statements are complementary, not interchangeable. A transparent experiment separates claims from measured outcomes.

## Worked case

If A reports base digest X and B reports Y, both may have finite vectors but their deltas cannot safely be averaged as one update to X.

**Interpretation.** The worked result is a defined calculation or carefully bounded scenario. It does not assert an observed speedup, network finality, legal authorisation or a trained production model. When interpreting a number, state its denominator, units, assumptions and the exact predicate being checked.

## Practical native engineering exercise

Reuse FederatedJob identity checks before invoking FederatedRound.

A safe experiment uses **synthetic or explicitly authorised inputs**, checks every buffer bound, preserves independent reference results and records both expected-success and deliberate-rejection cases. Implement reusable operations in Umicom Framework C23/Assembly first; an application or course laboratory consumes the published API rather than maintaining a second implementation of its mathematics or hashing.

## Independent exercise

**Question:** What is the minimum response to a base-digest mismatch?

<details><summary>Reveal a worked answer</summary>

Reject or quarantine B; request a fresh authorised assignment at the correct base rather than reinterpret its bytes.

</details>

## Security, scientific and governance limits

A digest match is not a signature or permission to read a dataset.

The small experiments in this course do not establish a deployed blockchain, secure multiparty computation, real Internet-scale learning, a signed identity infrastructure or superior model quality unless a separate qualification specifically measures that property. **Honest negative results are valuable evidence.**

## Primary research and technical reading

- [FedAvg, McMahan et al.](https://proceedings.mlr.press/v54/mcmahan17a.html)
- [NIST Blockchain Technology Overview](https://csrc.nist.gov/pubs/ir/8202/final)

## Continue learning

- [Previous lesson](476-separate-an-anchor-from-a-self-declared-root.md)
- [Next lesson](478-model-idempotent-submission-and-replay-rejection.md)
- [Browser lesson](../../courses/llm-from-scratch/lessons/477-check-model-base-identity-before-admission.html)
- [Complete study route](../../courses/llm-from-scratch/federated-evidence-and-trusted-anchors.html)

*Service to Many Leads to Greatness.*
