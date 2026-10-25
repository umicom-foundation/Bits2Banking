# Lesson 66 — Verify Chunked Generation, Cancellation and Decoder Invalidation

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Implementation authority:** Umicom Framework C23

## Learning objectives

Prove that the size of a streaming caller's requests does not change token results, examine failure-atomic output contracts and explain when training makes an existing inference snapshot stale.

## 1. Uneven pulls must preserve token order

For one unchanged model, prompt, sampling policy and seed, generate **24 tokens** using the Framework's cached one-shot API. Next, create a fresh session with identical inputs and request the first **3**, then **7**, then **14** tokens. All 24 IDs must match the one-shot result in sequence:

**Calculation:** `3+7+14=24.`

Do not recreate the session or reseed between the groups. A streaming group is just a caller's choice of when to stop asking for the next token; it is not part of the model's mathematics.

Compare **token IDs**, not merely displayed text. Byte-token output may contain zeros, control bytes or invalid UTF-8. Two different token streams can also appear similar after a lossy display conversion.

## 2. Inspect before drawing another token

`UmiAiTrainingGenerationSessionInspect` returns the number of successfully generated tokens together with `computedRows`, `windowRebuilds` and `retainedTokens`. The cache statistics exclude the most recently sampled token until it is appended for the next step. This matches the corresponding one-shot cache inspection point; it does not imply that a sampled token was lost.

When learned absolute positions force a context rollover, the row counter may jump by the full window length. These counters represent a workload; they are not a latency benchmark.

## 3. Failure-atomicity and exhaustion

A useful native test gives the token output a recognizable sentinel value, calls the API with an invalid session pointer, and checks **both** the returned error and the untouched sentinel.

For a null session, `UmiAiTrainingGenerationSessionNext` returns `UMI_STATUS_INVALID_ARGUMENT`; it must not modify the token output. After the documented maximum of **256** successful pulls in this teaching session, a further `Next` call returns `UMI_STATUS_CAPACITY_EXCEEDED` without rewriting the caller's token output.

Those are input or capacity refusals, not numerical token disagreements. The test should record which category occurred.

## 4. Why further training invalidates the session

A session's KV cache represents particular decoder parameters. If the decoder performs another successful training step, the model's optimiser-step identity changes and its earlier inference snapshot becomes stale. A subsequent session operation must refuse with `UMI_STATUS_INVALID_STATE` rather than silently combine old keys with new weights.

After such a refusal, destroy the stale session. Build a fresh session using the current decoder state rather than trying to reuse an invalid cache. The Framework, not Bits2Banking, owns the invalidation rule and storage.

## 5. Cancellation and terminal failures

Cancelling a session means ending its lifetime through the Framework destroy operation. A routine invalid-input or capacity refusal is different from a rare internal numerical failure after partially advancing inference state; the latter may leave the session terminal, even if caller outputs were not published. The Framework header directs callers to destroy such a session instead of retrying a partially advanced operation.

## 6. A test plan you can explain

| Case | Expected evidence |
| --- | --- |
| 24 uninterrupted outputs versus pulls 3 + 7 + 14 | Every token ID and count matches. |
| Inspect after several pulls | Counts and cache work reflect successful pulls only. |
| Null session | Invalid-argument status; sentinel output unchanged. |
| Pull after limit | Capacity-exceeded status; sentinel output unchanged. |
| Train model after creating session | Invalid-state refusal; stale session destroyed. |
| Cancel without additional pulls | Model parameters remain unchanged. |

For an already configured Framework native-LLM laboratory, its existing session tests may be selected with:

```powershell
Set-Location 'C:\umicom\Umicom-Applications'
ctest --test-dir '.\build\windows-ucrt64-native-llm-debug' `
    -R '^framework\.ai\.training\.generation_session_' `
    --output-on-failure --no-tests=error
```

A test that does not start is not a passing result. Investigate an absent executable or missing dependency separately from assertions made by a running test.

## 7. Exercises

1. Explain why changing pull-group sizes should leave every token unchanged.
2. If the last sampled token has not been appended, is the statistics report necessarily incorrect?
3. Explain why mixing a cache from earlier decoder weights with a newly trained decoder would violate ownership and numerical correctness.
4. Why is returning an error insufficient unless caller-owned outputs are also protected?

<details>
<summary>Worked answers</summary>

1. Grouping controls when the caller invokes `Next`; it does not change the persistent model, prompt, seed or session state.
2. **No.** The inspection point intentionally excludes that token until the next iteration, matching one-shot semantics.
3. The cached representations describe a different parameter snapshot; mixing revisions can change scores unpredictably.
4. A failed native API call that also mutates outputs can corrupt later processing even when its status is checked.

</details>

**Companion reading:** [Illustrated Lesson 66](../../courses/llm-from-scratch/lessons/66-test-streamed-generation-parity-and-cancellation.html) · [Previous: Session Lifecycle](65-stream-native-llm-tokens-one-at-a-time.md) · [Next illustrated lesson: Measure Decoder Work](../../courses/llm-from-scratch/lessons/67-measure-decoder-and-kv-cache-work.html).
