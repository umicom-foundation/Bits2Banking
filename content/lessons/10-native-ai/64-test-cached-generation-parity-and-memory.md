# Lesson 64 — Test Cached Generation Parity and Bounded Memory

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Implementation authority:** Umicom Framework C23

## Learning objectives

Design deterministic comparisons between cached and canonical generation, test failure-atomic output handling, and distinguish a failed programme from a test executable that did not start.

## 1. A fair parity comparison

Generation parity means that two implementations return the **same sequence of token IDs** under matching input conditions. Use one unchanged decoder checkpoint and match every relevant input:

| Input | Why it must match |
| --- | --- |
| Prompt token IDs and length | Token history determines logits. |
| `temperature`, `topK`, `topP` | The policy controls candidate probabilities. |
| Seed | Random draws must be reproducible. |
| New-token count | Compare the same output horizon. |
| Decoder parameters | A weight change makes the experiment incomparable. |

Call `UmiAiTrainingDecoderGenerateNucleus` and `UmiAiTrainingDecoderGenerateCachedNucleus` independently with identical settings. Compare the returned token counts and each token ID at the same position. Comparing only printable text is insufficient: the byte vocabulary can produce NUL and other non-printable values.

## 2. The necessary test cases

A useful regression matrix covers an empty prompt, short BOS-padded prompt, exactly full context, overlong prompt admitted by the API, greedy selection, and seeded nucleus sampling. Verify that compatibility holds before and after the context window rolls. A test that checks only the first token may miss the positional-error case entirely.

The existing Framework cache API also returns `UmiAiTrainingGenerationCacheStats`. Inspect `computedRows`, `windowRebuilds` and `retainedTokens` rather than inventing a performance percentage.

## 3. Failure-atomic outputs

A rejected request must not partially rewrite caller-owned output buffers. This is important in native systems: a failed function that leaves half a new answer alongside half an old one is difficult to reason about.

For a test, initialise an output array to known sentinel IDs and initialise the output count to a distinct sentinel. Invoke the Framework function with a deliberately invalid policy (for example `topP=0`), then check the returned error and verify that the array and count still contain their original values. A similar test can protect the optional statistics structure.

These conditions can be checked using the *existing Framework test harness*. Bits2Banking does not need a second generator, parser or test engine.

## 4. Checkpoint immutability

Generation is an inference operation. Compare the decoder checkpoint bytes before and after generation to verify that the operation did not modify the saved checkpoint. A byte match is meaningful evidence of immutability, **not** evidence that the model's answers are accurate, unbiased or suitable for production use.

## 5. Build failures are not mathematical failures

A CTest result of `Not Run` or `BAD_COMMAND` indicates that a test executable could not be started. It must not be counted as a pass and does not, by itself, prove a mathematical defect. Confirm that the target was compiled and that the executable can load its runtime dependencies. An assertion failure after a successfully started programme is a different category: the behaviour under test did not satisfy its expectation.

For an already configured and built Framework native-LLM laboratory, the dedicated regression tests may be inspected with:

```powershell
Set-Location 'C:\umicom\Umicom-Applications'
ctest --test-dir '.\build\windows-ucrt64-native-llm-debug' `
    -R '^framework\.ai\.training\.generation_cache_' `
    --output-on-failure --no-tests=error
```

The test names and executable targets belong to Umicom Framework. This course supplies an interpretation guide, not a separate implementation.

## 6. Exercises

1. A cached generator agrees with the original on the first token but differs after the context rolls. Name two plausible causes.
2. Why must the two generators use identical seeds?
3. What does a successful checkpoint byte comparison establish? What important question does it *not* answer?
4. Why should invalid-input testing also inspect output buffers rather than only checking the returned status code?

<details>
<summary>Worked answers</summary>

1. Stale keys/values after learned-position reassignment, or different BOS/rolling-context construction.
2. Otherwise a difference may come from random token sampling rather than cache calculations.
3. It establishes that the recorded checkpoint bytes are unchanged; it does not establish model quality or correctness of every internal temporary allocation.
4. A function can report failure but still corrupt caller state. Failure-atomicity rules out that class of outcome for the documented outputs.

</details>

**Companion reading:** [Illustrated Lesson 64](../../courses/llm-from-scratch/lessons/64-test-cached-generation-parity-and-memory.html) · [Previous: Cache Semantics](63-qualify-kv-cached-nucleus-generation.md) · [Next: Pull-Based Sessions](65-stream-native-llm-tokens-one-at-a-time.md).
