# Lesson 16 — Train an Umicom Decoder on C23 Source Code

**Bits to Banking · Build Your Own LLM from Scratch**  
**Author:** Sammy Hegab · Umicom Foundation  
**Implementation:** Umicom Framework, C23 · **Batch:** Native AI 06

## What you will build

In Lessons 01–15 and their supplements, we learned how text becomes tokens, how a transformer processes those tokens, and how gradients update its parameters. We also built the reusable Umicom decoder in the Framework. Until now, the decoder's training inputs were prepared arrays rather than source-code documents selected by a learner.

This lesson takes a concrete next step: **train the existing native decoder on small C23 files**, hold out a separate source file for evaluation, and record precisely what the experiment proves. The model's parameters begin as numbers generated from a fixed seed; no pretrained weights are loaded. It is not yet a useful programming assistant. The goal is to understand the *complete data-to-training loop* and its limitations.

The Framework remains the owner of training mathematics. The executable in `framework/learning/native-llm/train_source.c` is a thin teaching client of the same public services used elsewhere.

## 1. Three distinct questions

Suppose the training dataset contains part of a fictional banking application:

```c
bool UmiLearningAccountCredit(UmiLearningAccount *account, int64_t amount)
{
    if (account == 0 || amount < 0) return false;
    account->minorUnits += amount;
    return true;
}
```

We can ask three different questions.

**Can the model improve predictions on passages from its training files?** We measure this with *training loss*. A model can improve by memorising tokens and frequent substrings.

**Can the model make better predictions on a different file it has never trained on?** We measure this with *held-out evaluation loss*. That is a useful but incomplete measure of generalisation. Code repositories frequently contain boilerplate, copies and near-duplicates, which can leak information across a naïve split.

**Can the model correctly implement a banking application?** Neither of these loss numbers answers that question. Producing syntactically valid C23, satisfying Framework contracts, running tests and preserving security boundaries require separate evaluations.

## 2. Why entire files are assigned to each partition

A *partition* is a group of data used for one purpose. This experiment has two: `train` and `eval`.

The manifest shipped with the lesson identifies them explicitly:

```text
UMICOM-AI-DATASET-1
train train/account.c
train train/notes.c
eval eval/payment.c
```

All three files are self-contained, small educational C23 source files. The training files describe an account and a Notes record. The evaluation file describes a fictional payment. They do **not** contain real account details or financial records.

Why not divide a single source file into random overlapping 8-byte windows and send some to each partition? Two neighbouring windows could share seven out of eight input bytes. A model that memorises one window could look unexpectedly good on the other, even if it learned little that transfers to different programs.

**File-level partitioning** ensures that a particular file is loaded into one partition only. The loader also refuses repeated relative paths and simple identical-file fingerprints. This does not detect semantic duplicates, copied code blocks or related files: a real evaluation corpus needs a human review and stronger similarity checks.

## 3. Who owns the source bytes?

The C23 `UmiAiTrainingDatasetLoadManifest` service parses a trusted, explicitly selected manifest. It delegates each file read to the existing `UmiAiCorpusLoadFile`, which copies the bytes into Framework-owned storage.

```
Reviewed manifest
     |
     v
Framework dataset loader
     |-- training/account.c  -> immutable corpus
     |-- training/notes.c    -> immutable corpus
     `-- evaluation/payment.c -> immutable corpus
     |
     v
Seeded batch sampler
     |
     v
UmiAiTrainingDecoderTrainStep / Evaluate
```

The caller owns the dataset handle and must destroy it. Each source has copied metadata: partition, relative path, byte count and a reproducible FNV-1a64 fingerprint. That fingerprint detects some accidental changes, **not** deliberate tampering; it cannot authenticate a source file.

The path checks reject obvious `../` components. They do not constitute a filesystem sandbox: symlinks, junctions and file races are outside the trust boundary of this small educational loader. Only use reviewed local source manifests, and never train on private client files or proprietary Calypso SDKs without authorisation.

## 4. From source bytes to a training window

The existing Umicom byte tokenizer reserves IDs `0–3`. A byte with numerical value `b` becomes token `b + 4`, yielding **260 possible token IDs**.

For example, the first three characters in `int` have these byte/token values:

| Character | ASCII byte | Umicom token |
|---|---:|---:|
| `i` | 105 | 109 |
| `n` | 110 | 114 |
| `t` | 116 | 120 |

Training one next-token window uses a length-`C` input sequence and a length-`C` target sequence shifted one byte forward.

For the source bytes `int value`, using a window of 4 bytes from the beginning:

```text
Input bytes:   i  n  t  <space>
Target bytes:  n  t  <space> v
```

At every position the model predicts the **next** byte. Each training/evaluation sample remains inside one original file; samples never silently cross into another file.

The Batch 06 sampler chooses from *all valid windows in the specified partition*. It uses the Framework's existing seeded random service. An unbiased integer index avoids floating-point rounding when choosing a file/window. A fixed dataset, seed and batch number produce reproducible selections.

The teaching contract permits 1–32 context tokens and 1–4 sequences per requested batch. Additional limits apply at the decoder and tensor layer. The default experiment uses **eight tokens and one sequence per optimisation step**.

## 5. Why the decoder vocabulary limit changes

Earlier decoder demonstrations used tiny hand-written vocabularies. The byte tokenizer needs token IDs up to 259, so a 64-token decoder cannot accept its outputs.

Batch 06 extends the public maximum vocabulary from 64 to 260 while retaining the existing decoder implementation and checkpoint format. This is a bounded limit, not a performance claim. Since the tape permits at most 4096 elements per tensor, large vocabulary and channel combinations may still be refused. The teaching configuration uses:

```text
Vocabulary:          260 tokens
Context:               8 tokens
Channels:              8
Feed-forward channels: 16
Attention heads:       2
Initial seed:       20261021
```

This is a very small model intended for mathematical inspection. It will not understand the meaning of `int64_t`, payment validation or the Umicom architecture after a few dozen tiny training examples.

## 6. Build and test the real Framework implementation

Open PowerShell in the root of your Umicom Applications checkout:

```powershell
Set-Location "C:\umicom\Umicom-Applications"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"

