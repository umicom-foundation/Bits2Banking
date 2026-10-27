# Practical laboratory — one-query attention and independent verification

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Language:** Native C23

## Learning objectives

Reproduce a two-token attention calculation, inspect the native output contract, run the isolated arithmetic tests and explain how a canonical multi-head tape oracle would validate the last row. This laboratory uses the **existing Framework source of truth**; it does not copy an attention or inference implementation into the educational repository.

## 1. Calculate a two-token example

Use one query `Q=[1,0]`, two keys `K=[ [1,0], [0,1] ]` and two values `V=[ [2,4], [6,8] ]`. The head width is two. Divide dot products by `√2`, subtract the maximum and obtain probabilities approximately `[0.6698,0.3302]`. The weighted output should be approximately `[3.321,5.321]`.

## 2. Inspect the C23 public boundary

The Framework companion defines `UmiAiTrainingSingleQueryAttentionForward` in `include/umicom/ai/training/single_query_attention.h`. Its inputs are caller-owned arrays; its outputs are unchanged on rejection. Read the header alongside `src/ai/training/single_query_attention.c` and identify every dimension, capacity and ownership rule.

## 3. Build the standalone unit target

From a checkout containing the corresponding Framework laboratory, use CMake and Ninja with a C23 compiler:

```powershell
cmake -S ".\framework\learning\native-ai-single-query-attention" `
      -B ".\build\native-single-query-attention" `
      -G Ninja -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTING=ON

cmake --build ".\build\native-single-query-attention"

ctest --test-dir ".\build\native-single-query-attention" `
      --output-on-failure --no-tests=error
```

The directory shown is relative to the containing `Umicom-Applications` workspace. A different checkout arrangement may require adjusting `-S` and `-B` paths.

## 4. Compare against the existing canonical tape

An additional Framework test source, `tests/ai_training/test_single_query_tape_parity.c`, compares the last row of the existing `UmiAiTrainingMultiHeadCausalAttention` with the candidate C23 kernel. This test is registered only when the required canonical tape target is included by the containing Framework CMake project. Unlike the standalone arithmetic test, it requires the full Framework dependencies.

## 5. Explore rejection behaviour

Change only an input of a temporary *test fixture*, not an existing committed model or production source: try a zero head count, output capacity one element too small, a NaN key, and overlapping output/input buffers. Observe the returned status and output sentinels. An invalid call must not leave half a vector published.

## 6. Study the limits

The new forward-only kernel does not replace the stacked decoder's attention step automatically and does not create reverse-mode gradients. Replacing an inference-time computation still requires independent full decoder tests across every vocabulary logit and learned-absolute-position rollover. The correctness of that complete path cannot be inferred from this lab alone.

*Service to Many Leads to Greatness.*
