# Video lesson — Position schemes, KV quantisation and speculative verification

**Bits to Banking · Umicom Foundation**  
**Script and storyboard:** Sammy Hegab  
**Format:** Short educational lecture with numerical overlays and captions.

## Purpose

This lesson reinforces native LLM Lessons 256–260 and Mathematics Units 142–147. Diagram annotations are conceptual and do not depict measured Umicom Framework runtime performance.

## Storyboard and narration

### Scene 1 — A cache is derived state

**Visual:** Weights, prompt and positional scheme feeding K/V projections. **Narration:** A cache is not raw text. It is a model-specific numerical product. Changing weights or position IDs changes its meaning. A full context rollover is necessary for the established learned-absolute-position decoder because the surviving tokens move to different positions.

### Scene 2 — Compressing the cache

**Visual:** FP32 numbers become signed 8-bit approximations with a scale. **Narration:** Quantisation lowers storage and traffic but introduces numerical error. The example 0.37 with scale 0.02 becomes integer 19 and reconstructs as 0.38. The resulting error must be evaluated not only per tensor element but also through attention and vocabulary logits.

### Scene 3 — Rotary coordinates

**Visual:** Rotate vector (1,0) through 90 degrees to (0,1). **Narration:** Rotary position embeddings transform paired Q/K dimensions with position-dependent rotations. They explain a different positional model; they are not a free replacement for a checkpoint trained with learned absolute embeddings.

### Scene 4 — Draft and verify

**Visual:** Draft sequence A–B–C; target checks A–B–D, rejecting C. **Narration:** Speculative decoding can use a cheaper model to propose work, but acceptance is governed by target-model predictions. Random sampling needs a defined acceptance and correction distribution, not merely token matching.

## On-screen recap

The architecture, mathematical contract and actual observed performance are three different subjects. A viewer should be able to repeat the worked numbers and identify which proof would establish an inference optimisation's correctness.

## Suggested check-for-understanding

Pause before the final scene, hide the answer and ask the learner to explain one invariant using the numbers on screen. Reveal the original equation, not merely a claimed conclusion.

*Service to Many Leads to Greatness.*
