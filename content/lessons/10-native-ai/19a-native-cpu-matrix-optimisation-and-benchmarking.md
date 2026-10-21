# Supplement 19A — Make Our Native Model's Mathematics Measurable

**Bits to Banking · Build Your Own LLM from Scratch · Umicom Foundation**  
**Author:** Sammy Hegab  
**Language:** C23; Assembly becomes an optional later optimisation  
**Prerequisites:** matrix multiplication (Lesson 06), gradients (Lesson 07),
transformer blocks (Lesson 12) and incremental inference (Lesson 19).

## Learning objectives

After completing this lesson you should be able to explain why matrix
multiplication dominates many neural-network operations, calculate the work
required for a projection, compare two equivalent CPU implementations, build
and test the actual Framework operator, and distinguish a measured result from
a performance promise. Our goal is not to write a faster-looking loop; it is
to make a correct, reusable implementation whose cost can be investigated.

## 1. Why our language model multiplies matrices

When the decoder processes an embedding, it produces vectors representing
information about the current token. Attention needs **query**, **key** and
**value** projections. The feed-forward network also transforms vectors
through learned weight matrices. Finally, a projection converts the decoder's
internal representation into a score for each vocabulary token.

These operations share one mathematical structure:

```
   Input activations             Weight matrix             Output
   [rows x inner]       times    [inner x columns]   =    [rows x columns]
```

Suppose two fictional bank-account feature vectors are:

```
A = [1 2 3]
    [4 5 6]
```

and the projection weights are:

```
B = [ 7  8]
    [ 9 10]
    [11 12]
```

To calculate the first output value, multiply corresponding elements and add:

`(1 x 7) + (2 x 9) + (3 x 11) = 7 + 18 + 33 = 58`.

The full result is:

```
C = [ 58  64]
    [139 154]
```

This is an ordinary matrix multiplication. The exact same operation is reused
throughout a transformer, although its matrices are considerably larger than
this teaching example.

## 2. How much computation does it require?

Let **M** be the number of rows, **K** the input width and **N** the output
width. Every one of the `M x N` output elements needs `K` products and
accumulations. The approximate arithmetic workload is therefore:

`multiply-accumulate operations = M x K x N`

`nominal floating-point operations = 2 x M x K x N`

These counts deliberately treat each multiplication and addition as one
operation. Hardware may fuse them, and the algorithmic estimate is not a count
of processor instructions.

For a single-token output projection of shape `[1, 8] x [8, 260]`, that is
**2,080 multiply-accumulates**, or **4,160 nominal floating-point operations**.
There are also **32 input bytes**, **8,320 weight bytes** and **1,040 output
bytes**, when values use 32-bit floats. The real processor may read the same
cache line multiple times or reuse data already in cache.

Umicom Framework now calculates these values through
`UmiAiTrainingMatrixEstimateWork`. Its role is to give us a verified cost model
before we attempt acceleration.

## 3. Two correct ways to arrange the loops

The original reference implementation calculates one output column at a time.
For each column, it walks the entire inner dimension. This is easy to read and
provides a valuable baseline.

A different implementation works on **16 neighbouring output columns**
together. It loops over the shared input element and updates 16 accumulators.
This can reuse a contiguous section of the weight matrix while that data is
close to the processor.

The second approach is called **column tiling**. Its purpose is to improve
memory locality. It does not change our model, weights, training objective or
output dimensions. Crucially, we keep the summation order for each individual
output unchanged: increasing input index, double-precision accumulation, and
one float32 result at the end.

Why is that detail important? Floating-point addition is not generally
associative. Changing `(a + b) + c` into `a + (b + c)` can change rounded bits.
An optimisation that changes predictions requires separate qualification.

The Framework exposes `UMI_AI_MATRIX_REFERENCE`, `UMI_AI_MATRIX_TILED` and
`UMI_AI_MATRIX_AUTO`. The automatic method selects a conservative implementation
based on matrix shape, because a tiled loop is not always faster. No graphics
application or model-training lesson needs its own multiplication code.

## 4. Read the real Framework code

Open the complete source files:

```
C:\umicom\Umicom-Applications\framework\include\umicom\ai\training\matrix_kernel.h
C:\umicom\Umicom-Applications\framework\src\ai\training\matrix_kernel.c
C:\umicom\Umicom-Applications\framework\src\ai\training\tape.c
C:\umicom\Umicom-Applications\framework\src\ai\training\kv_cache.c
```

The training tape creates a result tensor with the correct dimensions and
calls the shared CPU kernel. Its automatic-differentiation rules still belong
to the tape. The KV cache invokes the **same kernel** for query, key, value,
feed-forward and vocabulary projections. It does not introduce a second,
unreviewed mathematical implementation.

