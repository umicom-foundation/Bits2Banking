# Mathematics for AI — Unit 311: Compute batch acceptance rates carefully

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Licence:** MIT · **Language:** UK English  
**Study route:** Mathematics for AI · **Method:** reason → compute → test → qualify

## Learning objective

A contribution-admission report records how many submissions were attempted and how many updates were accepted. Acceptance fraction alone does not measure training usefulness.

By the end of the lesson, a learner should be able to distinguish what the method mathematically establishes from what its security or distributed-systems context still requires. The objective is to explain the mechanism, reproduce the worked argument and recognise an invalid inference.

## Mechanism and architecture

A contribution-admission report records how many submissions were attempted and how many updates were accepted. Acceptance fraction alone does not measure training usefulness. Consider the boundaries of **data identity**, **computation**, **trust** and **governance** independently. When several computers contribute to a model or ledger, the system must identify the exact input revision, define the legal operation, check the output against an independently fixed reference and record which entity has authority to accept the transition.

A hash or signature secures a *statement about bytes and keys*; a numerical test constrains a *calculation*; a protocol governs *who may decide*; and an independent benchmark measures *whether the model is useful*. These statements are complementary, not interchangeable. A transparent experiment separates claims from measured outcomes.

## Worked case

A round receives 80 contributions and accepts 60: 60/80=75%. If 12 of the accepted later fail a hold-out gate, the final quality-passing fraction is 48/80=60%.

**Interpretation.** The worked result is a defined calculation or carefully bounded scenario. It does not assert an observed speedup, network finality, legal authorisation or a trained production model. When interpreting a number, state its denominator, units, assumptions and the exact predicate being checked.

## Practical native engineering exercise

Keep admission, integrity and quality counts separate in evidence receipts.

A safe experiment uses **synthetic or explicitly authorised inputs**, checks every buffer bound, preserves independent reference results and records both expected-success and deliberate-rejection cases. Implement reusable operations in Umicom Framework C23/Assembly first; an application or course laboratory consumes the published API rather than maintaining a second implementation of its mathematics or hashing.

## Independent exercise

**Question:** Why is '75% of contributions useful' unsupported?

<details><summary>Reveal a worked answer</summary>

The first gate may only validate framing, identity or norm; usefulness needs independent evaluation.

</details>

## Security, scientific and governance limits

Silent selection effects and non-IID data can bias comparisons.

The small experiments in this course do not establish a deployed blockchain, secure multiparty computation, real Internet-scale learning, a signed identity infrastructure or superior model quality unless a separate qualification specifically measures that property. **Honest negative results are valuable evidence.**

## Primary research and technical reading

- [NIST Blockchain Technology Overview](https://csrc.nist.gov/pubs/ir/8202/final)
- [Umicom Framework bounded Merkle code](https://github.com/umicom-foundation/umicom-framework)

## Continue learning

- [Previous lesson](310-distinguish-committed-and-replicated-bytes.md)
- [Next lesson](312-estimate-confirmation-and-finality-latency.md)
- [Browser lesson](../../courses/maths-for-ai/lessons/311-compute-batch-acceptance-rates-carefully.html)
- [Complete study route](../../courses/maths-for-ai/evidence-consensus-mathematics.html)

*Service to Many Leads to Greatness.*
