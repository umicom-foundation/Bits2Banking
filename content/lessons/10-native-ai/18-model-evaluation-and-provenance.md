# Lesson 18 — Evaluate Our Native Language Model and Preserve its Provenance

**Bits to Banking · Build Your Own LLM from Scratch**  
**Sammy Hegab · Umicom Foundation**  
**Implementation:** reusable Umicom Framework C23; thin native console consumer

## Learning objectives

After completing this lesson, you should be able to explain why a successful
training run is not evidence of useful language understanding, evaluate
next-token predictions on held-out documents, calculate accuracy and
perplexity, and distinguish an experiment fingerprint from a trustworthy
cryptographic signature. You will also build and execute the actual Umicom
Framework implementation and verify that the model was not trained during the
evaluation itself.

## 1. From generated examples to measurable behaviour

Our previous lesson showed the autoregressive loop: encode a prompt, obtain
logits, select a token, append it to the context and repeat. A generated string
can *look* like meaningful C code even when the model predicts most unseen
tokens incorrectly. Conversely, a small byte-level model might predict spaces
and punctuation reliably without understanding the program around them.

Consider this fictional source fragment:

```c
/* A simplified Umicom account model, not a real banking ledger. */
typedef struct Account {
    long balancePence;
} Account;
```

A model may learn that `typedef struct` is usually followed by an identifier
or opening brace. This is a pattern-learning achievement, but it says nothing
about checking monetary overflows, enforcing transaction atomicity or using
the correct Umicom Data Server repository contracts.

Our evaluation must therefore compare *predictions against known target
bytes* from entire source files which the trainer was not allowed to see.
We do not claim that those files were truly unseen by any outside model:
this is our own newly initialised native model, and its educational manifest
specifies which files are used for training and which are held out.

## 2. Define the predictions precisely

Each evaluation window contains input token IDs and their one-position-shifted
next-token targets. Suppose the input bytes are `int` and the target bytes
are `nt ` at the next positions. With the existing byte vocabulary, `i` is
encoded as ID `109` (byte value `105` plus reserved-token offset `4`). The
predicted next byte following that `i` should be `n`, ID `114`.

The decoder's output at a position is a vector of **260 logits**. A logit is a
raw score, not a probability. The Framework's existing cross-entropy operator
uses the log-sum-exp calculation rather than exponentiating raw large logits.

For a correct target index `y` and raw scores `z[j]`, the target
probability and cross-entropy are:

```text
P(y) = exp(z[y] - maximumLogit) / sum(exp(z[j] - maximumLogit))
L    = -ln(P(y))
```

Subtracting `maximumLogit` from every logit gives the same probabilities
while avoiding unnecessary exponential overflow.

If a model assigns the correct next token probability `0.5`, its loss on that
one prediction is about `0.6931`. If it assigns probability `0.01`, the loss
is approximately `4.6052`. The lower the average held-out cross-entropy,
the better the model's probabilistic next-token predictions *on that sample*.

For a mean cross-entropy `L`, perplexity is `exp(L)`. Perplexity is a
transformation of the same measurement, not an independent accuracy test.
Results are comparable only when vocabulary, target handling and evaluation
samples are consistent.

## 3. Top-1 and Top-5 accuracy

Besides loss, we can rank the model's token scores. **Top-1 accuracy** counts
how often the true next token has the highest score. **Top-5 accuracy** counts
how often the true token is among the five highest-scoring IDs. Ties favour
the lower token ID so that two machines can reproduce the same ranking.

Suppose an evaluation contains 100 token predictions. If the true token ranks
first 18 times and lies in the top five 42 times, the accuracies are **18%**
and **42%** respectively. Top-5 cannot be lower than Top-1 when both use the
same predictions, vocabulary and tie convention.

These metrics must not be confused with source-code compilation success,
security reviews or correct financial calculations. An expert system should
add task-specific held-out questions and run compiled tests before claiming
engineering competence.

## 4. Bind every measurement to its source

A reported loss is not reproducible unless we know which decoder parameters,
training plan and source files produced it. The new Framework
`UmiAiTrainingModelAudit` records four identifiers:

| Identifier | Source of the identifier |
| --- | --- |
| Model fingerprint | Canonical encoded checkpoint bytes, including parameter state and completed optimiser steps. |
| Dataset fingerprint | Ordered manifest document paths, file-level training/evaluation assignments, byte lengths and content fingerprints. |
| Plan fingerprint | Model architecture, learning rate, random seeds, step target and evaluation settings. |
| Combined fingerprint | The three identifiers and completed optimiser steps. |

The implementation computes FNV-1a64 fingerprints with explicit byte order.
This helps detect *accidental* changes, but it is **not** a cryptographic
signature. An attacker could forge an unkeyed fingerprint; never treat a
matching value as proof that an untrusted checkpoint or dataset is safe.

