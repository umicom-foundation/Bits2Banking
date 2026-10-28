# Testing Native C23 Merkle Evidence — narration and storyboard

**Bits to Banking · Umicom Foundation**  
**Script author:** Sammy Hegab · **Licence:** MIT

## Sequence and narration

**Scene 1.** 0:00–0:45 — Introduce the canonical Framework SHA-256 and record-chain modules. The lesson must not duplicate either implementation.

**Scene 2.** 0:45–2:00 — Read the Merkle header, identify leaf count 1–1024, caller-owned buffers and the output-unchanged-on-error contract.

**Scene 3.** 2:00–3:20 — Demonstrate tree construction for three leaves and explain duplicate-last and the count-binding root. The recorded source path remains the module in the shared Framework.

**Scene 4.** 3:20–4:20 — Explain native regression tests for wrong indices, changed leaves, mutated siblings, wrong root and overlapping outputs.

**Scene 5.** 4:20–5:40 — Conclude by listing real unperformed tests: authenticated WAN workers, full Windows checkout integration, governance finality and actual LLM convergence.

## Accessibility and captions

Read all symbols aloud (including root, sequence, threshold and byte count). Put the intermediate equations into subtitles. Use distinguishable visual labels for independently authenticated facts, mathematical assumptions and conceptual examples. All figures are instructional, not real network captures or performance measurements.

## Closing prompt

Ask the learner which checks would still be missing after a successful Merkle membership proof. A satisfactory answer mentions actor authentication, authorisation, independent anchoring, ledger consensus/finality when relevant, and model usefulness evaluation.
