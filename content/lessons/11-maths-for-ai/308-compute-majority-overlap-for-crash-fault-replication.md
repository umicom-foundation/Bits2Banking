# Mathematics for AI — Unit 308: Compute majority overlap for crash-fault replication

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Licence:** MIT · **Language:** UK English  
**Study route:** Mathematics for AI · **Method:** reason → compute → test → qualify

## Learning objective

In a crash-fault majority system, any majority of an odd n intersects every other majority. A leader can commit only under the protocol's actual terms, not solely because packets arrived.

By the end of the lesson, a learner should be able to distinguish what the method mathematically establishes from what its security or distributed-systems context still requires. The objective is to explain the mechanism, reproduce the worked argument and recognise an invalid inference.

## Mechanism and architecture

In a crash-fault majority system, any majority of an odd n intersects every other majority. A leader can commit only under the protocol's actual terms, not solely because packets arrived. Consider the boundaries of **data identity**, **computation**, **trust** and **governance** independently. When several computers contribute to a model or ledger, the system must identify the exact input revision, define the legal operation, check the output against an independently fixed reference and record which entity has authority to accept the transition.

A hash or signature secures a *statement about bytes and keys*; a numerical test constrains a *calculation*; a protocol governs *who may decide*; and an independent benchmark measures *whether the model is useful*. These statements are complementary, not interchangeable. A transparent experiment separates claims from measured outcomes.

## Worked case

With n=5 nodes, a majority is floor(5/2)+1=3. Any two sets of three among five overlap in at least one node.

**Interpretation.** The worked result is a defined calculation or carefully bounded scenario. It does not assert an observed speedup, network finality, legal authorisation or a trained production model. When interpreting a number, state its denominator, units, assumptions and the exact predicate being checked.

## Practical native engineering exercise

Compare the idea with BFT quorum requirements and Raft safety rules.

A safe experiment uses **synthetic or explicitly authorised inputs**, checks every buffer bound, preserves independent reference results and records both expected-success and deliberate-rejection cases. Implement reusable operations in Umicom Framework C23/Assembly first; an application or course laboratory consumes the published API rather than maintaining a second implementation of its mathematics or hashing.

## Independent exercise

**Question:** Can two nodes alone establish a three-vote majority?

<details><summary>Reveal a worked answer</summary>

No; two out of five is insufficient even if both agree.

</details>

## Security, scientific and governance limits

Majority overlap does not defend against malicious replicas fabricating conflicting votes.

The small experiments in this course do not establish a deployed blockchain, secure multiparty computation, real Internet-scale learning, a signed identity infrastructure or superior model quality unless a separate qualification specifically measures that property. **Honest negative results are valuable evidence.**

## Primary research and technical reading

- [NIST Blockchain Technology Overview](https://csrc.nist.gov/pubs/ir/8202/final)
- [Umicom Framework bounded Merkle code](https://github.com/umicom-foundation/umicom-framework)

## Continue learning

- [Previous lesson](307-derive-byzantine-quorum-sizes.md)
- [Next lesson](309-convert-canonical-evidence-payload-units.md)
- [Browser lesson](../../courses/maths-for-ai/lessons/308-compute-majority-overlap-for-crash-fault-replication.html)
- [Complete study route](../../courses/maths-for-ai/evidence-consensus-mathematics.html)

*Service to Many Leads to Greatness.*
