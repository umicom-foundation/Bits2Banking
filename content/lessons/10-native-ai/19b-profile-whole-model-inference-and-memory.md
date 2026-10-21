# Supplement 19B — Profile Whole-Model Inference and Memory in C23

**Bits to Banking · Build Your Own LLM from Scratch**  
**Author:** Sammy Hegab · Umicom Foundation  
**Code owner:** Umicom Framework · C23

## Learning objectives

After completing this lesson, you should be able to explain the difference
between a model's mathematical workload, the memory it reserves, and the CPU
time observed while it executes. You will compare two real Umicom Framework
inference paths on the same input without changing the model's trained
weights. You will also identify when a key/value cache cannot save work.

### Prerequisites

Read [causal attention](10-causal-self-attention-and-context.md),
[checkpoint and model evaluation](18-model-evaluation-and-provenance.md),
[key/value caching](19-incremental-inference-and-kv-caching.md), and
[the reusable matrix kernel](19a-native-cpu-matrix-optimisation-and-benchmarking.md).

## 1. What does it mean to make a model faster?

Suppose Umicom Studio asks our native model to complete a C23 function that
validates an account number. The model must calculate token embeddings,
attention, feed-forward operations, and final vocabulary scores. Even a
short answer may require many successive predictions.

Three different measurements matter:

1. **Work:** how many token rows or matrix operations were computed?
2. **Memory:** how much storage is needed for parameters, cached keys/values,
   scratch tensors and output logits?
3. **Time:** how many seconds did a real execution consume on this computer?

Those measurements are related but are not interchangeable. A cache might
reduce attention work and still be slower for a tiny model because the cache
itself requires bookkeeping. A faster matrix kernel might consume additional
scratch storage. A small number of learned parameters does not guarantee
small heap allocations if data structures reserve fixed maximum capacities.

## 2. Follow the existing Umicom interfaces

The same Framework already contains:

| Contract | Responsibility |
| --- | --- |
| `decoder.h` | The authoritative trainable native Transformer decoder |
| `kv_cache.h` | Read-only cached keys and values for incremental inference |
| `matrix_kernel.h` | Reference and tiled float32 matrix multiplication |
| `inference_profile.h` | Whole-stream comparisons and memory/work accounting |

The profiler **calls** existing decoder and cache functions. It does not
reimplement attention or turn Bits2Banking into a separate inference engine.
A thin C23 learning executable prints the resulting measurements.

## 3. Calculate storage using real model shapes

Our simplest C23 decoder uses float32 parameters. Each logical parameter
element occupies four bytes. If an example model has 4,792 elements,
its logical parameter payload is:

```text
4,792 elements × 4 bytes = 19,168 bytes
```

That is **not** the total process memory. The model also uses a tape,
intermediate tensors, gradients, bookkeeping, code pages and allocator
metadata. The current cache reserves fixed arrays large enough for the
largest supported matrices, whether a particular model uses them or not.
The Framework therefore reports both logical parameter bytes and the
**actual allocated cache structure size** for the compiled platform.

For a context of eight tokens and eight channels, live key/value storage
needs two matrices of eight rows by eight channels:

```text
keys   = 8 × 8 × 4 = 256 bytes
values = 8 × 8 × 4 = 256 bytes
combined K/V payload = 512 bytes
```

The cache's reserved allocation may be much larger than 512 bytes. The
profiling output makes that difference visible so engineers can determine
whether variable-sized allocation is worthwhile.

## 4. Why context length changes the amount of work

Consider a model that can remember six input tokens.

We prefill its cache with two tokens, and then supply nine more. The
cache initially grows by one row per new token. Once six tokens have been
stored, the next token pushes the oldest token out.

Our model uses *learned absolute positions*. After such a shift, a token
previously at position two becomes position one, so its positional embedding
changes. Reusing the old key and value would compute the wrong prediction.
The cache must rebuild its six rows.

In this experiment:

```text
Initial prefill:               2 calculated rows
Growth until full:             4 calculated rows
Five full-window rebuilds:     5 × 6 = 30 rows
Total cached work:             36 rows

Reference decoder queries:    10
Rows per reference query:       6
Total reference work:          60 rows
```

The cache calculates **24 fewer token rows** in this example. That is an
instrumented workload count. It does **not** promise that the cache executes
faster or uses less memory.

## 5. Build and inspect the real C23 implementation

Use PowerShell on Windows. The repository names below match the Umicom
checkout under `C:\umicom`.

```powershell
Set-Location "C:\umicom\Umicom-Applications"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"

cmake -S ".\framework\learning\native-llm" `
    -B ".\build\windows-ucrt64-native-llm-debug" `
    -G Ninja -DBUILD_TESTING=ON -DCMAKE_BUILD_TYPE=Debug

cmake --build ".\build\windows-ucrt64-native-llm-debug" --parallel 2

ctest --test-dir ".\build\windows-ucrt64-native-llm-debug" `
    --output-on-failure --no-tests=error

& ".\build\windows-ucrt64-native-llm-debug\umicom-native-llm-profile.exe"
```

The executable uses an original Umicom account-validation source fragment as
a read-only teaching input. By default it creates a seeded, **untrained**
decoder. To profile previously trained weights, pass an approved checkpoint:

```powershell
& ".\build\windows-ucrt64-native-llm-debug\umicom-native-llm-profile.exe" `
    "C:\umicom\_local\decoder-training-demo.umi"
```

The output includes calculated token rows, rolling-window rebuilds,
maximum logit deviation, logical parameter bytes, reserved cache bytes and
process CPU time. Each output explains a distinct property of the execution.

## 6. What are we actually validating?

The existing Framework decoder supplies the reference logits. Every cached
result is compared against them. A short prefix is placed at the beginning
of the reference context and padded with **future** BOS tokens. Causal
attention prevents those future positions from influencing the prefix.
A full rolling window is compared at its final token position.

The public profiler rejects incorrect token IDs or invalid prefix lengths.
It leaves the caller's report unchanged if a request fails. It refuses to
publish numerical results if cache and reference logits differ by more than
`0.00005` in absolute value.

Regression checks also ensure that profiling a trained model and then
saving it produces an identical checkpoint. A profiler must observe a model,
not silently train or modify it.

## 7. Why elapsed time is not used to pass tests

The benchmark uses the C standard library's `clock()` function. This reports
**process CPU time** and may include time consumed by other threads. It is
not a monotonic wall-clock timer or a hardware performance counter.

A single run on a laptop can be affected by the compiler's optimisation
level, battery policy, background work, processor temperature and cache
warm-up. Reproducible tests therefore validate *numerical equality and work
counts*, while performance numbers remain observations to investigate.

## Review questions

1. Why can a cache save calculated rows but take more CPU time?
2. How is logical model-parameter storage different from total process memory?
3. What makes the cache rebuild when the learned absolute positions shift?
4. Why does the profiler compare cached logits with the original decoder?
5. What would you need to measure before claiming a 20% performance gain?

## Practical extension

Run the profiler in Debug and Release configurations with the same input.
Record CPU seconds and work counters separately. Do the work counters stay
the same? Do the timings change? Explain why timing alone is insufficient to
claim that an optimisation improves every Umicom application.

## Engineering boundary

This lesson does not increase the permitted tensor size or train a larger
language model. The next scalable-memory work must introduce reviewed
allocation ownership and allocation-failure tests before changing the cache
from fixed reservations to shape-dependent buffers. The educational objective
remains to build an increasingly capable, measurable C23 model from scratch.
