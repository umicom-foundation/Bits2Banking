# Supplement 16B — Reproducible Native Training Experiments in C23

**Bits to Banking · Build Your Own LLM from Scratch · Umicom Foundation**  
**Author and project originator:** Sammy Hegab  
**Implementation:** Umicom Framework, native C23  
**Prerequisites:** Lessons 09–16 and Supplement 16A; basic C structures and function calls.

## Learning objective

Create an experiment whose model architecture, data selection, optimiser steps and evaluation measurements can be reviewed **before** it executes. Build and run the genuine Framework implementation, then reproduce a result with the same configuration and immutable source files.

This is an educational language-model experiment. It does not create a capable C23 programming assistant or demonstrate that the model understands software architecture. We use narrow measurements so each outcome is understandable and independently testable.

## 1. Why a training run needs a plan

Consider asking Umicom Studio to train its first C23 assistant. The instruction *"train on our C source"* leaves several crucial questions unanswered. Which files? Which are excluded from training? What model dimensions will be used? How many training steps? Which learning rate? How will results be compared?

Batch 06 made the source list explicit using a **dataset manifest**. Batch 07 adds a second reviewed input: the **experiment plan**. It fixes the model and training settings so that two experiments can be meaningfully compared.

The two inputs have different purposes:

| Input | Responsibility | Example |
| --- | --- | --- |
| Dataset manifest | Select whole authorised files for training or evaluation | `train train/account.c`, `eval eval/payment.c` |
| Experiment plan | Select model, seeds, learning rate, training steps and evaluation frequency | `steps=32`, `learning_rate=0.025` |

The Framework continues to own both contracts. Umicom LLM and other applications need only provide a suitable user interface and require approval before selecting datasets or writing checkpoints.

## 2. Inspect a complete plan

Open `C:\umicom\Umicom-Applications\framework\learning\native-llm\fixtures\experiment.conf`. The file contains:

```text
UMICOM-AI-EXPERIMENT-1
manifest=manifest.txt
steps=32
eval_interval=8
eval_batches=4
batch_sequences=1
learning_rate=0.025
model_seed=20261021
train_seed=4477
eval_seed=5544
context=8
channels=8
hidden_channels=16
attention_heads=2
```

The version marker enables future changes without silently reinterpreting old experiments. The manifest location is resolved **relative to this plan file**, not to the PowerShell working directory. The plan is intentionally plain data: it cannot run a shell command, include another file, interpolate an environment variable or inject application code.

The `model_seed` chooses the initial random weights. The `train_seed` chooses training windows from the authorised training files. The `eval_seed` chooses a **fixed, independent set of held-out windows**; the same held-out positions are measured before training and after each evaluation interval.

`batch_sequences=1` means one eight-token sequence is used in each gradient step. The current educational model has a 260-token vocabulary and a 4,096-element tensor limit. Two eight-token sequences would require 16 × 260 = **4,160 logit values**, exceeding that limit. The Framework rejects the configuration **before** training begins rather than truncating a tensor or pretending the larger batch succeeded.

## 3. Understand the native ownership boundaries

The authoritative Framework files are:

```text
framework/include/umicom/ai/training/experiment.h
framework/src/ai/training/experiment.c
framework/include/umicom/ai/training/experiment_plan.h
framework/src/ai/training/experiment_plan.c
```

The plan parser copies validated settings into a caller-owned `UmiAiTrainingExperimentConfig`. It does not keep a pointer to the text file. The dataset service owns an immutable corpus snapshot, and the decoder service owns its parameters and tensor tape.

`UmiAiTrainingExperimentRun` composes these services. It first constructs a randomly initialised decoder using the reviewed seed, measures the held-out baseline, and then repeats the native training step. A progress callback receives **copies** of the metrics, not internal model pointers.

When the run finishes successfully, the caller receives the owned trained decoder and must call `UmiAiTrainingDecoderDestroy`. If validation, evaluation or an observer fails, no incomplete decoder is published.

## 4. Build and run the actual experiment

These are interactive PowerShell commands for the Windows development environment, **not application implementation scripts**.

```powershell
Set-Location "C:\umicom\Umicom-Applications"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"

cmake -S ".\framework\learning\native-llm" `
      -B ".\build\windows-ucrt64-native-llm-debug" `
      -G Ninja `
      -DCMAKE_BUILD_TYPE=Debug `
      -DBUILD_TESTING=ON

cmake --build ".\build\windows-ucrt64-native-llm-debug" --parallel 2

ctest --test-dir ".\build\windows-ucrt64-native-llm-debug" `
      --output-on-failure --no-tests=error

& ".\build\windows-ucrt64-native-llm-debug\umicom-native-llm-experiment.exe" `
  ".\framework\learning\native-llm\fixtures\experiment.conf"
```

The printed dataset information includes the partition, relative path, byte count and FNV-1a fingerprint of each immutable source snapshot. **FNV-1a detects many accidental changes but is not a cryptographic authenticity proof.** Never import credentials, client material, proprietary SDK files or unapproved source.

## 5. Read the training metrics correctly

The Framework reports cross-entropy for fixed held-out samples, and their perplexity:

\[
\text{perplexity} = e^{\text{average cross-entropy}}
\]

For example, a held-out cross-entropy of approximately `5.5726` corresponds to a perplexity of about `263.1` when the vocabulary has 260 entries. This means the model is initially near the level of a uniform guess over the vocabulary. Training may lower that number for this very small corpus.

The label **"last train-batch CE"** refers to a single recent training batch. It is **not** the average cross-entropy across all training files. Likewise, four held-out windows provide only a limited snapshot, not full-corpus evidence of generalisation. The teacher should ask learners to distinguish these three notions: one training batch, fixed sampled held-out batches, and a completely separate task benchmark.

## 6. Perform a controlled experiment

Copy `experiment.conf` to a new, appropriately reviewed filename within the fixture folder. Change `steps=32` to `steps=16`. Leave the seeds, model dimensions and manifest unchanged. Run both plans and compare their final held-out cross-entropy.

Next, try `batch_sequences=2`. The Framework should report a capacity error rather than crash or silently reduce the batch. Restore the original configuration afterwards.

Finally, change `eval_seed` only. The resulting held-out measurements can change even when the training trajectory is identical, because a different fixed sample of evaluation windows is being measured. This illustrates **evaluation sampling uncertainty**.

## 7. Questions for review

1. Why are the dataset manifest and the experiment plan separate files?
2. What is the difference between `model_seed`, `train_seed` and `eval_seed`?
3. Why does a smaller held-out cross-entropy not prove that a model is an expert in C23?
4. Why must the Framework check `batchSequences × contextLength × vocabularySize` before allocating logits?
5. Why should the training engine run without requiring Umicom Studio or a GUI?

**Next:** [Supplement 16C — Reproducible checkpoint resume and scientific evidence](16c-resume-checkpoints-and-training-evidence.md).
