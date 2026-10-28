# Native LLM Engineering — Lesson 486: Measure verification cost against training cost

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Licence:** MIT · **Language:** UK English  
**Study route:** Native LLM Engineering · **Method:** reason → compute → test → qualify

## Learning objective

Verification may involve short hashes, signature checks, sampling or full training replay. The comparison must count verifier compute and communication, not only worker compute.

By the end of the lesson, a learner should be able to distinguish what the method mathematically establishes from what its security or distributed-systems context still requires. The objective is to explain the mechanism, reproduce the worked argument and recognise an invalid inference.

## Mechanism and architecture

Verification may involve short hashes, signature checks, sampling or full training replay. The comparison must count verifier compute and communication, not only worker compute. Consider the boundaries of **data identity**, **computation**, **trust** and **governance** independently. When several computers contribute to a model or ledger, the system must identify the exact input revision, define the legal operation, check the output against an independently fixed reference and record which entity has authority to accept the transition.

A hash or signature secures a *statement about bytes and keys*; a numerical test constrains a *calculation*; a protocol governs *who may decide*; and an independent benchmark measures *whether the model is useful*. These statements are complementary, not interchangeable. A transparent experiment separates claims from measured outcomes.

## Worked case

If training takes 90 s and full replay takes 90 s, the verifier adds a 100% compute overhead. If a sampled check takes 6 s, its 6.7% cost comes with weaker detection guarantees.

**Interpretation.** The worked result is a defined calculation or carefully bounded scenario. It does not assert an observed speedup, network finality, legal authorisation or a trained production model. When interpreting a number, state its denominator, units, assumptions and the exact predicate being checked.

## Practical native engineering exercise

Record timing and CPU/energy evidence separately from crypto and model scores.

A safe experiment uses **synthetic or explicitly authorised inputs**, checks every buffer bound, preserves independent reference results and records both expected-success and deliberate-rejection cases. Implement reusable operations in Umicom Framework C23/Assembly first; an application or course laboratory consumes the published API rather than maintaining a second implementation of its mathematics or hashing.

## Independent exercise

**Question:** Why cannot a cheap Merkle proof substitute for a model-quality evaluation?

<details><summary>Reveal a worked answer</summary>

It checks inclusion of bytes in a commitment, not the mathematical effect of the underlying update.

</details>

## Security, scientific and governance limits

Adversaries can optimise against fixed, publicly known checks; sampling assumptions must be explicit.

The small experiments in this course do not establish a deployed blockchain, secure multiparty computation, real Internet-scale learning, a signed identity infrastructure or superior model quality unless a separate qualification specifically measures that property. **Honest negative results are valuable evidence.**

## Primary research and technical reading

- [FedAvg, McMahan et al.](https://proceedings.mlr.press/v54/mcmahan17a.html)
- [NIST Blockchain Technology Overview](https://csrc.nist.gov/pubs/ir/8202/final)

## Continue learning

- [Previous lesson](485-handle-contradictory-audit-branches.md)
- [Next lesson](487-publish-a-reproducible-evidence-package.md)
- [Browser lesson](../../courses/llm-from-scratch/lessons/486-measure-verification-cost-against-training-cost.html)
- [Complete study route](../../courses/llm-from-scratch/federated-evidence-and-trusted-anchors.html)

*Service to Many Leads to Greatness.*
