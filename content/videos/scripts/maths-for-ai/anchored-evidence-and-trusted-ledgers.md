# The arithmetic of anchored evidence — Video narration and storyboard

**Series:** Bits to Banking · Maths For Ai  
**Author:** Sammy Hegab · **Organisation:** Umicom Foundation · **Licence:** MIT

## Learning objectives

Explain the difference between a cryptographic commitment, a test result and an authorised distributed decision. Complete the linked numerical exercises before treating an experiment as qualified.

## Scene 1 — Define the question

**Visual:** Three labelled cards: *byte integrity*, *model quality*, *consensus finality*. Each represents a different claim.

**Narration:** Count proofs, not promises. For 1,000 leaves, a balanced binary tree needs ten sibling levels. With SHA-256 digests, that is 320 bytes of sibling values before metadata.

## Scene 2 — The reproducible worked case

**Visual:** A plain-text dependency chain showing input revisions, a finite operation and the resulting evidence object.

**Narration:** Four replicas storing the same two-mebibyte log hold eight mebibytes of logical payload. This calculation says nothing about whether a consensus protocol is safe.

## Scene 3 — Demonstrate a failed assumption

**Visual:** Original record versus altered record, with a clear rejection outcome and no decorative success icon for a failing check.

**Narration:** Three workers have accepted deltas of 0.04, −0.02 and 0.08 with sample counts 100, 250 and 150. Reject the middle worker: the accepted weighted mean is 0.064, not 0.032.

## Scene 4 — What remains to be proven

**Visual:** A two-column comparison: independently verified properties on the left and outstanding network, data-rights or model-quality checks on the right.

**Narration:** The denominator, exclusions and trusted reference must always be shown. An accepted fraction is not a model-quality rate.

## Learner pause and answer

**Question:** Why does a valid SHA-256 or Merkle commitment not alone prove that a training contribution was honest and useful?

**Answer:** Cryptographic integrity establishes a reproducible relation between supplied bytes and a commitment. Honest training and usefulness require separately specified execution, identity, data governance and independent evaluation evidence. Consensus, where used, addresses shared ordering and finality rather than training correctness.

## Further reading

- [NIST Blockchain Technology Overview](https://csrc.nist.gov/pubs/ir/8202/final)
- [Communication-Efficient Learning of Deep Networks from Decentralized Data](https://proceedings.mlr.press/v54/mcmahan17a.html)

*Service to Many Leads to Greatness.*
