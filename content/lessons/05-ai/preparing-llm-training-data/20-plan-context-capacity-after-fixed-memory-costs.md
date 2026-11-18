<!--
Umicom Bits2Banking
File: content/lessons/05-ai/preparing-llm-training-data/20-plan-context-capacity-after-fixed-memory-costs.md

PURPOSE:
Plan context capacity after fixed memory costs

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Plan context capacity after fixed memory costs

[Course contents](index.md)

## Connect a dataset decision to a memory question

A dataset can contain long documents, short questions or multi-turn conversations. Before choosing a context length, you need to understand what that length means for the backend that will process the tokens. This lesson uses a dense inference key/value cache as a concrete arithmetic exercise. It does not calculate the complete memory cost of training. The purpose is to learn how to account for known costs, preserve unknown information and avoid treating a model file size as a promise that the model will fit.

You will run a small native C program using the existing Framework memory services. It asks for a cache capacity of 4096 tokens in each of two sequences, subtracts declared fixed costs from a synthetic host-memory observation and finds a capacity of 3072. It then shows why stale observations, fixtures and unknown costs must not produce an apparently trustworthy plan. No model is downloaded or loaded by this exercise.


## Learn the units and objects

A byte is a unit of storage containing eight bits on the platforms covered by this exercise. A kibibyte, written KiB, is 1024 bytes. A mebibyte, MiB, is 1024 KiB, and a gibibyte, GiB, is 1024 MiB. These binary units differ from decimal KB, MB and GB. Keep the unit next to each number. The C API uses unsigned 64-bit integer byte counts so that the arithmetic does not silently round a large count through floating point.

A token is an item in a model tokenizer vocabulary. It is not reliably one character, one word or one byte. A context capacity is the maximum token positions a backend is prepared to keep for a sequence. A sequence is one independent stream of positions; two simultaneous sequences can need two sets of cache storage. A key/value cache stores attention-related arrays so that an inference backend can reuse past computation. It does not store the same thing as a vector database used for retrieval.


## Write the fixed costs first

1. Start with the synthetic available-memory observation: 8 GiB. The synthetic machine total is 16 GiB, but this calculation uses the available amount, not the full installed amount.
2. Declare resident weights as 6 GiB. This is a supplied resident-memory estimate, not a number inferred from a downloaded file size.
3. Declare workspace as 512 MiB and runtime overhead as 256 MiB. These are illustrative values, not universal overhead formulas.
4. Set aside a 512 MiB host reserve. This reserve reduces the arithmetic budget once; it does not reserve operating-system pages.
5. Add these fixed costs: 6144 + 512 + 256 + 512 = 7424 MiB. Subtract from 8192 MiB available to leave 768 MiB for the dense cache.

A real estimate must explain what each field includes. Temporary conversion buffers, loading peaks, alignment and allocator overhead cannot simply disappear because they are inconvenient to estimate. If a required component is unknown, leave its known bit unset and its numeric field zero. That zero represents an absent value, not a claim that the component is free. The planner keeps the assessment incomplete until the required non-cache components are supplied.


## Calculate the dense cache cost independently

The example shape has two sequences, 32 layers, eight key heads, eight value heads, 128 dimensions in each head and two bytes per stored element. A head is one group of attention features; the shape explicitly describes the backend layout instead of assuming all models use identical attention geometry. Key and value dimensions and element sizes can differ, which is why the API keeps them separate.

~~~text
bytes per token = sequences × layers ×
    (key heads × key dimensions × key element bytes
     + value heads × value dimensions × value element bytes)

= 2 × 32 × (8 × 128 × 2 + 8 × 128 × 2)
= 262144 bytes = 256 KiB

affordable capacity = floor(768 MiB / 256 KiB) = 3072 tokens
~~~

The capacity is per sequence for this shape; the bytes-per-token term already includes both sequences. Do not multiply by the sequence count a second time. The requested maximum remains 4096. The selected capacity is the smaller of the request and the affordable count. In this example the request does not fit, even though a smaller arithmetic plan exists. Reducing context can change which records fit your data pipeline, so it is a visible configuration decision rather than a hidden repair.


## Read the native API contract

~~~c
UmiModelHostKvPlan plan;
UmiStatus status = UmiModelDenseKvPlanHostMemory(
    &non_cache_costs, &shape, snapshot,
    age_millis, maximum_age_millis, host_reserve_bytes, &plan);

if (status != UMI_STATUS_OK) {
    /* Invalid inputs or arithmetic overflow: do not read a new plan. */
} else if (!plan.cache_plan_available) {
    /* Inspect plan.fixed_memory.verdict to explain the missing plan. */
} else {
    /* Inspect token count and request_fits; this is still not a launch grant. */
}
~~~

The non-cache requirements must contain neither a cache value nor the cache-known bit. This prevents the same cache from being counted twice. Internally the function assesses the fixed costs with a known-zero cache, uses the resulting remainder with UmiModelDenseKvPlanTokens, then assesses the selected cache cost through UmiModelMemoryAssess. The application does not need its own copies of freshness, reserve and overflow rules.

