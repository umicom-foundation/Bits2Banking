# How to test a verifiable-learning thesis — Video narration and storyboard

**Series:** Bits to Banking · Ai Research  
**Author:** Sammy Hegab · **Organisation:** Umicom Foundation · **Licence:** MIT

## Learning objectives

Explain the difference between a cryptographic commitment, a test result and an authorised distributed decision. Complete the linked numerical exercises before treating an experiment as qualified.

## Scene 1 — Define the question

**Visual:** Three labelled cards: *byte integrity*, *model quality*, *consensus finality*. Each represents a different claim.

**Narration:** Make failure observable. Compare a single-worker or centralised baseline against a federated variant using the same model, dataset split and token budget.

## Scene 2 — The reproducible worked case

**Visual:** A plain-text dependency chain showing input revisions, a finite operation and the resulting evidence object.

**Narration:** Set attack cases and quality metrics before running. A verifier catching 70 of 100 malicious updates while rejecting 8 of 200 honest updates has 70 percent detection and 4 percent false-rejection.

## Scene 3 — Demonstrate a failed assumption

**Visual:** Original record versus altered record, with a clear rejection outcome and no decorative success icon for a failing check.

**Narration:** Add independent variables for WAN delay, checkpoint staleness and worker dropout. Report time to target quality and negative results, not only reduced network bytes.

## Scene 4 — What remains to be proven

**Visual:** A two-column comparison: independently verified properties on the left and outstanding network, data-rights or model-quality checks on the right.

**Narration:** A blockchain is an option only if a real multi-administrator trust problem emerges and its overhead is justified experimentally.

## Learner pause and answer

**Question:** Why does a valid SHA-256 or Merkle commitment not alone prove that a training contribution was honest and useful?

**Answer:** Cryptographic integrity establishes a reproducible relation between supplied bytes and a commitment. Honest training and usefulness require separately specified execution, identity, data governance and independent evaluation evidence. Consensus, where used, addresses shared ordering and finality rather than training correctness.

## Further reading

- [NIST Blockchain Technology Overview](https://csrc.nist.gov/pubs/ir/8202/final)
- [Communication-Efficient Learning of Deep Networks from Decentralized Data](https://proceedings.mlr.press/v54/mcmahan17a.html)

*Service to Many Leads to Greatness.*
