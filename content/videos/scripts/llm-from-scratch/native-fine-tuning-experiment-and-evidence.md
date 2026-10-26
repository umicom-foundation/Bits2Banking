# Video lesson — Run and Evaluate a Native C23 Fine-Tuning Experiment

**Umicom Foundation · Bits to Banking · Sammy Hegab**  
**Format:** Teaching narration and storyboard. This is a script, not a recorded video.

## Teaching goal

Explain a complete but **bounded** native experiment: reviewed source data, deterministic epoch order, frozen decoder, trainable low-rank projections, held-out cross-entropy, top-1 accuracy, and an unsigned experiment receipt. Never imply that the classroom model is ready for regulated financial operations.

## Scene 1 — What actually changes? (0:00–1:15)

**Visual:** A Transformer block with frozen weights in neutral colour and small query/value adapter matrices in accent colour. The base checkpoint remains locked as the adapter values move.

**Narration:** “The model already has many numerical parameters. This experiment freezes the established decoder and trains small low-rank corrections to selected projections. Umicom Framework owns the tensor tape, attention, optimiser and loss. We are not writing a second Transformer in the teaching repository.”

## Scene 2 — A deterministic epoch (1:15–2:40)

**Visual:** Four fictional examples in shuffled order `C, A, D, B`. Highlight each once, then display a new valid order for the next epoch. Keep two held-out examples in a separate area, never connected to the update arrow.

**Narration:** “An epoch visits each approved training example once. A seeded Framework RNG makes the order reproducible. The held-out set is used only to ask how the current model predicts targets it did not train on.”

**Worked calculation:** `4 training examples × 3 completed epochs = 12 SGD updates`.

## Scene 3 — Two different losses (2:40–4:05)

**Visual:** A short answer contributes two selected targets with mean loss `0.4`. A longer answer contributes six with mean loss `1.2`. Animate the calculation `(2×0.4+6×1.2)/(2+6)=1.0`.

**Narration:** “Do not average example means blindly when reporting loss per supervised token. The correct denominator counts selected answer targets. That is distinct from prompt and padding token positions.”

**Visual second panel:** Three of five correct next-token predictions, top-1 accuracy `60%`. Show that accuracy and perplexity are different measurements.

## Scene 4 — Run the real native service (4:05–5:30)

**Visual:** Show the compact C23 call:

```c
UmiAiTrainingSupervisedExperimentReport report = {0};
UmiStatus status = UmiAiTrainingSupervisedExperimentRun(
    adapter, dataset, &plan, &report);
```

**Narration:** “After the model has been created and the dataset audited, the runner composes the existing Framework services. It reports held-out results before and after training, checks optimiser-step identity and publishes a completed run report.”

## Scene 5 — What does the receipt certify? (5:30–6:35)

**Visual:** A 208-byte portable record labelled: dataset digest, frozen-model digest, steps, loss, accuracy, SHA-256 trailer. Next to it, two crossed-out labels: “NOT MODEL WEIGHTS” and “NOT DIGITAL SIGNATURE”.

**Narration:** “A portable receipt lets us detect changed evidence and compare the exact input/model identities. It cannot reload adapter weights. A digest is not a trusted publisher signature. Resumable training requires a separate adapter and optimiser checkpoint.”

## Scene 6 — A controlled failure (6:35–7:30)

**Visual:** A ten-step planned run; seven updates succeed and the eighth fails. The report remains unpublished, but the adapter's step counter reads seven.

**Narration:** “A failed training run does not reverse successful earlier updates. That distinction matters before claiming an experiment is atomic or resumable.”

**End-of-lesson questions:** “Where does the tokenizer live?” “What does a held-out loss measure?” “Why can the model change even when the report output is untouched?”

**Related manuscripts:** [Deterministic training epochs](../../../lessons/10-native-ai/train-with-deterministic-epochs.md), [held-out metrics](../../../lessons/10-native-ai/measure-held-out-token-loss-and-accuracy.md), and [checkpoint limits](../../../lessons/10-native-ai/understand-training-failures-and-resume-limits.md).
