# Lesson 08 — Optimisers and Our First Native Training Run

**Bits to Banking · Build Your Own LLM from Scratch**  
**Sammy Hegab · Umicom Foundation**  
**Laboratory:** `framework/learning/native-llm/train_bigram.c`  
**Implementation:** SGD in C23; AdamW, checkpointing, reproducible PRNG and transformers remain later milestones.

## From a gradient to a new model

After the forward pass produces a loss and backpropagation produces gradients, an **optimiser** updates trainable parameters. Our initial optimiser is **stochastic gradient descent** (SGD). For a parameter `w`, gradient `g` and learning rate `α`:

`w_new = w_old - α * g`.

The learning rate determines how far an individual update moves. A rate that is too large can cause training to oscillate or diverge; an extremely small rate may require many updates. Our laboratory uses fixed learning rates to make the mechanics easy to inspect. It does not perform learning-rate scheduling.

`UmiAiTrainingSgdStep` operates only on original trainable leaf tensors. It verifies the learning rate is positive and finite and that backpropagation has produced gradients. It checks all proposed updated values before writing any parameter; a later overflowing element must not leave earlier parameters partially modified.

## A complete training iteration

This is the exact lifecycle used by the first native demonstration:

```text
1. Begin with a tape containing input examples and trainable parameters.
2. Calculate logits using matrix multiplication.
3. Compute categorical cross-entropy against known next tokens.
4. Run reverse-mode automatic differentiation.
5. Apply SGD to the parameter tensor.
6. Rewind derived nodes, preserving the original leaves.
7. Repeat from step 2 with the updated parameters.
```

The tape's `Rewind` method matters because keeping every intermediate tensor forever would steadily consume memory. The input and parameter leaves survive; the derived logits and loss are recreated each iteration. A new forward pass is required after weights have changed.

## Train the simplest possible next-token model

Our first data sequence is deliberately tiny:

```text
umicom framework trains
```

It contains three unique tokens and three predictable transitions. A one-hot input matrix selects a row from a `3 × 3` weight matrix. This is a simple **bigram neural language model**: it predicts the next token using only the immediately preceding token.

The weights start at zero. On the first pass, all next-token classes have probability `1/3`, and the mean cross-entropy is approximately `ln(3) = 1.098612`. SGD gradually changes the weights so that the known successor receives a higher score than the two other tokens.

### Build with PowerShell

Merge the delivered files into your existing `C:\umicom\Umicom-Applications` checkout first. Do not create another copy of the canonical Framework status header: the real repository already contains it.

```powershell
Set-Location 'C:\umicom\Umicom-Applications'

cmake -S '.\framework\learning\native-llm' `
      -B '.\build\native-llm-lesson' `
      -G Ninja `
      -DBUILD_TESTING=ON

cmake --build '.\build\native-llm-lesson' --parallel 2
ctest --test-dir '.\build\native-llm-lesson' --output-on-failure

& '.\build\native-llm-lesson\umicom-native-llm-train.exe'
```

The executable name above is for Windows. On Linux, omit `.exe`. Ensure that CMake, Ninja and a C23-capable compiler are available in your environment.

### Expected reference output

The laboratory was tested with GCC 14.2.0 and Clang 17.0.0 on Linux. The reference values below are produced by our deterministic test corpus and fixed update rule. Other floating-point implementations may differ slightly:

```text
epoch   1: cross-entropy 1.098612
epoch  50: cross-entropy 0.065872
epoch 100: cross-entropy 0.031204
epoch 200: cross-entropy 0.015052
epoch 350: cross-entropy 0.008442

Learned next-token predictions:
  umicom     -> framework
  framework  -> trains
  trains     -> umicom
```

A loss reduction indicates the weights changed to fit the **training examples**. It is not evidence of general language understanding, held-out performance or a transformer implementation.

## The second experiment: regression

The test `test_training_regression.c` uses a different supervised task: learning the relationship `y = 2x + 1` from four numerical examples. The model starts with inaccurate parameters, then learns a weight approaching `2` and a bias approaching `1`. This shows that the reusable tape is not tied to language data.

Compare the two experiments. Both call the same underlying tensor, forward, backward and SGD APIs. Only the graph and objective differ. That is why these operations belong in the Framework, while future LLM applications select datasets and model architectures.

## What about AdamW?

AdamW is a more sophisticated optimiser that keeps running estimates of gradients and squared gradients and handles weight decay separately. It is commonly used in transformer training. We have intentionally **not** implemented it in Batch 01. First, the learner should be able to trace a simple SGD update without additional hidden optimiser state. We can introduce AdamW with deterministic tests after validating the trainer's interfaces and checkpoint requirements.

## Review questions and extensions

1. Starting from `w=1.0`, `g=0.2`, and `α=0.1`, calculate the updated weight.
2. Why does the model need a new forward pass after updating its weights?
3. Why is a bigram model fundamentally different from a decoder-only transformer with causal attention?
4. Which independent results would we need before claiming a trained C Expert or Framework Expert is useful?
5. As an optional experiment, change the demo's learning rate to `0.1F`, rebuild, and compare the loss at epochs 50 and 350. Restore the original value after reviewing the output.

**Next research milestone:** token embeddings, seeded initialisation, causal attention, higher-rank tensors and a real trainable transformer block—implemented only after the current tests remain green.