The previous projection loops are preserved in disabled `#if 0` blocks with
comments explaining what replaces them. This makes the migration reviewable
and keeps the historical educational calculations available.

### What happens when input is invalid?

A source model could contain a damaged weight, an infinity, or a dimension
that would exceed the allowed buffer. We reject those cases before publishing
output. The operator writes into temporary storage first, so a failed call
cannot leave the first half of a matrix updated and the second half unchanged.
The output may even overlap an input because it is not copied until all values
have been validated.

This is important for financial applications: partial writes can be more
harmful than a clear, explicit failure. The exact same safety principles apply
to model-development infrastructure.

## 5. Build and test in PowerShell

Open PowerShell and compile the native learning project:

```powershell
Set-Location "C:\umicom\Umicom-Applications"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"

cmake -S ".\framework\learning\native-llm" `
    -B ".\build\windows-ucrt64-native-llm-debug" `
    -G Ninja `
    -DCMAKE_BUILD_TYPE=Debug `
    -DBUILD_TESTING=ON

cmake --build ".\build\windows-ucrt64-native-llm-debug" --parallel 2

ctest --test-dir ".\build\windows-ucrt64-native-llm-debug" `
    --output-on-failure `
    --no-tests=error
```

The matrix contract test checks known values, several different shapes,
reference/tiled/automatic equality, and failure-atomic handling of invalid
inputs. The tape test checks mathematical gradients against independent
expected derivatives. The inference test checks the KV cache against the
canonical decoder, including a rolling-context rebuild.

If any of these tests fails, **do not** claim the optimisation is correct.
Inspect the failure before attempting to measure performance.

## 6. Measure CPU time instead of guessing

Run the benchmark with a fixed number of repetitions:

```powershell
& ".\build\windows-ucrt64-native-llm-debug\umicom-native-llm-matrix-benchmark.exe" 1000
```

The native benchmark confirms output equality first, then measures process CPU
time with C23 `clock()`. It reports the same input dimensions for reference
and tiled code, their nominal arithmetic work and the observed runtime.

One developer run under **GCC 14.2 on Linux with Debug settings** observed the
tiled loop taking less CPU time on both sampled shapes. In a subsequent
**optimised Release** run, it was faster on the larger matrix but slower on
the short single-row projection. That difference is expected: compilers and
hardware optimisations interact with matrix dimensions. We therefore introduced
conservative automatic dispatch rather than treating a single benchmark as a
universal truth.

Do not compare Debug against Release and call the difference a code speedup.
Use the same compiler, optimisation flags, datasets and machine state. Repeat
runs and record variability. A stopwatch reading is evidence about *that run*,
not evidence about every future user and CPU.

## 7. Prepare for model scalability

Our current tensor operator allows up to 4096 elements per matrix. The decoder
also has separate restrictions on vocabulary, context length, channels and
parameter count. Improving a matrix loop does **not** remove those bounds.

Before building a larger model, we must decide how much memory each tensor
needs, how intermediate values are allocated and released, and which numerical
backend is responsible for the result. After establishing a reliable CPU
baseline, we can evaluate Assembly or SIMD implementations using the same
reference outputs and tests.

A large model also requires realistic datasets, multiple training iterations,
adequate memory and independent evaluation. A faster matrix multiplication by
itself does not make our tiny transformer knowledgeable about C23 or Calypso.

## 8. Exercises and review questions

**Exercise A — Calculate the work.** For `[4, 8] x [8, 16]`, calculate output
shape, multiply-accumulates and nominal floating-point operations before
checking your answer against the Framework estimate.

**Exercise B — Compare shapes.** Run the native benchmark on your Windows
computer in both Debug and Release builds. Record CPU type, compiler, command,
repetitions and observed reference/tiled ratio. Explain why the ratios differ.

**Exercise C — Verify memory safety.** Read
`tests/ai_training/test_training_matrix_contract.c`. Explain why the result
buffer must remain unchanged when one input contains `NAN`, even if earlier
matrix elements are valid.

**Question:** Why do we preserve a reference implementation when an optimised
implementation passes all tests? **Answer:** We need an independent baseline
against which to compare numerical correctness, diagnose regressions and
qualify future hardware-specific implementations.

## Where we go next

We will extend quantitative profiling from isolated matrix operations to
complete decoder inference: prefill, token-by-token generation, rolling-window
rebuilds and memory use. Larger models will need explicit memory budgets and
hardware qualification rather than only larger numeric constants.

**Service to Many Leads to Greatness.**
