# KV session lifecycle laboratory

The learner builds the Umicom Framework native C23 `stacked_kv_pool` component, then runs four focused CTest cases covering lease lifecycle, finite memory budget, learned-position rollover and rejected operations. The pool owns **independent instances** of the existing stacked K/V store; it does not replace attention mathematics or decode a trained model itself.

## Worked scenario

Two Transformer layers, four context positions, eight channels, two attention heads and FP32 storage reserve `2 × 2 × 4 × 8 × 4 = 512` bytes per session. With three slots and a 1,024-byte raw K/V budget, only two sessions can be active. A third request is rejected without changing the caller's lease. After release, a fresh lease can reuse the slot only under a **new generation**.

## Experiment

1. Calculate the per-session raw storage and compare it with `UmiAiTrainingStackedKvPoolStats.rawKvBytesPerSession`.
2. Acquire two leases, reject the third and inspect the reserved bytes.
3. Prefill a valid prompt, append a new token and read its K/V vectors.
4. Reach the context boundary and reject an invalid shift before applying a complete legitimate rollover.
5. Release and reacquire a slot; confirm that its old lease cannot operate on the newly acquired store.
6. Identify observations that remain outside the exercise: allocator overhead, process RSS, full-model numerical parity, true concurrent access and measured inference speed.

## C23 laboratory location

The CMake entry point is `Umicom-Applications/framework/learning/native-ai-kv-session-pool/CMakeLists.txt`. Its tests use the real Framework store and planner when built against the complete source tree. The standalone exercise does not copy their algorithms into Bits2Banking.

The HTML reading route is [KV Session Ownership and Lifecycle](../../../content/courses/llm-from-scratch/kv-session-lifecycle-learning-path.html).
