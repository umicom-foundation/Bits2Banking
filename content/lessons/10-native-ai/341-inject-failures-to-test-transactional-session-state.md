# Lesson 341 — Inject failures to test transactional session state

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Implementation:** C23 and native Umicom Framework APIs  
**Prerequisite:** LLM Lesson 340; Mathematics Unit 201.

## Learning objective

Explain and test **inject failures to test transactional session state** within the bounded, educational native Transformer architecture.

## Technical explanation and worked example

Happy-path tests prove little about ownership boundaries. A pool's most important guarantees appear when a request fails: no corrupted session, no leaked reservation and no partially published lease. Test malformed dimensions, budget exhaustion, wrong checkpoint identity, stale generation, full-window append and invalid shifted histories.

Failure injection is stronger when each case checks both the return code **and** the state that follows. Initialise an output lease with a sentinel, attempt an acquisition that must fail, and assert the sentinel is unchanged. Then inspect active count and reserved bytes. For a rejected rollover, compare the retained K/V row against the previous canonical data.

**Worked scenario.** Before a wrong-shift attempt, the store has `retained=4` and `fullWindowRebuilds=0`. The invalid token sequence is rejected. After the call, both numbers remain unchanged. A subsequent valid full replacement must succeed and increment rebuilds to one.

**Native walkthrough.** Execute the new CTest cases `budget`, `rollover`, `rejections` and `lifecycle`. Use sanitizers in an integrated Framework build as an additional class of evidence; sanitizer success in a fixture-only test does not prove whole-product safety.

## Practise

**Question:** Is a returned error code enough to prove failure atomicity?

<details><summary>Reveal the worked answer</summary>

No. You must also verify unchanged outputs, counts and underlying cache contents after rejection.

</details>

## Explore the mathematics

[Mathematics Unit 201](../11-maths-for-ai/201-prove-reservation-accounting-across-a-release.md) develops a related calculation. Distinguish stated design, tested library contracts and measured runtime evidence.

## Continue learning

[Previous lesson](340-separate-raw-cache-payload-from-process-memory-overhead.md) · [Next lesson](342-measure-latency-and-allocations-independently.md) · [Browser lesson](../../courses/llm-from-scratch/lessons/341-inject-failures-to-test-transactional-session-state.html)

*Service to Many Leads to Greatness.*
