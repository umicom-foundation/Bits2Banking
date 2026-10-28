# Mathematics for AI — Unit 315: Calculate weighted mean after rejection

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Licence:** MIT · **Language:** UK English  
**Study route:** Mathematics for AI · **Method:** reason → compute → test → qualify

## Learning objective

FedAvg combines compatible weight-space updates using accepted sample counts as weights. Rejected workers must not remain in the denominator.

By the end of the lesson, a learner should be able to distinguish what the method mathematically establishes from what its security or distributed-systems context still requires. The objective is to explain the mechanism, reproduce the worked argument and recognise an invalid inference.

## Mechanism and architecture

FedAvg combines compatible weight-space updates using accepted sample counts as weights. Rejected workers must not remain in the denominator. Consider the boundaries of **data identity**, **computation**, **trust** and **governance** independently. When several computers contribute to a model or ledger, the system must identify the exact input revision, define the legal operation, check the output against an independently fixed reference and record which entity has authority to accept the transition.

A hash or signature secures a *statement about bytes and keys*; a numerical test constrains a *calculation*; a protocol governs *who may decide*; and an independent benchmark measures *whether the model is useful*. These statements are complementary, not interchangeable. A transparent experiment separates claims from measured outcomes.

## Worked case

Workers A,B,C have samples 100,250,150 and deltas 0.04,−0.02,0.08. If B is rejected, aggregate (100×0.04+150×0.08)/(100+150)=16/250=0.064.

**Interpretation.** The worked result is a defined calculation or carefully bounded scenario. It does not assert an observed speedup, network finality, legal authorisation or a trained production model. When interpreting a number, state its denominator, units, assumptions and the exact predicate being checked.

## Practical native engineering exercise

Reuse FederatedRound; avoid reimplementing aggregator arithmetic in the teaching app.

A safe experiment uses **synthetic or explicitly authorised inputs**, checks every buffer bound, preserves independent reference results and records both expected-success and deliberate-rejection cases. Implement reusable operations in Umicom Framework C23/Assembly first; an application or course laboratory consumes the published API rather than maintaining a second implementation of its mathematics or hashing.

## Independent exercise

**Question:** What incorrect result comes from keeping B's 250 samples in the denominator after excluding its delta?

<details><summary>Reveal a worked answer</summary>

16/500=0.032, which is not the accepted-worker weighted mean.

</details>

## Security, scientific and governance limits

Matching the same base checkpoint is required before averaging.

The small experiments in this course do not establish a deployed blockchain, secure multiparty computation, real Internet-scale learning, a signed identity infrastructure or superior model quality unless a separate qualification specifically measures that property. **Honest negative results are valuable evidence.**

## Primary research and technical reading

- [NIST Blockchain Technology Overview](https://csrc.nist.gov/pubs/ir/8202/final)
- [Umicom Framework bounded Merkle code](https://github.com/umicom-foundation/umicom-framework)

## Continue learning

- [Previous lesson](314-model-verification-economic-break-even.md)
- [Next lesson](316-quantify-rollback-and-evidence-finality.md)
- [Browser lesson](../../courses/maths-for-ai/lessons/315-calculate-weighted-mean-after-rejection.html)
- [Complete study route](../../courses/maths-for-ai/evidence-consensus-mathematics.html)

*Service to Many Leads to Greatness.*
