# Lesson 05 — Tensor Shapes, Memory and Ownership in C23

**Bits to Banking · Build Your Own LLM from Scratch**  
**Sammy Hegab · Umicom Foundation**  
**Laboratory:** Umicom Framework native AI training tape  
**Reference files:** `include/umicom/ai/training/tape.h`, `src/ai/training/tape.c`

## The problem we are solving

A neural network calculates with large collections of numbers. We call a structured collection of numbers a **tensor**. A scalar (one number) can be considered a rank-0 tensor, a vector a rank-1 tensor, and a matrix a rank-2 tensor. General tensor libraries support more dimensions; our first working library deliberately supports **row-major two-dimensional float32 matrices**. A `1 × 1` matrix represents a scalar loss in this bounded experiment.

This scope is deliberate. A correct small implementation makes shape validation, ownership and differentiation observable. Later transformer work must extend the tensor representation to support batch, sequence, head and hidden dimensions; this batch must not be described as a general-purpose tensor runtime.

## Reading a tensor's shape

Consider a matrix containing three token features for two training examples:

```text
rows=2, columns=3

[ 1.0  0.0  0.0 ]
[ 0.0  1.0  0.0 ]
```

Its **shape** is `(2,3)`, and its **element count** is `2 × 3 = 6`. Because the storage is row-major, the element at row `r` and column `c` is stored at linear index `r * columns + c`. For example, row 1, column 1 maps to index `1*3+1=4`, where the value is `1.0`.

The caller must not blindly multiply `rows*columns` without first guarding against integer overflow. The C23 implementation checks `columns <= MAX_ELEMENTS` and `rows <= MAX_ELEMENTS / columns` before allocating any storage. Both dimensions must be positive.

## Who owns the memory?

The public contract has two opaque types:

```c
/* The Framework owns the internal representation. */
typedef struct UmiAiTrainingTape UmiAiTrainingTape;
typedef struct UmiAiTrainingTensor UmiAiTrainingTensor;
```

The application creates a **tape**, then creates tensors within it. The tape owns their float values, gradients and any saved targets required for differentiation. Values passed to `UmiAiTrainingTensorCreate` are copied into newly allocated storage. Callers retain neither the internal buffer nor a promise that their own input arrays remain unchanged outside the call.

This explicit lifetime arrangement is important in a C23 application. It prevents a model-training component from storing a borrowed pointer to an editor buffer, temporary array or file-mapped region that might be released by another subsystem.

## Trace a complete call

```c
UmiAiTrainingTape *tape = NULL;
UmiAiTrainingTensor *input = NULL;
const float values[2] = {1.0F, 2.0F};

UmiStatus status = UmiAiTrainingTapeCreate(&tape);
if (status == UMI_STATUS_OK) {
    status = UmiAiTrainingTensorCreate(
        tape, 2U, 1U, values, 2U, 0, &input);
}
/* Real application code should handle each failed status. */
UmiAiTrainingTapeDestroy(tape);
```

The final argument to `UmiAiTrainingTensorCreate` is an output parameter. A successful call stores a borrowed handle there, **but the tape still owns the tensor**. Destroying the tape invalidates every tensor handle. Calling a tensor API after that would violate the lifetime contract. An output copy API allows the application to retain numerical results independently.

## Why this first engine has hard limits

Batch 01 uses:

```c
#define UMI_AI_TRAINING_MAX_TENSORS 256U
#define UMI_AI_TRAINING_MAX_ELEMENTS 4096U
```

These are educational resource limits, not a claim about maximum LLM size. An operator refuses a new node once the tape has reached capacity. This protects our early tests from accidentally creating very large graphs. A production trainer will require configurable budgets, pooling, efficient storage and additional dimensions.

A training loop creates temporary operation nodes for each forward pass. `UmiAiTrainingTapeRewind(tape, retainedLeafCount)` releases those temporary nodes while preserving the specified input and parameter leaves. The retained prefix must consist exclusively of original leaves; the function checks this before changing anything. Discarded tensor handles immediately become invalid.

## Test the contract

After merging the files into the real Framework checkout:

```powershell
Set-Location 'C:\umicom\Umicom-Applications'
cmake -S '.\framework\learning\native-llm' -B '.\build\native-llm-lesson' -G Ninja -DBUILD_TESTING=ON
cmake --build '.\build\native-llm-lesson' --parallel 2
ctest --test-dir '.\build\native-llm-lesson' -R 'framework\.ai\.training\.contract' --output-on-failure
```

In `test_training_contract.c`, identify a test for wrong dimensions, non-finite input, a tensor from another tape, output-buffer capacity and invalid rewind. Notice that rejected operations do not publish a partially constructed node. Explain why failure isolation is essential when training a model for hours rather than milliseconds.

## Review questions

1. What is the linear index for row 2, column 1 in a `4 × 3` row-major tensor?
2. Why is returning a mutable pointer to the internal tensor buffer dangerous?
3. What happens to derived tensors when the tape is rewound?
4. Why is a `2 × 3` matrix not automatically compatible with a `3 × 2` matrix for element-wise addition?

**Next:** [Lesson 06 — Matrix operations and activations](06-matrix-operations-and-activations.md).
