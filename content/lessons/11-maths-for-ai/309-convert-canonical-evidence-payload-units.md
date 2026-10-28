# Mathematics for AI — Unit 309: Convert canonical evidence payload units

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Licence:** MIT · **Language:** UK English  
**Study route:** Mathematics for AI · **Method:** reason → compute → test → qualify

## Learning objective

The example evidence anchor has a fixed 160-byte canonical payload: 8 schema bytes, 24 count/round bytes and 4×32 digests. Payload count does not include the enclosing record-chain metadata.

By the end of the lesson, a learner should be able to distinguish what the method mathematically establishes from what its security or distributed-systems context still requires. The objective is to explain the mechanism, reproduce the worked argument and recognise an invalid inference.

## Mechanism and architecture

The example evidence anchor has a fixed 160-byte canonical payload: 8 schema bytes, 24 count/round bytes and 4×32 digests. Payload count does not include the enclosing record-chain metadata. Consider the boundaries of **data identity**, **computation**, **trust** and **governance** independently. When several computers contribute to a model or ledger, the system must identify the exact input revision, define the legal operation, check the output against an independently fixed reference and record which entity has authority to accept the transition.

A hash or signature secures a *statement about bytes and keys*; a numerical test constrains a *calculation*; a protocol governs *who may decide*; and an independent benchmark measures *whether the model is useful*. These statements are complementary, not interchangeable. A transparent experiment separates claims from measured outcomes.

## Worked case

300 anchors use 300×160=48,000 payload bytes, or about 46.875 KiB, excluding record headers, signatures and replication.

**Interpretation.** The worked result is a defined calculation or carefully bounded scenario. It does not assert an observed speedup, network finality, legal authorisation or a trained production model. When interpreting a number, state its denominator, units, assumptions and the exact predicate being checked.

## Practical native engineering exercise

Inspect offsets 0,8,16,24,32,64,96,128 in the canonical C23 encoding.

A safe experiment uses **synthetic or explicitly authorised inputs**, checks every buffer bound, preserves independent reference results and records both expected-success and deliberate-rejection cases. Implement reusable operations in Umicom Framework C23/Assembly first; an application or course laboratory consumes the published API rather than maintaining a second implementation of its mathematics or hashing.

## Independent exercise

**Question:** What is the total raw payload for 20 anchors?

<details><summary>Reveal a worked answer</summary>

3,200 bytes; do not count cryptographic wrappers unless the problem states their size.

</details>

## Security, scientific and governance limits

A cryptographic digest may be only a commitment to external storage, not a copy of the underlying dataset.

The small experiments in this course do not establish a deployed blockchain, secure multiparty computation, real Internet-scale learning, a signed identity infrastructure or superior model quality unless a separate qualification specifically measures that property. **Honest negative results are valuable evidence.**

## Primary research and technical reading

- [NIST Blockchain Technology Overview](https://csrc.nist.gov/pubs/ir/8202/final)
- [Umicom Framework bounded Merkle code](https://github.com/umicom-foundation/umicom-framework)

## Continue learning

- [Previous lesson](308-compute-majority-overlap-for-crash-fault-replication.md)
- [Next lesson](310-distinguish-committed-and-replicated-bytes.md)
- [Browser lesson](../../courses/maths-for-ai/lessons/309-convert-canonical-evidence-payload-units.html)
- [Complete study route](../../courses/maths-for-ai/evidence-consensus-mathematics.html)

*Service to Many Leads to Greatness.*
