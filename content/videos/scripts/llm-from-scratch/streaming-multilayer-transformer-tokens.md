# Video teaching script — Streaming a multi-layer Transformer, one token at a time

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Format:** English narration with a screen-recorded C23 demonstration and simple diagrams.

## Intended learning outcome

Learners should understand the numerical contract and the Framework's
ownership boundaries without needing an external AI provider or access to
any private training data. Use invented token IDs and local synthetic model
configurations in every scene.

## Storyboard and narration

### 00:00–00:50

**On screen:** A simple diagram or code panel illustrating this step.

**Narration:** Show an incoming prompt and three stacked Transformer blocks. Explain that streaming determines when output is delivered, not whether attention is cached.

### 00:50–01:50

**On screen:** A simple diagram or code panel illustrating this step.

**Narration:** Draw a four-position BOS-left-padded context. Show token IDs 109 and 114 on the right; highlight that the current model uses learned absolute positions.

### 01:50–02:50

**On screen:** A simple diagram or code panel illustrating this step.

**Narration:** Animate logits from the last position into the existing Framework top-K/top-p sampler. Explain how a seeded choice becomes one returned token ID.

### 02:50–03:45

**On screen:** A simple diagram or code panel illustrating this step.

**Narration:** Shift the context left and append the sampled token. Re-evaluate every Transformer layer; explicitly note that the current stacked model has no KV speedup.

### 03:45–04:30

**On screen:** A simple diagram or code panel illustrating this step.

**Narration:** Display the native C23 Create–Next–Inspect–Destroy ownership sequence. End with a reminder that generated source is not executed and output may be binary.

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
