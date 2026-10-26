# Video lesson — From Reviewed Sources to Native Training Windows

**Umicom Foundation · Bits to Banking · Sammy Hegab**  
**Format:** Teaching narration and storyboard. This is a script, not a recorded video.

## Teaching goal

A new learner should understand why a licensed source, an extracted text file, a reviewed prompt/completion example and a native training window are **four distinct things**. The learner should be able to explain how source identity prevents train/evaluation leakage.

## Scene 1 — Four doors, not one (0:00–1:10)

**Visual:** A clean, left-to-right diagram drawn from editable shapes: original document → reviewed extraction → admitted example → native token window. A separate red “NOT APPROVED” branch leaves the diagram before the admission door.

**Narration:** “A computer can read a file without having the right to use it for training. The original recording or document needs a known source, training permission, a privacy check and a reviewed text derivative. Umicom keeps these decisions separate so that passing a file parser is never mistaken for permission.”

**On-screen question:** “If a webpage is public, does that automatically permit training?” Reveal: “No.”

## Scene 2 — One fictional question and response (1:10–2:45)

**Visual:** Show the synthetic JSONL line:

```json
{"prompt":"Q","completion":"A"}
```

Animate the model token stream `[BOS, Q, A, EOS]` and an eight-position training window. Highlight only the response `A` and `EOS` targets; leave prompt and padding muted.

**Narration:** “The native tokenizer maps each byte to an ID using the established Framework vocabulary. A response-only loss mask tells the learning operation which next-token targets matter. Masking prompt targets does not prevent the model from reading the prompt as context.”

## Scene 3 — Keep related excerpts together (2:45–4:05)

**Visual:** One fictional book splits into three training questions. Draw all three under a common source-digest bracket, then point that bracket entirely to TRAIN or entirely to EVALUATE. Reject an arrow that divides it across both.

**Narration:** “A held-out evaluation is supposed to test generalisation. If we train on one part of a document and evaluate on another nearly identical part, the measurement can mislead us. The native reviewed-corpus audit checks exact duplicates and source groups. It does not magically find every paraphrase, so editorial review still matters.”

## Scene 4 — Inspect the Framework C23 API (4:05–5:30)

**Visual:** Show only the C23 declarations:

```c
UmiAiTrainingSupervisedDataset *dataset = NULL;
UmiStatus status = UmiAiTrainingSupervisedDatasetCreate(
    records, lengths, evidence, count, 8U, &dataset);
```

**Narration:** “The repository that teaches this course does not implement the JSON parser, tokenizer or data admission logic again. The Framework creates an immutable owned dataset only after the entire reviewed collection passes its checks.”

## Scene 5 — Verify learning (5:30–6:20)

**Visual:** A short recap of four gates: rights, privacy, integrity, partition. End with the next lesson link.

**Questions:** “What is the purpose of the mask?” “Why does a digest not prove ownership?” “Why must the whole collection be audited?”

**Closing narration:** “Trustworthy training begins with controlled sources, not larger neural networks. We will use these windows next to measure actual adapter training and held-out loss.”

**Related manuscripts:** [Training windows](../../../lessons/10-native-ai/from-approved-jsonl-to-training-windows.md) and [source auditing](../../../lessons/10-native-ai/audit-supervised-learning-datasets.md).
