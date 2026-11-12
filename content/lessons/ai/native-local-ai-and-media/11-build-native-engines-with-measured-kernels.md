<!--
Umicom Bits2Banking
File: content/lessons/ai/native-local-ai-and-media/11-build-native-engines-with-measured-kernels.md

PURPOSE:
Teach build native engines with measured kernels.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original material; cited sources retain their own terms.
-->
![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Build native engines with measured kernels

## What you will learn
Plan an original C implementation without confusing orchestration work with model computation. Use Assembly only where a measured low-level contract needs it.

## Two distinct paths
The first path is interoperability: a C adapter connects an existing engine to Umicom's shared services. The [llama.cpp project](https://github.com/ggml-org/llama.cpp) is an example of a C/C++ inference engine. Using it requires an explicit external dependency boundary; this course does not upgrade Umicom's approved vendor pins.

The second path is Umicom's own model implementation. Existing ai/training code already covers numerical and generation responsibilities. Extend it through measured, compatible steps instead of starting another model engine in each application.

## Grow one supported contract
1. Define the tokenizer, model architecture and supported tensor shapes.
2. Specify weight format, integrity checks, numeric types and ownership.
3. Establish a portable C reference for each operation.
4. Check output against independently calculated small fixtures.
5. Profile complete inference to locate costly work.
6. Introduce an optimized kernel only after its semantics are fixed.
7. Keep the portable path for unsupported CPUs and parity checks.

A GGUF filename does not establish that an engine supports the file's architecture, quantization or tokenizer. Likewise, a C ABI around a GPU library does not prove the whole implementation is C. Document exactly what runs inside and outside the native engine.

## Where Assembly can help
Vectorized matrix multiplication or quantized dot products may benefit from architecture-specific instructions. Dispatch must check CPU capabilities before entering a kernel. Alignment, tail elements, calling conventions and floating-point tolerances belong in the contract.

Do not write Assembly for model dropdowns, HTTP request policy or course navigation. Portable C expresses those responsibilities clearly. A fast kernel cannot repair an incorrect cache position or tokenizer.

## Exercise
For a dot product, use vectors [1, 2, 3] and [4, 5, 6]. The reference result is 32. Add a length that is not a multiple of the vector width and compare the complete result with the portable implementation.

**Expected result:** correctness is established before speed is reported. Record hardware, compiler flags, input dimensions and numerical tolerance with any timing.

## Continue and recover
The [LLM from scratch course](../../../courses/llm-from-scratch/index.html) covers decoder training, cache semantics and generation evidence. This application course builds on that material.

When optimized and reference outputs disagree, isolate the smallest failing shape. Keep the original reference implementation. Do not widen tolerances until a test passes without understanding the numerical difference.

[Course contents](index.md) · [Next lesson](12-qualify-a-complete-ai-workflow.md)