The return status and the report answer different questions. UMI_STATUS_OK means the input was processed into a valid report. cache_plan_available says whether the report contains a cache plan. Even when that flag is true, affordable_tokens can be zero. A zero-capacity arithmetic answer is not a usable model context. selected_memory and cache are meaningful only when that flag is true; otherwise fixed_memory explains the absence.


## Configure and run the source-linked exercise

~~~powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S labs/framework/host-cache-budget -B build/host-cache-budget -G Ninja -DUMICOM_FRAMEWORK_SOURCE=C:/umicom/Umicom-Applications/framework
cmake --build build/host-cache-budget --parallel 2
ctest --test-dir build/host-cache-budget --output-on-failure --no-tests=error
~~~

1. Open PowerShell in the Bits2Banking checkout. Confirm that the matching primary Framework checkout contains the new memory-plan declaration and implementation.
2. Configure the small lesson with UMICOM_FRAMEWORK_SOURCE pointing to that checkout. This exercise links canonical source directly and does not install or qualify a packaged SDK.
3. Build the lesson, then run its CTest check. Execute each command separately and stop on errors.
4. Use -V with CTest if you want to see the printed report. Compare the expected values below with your own output.

The expected request is 4096, the affordable capacity is 3072, the per-token cost is 262144 bytes across both sequences and the selected cache is 805306368 bytes. These are synthetic arithmetic results. The program does not report that your computer currently has 8 GiB available. Its later checks explicitly mark the observation as a fixture, make its age stale and remove the runtime-cost estimate; each case should produce no token plan.


## Understand freshness and fixtures

A memory observation describes a moment. Another process can allocate memory after that moment. Supply its age from a compatible monotonic elapsed-time measurement and choose a nonzero maximum acceptable age. Do not mix clock origins or turn a stale observation into a current one by setting its age to zero. A fixture is a stored or synthetic observation used for testing. It is valuable for reproducible arithmetic tests but cannot establish current host capacity.

A failure to obtain the memory component makes it unavailable even if other system metrics succeeded. Conversely, a failed CPU metric does not automatically invalidate an independently successful memory component. This is why the existing snapshot exposes separate component statuses. The new planner respects those statuses; it does not guess availability from an unrelated top-level success or from a numeric field left in a failed snapshot.


## Separate inference planning from training planning

An inference KV cache is only one memory owner. Training can additionally require gradients, optimizer state, saved activations, temporary tensors and checkpoint buffers. Their sizes depend on the model, precision, optimizer, batch shape, checkpointing strategy and backend. Do not use the 3072-token result as a training limit. Use the earlier training-capacity and loss-mask lessons to identify those owners, then measure the actual implementation under a bounded experiment.

Likewise, an image or video generator can have very different arrays: latent frames, attention states, image tensors, decoder buffers and temporal intermediates. The dense text-cache shape is not a universal multimedia estimator. A backend-specific plan should identify each real allocation owner and reuse the Framework checked arithmetic where appropriate. Shared GPU memory is part of system memory, not an extra pool that can be counted twice.


## Apply the result to dataset preparation

Keep token-length statistics after applying the actual tokenizer and chat template. A raw document byte count cannot determine whether its final record fits the chosen context. If a record is too long, choose a documented policy such as splitting at reviewed boundaries, shortening selected content or using a longer-capacity backend. Preserve source identity and related-record partition rules after splitting so that nearly identical chunks do not leak across evaluation and training partitions.

Changing context capacity should not silently alter the supervised target. For example, cutting a conversation may remove the instruction while leaving an answer, or remove the answer while preserving only the prompt. Review the aligned tokens, labels and loss mask after the actual transformation. A memory plan is an input to that decision; it is not a data-quality validator.


## Practice and recovery

1. Recalculate the cache capacity for one sequence while keeping the same fixed costs. The per-token cache cost halves, but the request still caps the selected capacity at 4096.
2. Reduce synthetic available memory below the fixed total. Predict an insufficient fixed-memory verdict and no token plan.
3. Set available memory exactly equal to the fixed total. Predict an available arithmetic plan with zero affordable tokens, which is not usable for inference.
4. Remove one known non-cache component rather than setting a guessed value. Confirm the report remains incomplete.
5. If compilation reports a missing API, reconcile the selected Framework source and headers. If a test reports a different number, compare every byte unit and shape field before changing expected results.


## Further reading

- [Complete host/cache C exercise](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/framework/host-cache-budget/main.c)
- [Exercise build and recovery guide](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/framework/host-cache-budget/README.md)
- [Framework memory-planning API contract](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/local_models/memory_plan.h)
- [Framework host/cache regression cases](https://github.com/umicom-foundation/umicom-framework/blob/main/tests/local_models/test_host_kv_plan.c)

[Previous: Keep memory observations honest before training](19-keep-memory-observations-honest.md)

[Next: Separate attention masks from loss masks](21-separate-attention-and-loss-masks.md)
