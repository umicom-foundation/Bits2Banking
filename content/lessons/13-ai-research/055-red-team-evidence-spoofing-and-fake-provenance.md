# AI Research Frontiers — Lesson 055: Red-team evidence spoofing and fake provenance

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Licence:** MIT · **Language:** UK English  
**Study route:** AI Research Frontiers · **Method:** reason → compute → test → qualify

## Learning objective

A malicious coordinator can build a perfectly valid Merkle root over invented receipts. Security requires a trusted checkpoint distribution and independently authenticated workers.

By the end of the lesson, a learner should be able to distinguish what the method mathematically establishes from what its security or distributed-systems context still requires. The objective is to explain the mechanism, reproduce the worked argument and recognise an invalid inference.

## Mechanism and architecture

A malicious coordinator can build a perfectly valid Merkle root over invented receipts. Security requires a trusted checkpoint distribution and independently authenticated workers. Consider the boundaries of **data identity**, **computation**, **trust** and **governance** independently. When several computers contribute to a model or ledger, the system must identify the exact input revision, define the legal operation, check the output against an independently fixed reference and record which entity has authority to accept the transition.

A hash or signature secures a *statement about bytes and keys*; a numerical test constrains a *calculation*; a protocol governs *who may decide*; and an independent benchmark measures *whether the model is useful*. These statements are complementary, not interchangeable. A transparent experiment separates claims from measured outcomes.

## Worked case

An attacker creates a new three-leaf root and a mathematically valid proof, then claims it represents authorised training.

**Interpretation.** The worked result is a defined calculation or carefully bounded scenario. It does not assert an observed speedup, network finality, legal authorisation or a trained production model. When interpreting a number, state its denominator, units, assumptions and the exact predicate being checked.

## Practical native engineering exercise

Threat-model independent checkpoint publication before designing incentives.

A safe experiment uses **synthetic or explicitly authorised inputs**, checks every buffer bound, preserves independent reference results and records both expected-success and deliberate-rejection cases. Implement reusable operations in Umicom Framework C23/Assembly first; an application or course laboratory consumes the published API rather than maintaining a second implementation of its mathematics or hashing.

## Independent exercise

**Question:** What evidence is missing?

<details><summary>Reveal a worked answer</summary>

A trusted chain anchor, independent identity/permission record, actual source/step verification and held-out quality evidence.

</details>

## Security, scientific and governance limits

A hash proof is not a signature or correctness proof.

The small experiments in this course do not establish a deployed blockchain, secure multiparty computation, real Internet-scale learning, a signed identity infrastructure or superior model quality unless a separate qualification specifically measures that property. **Honest negative results are valuable evidence.**

## Primary research and technical reading

- [DiLoCo research](https://arxiv.org/abs/2311.08105)
- [LoRA research](https://arxiv.org/abs/2106.09685)
- [NIST Blockchain Technology Overview](https://csrc.nist.gov/pubs/ir/8202/final)

## Continue learning

- [Previous lesson](054-study-hardware-portability-for-cryptographic-evidence.md)
- [Next lesson](056-measure-governance-value-before-introducing-tokens.md)
- [Browser lesson](../../courses/ai-research/lessons/055-red-team-evidence-spoofing-and-fake-provenance.html)
- [Complete study route](../../courses/ai-research/verifiable-learning-research-methods.html)

*Service to Many Leads to Greatness.*
