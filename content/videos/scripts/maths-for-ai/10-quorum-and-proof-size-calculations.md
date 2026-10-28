# Calculating Merkle Heights and Quorums — narration and storyboard

**Bits to Banking · Umicom Foundation**  
**Script author:** Sammy Hegab · **Licence:** MIT

## Sequence and narration

**Scene 1.** 0:00–1:00 — Start with 13 leaves. Apply repeated ceil(n/2) until reaching one: 13→7→4→2→1. Four sibling hashes are required.

**Scene 2.** 1:00–2:00 — Convert four 32-byte siblings into 128 bytes; add protocol metadata only after defining it.

**Scene 3.** 2:00–3:10 — Build a five-replica Raft example with majority three, then explain why this arithmetic is not Byzantine consensus.

**Scene 4.** 3:10–4:20 — Work a classical f=2 BFT threshold: N≥7 and at least five votes. Explain quorum intersection and the fault assumptions.

**Scene 5.** 4:20–5:30 — Close by comparing the cost of a Merkle proof with the cost of actual neural model verification; the quantities are not interchangeable.

## Accessibility and captions

Read all symbols aloud (including root, sequence, threshold and byte count). Put the intermediate equations into subtitles. Use distinguishable visual labels for independently authenticated facts, mathematical assumptions and conceptual examples. All figures are instructional, not real network captures or performance measurements.

## Closing prompt

Ask the learner which checks would still be missing after a successful Merkle membership proof. A satisfactory answer mentions actor authentication, authorisation, independent anchoring, ledger consensus/finality when relevant, and model usefulness evaluation.
