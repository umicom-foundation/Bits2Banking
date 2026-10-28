# Merkle Trees from First Principles — narration and storyboard

**Bits to Banking · Umicom Foundation**  
**Script author:** Sammy Hegab · **Licence:** MIT

## Sequence and narration

**Scene 1.** 0:00–0:45 — A bank, an educational network and a scientific lab may all need to prove that a record belonged to a particular historical batch. What does an auditor need? Not all the documents—if the auditor already trusts a root.

**Scene 2.** 0:45–2:00 — Draw four boxes A/B/C/D as canonical digest inputs. Domain-hash each into leaves. Hash two adjacent leaves into a parent, then the two parents. Emphasise that the original record digest is not a signature.

**Scene 3.** 2:00–3:30 — Demonstrate an inclusion proof for C: show sibling D and left subtree P0, then reconstruct the root. Pause after each layer to ask learners which side the sibling occupies.

**Scene 4.** 3:30–4:30 — Reconstruct the same proof with one changed byte: the final root changes. Show that accepting an attacker-supplied replacement root would defeat the check.

**Scene 5.** 4:30–5:30 — Repeat with five leaves, duplicated last nodes and a count-bound final root. Close by distinguishing membership from consensus, trust and model quality.

## Accessibility and captions

Read all symbols aloud (including root, sequence, threshold and byte count). Put the intermediate equations into subtitles. Use distinguishable visual labels for independently authenticated facts, mathematical assumptions and conceptual examples. All figures are instructional, not real network captures or performance measurements.

## Closing prompt

Ask the learner which checks would still be missing after a successful Merkle membership proof. A satisfactory answer mentions actor authentication, authorisation, independent anchoring, ledger consensus/finality when relevant, and model usefulness evaluation.
