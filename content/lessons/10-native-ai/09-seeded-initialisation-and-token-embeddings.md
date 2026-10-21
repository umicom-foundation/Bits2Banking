# Lesson 09 — Seeded Initialisation and Token Embeddings in C23

**Bits to Banking · Build Your Own LLM from Scratch**  
**Author:** Sammy Hegab · Umicom Foundation  
**Framework implementation:** `include/umicom/ai/training/initialisation.h`, `src/ai/training/initialisation.c`, `include/umicom/ai/training/tape.h` and `src/ai/training/tape.c`  
**Repository:** `C:\umicom\Umicom-Applications\framework`

## Learning objectives

By the end of this lesson, the reader should be able to explain why neural-network parameters require an initial value, reproduce a seeded training run, distinguish a token identifier from its learned embedding, and calculate the gradient of an embedding table when a token occurs more than once.

**Prerequisites:** Lessons 03–08 (tokens, matrices, loss functions, backpropagation and SGD). This lesson **extends the same Framework-owned training tape**; it does not introduce another application-owned neural runtime.

## 1. Why random initialisation matters

The Batch 01 bigram example started with a small matrix filled with zeros. That is sufficient for illustrating logistic next-token prediction with an output layer, but using identical initial values for all hidden units of a deeper network can prevent those units from learning different representations. This problem is called **symmetry**: equal neurons may receive equal gradients and remain indistinguishable.

Trainable embedding rows and projection matrices therefore usually begin with varied, small parameters. A fixed **seed** makes this variation repeatable so the learner can distinguish a code change from a change caused solely by initial random values.

The new `UmiAiTrainingRandomState` keeps the pseudo-random generator state with its caller:

```c
UmiAiTrainingRandomState randomState;
float weights[16];

UmiStatus status = UmiAiTrainingRandomSeed(&randomState, UINT64_C(20261020));
if (status != UMI_STATUS_OK) return 1;  /* Inside main(). */
status = UmiAiTrainingRandomFillUniform(&randomState,
                                       -0.3F, 0.3F, weights, 16U);
```

This is executable source syntax from the actual Batch 02 public interface, not a separate teaching implementation. The program has no dependency on Python, global `rand()` state, an inference server or a remote model. The Framework implementation uses a SplitMix64-style sequence and converts its most significant 24 bits into uniform FP32 fractions. The generator is **not cryptographically secure**.

A second generator initialised with the same seed will produce the same sequence. That is useful for controlled experiments, but it does not guarantee bit-identical training results across all possible processors, math libraries or optimisation modes: later floating-point operations may differ slightly.

### Failure contract

A rejected range (`minimum >= maximum`), nonfinite bound, invalid pointer or excessive element count must leave the provided output and RNG state unchanged. The fill operation uses a temporary buffer and only publishes its values on success. `test_training_initialisation.c` checks those cases, including seed zero.

## 2. A token ID is not yet useful to a neural network

Our example vocabulary contains four tokens:

| Token ID | Symbol |
| ---: | --- |
| 0 | `framework` |
| 1 | `learns` |
| 2 | `calypso` |
| 3 | `C23` |

The token ID `2` is an index, not a measurement: it does not mean the concept *calypso* has twice the meaning of *learns*. A neural model needs a vector that can be **learned** from examples.

An **embedding table** is a matrix shaped `[vocabulary, channels]`. A table with four tokens and four channels has 16 trainable FP32 values. An embedding lookup selects a row for each token and produces a matrix shaped `[tokenCount, channels]`.

```text
Vocabulary matrix E (4 tokens x 2 channels):

Token 0  [ 0.10,  0.20 ]
Token 1  [-0.30,  0.40 ]
Token 2  [ 0.50, -0.10 ]
Token 3  [ 0.70,  0.20 ]

Input token IDs: [2, 1, 2]
Lookup result:   [[ 0.50, -0.10 ],
                  [-0.30,  0.40 ],
                  [ 0.50, -0.10 ]]
```

Notice that token `2` appears twice. Both occurrences select the **same parameter row**. That is how an embedding learns a shared representation for the same token in different positions.

## 3. Backpropagating into an embedding table

During the backward pass, a model may compute different gradients for the two occurrences of token `2`. Those gradients must be **added together** into the same embedding row, not overwritten by the most recent occurrence.

Suppose the two positions generate the gradients `[0.1, 0.2]` and `[0.4, -0.1]`. The embedding row for token `2` must receive:

```text
gradE[2] = [0.1, 0.2] + [0.4, -0.1]
         = [0.5, 0.1]
```

`UmiAiTrainingEmbeddingLookup` implements the forward gather and the reverse scatter-add. The token ID array is copied into the tape node; the caller may release its original array after a successful operation. The tape owns the resulting values and gradients. No gradient is calculated for the discrete token IDs themselves.

### Read the actual Framework APIs

| Public function | What it guarantees |
| --- | --- |
| `UmiAiTrainingRandomSeed` | Creates deterministic local pseudo-random state. |
| `UmiAiTrainingRandomFillUniform` | Populates finite initial values, or leaves outputs untouched on rejection. |
| `UmiAiTrainingTensorCreate` | Copies the embedding table into a tape-owned trainable leaf. |
| `UmiAiTrainingEmbeddingLookup` | Copies the IDs and gathers table rows into a derived tensor. |
| `UmiAiTrainingBackward` | Accumulates repeated-token gradients into table rows. |
| `UmiAiTrainingSgdStep` | Updates only a validated trainable leaf after backpropagation. |

A consumer never receives an internal writable pointer to the tape's parameter buffer.

## 4. Exercise using the real implementation

After merging Batch 02, build the Framework's educational target using PowerShell:

```powershell
Set-Location 'C:\umicom\Umicom-Applications'
$env:Path = 'C:\msys64\ucrt64\bin;' + $env:Path

cmake -S '.\framework\learning\native-llm' `
    -B '.\build\windows-ucrt64-native-llm-debug' `
    -G Ninja -DBUILD_TESTING=ON -DCMAKE_BUILD_TYPE=Debug
cmake --build '.\build\windows-ucrt64-native-llm-debug' --parallel 2
ctest --test-dir '.\build\windows-ucrt64-native-llm-debug' `
    -R 'framework.ai.training.(initialisation|embedding)' --output-on-failure
```

`test_training_embedding.c` independently checks the forward values and the accumulated row gradients. It does not merely assert that a function returns success.

**Try it yourself:** Calculate the gradient contribution when token `0` occurs three times. Explain why sharing the embedding row is different from storing three unrelated copies of its values. Then change only the seed in the standalone demonstration, rebuild, and compare its initial loss. Restore the reference seed to preserve reproducible examples.

## 5. What we have, and what is still missing

Batch 02 has a real, differentiable embedding lookup and reproducible initialisation. It does **not** yet have a tokenizer that converts arbitrary UTF-8 text to training IDs, positional embeddings, optimiser checkpointing, a complete transformer block or a capable coding assistant. Those require separate, testable milestones.

**Next:** [Lesson 10 — Causal Self-Attention and Context-Sensitive Training](10-causal-self-attention-and-context.md).
