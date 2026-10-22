# Lesson 21 — Construct and Check Next-Token Windows

**Level:** beginner to intermediate • **Estimated time:** 16 minutes • **Language:** C23

## Learning objectives

Understand **context length**, **sequence count**, **target alignment** and the difference between a model's numerical output dimensions and the small input arrays passed to the Framework.

## The one-position shift

Consider the text `BANK`. A byte-level training window of three positions can be explained as follows:

| Position | Input byte | Desired next byte |
|---|---|---|
| 0 | `B` | `A` |
| 1 | `A` | `N` |
| 2 | `N` | `K` |

The input array and target array therefore have equal lengths. The target at position `t` is the next byte following input at `t`. Our four reserved token IDs mean the actual array entries are numeric IDs rather than characters.

It would be incorrect to place `B`, `A` and `N` in both arrays without shifting. That teaches the model to reproduce the current input instead of predicting what comes next.

## What context length means

With context length eight, a model receives eight token positions for each training sequence. The first position can read only itself; the last position can attend to up to eight input positions including itself. The model cannot access future positions because causal attention masks them.

A training **batch** may contain multiple independent sequences. For example, two sequences of length eight yield **16 input token IDs** and **16 target token IDs**. The sequences cannot attend to one another.

Because the teaching vocabulary contains 260 IDs, the logits tensor for 16 positions has **16 × 260 = 4,160** values. Each `float` normally occupies four bytes, so the logits values alone require **16,640 bytes**. This excludes gradients, parameters and other activations.

## The Framework's actual dataset contract

The public API declares:

```c
UmiStatus UmiAiTrainingDatasetBatch(
    const UmiAiTrainingDataset *dataset,
    UmiAiTrainingPartition partition,
    size_t contextLength, size_t sequenceCount,
    uint64_t seed, uint64_t batchNumber,
    size_t *outInputs, size_t *outTargets, size_t capacity);
```

Both output buffers belong to the caller and must contain at least `contextLength * sequenceCount` **elements**, not bytes. They must not overlap. The sampler bounds one draw to at most **32 context positions** and **four sequences**, while the consuming decoder can impose tighter tensor restrictions.

### Worked C23 example

For a previously loaded and validated dataset, prepare two eight-token windows:

```c
size_t inputs[16] = {0};
size_t targets[16] = {0};

UmiStatus status = UmiAiTrainingDatasetBatch(
    dataset, UMI_AI_TRAINING_PARTITION_TRAIN,
    8U, 2U, UINT64_C(4477), UINT64_C(0),
    inputs, targets, 16U);

if (status != UMI_STATUS_OK) {
    /* Stop here; do not inspect uninitialised sample output. */
}
```

The sample is illustrative **inside a C23 application that already has a valid `dataset` handle**. It is not a stand-alone source file. The Framework owns the source snapshot and validation; the caller owns `inputs` and `targets`.

## Avoid two common mistakes

**Mistake 1: mixing two source files inside one window.** A token at the end of `account.c` must not suddenly predict the first byte of `payment.c`. Umicom's source sampler keeps each window inside a single file and partition.

**Mistake 2: multiplying bytes twice.** `capacity` is a count of `size_t` entries. Passing `sizeof(inputs)` as capacity would supply the byte size, not the required element count.

## Practice task

Draw two eight-position rows on paper. Write `input[0..7]` and `target[0..7]`, with each target shifted forward by one position. Then compute the logits shape for three sequences of context length eight and vocabulary 260.

<details><summary>Show the arithmetic</summary><p>Three sequences × eight positions = 24 positions. The logits tensor contains 24 × 260 = 6,240 float values, occupying 24,960 bytes of values only. Additional training memory is required.</p></details>

**Next:** understand why training and held-out evaluation must use different source files.
