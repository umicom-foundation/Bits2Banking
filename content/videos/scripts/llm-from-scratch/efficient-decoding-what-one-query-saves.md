# Video lesson — One query versus the complete attention matrix

**Bits to Banking · Umicom Foundation**  
**Script and storyboard:** Sammy Hegab  
**Format:** Short educational lecture with numerical overlays and captions.

## Purpose

This lesson reinforces native LLM Lessons 249–252 and Mathematics Units 137–139. Diagram annotations are conceptual and do not depict measured Umicom Framework runtime performance.

## Storyboard and narration

### Scene 1 — The last token

**Visual:** Five tokens arranged left to right; show the lower triangular attention mask. **Narration:** A causal Transformer can read its past but not its future. A full sequence calculation includes several query rows. Incremental decoding asks a narrower question: what does the newest query need to read? Its keys and values come from admitted previous tokens plus the latest token, so the answer is one vector, not another square matrix.

### Scene 2 — Count the work

**Visual:** A four-by-four causal attention triangle; ten illuminated cells. Then add a fifth token and highlight only its five scores. **Narration:** Four causal rows require one plus two plus three plus four, ten scores per head. A fifth token requires just five new query–key scores. This saves unnecessary query-row arithmetic, but a model still performs projections, residuals and feed-forward operations.

### Scene 3 — Calculate the output

**Visual:** Q=[1,0], two key vectors and two value vectors. Display stable scores, probabilities about 0.6698 and 0.3302, and final vector [3.321,5.321]. **Narration:** The values are weighted by probabilities. We compute the score with the head-width scale, subtract the maximum for stability, then form a weighted sum. The order and finite-value rules matter when checking the native operator against the canonical one.

### Scene 4 — The experiment

**Visual:** Split display: canonical training tape on the left and candidate forward-only operator on the right. **Narration:** The first proof checks the last attention row for the same Q, K and V. Later proofs must compare every layer and every vocabulary logit. That is how we separate numerical correctness from hopeful performance claims.

## On-screen recap

The architecture, mathematical contract and actual observed performance are three different subjects. A viewer should be able to repeat the worked numbers and identify which proof would establish an inference optimisation's correctness.

## Suggested check-for-understanding

Pause before the final scene, hide the answer and ask the learner to explain one invariant using the numbers on screen. Reveal the original equation, not merely a claimed conclusion.

*Service to Many Leads to Greatness.*
