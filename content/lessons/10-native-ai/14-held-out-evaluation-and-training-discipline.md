# Lesson 14 — Train/Evaluation Splits and What a Falling Loss Really Means

**Bits to Banking · Build Your Own LLM from Scratch · Umicom Foundation**  
**Author:** Sammy Hegab  
**Implementation:** Umicom Framework C23, lessons 13–14  
**Prerequisites:** Lesson 13 and an understanding of cross-entropy.

## The engineering question

In Batch 03, a small Transformer Block drove training loss almost to zero on a few memorisable examples. That proved the gradient path and optimiser could change its weights. It did **not** prove that the model could answer an unfamiliar question.

For a software-engineering expert, this difference is decisive. A model that repeats the source it was trained on may look impressive, yet fail to analyse a new compiler error. We must therefore measure performance on **data withheld from parameter updates**.

## 1. An independently measured held-out set

The course now includes the Framework API:

```c
UmiStatus UmiAiTrainingSplitSequences(
    size_t sequenceCount,
    size_t evaluationCount,
    uint64_t seed,
    size_t *outOrder,
    size_t capacity);
```

It produces a deterministic permutation of **whole sequence indices**. The first `sequenceCount - evaluationCount` indices belong to the training set. The remainder belong to evaluation. The dataset stays caller-owned; the Framework only selects indices, avoiding duplicated storage and accidental mutation.

For twelve two-token examples, a split with three evaluation sequences creates nine training sequences and three held-out sequences. The shuffle is seeded, repeatable and checked for no overlap. It never breaks a sequence halfway through.

This is a basic partitioning service, **not** a guarantee that the original corpus contains no duplicates or near-duplicates. For repository-source datasets, splitting individual functions randomly may put near-identical copies from the same project in both groups. Use repository, project or time-based grouping when appropriate.

## 2. Training loss and evaluation loss are different measurements

For input tokens `x` and correct next-token targets `y`, the average cross-entropy is:

\[
 L(\theta)=-\frac{1}{N}\sum_{i=1}^{N} \log P_\theta(y_i \mid x_{\le i}).
\]

Here `\theta` denotes the model weights. During training, backpropagation calculates gradients of the loss with respect to `\theta`, and SGD updates those weights. During **evaluation**, the model calculates the same loss but must NOT call backward or update any parameter.

Our `UmiAiTrainingDecoderEvaluate` has exactly that contract. It returns a bounded, finite loss value and never advances the completed-step counter. After evaluation, temporary graph nodes are rewound so they cannot contaminate the next training step.

## 3. The first honest experiment

The Batch 04 executable contains twelve distinct two-token input sequences drawn from a tiny four-token vocabulary. Each input pair has a target pair, and three input combinations are held out. It is a deliberately tiny synthetic task, not a language benchmark.

An independently reproduced GCC 14.2 laboratory run on 21 October 2026 reported:

| Measurement | Before training | After 420 SGD updates |
|---|---:|---:|
| Training cross-entropy | 1.386273 | 0.590156 |
| Held-out cross-entropy | 1.415977 | 4.573408 |

**The model fit its training examples better but became much worse on the withheld combinations.** This is a useful educational outcome. It reveals overfitting or poor generalisation, not a defect we should conceal. Small training sets, little capacity, high learning rates and weak data coverage can all contribute. The present experiment does not isolate which factor dominates.

The correct conclusion is not *“the model has learned the Umicom architecture”*. It is that its native forward/backward pipeline can optimise a loss, while its ability to predict unseen combinations needs improvement.

## 4. How to run a controlled experiment

When changing a model, hold as much else constant as possible:

1. Fix the source dataset and approved licence/provenance.
2. Fix the split seed and keep evaluation examples out of gradient updates.
3. Record model seed, tensor shapes, learning rate and completed step count.
4. Measure initial training and evaluation loss.
5. Perform a documented number of updates, checking for non-finite values.
6. Measure both losses again without updating the model.
7. Save a checkpoint, reload it, and confirm identical predictions.
8. Repeat with one changed setting and compare evidence.

The Framework stores the **model seed and completed-step count** in the checkpoint introduced in Lesson 15. Full reproducibility also requires the corpus identity, ordering, per-run configuration and environment. Those are not magically guaranteed by the model checkpoint alone.

## 5. Interpret evaluation honestly

A lower training loss is a necessary, but not sufficient, sign of successful optimisation. A higher evaluation loss means the model performs worse on the withheld sample distribution. We should investigate whether the data are representative, whether the model memorises specific pairs, and whether the task requires more context or different inductive bias.

For our future C23 and Calypso expert models, we will need stronger evaluations, such as compiling unfamiliar programs, selecting the correct Framework API and diagnosing deliberately withheld defects. Merely repeating exact training text will not count as expertise.

## 6. Study the real implementation and tests

Open these files from the merged Framework repository:

```text
include/umicom/ai/training/dataset_split.h
src/ai/training/dataset_split.c
include/umicom/ai/training/decoder.h
src/ai/training/decoder.c
tests/ai_training/test_training_dataset_split.c
tests/ai_training/test_training_decoder_train.c
learning/native-llm/train_decoder.c
```

The split test checks reproducible permutations, one appearance of each original sequence and failure-atomic rejection of inadequate output capacity. The decoder test trains on nine sequences and verifies that training loss falls while held-out loss remains a separate observation.

### Independent exercises

**Experiment A — Change the model seed.** Keep the same train/evaluation split. Does the initial loss change? Does the evaluation loss always improve after training?

**Experiment B — Change the split seed.** Keep the model seed fixed. Record which combinations moved into evaluation. Why does changing the split prevent a like-for-like comparison?

**Experiment C — Identify leakage.** If two input sequences are identical but placed in different groups, would the evaluation truly measure unseen examples? What should a corpus curator do?

**Experiment D — Develop a stopping rule.** Track held-out loss after each 25 updates. Propose an early-stopping criterion that relies only on the evaluation set rather than the training set.

## What is still missing

This lab has a fixed input context and hand-labelled token IDs. It does not yet stream arbitrary documents, support subword tokenisation, pad/mask variable-length sequences, use AdamW, or optimise GPU batches. The result is an inspectable CPU baseline for those future developments.

Next: [Lesson 15 — Portable Checkpoints and Exact Resume](15-portable-checkpoints-and-recovery.md).
