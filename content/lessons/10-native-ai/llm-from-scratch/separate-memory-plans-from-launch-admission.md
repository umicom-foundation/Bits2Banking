<!--
Umicom Bits2Banking
File: content/lessons/10-native-ai/llm-from-scratch/separate-memory-plans-from-launch-admission.md

PURPOSE:
Separate memory plans from launch admission

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Separate memory plans from launch admission

[Course contents](../../../courses/llm-from-scratch/index.html)
A plan describes what a calculation predicts from supplied facts. Admission decides whether a real operation may begin now. Combining them into a single green indicator can hide missing costs, stale observations or unsupported model layouts. Framework keeps those conditions explicit.


## 1. Identify the evidence

Declared weights, cache, workspace and runtime costs are estimates supplied by the caller. A desktop memory snapshot is an observation captured at a particular time. Its available memory can change immediately because other programs are active. A successful snapshot call does not reserve those bytes for the model.


## 2. Handle unknown values correctly

Unknown does not mean zero. If the loading workspace has not been measured or estimated, mark that component absent from the known-components mask and keep its numeric field zero. The assessment can then report INCOMPLETE. Filling in a convenient zero and marking it known would produce misleading evidence.

~~~text
known cost of zero: caller has evidence that this component needs no extra bytes
unknown cost: caller has no reliable value

These two states must not share the same interpretation.
~~~


## 3. Check freshness and provenance

A fixture is synthetic data used for testing. It cannot establish the machine's current capacity. A stale snapshot was captured too long ago for the chosen policy. The caller measures elapsed age using its monotonic clock and passes that age to the assessment. A monotonic clock measures intervals without following wall-clock corrections. Do not subtract timestamps from unrelated clock origins.


## 4. Distinguish CPU and GPU memory

Dedicated device memory is not interchangeable with CPU RAM. Integrated graphics may share system RAM, so counting it again as extra capacity double-counts the same resource. Device allocations, offloading and backend-specific peaks require their own contracts. The current dense CPU planning API does not grant GPU admission.


## 5. Investigate a real failure

1. Record the process, model identifier, backend, requested context and operation.
2. Capture the actual error or crash evidence if available.
3. Separate allocation refusal, process termination, driver failure and application exception.
4. Compare declared costs with observed peaks under a repeatable workload.
5. Fix the demonstrated cause and add a regression that exercises it.

A computer crash alone does not prove a leak. Large valid allocations, insufficient pagefile capacity, a driver fault or unrelated activity can produce different failures. Native C gives precise control over allocation and ownership, but it also requires explicit bounds, cleanup and overflow checks. Language choice is not a substitute for those practices.

Exercise: the dense cache fits a 512 MiB budget, but weights need 8 GiB and workspace is unknown. Is the model safe to load? There is not enough evidence. The cache plan answers one component question; the complete assessment must remain incomplete until the missing costs and current capacity are known.


[Previous lesson](plan-context-from-a-cache-budget.md)
