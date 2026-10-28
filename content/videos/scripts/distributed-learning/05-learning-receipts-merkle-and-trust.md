# Learning Receipts, Merkle Proofs and Trust — narration and storyboard

**Bits to Banking · Umicom Foundation**  
**Script author:** Sammy Hegab · **Licence:** MIT

## Sequence and narration

**Scene 1.** 0:00–0:50 — A training worker submits a signed synthetic update receipt; a second system records the decision. Explain why a valid signature can accompany a harmful or stale update.

**Scene 2.** 0:50–2:10 — Place an independently evaluated decision into a record chain, then use its digest as the Merkle leaf. The proof verifies inclusion in one batch, not correctness of the original decision.

**Scene 3.** 2:10–3:10 — Use three workers and a trusted root. One result is accepted, another rejected and the third cancelled. All three decisions can appear in a history but only an accepted finite delta can enter aggregation.

**Scene 4.** 3:10–4:10 — Describe an attacker replacing the entire archive and root. Show how separately retained trusted roots reveal the discrepancy.

**Scene 5.** 4:10–5:30 — Explain the limits: HMAC is not encryption, Merkle is not consensus, and a training reward needs independent usefulness evidence.

## Accessibility and captions

Read all symbols aloud (including root, sequence, threshold and byte count). Put the intermediate equations into subtitles. Use distinguishable visual labels for independently authenticated facts, mathematical assumptions and conceptual examples. All figures are instructional, not real network captures or performance measurements.

## Closing prompt

Ask the learner which checks would still be missing after a successful Merkle membership proof. A satisfactory answer mentions actor authentication, authorisation, independent anchoring, ledger consensus/finality when relevant, and model usefulness evaluation.
