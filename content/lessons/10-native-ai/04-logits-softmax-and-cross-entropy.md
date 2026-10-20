# Lesson 04 — Logits, Softmax and Cross-Entropy

**Bits to Banking · Build Your Own LLM from Scratch**  
**Sammy Hegab · Umicom Foundation**  
**Level:** introductory mathematics · **Implementation:** `UmiAiTrainingCrossEntropy` in the new C23 training tape.

## How a model expresses a prediction

A language model normally outputs one **logit** per vocabulary entry. A logit is a score, not a percentage. To obtain probabilities, apply the **softmax** function:

`p(i) = exp(z(i)) / sum(exp(z(j)))`.

Here `z(i)` is the logit for candidate `i`, and the sum covers all candidates. The probabilities are nonnegative and add to one. The model's expected next token is one of those candidates; during training we compare its probability with the known next token in the source sequence.

## Work through a three-token prediction

Assume the model considers `umicom`, `framework` and `trains`, with logits `[0, 0, 0]`. Their exponential values are all `1`, so the probability of each is `1/3`. If the correct next token is `framework`, its cross-entropy loss is:

`loss = -ln(1/3) = ln(3) ≈ 1.098612`.

This is exactly the initial loss expected by our three-token C23 demonstration, which starts with a zero-initialised `3 × 3` weight matrix. The demonstration uses zero weights because a single linear bigram layer can learn from them; later multilayer neural networks require an appropriate symmetry-breaking initialisation strategy.

After repeated gradient-based updates, the logit for the correct successor becomes larger than the others and the loss falls. For the deliberately repetitive three-token training corpus, the measured loss in the reference experiment falls from about `1.098612` to about `0.008442` over 350 updates. That demonstrates that parameters changed in the expected direction on this training corpus. It does not prove general language ability.

## Why naive exponentiation is dangerous

Computers store numbers in finite floating-point formats. Computing `exp(1000)` is likely to overflow. Yet the probability corresponding to logits `[1000, 999, 998]` can be calculated safely. Subtract the largest logit from every logit before exponentiation:

`softmax(z(i)) = exp(z(i) - max(z)) / sum(exp(z(j) - max(z)))`.

Subtracting the same constant from every logit does not change the final probabilities, because the common scaling factor cancels. The corresponding stable cross-entropy uses **log-sum-exp**:

`loss = max(z) + ln(sum(exp(z(j) - max(z)))) - z(target)`.

The C23 training operator uses this expression without materialising a separate probability tensor. Its implementation is in:

```text
framework/src/ai/training/tape.c
```

Read `UmiAiTrainingCrossEntropy` and find the three terms in the expression. Then inspect the backward branch of `BackwardNode` for the derivative:

`d(loss)/d(z(i)) = p(i) - 1 if i is the target, otherwise p(i)`.

The implementation also divides by the number of rows when returning the **mean** batch loss, so its derivatives are averaged across examples.

## Verify the mathematics using a native test

The following test records three zero logits and asks for the gradient when class 2 is correct:

```c
const float logitsValues[] = {0.0F, 0.0F, 0.0F};
const size_t classes[] = {2U};
```

The expected gradient is approximately:

```text
[ 0.333333, 0.333333, -0.666667 ]
```

Why is the third value negative? Gradient descent subtracts a positive learning rate times the gradient, so it **increases** the target logit while reducing the other logits. This is a concrete example of learning through calculus rather than merely counting adjacent words.

After merging the batch, run:

```powershell
Set-Location 'C:\umicom\Umicom-Applications'
cmake -S '.\framework\learning\native-llm' -B '.\build\native-llm-lesson' -G Ninja -DBUILD_TESTING=ON
cmake --build '.\build\native-llm-lesson' --parallel 2
ctest --test-dir '.\build\native-llm-lesson' --output-on-failure
```

This is a dedicated learning build. It uses the canonical `umicom/base/status.h` already present in your complete Framework checkout. There is no need for an external inference server, Python runtime or pretrained model file.

## Limits and review

Cross-entropy is only the **loss function**. It does not implement tokenisation, embeddings or a transformer. The operator accepts a finite `B × V` float matrix and an array of `B` target class indices. It rejects invalid shapes and class indices; the gradient tape is responsible for returning parameter derivatives.

Explain why these facts are distinct: (a) an operator is mathematically correct, (b) training loss decreases, and (c) a model generalises to unseen code. Only (a) and the toy demonstration of (b) are tested in this batch.

**Next:** [Lesson 05 — Tensor shapes and ownership](05-tensor-shapes-and-ownership.md).
