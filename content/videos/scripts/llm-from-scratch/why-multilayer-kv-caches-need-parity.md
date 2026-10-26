# Video script — Why multi-layer KV caches need parity

**Bits to Banking · Umicom Foundation · Sammy Hegab**

**Learning goal:** Explain why a cache correct for one attention block may not be equivalent after context eviction in a deeper Transformer.

## Opening · On-screen illustration

Show four fictional tokens A, B, C and D entering a three-layer decoder. Narration: “A key and value represent more than a token number when they were calculated from earlier attention outputs.”

## Scene 1 · A first-block representation

Illustrate token B at its original absolute position. In a first block, its projection may be determined by B's fixed input embedding and positional rule. On-screen label: “First-block projection: local model assumptions matter.”

## Scene 2 · Hidden-state history

Connect the output of B's first-block attention to its second-block key. Highlight a contribution from A. Slide the window to B–E and remove A. Show a fresh truncated-window calculation next to B's historical cached key. Narration: “These are not automatically the same hidden states; keeping a fixed RoPE angle is insufficient.”

## Scene 3 · Qualification before speed claims

Display a comparison table: same checkpoint; same token positions; canonical reference logits; candidate cached logits; fixed numerical tolerance; check just before and after eviction. Explain that comparing only the winning token misses changes to the probability distribution.

## Closing · Learner exercise

Ask: “How can a key at the same token position still be stale after an earlier token disappears?” Pause for an answer. Reveal: “Its layer input already contained information from the evicted history.”

**Production note:** This is an educational storyboard, not evidence that a multi-layer cache has been implemented or benchmarked.
