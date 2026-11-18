<!--
Umicom Bits2Banking
File: content/lessons/05-ai/generative-ai-foundations/09-memory-checkpoints-and-recovery.md

PURPOSE:
Bound memory and recover image/video training work

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Bound memory and recover image/video training work

[Course contents](index.md)
A training application can run out of memory without having a memory leak. It can also leak memory while using a small model. Peak demand, retained caches, fragmentation and unreleased resources are distinct causes. Diagnose with measurements rather than assuming that Python, C or a particular model name is the sole cause.

1. Measure memory before loading, after loading, during a step, after checkpointing and after unloading. Record host RAM and device memory separately.
2. Bound decoded input queues and preview frames. A loader that reads an entire video corpus into memory can exhaust RAM before the model starts.
3. Use one documented owner for each allocation and an explicit release path on success, failure and cancellation.
4. Checkpoint to a temporary file, verify completion under the storage contract, then publish the new checkpoint. Preserve the last known good checkpoint on failure.
5. Test recovery from an interrupted run using a copy of the checkpoint. Record which state resumes exactly and which is reconstructed.

A memory budget must include weights, gradients, optimizer arrays, activations, input staging and output previews. Reducing precision may lower some terms but not all. Checkpointing activations trades computation for memory. CPU offload changes transfer time and host-memory demand; it does not make the state disappear.

Framework’s bounded dataset services and native file ownership APIs can support these workflows. They do not prove that an entire diffusion trainer is implemented. A C program still needs checked size arithmetic, capacity limits, complete cleanup and regression tests. Never treat an allocation failure as permission to continue with a null pointer or partially filled tensor.


## Check

If memory returns close to baseline after unloading, that is useful evidence but not proof of no leak. Repeat a defined workload and distinguish allocator caching from growing live allocations. Preserve model and workload identities so the result can be reproduced.


## Continue learning

[Previous: Evaluate motion and temporal coherence](08-temporal-coherence-and-video-evaluation.md) · [Course contents](index.md) · [Next: Build a native generative-AI project in verifiable stages](10-native-framework-project-plan.md)
