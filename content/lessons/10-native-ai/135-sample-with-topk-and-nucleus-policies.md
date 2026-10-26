# Lesson 135 — Sample with native top-K and nucleus policies

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Topic:** Native C23 Transformers, inference and independent validation.

**Learning objective:** Learn how logits become reproducible decisions without inventing another sampler.

## 1. Understand the engineering problem

The decoder produces real-valued scores called logits. Their ordering identifies which IDs the model currently favours, but a score is not itself a probability. Umicom Framework already provides a temperature-aware top-K and top-p (nucleus) sampler. A stacked model needs to call that established owner instead of implementing a second softmax, random-number generator or selection rule in the application.

## 2. Follow a concrete example

Imagine candidate scores of 3, 2 and 1. At temperature one, softmax weights are approximately `0.665, 0.245, 0.090`. Top-K equal to two initially discards the third candidate. Within the remaining two candidates, top-p of 0.8 retains the smallest ranked prefix whose cumulative normalised mass reaches 0.8. The first candidate has mass around 0.731 after top-K filtering, so the nucleus includes both. Exactly which ID is sampled still depends on the seeded random draw.

## 3. Implement through the Framework

`UmiAiTrainingNucleusOptions` supplies `temperature`, `topK` and `topP`. Create a `UmiAiTrainingStackedGenerationSession` using one numeric seed and reuse the session for successive pulls. The existing `UmiAiTrainingSampleLogitsNucleus` receives the final-row logits and the allowed range `[4,vocabularySize)`. `topK=1` chooses the best allowed ID deterministically with no random draw; for larger choices the Framework RNG is advanced only after a successful selection.

## 4. Check the boundaries

Sampling deliberately excludes reserved PAD/BOS/EOS/UNK IDs 0–3, even though the model's raw logits include those positions and supervised loss may target EOS. Thus output does not stop automatically at EOS. A zero probability, a malformed temperature or a top-K limit outside the allowed range is a rejected configuration, not grounds for silently substituting a default policy. The chosen policy belongs in reproducibility evidence.

## Practice

**Question:** Can the same model and seed give a different stream when top-p changes?

<details>
<summary>Reveal the worked answer</summary>

Yes. Top-p changes the set of candidates before a random draw, so the selection distribution may change. Compare streams only when model checkpoint, prompt, seed and all sampler options match.

</details>

## Continue

[Return to the native stacked inference learning path](stacked-inference-learning-path.md). For the mathematical background, read the [stacked inference mathematics guide](../11-maths-for-ai/stacked-inference-mathematics.md). The canonical APIs are in `framework/include/umicom/ai/training/`; implementations and native tests remain in Umicom Framework, not in this educational repository.

*Service to Many Leads to Greatness.*
