# Supplement 19C — Compact Inference Memory and Ownership in C23

**Bits to Banking · Build Your Own LLM from Scratch**  
**Author:** Sammy Hegab · **Organisation:** Umicom Foundation  
**Language:** ISO C23 · **Implementation:** Umicom Framework

## What you will learn

By the end of this lesson you should be able to distinguish model weights,
key/value attention state and temporary computation, calculate the memory
needed for a small decoder, and explain how an opaque C23 API can reduce
reservations without changing a trained model's predictions. You will also
learn why a successful optimisation must preserve failure behaviour, not just
produce convincing sample output.

## 1. A model uses several different kinds of memory

Our native decoder has trainable parameter matrices: token embeddings,
position embeddings, attention projection weights, layer-normalisation
parameters and feed-forward weights. Training stores gradients and a graph;
inference does not need the training graph for every token. Attention also
needs *keys* and *values* from tokens it has processed. The model finally
calculates scores, called *logits*, for the next token.

These resources have different lifetimes. Parameters remain unchanged during
inference; keys and values belong to one active sequence; logits are replaced
with each prediction. An efficient design should reflect those lifetimes.

## 2. What went wrong with the original reservation?

Our first C23 cache was intentionally easy to inspect. It held every
parameter tensor in a fixed array of the largest permitted tensor size.
That made the data structure predictable, but it reserved space even for
nonexistent parameter elements. The profiling exercise found a cache object
of about 255 KB for a model whose parameters occupied roughly 19 KB.

A pointer to a 19 KB parameter set is not necessarily a 19 KB allocation:
`sizeof` measures the entire containing structure, including its unused
arrays. We therefore need to size memory from the **actual model shapes**.

## 3. Work the numbers

For a decoder with a 260-token vocabulary, eight positions, eight channels,
16 hidden channels and two attention heads, the Framework's canonical shape
contract describes **4,792 parameter floats**.

Each float32 occupies four bytes, so parameters take:

```text
4,792 × 4 = 19,168 bytes
```

Eight positions with eight channels need 64 key floats and 64 value floats:

```text
(8 × 8 × 2) × 4 = 512 bytes
```

The last position needs 260 vocabulary scores:

```text
260 × 4 = 1,040 bytes
```

The packed floating-point payload is therefore 20,720 bytes. The remaining
allocation contains the cache's pointers, configuration, counters, fixed
small token-ID array and alignment. In the qualified native GCC build, the
full requested cache allocation was **21,320 bytes**. The old conservative
upper bound was **255,592 bytes** in that build. Exact object sizes vary
with the C compiler's platform ABI; we never hard-code them into tests.

## 4. Flexible array members

C23 allows a structure to end with a flexible array member. It has no
compile-time number of elements. A checked allocator can reserve space for
the structure plus exactly the required payload.

Study the real code in
`framework/src/ai/training/kv_cache.c`. The private cache structure ends in
`float packed[]`. Separate pointer fields identify the parameter, key,
value and logit regions within that one owned allocation. The code validates
sizes before calling `calloc`; it never exposes these pointers through the
public API.

Why one allocation? It simplifies ownership and cleanup: constructing a
cache either publishes a completely usable object or frees the entire
candidate. Destroying the object releases all its packed storage.

## 5. Do not confuse memory planning with model accuracy

We did **not** change matrix multiplication, attention equations, the
trained parameters or the sampling algorithm. A decoder using compact
storage must produce the same logits as the original decoder.

The Framework's regression suite checks prefixes, rolling context windows,
checkpoint restoration, stale weights after training and invalid inputs.
The revised code still calculates results in a temporary state and copies
them to persistent storage only after every operator succeeds.

These safeguards are especially important for the Umicom applications:
rejecting a malformed request must not corrupt a previous valid result.

## 6. Practical exercise — inspect the real implementation

Open PowerShell on your Umicom development machine:

```powershell
Set-Location "C:\umicom\Umicom-Applications"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"

cmake -S ".\framework\learning\native-llm" `
    -B ".\build\windows-ucrt64-native-llm-debug" -G Ninja `
    -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTING=ON
cmake --build ".\build\windows-ucrt64-native-llm-debug" --parallel 2
ctest --test-dir ".\build\windows-ucrt64-native-llm-debug" `
    --output-on-failure --no-tests=error

& ".\build\windows-ucrt64-native-llm-debug\umicom-native-llm-cache-memory.exe"
& ".\build\windows-ucrt64-native-llm-debug\umicom-native-llm-profile.exe"
```

Compare the two displayed decoder configurations. Identify which memory
requirements grow with vocabulary, which grow with context and which grow
with channel width. Then read these Framework contracts:

- `include/umicom/ai/training/kv_cache.h`
- `include/umicom/ai/training/inference_profile.h`
- `src/ai/training/kv_cache.c`
- `tests/ai_training/test_training_cache_compact_layout.c`

The two allocation-inspection functions serve different purposes.
`UmiAiTrainingKvCacheAllocationForConfig` predicts the allocation before
constructing a cache; `UmiAiTrainingKvCacheAllocatedBytes` examines a real,
owned instance. Both must agree for the same validated configuration.

## 7. Questions to check understanding

1. Why does allocating the maximum size for every parameter waste memory?
2. Which memory regions are long-lived during inference, and which change
   when a new token is processed?
3. Why is `sizeof(cache)` not always the memory reserved for a cache with
   dynamically allocated payloads?
4. What should happen if a proposed allocation exceeds `SIZE_MAX`?
5. Why must a key/value cache be rejected or recreated after an optimiser
   update makes its weight snapshot stale?
6. Does reducing cache memory change the maximum context length or the
   model's ability to reason about C23 source code? Explain your answer.

## 8. Extension exercise

Using only the existing Framework source and its C23 build, investigate how
many bytes the cache would need for a different **valid** context length.
Do not increase the public model limits or modify the training mathematics.
Record the configuration, actual allocation, CPU timing and numerical
comparison separately. Explain why an observed speed difference does not,
by itself, prove that the new memory layout is faster.

## What comes next?

This exercise reduces waste in inference-cache storage while retaining
correctness. Future topics include compact per-operation staging, explicit
allocation budgets, precision trade-offs and larger-model capacity planning.
All reusable implementation belongs in Umicom Framework; lessons teach the
existing implementation instead of duplicating it inside Bits2Banking.
