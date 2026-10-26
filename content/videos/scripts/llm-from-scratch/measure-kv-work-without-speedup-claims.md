# Video lesson — Measure K/V Work Without Inventing a Speedup

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab

## Scene 1 — Three different measurements

**Visual:** Three panels: `Token-layer rows`, `Allocated K/V bytes`, and `Observed wall-clock milliseconds`.

**Narration:** "These three numbers answer three different questions. A token-layer count describes which rows have been requested or retained. A byte count describes raw storage capacity. A millisecond measurement describes elapsed time in a particular execution environment. None can be substituted automatically for either of the others."

## Scene 2 — Calculate before measuring

**Visual:** A four-token context, three layers, two prompt tokens and seven generated samples. Show two single-row appends and four full-window replacements.

**Narration:** "The established conditional prefix planner forecasts sixty stored token-layer rows and eighty-four for the repeated full-context reference. The real K/V storage owner reports its own cumulative row counter. The Framework work-audit service rejects any mismatch between that observed counter and the planner's assumptions."

**On-screen calculation:** `full = 3×4×7 = 84`; `candidate = 3×(2+2+4×4) = 60`.

## Scene 3 — A slower cache is possible

**Visual:** Two fictitious benchmarks with clear `ILLUSTRATIVE ONLY` labels: reference 6.0 ms and candidate 7.2 ms.

**Narration:** "Suppose a cache implementation reduced row work by about twenty-nine per cent, but took seven point two milliseconds rather than six. It is slower despite saving rows. Extra copies, smaller matrix operations, synchronisation and measurement noise can all affect timing. These timings are illustrative numbers, not observations from an Umicom model."

## Scene 4 — Sequence of trustworthy qualification

**Visual:** Four gates: same model identity, matching numerical logits, sound memory ownership, and repeated measured performance.

**Narration:** "A speed comparison is meaningful only when the two algorithms calculate the same task. An optimised multi-layer cache must first agree with the canonical decoder on the relevant vocabulary logits, including immediately after an eviction. Then we can compare repeated timings under matching hardware, configuration and compiler settings. Until then, report a verified storage owner, not a faster LLM."

## Practice

**Question:** A reference uses 84 token-layer rows and a cache candidate uses 60. What share of rows is avoided, and what is the observed speedup?

**Worked answer:** `(84−60)/84 ≈ 28.6%` fewer rows. No speedup can be stated without an actual timing comparison.

## Continue

[Read LLM Lesson 199](../../../lessons/10-native-ai/199-plan-a-fair-k-v-performance-experiment.md) and [Mathematics Unit 104](../../../lessons/11-maths-for-ai/104-distinguish-latency-from-workload.md).

*Service to Many Leads to Greatness.*