The Framework hashes an immutable in-memory dataset snapshot. If a source
file changes on disk, load its manifest again before checking identity.
A local path grammar is not an access-control system, particularly when
symbolic links can resolve elsewhere.

## 5. Inspect the actual Framework code

The authoritative public API is:

```text
Umicom-Applications/framework/include/umicom/ai/training/model_audit.h
```

Its implementation belongs to:

```text
Umicom-Applications/framework/src/ai/training/model_audit.c
```

The key call is:

```c
UmiStatus UmiAiTrainingModelAuditEvaluate(
    UmiAiTrainingDecoder *model,
    const UmiAiTrainingDataset *dataset,
    const UmiAiTrainingExperimentConfig *config,
    UmiAiTrainingModelAudit *outAudit);
```

`model` is owned by its caller and remains trained at exactly the same step
count. `dataset` is borrowed and immutable. The returned report is copied
into caller-owned memory only after **all** validation and evaluation succeed.

The service delegates loss to `UmiAiTrainingExperimentEvaluate` rather than
reimplementing cross-entropy. It delegates prediction to the existing
`UmiAiTrainingDecoderLogits` API and obtains held-out windows from the
existing `UmiAiTrainingDatasetBatch` service. This reuse is essential to
Umicom Framework's single-source-of-truth architecture.

## 6. Build and test the real C23 implementation

Open PowerShell on Windows and run:

```powershell
Set-Location "C:\umicom\Umicom-Applications"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"

cmake -S ".\framework\learning\native-llm" `
    -B ".\build\windows-ucrt64-native-llm-debug" -G Ninja `
    -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTING=ON

cmake --build ".\build\windows-ucrt64-native-llm-debug" --parallel 2

ctest --test-dir ".\build\windows-ucrt64-native-llm-debug" `
    --output-on-failure --no-tests=error
```

The relevant focused tests are `framework.ai.training.model_audit`,
`framework.ai.training.audit_changes` and
`framework.ai.training.audit_rejections`. They test deterministic measurements,
reloaded model equivalence, changed source partitions, modified optimiser
settings, changed weights, and failure-atomic outputs.

## 7. Audit a saved model

Use the previously established training experiment with a reviewed sample
plan. We explicitly choose a new checkpoint filename to avoid overwriting an
earlier result:

```powershell
New-Item -ItemType Directory -Force "C:\umicom\_local\models" | Out-Null

& ".\build\windows-ucrt64-native-llm-debug\umicom-native-llm-experiment.exe" `
    ".\framework\learning\native-llm\fixtures\experiment.conf" `
    "C:\umicom\_local\models\learning-decoder.umi"

& ".\build\windows-ucrt64-native-llm-debug\umicom-native-llm-audit.exe" `
    ".\framework\learning\native-llm\fixtures\experiment.conf" `
    "C:\umicom\_local\models\learning-decoder.umi"
```

The output reports cross-entropy, perplexity, Top-1 and Top-5 counts, model
steps and the exact combined fingerprint. Running the same model and plan
again should produce identical fingerprints and sample metrics in the same
native environment. Supply the printed fingerprint as the optional third
argument to verify an earlier reviewed identity. A mismatch returns a
nonzero exit code without modifying any files.

The current toy decoder is expected to score poorly. That is a useful
experimental result, not an excuse to claim it has become a professional
C23 programming assistant.

## 8. Research questions and exercises

1. Why is a visually convincing generated function not proof of correctness?
2. Explain why perplexity and cross-entropy describe the same sample with two different scales.
3. If a model predicts 12 target tokens correctly at Top-1 and 29 at Top-5 out of 100, what are the respective accuracies?
4. Without modifying model parameters, change only the evaluation seed in a copied plan. Why must the plan fingerprint change?
5. Reload the same checkpoint and confirm the model fingerprint remains unchanged. Explain how this differs from trusting an external, unsigned checkpoint.
6. Swap one source document between the training and evaluation splits in a reviewed copy of the manifest. Explain why the dataset fingerprint must change.
7. Describe a compiler-driven benchmark that would be more useful for assessing an eventual Umicom C Expert.

## Engineering limitations and next work

The present audit uses deterministic *sampled* held-out windows. It does not
scan every eligible window, perform semantic code evaluation or establish
model safety. Small samples can be noisy and can repeatedly select the same
window. File-level partitioning prevents a window from crossing the split,
but near-duplicate source files and shared template boilerplate still require
separate leakage reviews.

The inference service still computes a full context for every generated
token; no KV cache or streaming decoder is claimed here. The model's tensor
capacity and context length remain educational and bounded. We will need
measurable inference profiling, larger approved corpora, strong token and
task-level holdouts, and trustworthy signed model distribution before using
specialised models in sensitive financial workflows.
