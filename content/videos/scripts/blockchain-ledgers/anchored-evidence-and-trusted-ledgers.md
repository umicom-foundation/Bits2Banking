# What makes a distributed ledger trustworthy — Video narration and storyboard

**Series:** Bits to Banking · Blockchain Ledgers  
**Author:** Sammy Hegab · **Organisation:** Umicom Foundation · **Licence:** MIT

## Learning objectives

Explain the difference between a cryptographic commitment, a test result and an authorised distributed decision. Complete the linked numerical exercises before treating an experiment as qualified.

## Scene 1 — Define the question

**Visual:** Three labelled cards: *byte integrity*, *model quality*, *consensus finality*. Each represents a different claim.

**Narration:** Hash links, consensus and finality are different. A record chain links present data to previous data, and a Merkle root compresses a set of leaf commitments. Neither elects a leader or gives a malicious network one canonical history.

## Scene 2 — The reproducible worked case

**Visual:** A plain-text dependency chain showing input revisions, a finite operation and the resulting evidence object.

**Narration:** In a five-node crash-fault system, three votes are a majority. The isolated pair cannot elect a majority leader. With one Byzantine fault, a classical four-replica, three-vote design has different safety requirements.

## Scene 3 — Demonstrate a failed assumption

**Visual:** Original record versus altered record, with a clear rejection outcome and no decorative success icon for a failing check.

**Narration:** Contrast Proof of Work blocks, Proof of Stake validator votes, and Fabric-style endorsement, ordering and validation. The mathematics and threat models differ.

## Scene 4 — What remains to be proven

**Visual:** A two-column comparison: independently verified properties on the left and outstanding network, data-rights or model-quality checks on the right.

**Narration:** Do not mistake payment instructions for settlement or a signed training receipt for honest neural computation.

## Learner pause and answer

**Question:** Why does a valid SHA-256 or Merkle commitment not alone prove that a training contribution was honest and useful?

**Answer:** Cryptographic integrity establishes a reproducible relation between supplied bytes and a commitment. Honest training and usefulness require separately specified execution, identity, data governance and independent evaluation evidence. Consensus, where used, addresses shared ordering and finality rather than training correctness.

## Further reading

- [NIST Blockchain Technology Overview](https://csrc.nist.gov/pubs/ir/8202/final)
- [Communication-Efficient Learning of Deep Networks from Decentralized Data](https://proceedings.mlr.press/v54/mcmahan17a.html)

*Service to Many Leads to Greatness.*
