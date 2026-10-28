# Why Replication Is Not Consensus — narration and storyboard

**Bits to Banking · Umicom Foundation**  
**Script author:** Sammy Hegab · **Licence:** MIT

## Sequence and narration

**Scene 1.** 0:00–1:00 — Three computers have a copy of a financial ledger. A network partition splits one from the other two. Both sides can still compute hashes, but can they both commit conflicting balances safely?

**Scene 2.** 1:00–2:00 — Introduce Raft’s crash-fault majority with a five-voter example. Show that three reachable voters can form a majority while two cannot. Recompute the quorum as floor(N/2)+1.

**Scene 3.** 2:00–3:30 — Contrast Byzantine behaviour: a faulty node deliberately sends conflicting proposals. Explain why 3f+1 and 2f+1 arise in a family of authenticated BFT protocols, without pretending that these numbers alone implement consensus.

**Scene 4.** 3:30–4:30 — Compare Ethereum stake-weighted checkpoints and a permissioned Hyperledger Fabric ordering service. Use “different fault models” rather than “one is universally better”.

**Scene 5.** 4:30–5:30 — End with a decision table: signed log, Merkle batch, Raft replicated log, BFT ordering and public blockchain. Define which property each provides.

## Accessibility and captions

Read all symbols aloud (including root, sequence, threshold and byte count). Put the intermediate equations into subtitles. Use distinguishable visual labels for independently authenticated facts, mathematical assumptions and conceptual examples. All figures are instructional, not real network captures or performance measurements.

## Closing prompt

Ask the learner which checks would still be missing after a successful Merkle membership proof. A satisfactory answer mentions actor authentication, authorisation, independent anchoring, ledger consensus/finality when relevant, and model usefulness evaluation.
