# Mathematics for AI — Unit 16: Tensor Shapes and Indexing

**Bits to Banking · Umicom Foundation · Sammy Hegab**

## Objective

Translate a table of numbers into a tensor shape, locate values in row-major memory, calculate storage requirements and decide whether a tensor can be divided into equal attention heads.

## 1. Think of a familiar table

Suppose a teaching dashboard shows three fictional accounts. Each has four numerical attributes: balance, forecast, alert score and transfer count.

| Row | Balance | Forecast | Alert | Transfers |
|---|---:|---:|---:|---:|
| 0 | 100 | 120 | 0.1 | 2 |
| 1 | 80 | 75 | 0.2 | 1 |
| 2 | 40 | 60 | 0.5 | 4 |

The table has **three rows and four columns**. Its shape is `[3, 4]`. A two-dimensional tensor represents the same arrangement in numerical software; higher-dimensional tensors add further axes.

## 2. Calculate the element count and storage

`elementCount = rows × columns = 3 × 4 = 12`

If each element occupies four bytes of float32 storage, the raw values occupy `12 × 4 = 48` bytes. Gradients, metadata, allocator overhead and other graph nodes are separate costs. Do not describe 48 bytes as the memory consumption of a whole training run.

For very large inputs, production implementations must check integer multiplication for overflow *before* allocating. The Framework performs shape and capacity checks in its canonical tensor APIs.

## 3. Flatten a row-major tensor

C commonly stores a simple two-dimensional float array in **row-major** order: one complete row, followed by the next. With `columns = 4`, the zero-based flat index for row `r` and column `c` is:

`index = r × columns + c`

For row 2, column 1: `2 × 4 + 1 = 9`. This is the tenth stored element. An indexing expression is only valid when `0 ≤ r < rows` and `0 ≤ c < columns`.

An illustrative C23 declaration is:

```c
float values[3][4] = {
    {100.0F, 120.0F, 0.1F, 2.0F},
    { 80.0F,  75.0F, 0.2F, 1.0F},
    { 40.0F,  60.0F, 0.5F, 4.0F}
};
/* values[2][1] is the forecast for row 2: 60.0F. */
```

This is a language illustration, not a replacement for Umicom's tensor implementation.

## 4. A tensor can represent token features

In an attention example, `[3,4]` might mean three tokens, each with four feature channels. With two equal attention heads, `headWidth = channels / heads = 4 / 2 = 2`. Each head uses two channels, and both heads process token positions under the declared causal mask.

A proposed five-channel representation cannot be split into two **equal-width** heads because `5 / 2` is not an integer. Changing head count or model width is a model-architecture decision, not a runtime workaround.

## 5. Shape and training-contract checks

Before combining tensors, confirm that matrix dimensions match and the result fits limits. Multiplication `[3,4] × [4,2]` produces `[3,2]`, while `[3,4] × [5,2]` is undefined because the inner dimensions differ.

The Framework's `UmiAiTrainingTensorShape` lets a caller examine dimensions without obtaining mutable access to the tensor-owned buffer. Validation failures should preserve the caller's output objects, rather than publishing a partially computed result.

## Practice and answers

1. Five notes each have eight numerical features. Shape? **`[5,8]`**. Number of values? **40**.
2. In row-major storage with eight columns, what is the zero-based index for row 3, column 2? **`3 × 8 + 2 = 26`**.
3. Can six channels be divided into four equal-width attention heads? **No**, because `6 / 4 = 1.5`.

See the [illustrated HTML unit](../../courses/maths-for-ai/lessons/16-tensor-shapes-and-indexing.html), [matrix multiplication](04-matrices-and-shapes.md) and [training-tape memory](18-memory-budgets-and-rollback.md).
