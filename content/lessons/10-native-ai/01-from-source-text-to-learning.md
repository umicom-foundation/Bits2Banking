# Lesson 01 — From Source Text to Learned Predictions

**Bits to Banking · Build Your Own LLM from Scratch**  
**Sammy Hegab · Umicom Foundation**  
**Level:** introductory; no neural-network experience required  
**Implementation target:** Umicom Framework (C23); read-only audit in this lesson

## Why this lesson matters

The goal of this course is to build and train our own neural language model, not merely run a model trained by another organisation. We will eventually implement a transformer in C23, initialise all its weights ourselves, optimise them against training data, save the resulting model and load it into Umicom applications.

It helps to understand the complete process before examining the mathematics. Think of Umicom Studio IDE. When you type a question about the **Data Server**, the assistant must first convert your words into numeric tokens. The model then processes the token sequence and predicts a probability distribution over possible next tokens. During training, a loss function measures how far those predictions were from the known examples. An optimiser adjusts numerical parameters to make useful predictions more likely.

These operations are distinct from searching source files. Search or retrieval can supply up-to-date Framework evidence, but **retrieval does not train the model's weights**. The two techniques will eventually cooperate.

### Learning outcomes

By the end of the lesson, you should be able to explain:

- The distinction between a dataset, a token, a model parameter, a training step and an inference step.
- Why a next-token model produces probabilities rather than an infallible answer.
- How a numerical *loss* expresses the quality of one prediction.
- Why a small working transformer is a valid first research milestone even when its answers are not yet useful.
- Which Umicom repositories contain the educational material, reusable code and application workbench.

## 1. The model learns parameters, not files

Consider the sentence:

> The Umicom Data Server stores application records.

For a particular tokenizer, this sentence becomes an ordered sequence of numeric token identifiers. A real tokenizer might break words into multiple pieces. The exact identifiers depend on the vocabulary we train; this sentence does **not** have one universal tokenisation.

A transformer receives token identifiers and computes a prediction for the next token. The output is a vector of **logits**—one unnormalised score for each vocabulary entry. Converting these scores with *softmax* produces probabilities.

Before training, the parameters are random. The predicted probabilities are usually unhelpful. We evaluate the difference between a prediction and the expected next token, compute gradients and update the parameters. Repeating this over many examples is what allows patterns to emerge.

### A single training step

```text
A reviewed text corpus
         |
         v
    Token identifiers
         |
         v
  Transformer forward pass
         |
         v
  Next-token probability distribution
         |
         v
   Loss against the known target
         |
         v
  Backpropagation: compute gradients
         |
         v
  Optimiser: change model parameters
         |
         v
  Repeat with the next training batch
```

**Training** changes the parameters. **Inference** uses already-trained parameters to make a new prediction without changing them. The checkpoint file is the retained record of learned parameters and the training state needed for a reproducible restart.

## 2. A numerical example using Umicom terminology

Suppose the model has received the words:

> The Data Server

For the purpose of this exercise, imagine three candidate next tokens: **stores**, **validates** and **displays**. In a real model, the vocabulary would be much larger.

Assume the neural network produces these logits:

| Candidate next token | Logit | `exp(logit)` | Probability after softmax |
|---|---:|---:|---:|
| `stores` | 2.0 | 7.389 | approximately 0.665 |
| `validates` | 1.0 | 2.718 | approximately 0.245 |
| `displays` | 0.0 | 1.000 | approximately 0.090 |
| **Total** | | **11.107** | **1.000** |

Softmax divides each exponential score by the sum:

`P(stores) = exp(2) / (exp(2) + exp(1) + exp(0)) = 7.389 / 11.107 ≈ 0.665`.

If the recorded training target is `stores`, cross-entropy loss for this one next-token prediction is:

`loss = -ln(P(stores)) ≈ -ln(0.665) ≈ 0.408`.

A lower loss on correctly held-out examples means the model is assigning greater probability to the expected continuations. A low training loss by itself can also mean the model has memorised the training text. That is why we need independent evaluation data.

**Important:** these logits are made-up teaching values. They are not outputs measured from a trained Umicom transformer.

### Try the calculation yourself

1. Verify that the three probabilities add to approximately 1.
2. Imagine the correct token was `displays`. Compute `-ln(0.090)`; the result is approximately **2.408**, showing a much larger loss.
3. Explain why changing the target changes the loss even though the model's three logits have not changed.

## 3. From the earlier Umicom model to a transformer

*Bits to Banking, Volume 3I* introduces a genuine but limited **word-transition language model**. It counts adjacent-token transitions and uses those counts to generate text. It demonstrates corpus ingestion, model saving and inference in an inspectable way.

That teaching model should be retained as the simplest baseline. However, a word-transition count table is not the neural transformer we intend to build. It does not have trainable attention blocks and does not learn long-range dependencies through backpropagation.

Our next research goal is therefore **a small decoder-only transformer trained from randomly initialised weights**. We will not claim to have reached this milestone until the native implementation and its tests actually demonstrate it.

## 4. Where the real Umicom implementation belongs

