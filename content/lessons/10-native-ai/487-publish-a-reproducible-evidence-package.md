# Native LLM Engineering — Lesson 487: Publish a reproducible evidence package

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Licence:** MIT · **Language:** UK English  
**Study route:** Native LLM Engineering · **Method:** reason → compute → test → qualify

## Learning objective

A scientific result needs code revision, dataset licence and split, model checkpoint, independent test set, seeds, hardware, protocol, latency and actual outputs. Controlled negative results belong alongside successes.

By the end of the lesson, a learner should be able to distinguish what the method mathematically establishes from what its security or distributed-systems context still requires. The objective is to explain the mechanism, reproduce the worked argument and recognise an invalid inference.

## Mechanism and architecture

A scientific result needs code revision, dataset licence and split, model checkpoint, independent test set, seeds, hardware, protocol, latency and actual outputs. Controlled negative results belong alongside successes. Consider the boundaries of **data identity**, **computation**, **trust** and **governance** independently. When several computers contribute to a model or ledger, the system must identify the exact input revision, define the legal operation, check the output against an independently fixed reference and record which entity has authority to accept the transition.

A hash or signature secures a *statement about bytes and keys*; a numerical test constrains a *calculation*; a protocol governs *who may decide*; and an independent benchmark measures *whether the model is useful*. These statements are complementary, not interchangeable. A transparent experiment separates claims from measured outcomes.

## Worked case

A reported 20% reduction in bytes is not evidence of faster time to target accuracy if model loss is worse.

**Interpretation.** The worked result is a defined calculation or carefully bounded scenario. It does not assert an observed speedup, network finality, legal authorisation or a trained production model. When interpreting a number, state its denominator, units, assumptions and the exact predicate being checked.

## Practical native engineering exercise

Use native Framework evidence services and public Bits2Banking research manifests.

A safe experiment uses **synthetic or explicitly authorised inputs**, checks every buffer bound, preserves independent reference results and records both expected-success and deliberate-rejection cases. Implement reusable operations in Umicom Framework C23/Assembly first; an application or course laboratory consumes the published API rather than maintaining a second implementation of its mathematics or hashing.

## Independent exercise

**Question:** Specify the primary endpoints for a distributed-training comparison.

<details><summary>Reveal a worked answer</summary>

Include held-out loss/accuracy, time to a registered quality target, bytes transferred, total computation, verifier cost and attack outcomes.

</details>

## Security, scientific and governance limits

Publicly publish only authorised aggregate/synthetic data, not raw banking or patient records.

The small experiments in this course do not establish a deployed blockchain, secure multiparty computation, real Internet-scale learning, a signed identity infrastructure or superior model quality unless a separate qualification specifically measures that property. **Honest negative results are valuable evidence.**

## Primary research and technical reading

- [FedAvg, McMahan et al.](https://proceedings.mlr.press/v54/mcmahan17a.html)
- [NIST Blockchain Technology Overview](https://csrc.nist.gov/pubs/ir/8202/final)

## Continue learning

- [Previous lesson](486-measure-verification-cost-against-training-cost.md)
- [Next lesson](488-complete-an-anchored-learning-evidence-capstone.md)
- [Browser lesson](../../courses/llm-from-scratch/lessons/487-publish-a-reproducible-evidence-package.html)
- [Complete study route](../../courses/llm-from-scratch/federated-evidence-and-trusted-anchors.html)

*Service to Many Leads to Greatness.*