cmake -S ".\framework\learning\native-llm" `
    -B ".\build\windows-ucrt64-native-llm-debug" `
    -G Ninja -DBUILD_TESTING=ON -DCMAKE_BUILD_TYPE=Debug

cmake --build ".\build\windows-ucrt64-native-llm-debug" --parallel 2

ctest --test-dir ".\build\windows-ucrt64-native-llm-debug" `
    --output-on-failure --no-tests=error
```

This project builds the **actual Framework C23 sources**, not a second independent model inside Bits2Banking. The Batch 06 baseline registers 33 tests in this isolated learning build.

## 7. Train a source-code model from random weights

Use the supplied, independently reviewed, fictional source fixtures:

```powershell
Set-Location "C:\umicom\Umicom-Applications"

& ".\build\windows-ucrt64-native-llm-debug\umicom-native-llm-source-train.exe" `
    ".\framework\learning\native-llm\fixtures\manifest.txt" 64
```

The trainer prints the number of training/evaluation files, byte counts and fingerprints, then evaluates the **held-out file before any weight update**. It performs 64 train-only optimiser steps using the already-implemented decoder and reports held-out loss again. The program does not open a network connection or create output files by default.

In a tested GCC 14.2 Linux run on these fixtures, held-out loss went from approximately **5.569312** to **5.484966**. Your compiler, floating-point environment and local dataset will determine the observed results. This single number does not establish statistical significance or expert programming ability.

The initial held-out loss is close to `ln(260)` ≈ 5.561: a roughly uniform prediction over 260 possible tokens assigns little probability to the correct byte. A small decline after training means the parameters have changed in a direction that helped these particular sampled evaluation windows. It does not prove code generation quality.

## 8. Review and save a new checkpoint only when requested

The Batch 04 checkpoint API is already responsible for model persistence; Batch 06 does not create a competing format. If you want a checkpoint, supply a **new, nonexistent output filename**:

```powershell
& ".\build\windows-ucrt64-native-llm-debug\umicom-native-llm-source-train.exe" `
    ".\framework\learning\native-llm\fixtures\manifest.txt" 64 `
    "C:\umicom\_local\native-ai\source-model.umi"
```

Create the destination directory separately before this command. The checkpoint saver refuses to overwrite an existing file. Model files and arbitrary source corpora belong outside Git unless explicitly reviewed and approved for publication.

The checkpoint is a reproducible binary snapshot with an accidental-corruption check, **not** a signed or trusted model distribution package. Do not load model files from untrusted sources.

## 9. Tests and independent evidence

The Batch 06 regression suite adds three focused cases:

| Test | Engineering question |
|---|---|
| `framework.ai.training.manifest` | Are splits immutable, source fingerprints copied, sampling reproducible and capacity failures nonmutating? |
| `framework.ai.training.manifest_rejections` | Are invalid paths, duplicate entries, repeated bytes and missing evaluation groups refused? |
| `framework.ai.training.source_model` | Can the existing decoder train with all 260 byte tokens, keep evaluation read-only and survive checkpoint round-trip? |

These tests are run with ordinary compiler diagnostics and also under sanitizers where available. The complete Umicom Applications build must still be qualified independently after merging the Framework files.

## 10. Exercises and questions

**Exercise A — Inspect provenance.** Run the trainer, note the byte counts and fingerprints, and explain which fields would change if a source file changed.

**Exercise B — Adjust the sampling seed.** In a separate experiment, change the seed passed to `UmiAiTrainingDatasetBatch` in the teaching executable. Explain why the model may receive a different sequence of windows even when its own initialisation seed remains unchanged.

**Exercise C — Predict overfitting.** Train for 128 steps rather than 64 and compare held-out loss. Do not assume improvement; document the actual figures.

**Review questions:** Why do two adjacent windows from the same file make a poor train/evaluation split? Why does the saved FNV fingerprint not prove authenticity? Why does a model with falling cross-entropy still require an independent C23 compiler and Framework tests before its generated code can be trusted?

## What comes next

We now have a native, source-aware training loop, but its dataset and parameter count are deliberately small. Subsequent lessons will address safe streaming of larger corpora, tokeniser improvements, optimisers, independent evaluation and finally the specialist models. Before calling anything an **Umicom C Expert**, we must measure its performance on previously unseen programming tasks with independently verified answers.
