# Native LLM Engineering — Lesson 474: Build a canonical round evidence manifest

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Licence:** MIT · **Language:** UK English  
**Study route:** Native LLM Engineering · **Method:** reason → compute → test → qualify

## Learning objective

Canonical encoding avoids native struct padding and differing endian orders. Bind the round ID, submitted count, accepted count, base model, data policy, evaluation and ordered accepted-receipt root.

By the end of the lesson, a learner should be able to distinguish what the method mathematically establishes from what its security or distributed-systems context still requires. The objective is to explain the mechanism, reproduce the worked argument and recognise an invalid inference.

## Mechanism and architecture

Canonical encoding avoids native struct padding and differing endian orders. Bind the round ID, submitted count, accepted count, base model, data policy, evaluation and ordered accepted-receipt root. Consider the boundaries of **data identity**, **computation**, **trust** and **governance** independently. When several computers contribute to a model or ledger, the system must identify the exact input revision, define the legal operation, check the output against an independently fixed reference and record which entity has authority to accept the transition.

A hash or signature secures a *statement about bytes and keys*; a numerical test constrains a *calculation*; a protocol governs *who may decide*; and an independent benchmark measures *whether the model is useful*. These statements are complementary, not interchangeable. A transparent experiment separates claims from measured outcomes.

## Worked case

The educational anchor uses 160 bytes: 8 bytes schema, 24 bytes for three 64-bit counts and 128 bytes for four digests. 8+24+128=160.

**Interpretation.** The worked result is a defined calculation or carefully bounded scenario. It does not assert an observed speedup, network finality, legal authorisation or a trained production model. When interpreting a number, state its denominator, units, assumptions and the exact predicate being checked.

## Practical native engineering exercise

Inspect the 160-byte C23 payload under the existing Framework record-chain service.

A safe experiment uses **synthetic or explicitly authorised inputs**, checks every buffer bound, preserves independent reference results and records both expected-success and deliberate-rejection cases. Implement reusable operations in Umicom Framework C23/Assembly first; an application or course laboratory consumes the published API rather than maintaining a second implementation of its mathematics or hashing.

## Independent exercise

**Question:** Explain why a raw memory dump of a C struct is unsuitable for interoperable evidence.

<details><summary>Reveal a worked answer</summary>

Alignment gaps, pointer sizes and native endian order may differ across compilers and processors; explicit offsets prevent those ambiguities.

</details>

## Security, scientific and governance limits

The encoded count is an assertion from the coordinator, not independent proof that the declared workers trained.

The small experiments in this course do not establish a deployed blockchain, secure multiparty computation, real Internet-scale learning, a signed identity infrastructure or superior model quality unless a separate qualification specifically measures that property. **Honest negative results are valuable evidence.**

## Primary research and technical reading

- [FedAvg, McMahan et al.](https://proceedings.mlr.press/v54/mcmahan17a.html)
- [NIST Blockchain Technology Overview](https://csrc.nist.gov/pubs/ir/8202/final)

## Continue learning

- [Previous lesson](473-distinguish-provenance-from-learning-quality.md)
- [Next lesson](475-bind-approved-worker-contributions-with-merkle-roots.md)
- [Browser lesson](../../courses/llm-from-scratch/lessons/474-build-a-canonical-round-evidence-manifest.html)
- [Complete study route](../../courses/llm-from-scratch/federated-evidence-and-trusted-anchors.html)

*Service to Many Leads to Greatness.*
