# Video teaching script — Read held-out evidence before comparing models

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

**Narration:** Explain why held-out examples must not be used during training and why loss masks can select different numbers of targets.

### 00:50–01:50

**On screen:** A simple diagram or code panel illustrating this step.

**Narration:** Work through one target with loss 0.2 and three with mean 0.8. Show the correct combined loss 0.65 and contrast the incorrect simple average 0.5.

### 01:50–03:00

**On screen:** A simple diagram or code panel illustrating this step.

**Narration:** Show top-one accuracy as correct selected predictions divided by selected targets. Explain that ignored rows do not count.

### 03:00–04:00

**On screen:** A simple diagram or code panel illustrating this step.

**Narration:** Relate perplexity to the exponential of mean loss; use a natural-log example and note that tokenisation changes comparability.

### 04:00–05:00

**On screen:** A simple diagram or code panel illustrating this step.

**Narration:** Compare baseline and candidate under two explicit thresholds. A rejection is a valid comparison outcome, not a software crash.

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
