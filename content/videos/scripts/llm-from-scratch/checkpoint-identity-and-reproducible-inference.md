# Video teaching script — Which model produced this output?

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Format:** English narration with a screen-recorded C23 demonstration and simple diagrams.

## Intended learning outcome

Learners should understand the numerical contract and the Framework's
ownership boundaries without needing an external AI provider or access to
any private training data. Use invented token IDs and local synthetic model
configurations in every scene.

## Storyboard and narration

### 00:00–01:00

**On screen:** A simple diagram or code panel illustrating this step.

**Narration:** Contrast two models of identical shapes but different trained weights. Pose the question: can a human reproduce the answer?

### 01:00–02:00

**On screen:** A simple diagram or code panel illustrating this step.

**Narration:** Show the canonical stacked checkpoint being encoded and hashed. Explain SHA-256 as a content digest, not as a publisher signature.

### 02:00–03:00

**On screen:** A simple diagram or code panel illustrating this step.

**Narration:** Demonstrate how a session records the checkpoint identity, prompt, policy and seed. Training during an active session makes that identity stale.

### 03:00–04:15

**On screen:** A simple diagram or code panel illustrating this step.

**Narration:** Use six synthetic token IDs as a claimed completion. Re-run the same inference path and compare every token ID, then explain how one mismatch rejects the report.

### 04:15–05:00

**On screen:** A simple diagram or code panel illustrating this step.

**Narration:** Separate reproducibility, authentication, data rights and release permission into distinct concepts. None is interchangeable.

## Demonstration and review

Show the corresponding API declaration under
`framework/include/umicom/ai/training/` and, where useful, the focused
regression test under `framework/tests/ai_training/`. The demonstration
should report only synthetic numbers and aggregated validation results.
Avoid recording personal paths, credentials, customer documents, private
messages or real banking information. Distinguish an educational model
result from a production release decision.

**Review question:** Which Framework service owns the result's core
mathematics, and which component merely displays or summarises it?

**Teaching answer:** The existing decoder, sampler, tokeniser and
training-tape components own mathematics and trained state; the application
owns user interaction and obtains results through their public interfaces.