Our source-of-truth arrangement is:

```text
Bits2Banking
  content/lessons/10-native-ai/    <- teaching materials

umicom-framework
  include/umicom/ai/               <- inspect existing contracts
  src/ai/                          <- inspect existing implementations
  tests/                            <- tests for shared native facilities

umicom-llm
  model and experiment profiles     <- proposed application-level organisation

umicom-llm-module
  existing LLM workbench/module     <- inspect before extending
```

The last two descriptions are responsibilities, not claims that all proposed subdirectories already exist. New source paths will be selected only after inspecting what the repository currently provides.

**Engineering rule:** C23 is the primary implementation language. Assembly is introduced only when relevant and justified. Keep training and inference reusable in Framework; do not create a second core trainer in Bits2Banking or a product application. Preserve existing functions, headers, comments, behaviours and historical implementations when extending the codebase.

## 5. Practical laboratory — establish a read-only baseline

This first laboratory changes no source files. It verifies the toolchain and lets us inspect the existing native AI code before deciding what must be built.

Open PowerShell and run:

```powershell
# Confirm that the essential native development tools are available.
git --version
cmake --version
ninja --version
& 'C:\msys64\ucrt64\bin\gcc.exe' --version
```

The example GCC path matches the project's Windows UCRT64 setup. If GCC is installed elsewhere, use its actual path; do not replace a failed command with an assumed successful result.

If your existing consolidated checkout is at `C:\umicom\Umicom-Applications`, inspect it:

```powershell
Set-Location 'C:\umicom\Umicom-Applications'
git status --short
git submodule status --recursive

Set-Location 'C:\umicom\Umicom-Applications\framework'
git status --short
git log -1 --oneline
Get-ChildItem '.\include\umicom\ai' -File | Select-Object Name
Get-ChildItem '.\src\ai' -File | Select-Object Name
```

Record the Framework commit identifier and look for existing model, dataset, retrieval, evaluation, provider and runtime contracts. Do not assume a name proves a complete training engine exists: read its implementation and associated tests.

The existing Framework architectural direction can be found in `templates/workspace/docs/adr/ADR-0006-native-local-llm.md`. It accepts native training and inference as a goal but does not represent the production trainer as complete.

### Expected observations

- The version commands print the real installed tools, or an error that identifies a missing dependency.
- The Git commands report the real checkout state; they do not change it.
- The AI directory listings show the files actually present in your checkout.
- The resulting audit records **implemented**, **partial**, **proposed** or **missing** for each training capability, together with a source path and supporting test evidence.

Do not continue by introducing new tensor or trainer implementations until we have inspected the available Framework facilities. This prevents duplication and keeps the subsequent lessons connected to the maintained source tree.

## 6. First engineering decision: define a measurable model

The first target is intentionally modest: a decoder-only transformer with about 4–5 million parameters. One candidate design uses four layers, four attention heads, 256 hidden dimensions, a 4,096-token vocabulary and a 256-token context. Its parameter count depends on choices such as embedding weight tying and bias handling.

The **first successful training milestone** must demonstrate all of the following:

- The model starts from random, reproducible parameters.
- A native forward pass computes valid logits and cross-entropy loss.
- Backpropagation produces verified gradients and an optimiser changes the weights.
- At least one appropriate training dataset produces a measurable learning signal.
- The trainer saves a valid checkpoint, reloads it and reproduces inference outputs under controlled settings.
- Tests cover invalid shapes, out-of-range tokens, corrupt checkpoints and non-finite calculations.

A compelling demonstration is not necessarily a conversational assistant yet. A verified end-to-end training run is a real engineering achievement in its own right.

## 7. Review and assessment

Answer these questions before continuing:

1. What exactly changes during training? What stays fixed during inference?
2. Why do we need an evaluation set that does not overlap our training examples?
3. What is the difference between using retrieved source code and training the model on source code?
4. Why would the current Umicom C Expert still need to retrieve the latest Framework headers even after specialised training?
5. What tests would establish that our small network genuinely performs backpropagation rather than merely counting token transitions?

**Completion criterion:** you can explain one training step using the Data Server example, reproduce the numerical loss, and produce a read-only inventory of the real Framework AI source. No claims are made that a production native transformer trainer has already been delivered.

## What comes next

**Lesson 02 — Training Data, Ownership and Evaluation Splits** will build a small, reviewed corpus and establish a reproducible source manifest. We will distinguish clean instructional material, current Umicom source, historical implementations and licensed Calypso material before training on any of them.

Once the source audit is complete, the later tensor and neural-network lessons will implement full, tested native C23 components in Umicom Framework rather than maintaining educational duplicates.

## Further reading

- *Bits to Banking Volume 3H — External Connectivity, IBKR Adapter and Local AI Runtime*.
- *Bits to Banking Volume 3I — Building a Small Language Model and Native AI Inference Engine*.
- Umicom Framework `templates/workspace/docs/adr/ADR-0006-native-local-llm.md`.
- Umicom Framework `include/umicom/ai/ai.h` and corresponding `src/ai/` implementations.
