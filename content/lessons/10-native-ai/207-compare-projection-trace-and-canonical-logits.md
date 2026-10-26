# Lesson 207 — Compare projection-trace logits with canonical decoder logits

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Language:** C23  
**Scope:** Educational native model engineering; not production deployment.

**Learning objective:** Build a meaningful numerical regression and avoid merely comparing sampled token IDs.

## Why this matters

An observation hook must not change the answers of the program it observes. To verify that property, feed identical token IDs into two routes: `UmiAiTrainingStackedDecoderLogits` without a hook, and `UmiAiTrainingStackedDecoderTraceProjections` with the hook installed. Compare every vocabulary logit at every token position.

Both methods use the same underlying tape operators. Therefore this is a **hook transparency test**, not a fully independent mathematical oracle for attention. It is still stronger than checking only the top-ranked token: two logit vectors could select the same token while assigning very different probabilities to the alternatives.

Choose a tolerance before running the test, reject non-finite values, and report the maximum absolute difference. For a deterministic CPU execution following the same operation order, differences should be extremely small. A legitimate future accelerated backend will require a separately justified acceptance threshold.

## Work through the numbers and tensor shapes

For vocabulary size **260** and context length **4**, the complete comparison contains `260 × 4 = 1,040` logits. Suppose the largest discrepancy is `0.000012` and the declared absolute tolerance is `0.00004`. The transparency check passes because `0.000012 ≤ 0.00004`. If any value is NaN, it fails regardless of the apparent difference.

For byte-level model outputs, logit equality does not guarantee that emitted bytes form valid UTF-8. The canonical byte tokenizer preserves bytes exactly, while the Framework's UTF-8 streaming component controls presentation of complete characters.

## Where the implementation lives

The reusable implementation belongs to `Umicom-Applications/framework`. Use the public `umicom/ai/training/stacked_projection_trace.h` or `umicom/ai/training/stacked_kv_capture.h` interfaces, depending on the task. The trace observes the **original** decoder through its established Transformer projection hook; the existing cache store handles K/V row ownership. No C23 neural-network computations belong in the Bits2Banking course. Run the Framework CTest cases for numerical qualification on the actual model before interpreting these services as integrated.

## Limitations and engineering evidence

The current observation pipeline performs a **complete canonical Transformer forward** for each observed prompt state. A smaller number of rows accepted into a store is not proof of fewer operations, lower latency or more accurate generated text. SHA-256 identifies checkpoint bytes but does not authenticate a publisher. No generated output should be executed as source code or treated as financial advice.

## Practice

**Question:** Why is exact agreement between the two most probable token IDs a weaker acceptance test than comparing all logits?

<details><summary>Reveal the worked explanation</summary>

The top token can remain unchanged while other logits—and therefore probabilities under top-K or top-p sampling—change. Comparing all 1,040 values detects differences that top-one comparison misses.

</details>

## Continue studying

[Previous lesson](206-trace-projections-without-duplicating-attention.md) · [Next lesson](208-bind-the-capture-to-a-frozen-checkpoint.md) · [View the browser lesson](../../courses/llm-from-scratch/lessons/207-compare-projection-trace-and-canonical-logits.html) · [K/V projection learning path](kv-projection-observation-study-route.md).

*Service to Many Leads to Greatness.*
