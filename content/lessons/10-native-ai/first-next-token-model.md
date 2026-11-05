# LLM from Scratch: understand one next-token prediction

## Goal and prerequisites

You will turn three familiar words into numbered inputs, predict the next word
and understand what training changes. No machine-learning knowledge is assumed.
Read [Introduction to Computers](../../courses/learning-computer-architecture/index.html)
first if a program or saved file is unfamiliar. Later code-reading sections use
arrays and functions from [Learning C](../../courses/learning-c/index.html).

A **language model** predicts a continuation of text. An **LLM** is a large
language model. We begin with a tiny example; understanding it does not require
a large model, paid service or GPU. A GPU is a processor particularly suited
to performing many numerical operations in parallel. This first example runs
on the computer's ordinary processor, its CPU.

## 1. Choose an understandable task

Our vocabulary is a list of three tokens:

| Token identifier | Text |
| --- | --- |
| 0 | umicom |
| 1 | framework |
| 2 | trains |

A **token** is a unit the model works with. In this small example it is one
whole word. Other models may use parts of words or bytes. The identifier is a
label, not a statement that token 2 is worth twice token 1.

We use these six teaching pairs:

```text
input       expected next token
umicom      framework
framework   trains
trains      umicom
umicom      framework
framework   trains
trains      umicom
```

The return from `trains` to `umicom` is an intentional cycle in this artificial
exercise. It is not a claim about ordinary English. Two examples say that
`framework` follows `umicom`; no example says that either other token follows
it. Counting gives a simple reference prediction before any neural mathematics.

## 2. Represent one input as numbers

The implementation uses **one-hot** rows. Exactly one entry is 1 and the rest
are 0:

```text
umicom       -> [1, 0, 0]
framework    -> [0, 1, 0]
trains       -> [0, 0, 1]
```

A **matrix** is a rectangular table of numbers. Six input rows and three
columns form a 6-by-3 matrix. The model keeps a 3-by-3 matrix of **weights**,
numbers that training can change. Multiplication of a one-hot row by this
weight matrix selects the corresponding row of weights.

```text
[1, 0, 0] x [ row for umicom    ] -> three scores for what follows umicom
            [ row for framework ]
            [ row for trains    ]
```

The three scores are **logits**, not probabilities yet. A softmax calculation
turns them into positive probabilities whose sum is 1. Equal starting scores
give each token probability 1/3. A probability describes the model's prediction;
it does not prove the prediction is true.

## 3. Explain one training step

The **target** is the expected answer, such as identifier 1 after `umicom`.
**Loss** is a number measuring the prediction's error. The example uses
cross-entropy: a low probability for the target produces a larger loss.
For one row it is `-ln(target probability)`, where `ln` is the natural logarithm.
At probability 1/3 this is about 1.099; at probability 0.9 it is about 0.105.
You can follow the comparison without memorising the formula.

```text
inputs + weights -> scores -> loss compared with targets
                              |
                  backward: how does each weight affect loss?
                              |
                  update weights a small amount -> repeat
```

A **gradient** measures how a small change in a number changes loss. Stochastic
gradient descent, abbreviated **SGD**, changes weights in the direction expected
to reduce loss. A **learning rate** controls the size of each change. Training
updates weights; prediction using existing weights is **inference**. They are
different operations.

## 4. Find the real Umicom example

Open `Umicom-Applications/framework/learning/native-llm/train_bigram.c`.
Its public [source link](https://github.com/umicom-foundation/umicom-framework/blob/main/learning/native-llm/train_bigram.c)
provides the same entry point. Read in this order:

1. `vocabulary` contains the three words.
2. `oneHot[18]` holds six rows times three columns. Match each group of three
   numbers to the table above.
3. `targets[6]` contains `1, 2, 0, 1, 2, 0`, the expected identifier for each row.
4. `zeroWeights[9]` starts all nine weights at zero.
5. `UmiAiTrainingMatmul` computes scores. `UmiAiTrainingCrossEntropy` computes loss.
6. `UmiAiTrainingBackward` computes gradients and `UmiAiTrainingSgdStep` updates
   weights. The example's rate is 0.7.
7. `UmiAiTrainingTapeRewind(tape, 2U)` removes temporary calculation nodes while
   keeping the two original tensors. A **tensor** here is a numerical array;
   the tape owns its storage and records the calculation for differentiation.

The loop runs 350 **epochs**, repeated training passes over these six pairs.
The final loop chooses the largest score in each row and prints the next word.
This is a bigram model: each prediction uses one preceding token. It does not
have a Transformer's larger context or general conversation ability.

## 5. Exercise before running

What should follow identifier 2 in this corpus? Write your prediction.
**Answer:** identifier 0, `umicom`. Locate the corresponding entries in `targets`.

How many trainable weights are present? **Answer:** nine, from three inputs by
three possible next tokens. The 18 input numbers are training data, not weights.

Would low loss prove the model can answer a question about banking?
**Answer:** no. These six repeated pairs demonstrate a training mechanism;
they do not test knowledge or generalisation to unseen examples.

Continue with [Run and inspect the first training experiment](first-training-run.md).
The wider [LLM from Scratch course](../../courses/llm-from-scratch/index.html)
then develops tensors, gradients, attention and larger experiments in sequence.
