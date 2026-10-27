# Native AI Laboratory — K/V Idle Allocation Reuse

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Language:** C23

## Objective

Observe how a generation-stamped K/V lease pool can retain **reset storage allocations** without retaining prompt histories. The canonical numerical operations remain in Umicom Framework; this laboratory defines tests and expected results, not a second K/V store implementation.

## Laboratory model

Use 2 layers, context 4, channels 8, FP32 and 3 maximum leases. One store occupies `2 × 2 × 4 × 8 × 4 = 512` raw bytes. Choose a 1,024-byte payload budget. Start with the default idle policy of zero and verify that release frees storage. Set idle retention to one and acquire, release, then reacquire a store. The second acquisition should have a newer generation and an empty retained-token history.

## Four regression experiments

| Experiment | Expected invariant |
|---|---|
| Reset and reuse | Old lease is stale; new lease has no retained rows; reuse counter increases. |
| Trim idle | Lowering the idle limit reduces physical bytes without invalidating active leases. |
| Budget pressure | Physical active+idle bytes never exceed the budget; rejected lease output remains unchanged. |
| Cross-pool staleness | Pool identity and generation checks reject foreign and already-released leases. |

## Native execution

The CMake project `framework/learning/native-ai-kv-pool-reuse` registers the existing and additional CTest cases. Build with a C23-capable GCC or Clang compiler, then run CTest to validate all cases. The standalone demo prints active, idle, physical-byte, allocation and reuse counters. No Python or PowerShell implementation is necessary for these features.

## Evidence boundaries

Counted K/V payload excludes process allocator metadata, other native buffers, CPU stack, GPU allocations and model parameters. The idle cache is reset and does not establish cross-session prefix sharing. Additional canonical decoder tests are required for numerical parity. Only controlled whole-request Release benchmarks can establish performance changes.

## Questions

1. Why does a warm allocation still require neural prefill of a new prompt?
2. Which field prevents an old lease from referring to the next owner of a recycled slot?
3. How can active payload fall while physical payload stays constant?

<details><summary>Show answers</summary><p>1. The store was reset; no valid K/V history remains. 2. The lease generation, together with the pool identity, slot and active state. 3. Releasing a store into idle retention moves bytes from the active column to the idle column rather than freeing them.</p></details>

*Service to Many Leads to Greatness.*
