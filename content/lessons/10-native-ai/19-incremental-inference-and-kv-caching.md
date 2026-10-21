# Lesson 19 — Incremental Native Inference and Key/Value Caching

**Bits to Banking — Build Your Own LLM from Scratch**  
**Author:** Sammy Hegab · **Organisation:** Umicom Foundation  
**Language:** ISO C23 · **Runtime owner:** Umicom Framework

## Learning objectives

By the end of this lesson you should understand how causal attention can reuse
previously computed keys and values, which calculations still need to be
performed for each new token, and when such reuse becomes mathematically
incorrect. You will inspect a native C23 implementation, compare its outputs
against a reference decoder, and verify that training invalidates cached model
weights. No pretrained language model is required.

## Why inference repeats work

Consider a source-code prompt:

```c
int accountBalance =
```

A causal decoder predicts the next token from the preceding context. A naïve
autoregressive generator can submit the entire context again after every
generated token. The previous tokens' attention keys and values are then
recalculated even though the model parameters and those token representations
have not changed.

A transformer maps a token representation `x` to three projections:

\[
q = x W_Q,\qquad k = x W_K,\qquad v = x W_V.
\]

The attention output for a token at position `t` uses its query with the keys
of all visible positions `0..t`:

\[
\operatorname{Attention}(q_t,K,V)
 = \sum_{i=0}^{t} \frac{\exp(q_t k_i^{T}/\sqrt{d})}
 {\sum_{j=0}^{t}\exp(q_t k_j^{T}/\sqrt{d})}v_i.
\]

The sum only includes past and current tokens. Future token positions are
excluded by the causal mask. **When past token representations are unchanged**,
we can save their `k_i` and `v_i`, compute the new token's query/key/value
projections, and reuse the stored rows for the next attention calculation.

## What the Umicom cache owns

The native API is declared in
`framework/include/umicom/ai/training/kv_cache.h`. Its implementation is
`framework/src/ai/training/kv_cache.c`. The model itself remains the existing
`UmiAiTrainingDecoder`: we do not create a second set of trainable parameters.

Each cache owns a snapshot of the trained decoder's parameter values, the
retained token history and the key/value rows corresponding to that history.
The caller owns the decoder and must keep it alive for the entire cache
lifetime. Calls must be serialised; a cache is not thread-safe.

The interface offers these native operations:

| Operation | Responsibility |
| --- | --- |
| `UmiAiTrainingKvCacheCreate` | Allocate a new cache and copy the decoder's approved weight values. |
| `UmiAiTrainingKvCachePrefill` | Compute a complete prefix and return its final token's logits. |
| `UmiAiTrainingKvCacheAppend` | Append a token, using saved K/V rows when positions remain unchanged. |
| `UmiAiTrainingKvCacheInspect` | Return retained token count, computed rows and complete-window rebuild count. |
| `UmiAiTrainingKvCacheReset` | Discard one context's state before processing a separate sequence. |
| `UmiAiTrainingKvCacheDestroy` | Release cache-owned memory without changing the model. |

The public API deliberately returns a **single row of vocabulary logits** for
the newest token, rather than generating text silently. Applications may pass
that row to the existing Framework `UmiAiTrainingSampleLogits` function.
Temperature and top-K sampling therefore retain one authoritative
implementation.

## The positional-embedding trap

This first Umicom decoder uses learned **absolute positional embeddings**.
The token at position zero is represented differently from the same token at
position one. While the prefix is growing and positions remain fixed, old
K/V rows are reusable.

But imagine the cache has a context length of four:

```text
Positions     0      1      2      3
Tokens       int     x      =      0
```

When we append `;` after filling the context, the rolling window becomes:

```text
Positions     0      1      2      3
Tokens        x      =      0      ;
```

The surviving tokens have **new absolute positions**. Their embedding vectors
and therefore their keys and values are no longer the same. Simply discarding
`int` and shifting old K/V rows would produce the wrong answer.

Our implementation intentionally invalidates and reconstructs the full window
at this boundary. This protects correctness but also means the cache cannot
promise ongoing speed gains after the window is full. Later research could
examine position schemes and retention policies designed for incremental
streaming, but changing those would alter the learned model architecture and
require separate training and compatibility work.

## Follow the C23 implementation

Open `kv_cache.c` and follow the single-token path. It first combines the
existing token embedding with its absolute positional embedding. Then it
reproduces the canonical pre-layer-normalised attention block using the same
projection matrices, multi-head attention, residual additions and ReLU
feed-forward layer. Finally, it multiplies the resulting representation by the
canonical output-logits matrix.

The cached decoder is an **inference-only mathematical kernel**, not a second
training engine. Its float32 materialisation points and double-precision
intermediate sums mirror the established training tape to support numerical
parity checks. The tests compare predicted logits against
`UmiAiTrainingDecoderLogits`, using a bounded numerical tolerance.

All cache operations stage mutable state before publishing it. A rejected
input token, insufficient caller capacity or numerical failure leaves the
previous cached history and caller output unchanged.

Training updates the decoder's parameter values and increments its completed
optimiser-step count. An existing cache therefore rejects subsequent requests
with `UMI_STATUS_INVALID_STATE`: the caller must destroy it and create a fresh
cache from the new model. Checkpoint reload likewise uses the normal decoder
constructor before starting a new cache.

## Compile and verify on Windows

The following commands use the existing Umicom Framework source and CMake
learning laboratory rather than duplicating its AI mathematics in Bits2Banking:

```powershell
Set-Location "C:\umicom\Umicom-Applications"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"

cmake -S ".\framework\learning\native-llm" `
    -B ".\build\windows-ucrt64-native-llm-debug" `
    -G Ninja -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTING=ON
cmake --build ".\build\windows-ucrt64-native-llm-debug" --parallel 2
ctest --test-dir ".\build\windows-ucrt64-native-llm-debug" `
    -R "kv_cache" --output-on-failure
& ".\build\windows-ucrt64-native-llm-debug\umicom-native-llm-kv-inspect.exe"
```

The inspector can optionally load a locally reviewed, valid Umicom decoder
checkpoint. Without one, it constructs a reproducible untrained demonstration
model. It then appends source-text bytes and compares each cached result with
the original decoder's logits. It prints the number of cached tokens and the
number of token rows actually computed.

Do not interpret a lower work count during prefix growth as proof of a measured
end-to-end speedup. CPU cost, memory allocation and cache invalidations must
be benchmarked separately before making performance claims.

## Practical exercise

Start with the inspector's reproducible model and identify the first
full-window rebuild. Explain why it occurs. Then create a checkpoint with the
existing training experiment, load it into the inspector and check that logits
still match. Change the context length in a controlled test and predict how
the first rebuild point moves.

For a more demanding extension, profile memory allocations and multiply-add
counts separately from elapsed time. Any SIMD or Assembly optimisation must
produce results within the same reference decoder tolerance and must not
change parameter ownership.

## Review questions

1. What is the difference between a query, a key and a value in causal attention?
2. Why is a token's cached key reusable while its absolute position is stable?
3. Why must the current implementation rebuild K/V rows when the rolling
   context shifts by one position?
4. What guarantees that model training does not silently leave a cache with
   outdated weights?
5. Why do we compare logits numerically rather than comparing only the chosen
   next-token ID?

**Evidence boundary:** This lesson demonstrates a numerically qualified,
bounded key/value cache for our existing small educational model. It does not
claim a production-scale transformer, general C23 reasoning skill or guaranteed
long-prompt acceleration. The source code and acceptance tests provide the
evidence for each supported behaviour.
