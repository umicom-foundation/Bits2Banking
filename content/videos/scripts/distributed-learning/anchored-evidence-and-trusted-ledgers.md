# Safe federated admission and evidence — Video narration and storyboard

**Series:** Bits to Banking · Distributed Learning  
**Author:** Sammy Hegab · **Organisation:** Umicom Foundation · **Licence:** MIT

## Learning objectives

Explain the difference between a cryptographic commitment, a test result and an authorised distributed decision. Complete the linked numerical exercises before treating an experiment as qualified.

## Scene 1 — Define the question

**Visual:** Three labelled cards: *byte integrity*, *model quality*, *consensus finality*. Each represents a different claim.

**Narration:** An authenticated update can still be wrong. A worker returns a mathematically finite model delta. The coordinator checks message authentication, worker permission, base checkpoint identity and ticket freshness separately.

## Scene 2 — The reproducible worked case

**Visual:** A plain-text dependency chain showing input revisions, a finite operation and the resulting evidence object.

**Narration:** Demonstrate a lost-ack scenario. A successful update is resent; the round+sequence mapping prevents the contribution from being counted twice.

## Scene 3 — Demonstrate a failed assumption

**Visual:** Original record versus altered record, with a clear rejection outcome and no decorative success icon for a failing check.

**Narration:** A permissioned consortium can have a finalised entry recording a low-quality model. Consensus says an entry was agreed; an evaluator still decides whether the model is fit for use.

## Scene 4 — What remains to be proven

**Visual:** A two-column comparison: independently verified properties on the left and outstanding network, data-rights or model-quality checks on the right.

**Narration:** Only synthetic and authorised data belongs in the classroom. Real patient, banking or private training examples must remain excluded.

## Learner pause and answer

**Question:** Why does a valid SHA-256 or Merkle commitment not alone prove that a training contribution was honest and useful?

**Answer:** Cryptographic integrity establishes a reproducible relation between supplied bytes and a commitment. Honest training and usefulness require separately specified execution, identity, data governance and independent evaluation evidence. Consensus, where used, addresses shared ordering and finality rather than training correctness.

## Further reading

- [NIST Blockchain Technology Overview](https://csrc.nist.gov/pubs/ir/8202/final)
- [Communication-Efficient Learning of Deep Networks from Decentralized Data](https://proceedings.mlr.press/v54/mcmahan17a.html)

*Service to Many Leads to Greatness.*
