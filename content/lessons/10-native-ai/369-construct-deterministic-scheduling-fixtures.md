# Lesson 369 — Construct deterministic scheduling fixtures

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Language:** Native C23 · **Prerequisites:** Lessons 329–360 and Mathematics Unit 221.

## Learning outcome

Use reproducible request sequences to test admission, fairness and failure behaviour.

## Technical foundations

A scheduling fixture needs only request IDs, declared step budgets, admission actions and expected dispatch order. It does not need pseudo-random neural data. Keep the canonical decoder tests separate: those check logits, sampled IDs, attention masks and K/V positions against actual checkpoint data. For scheduler tests use bounded model geometry, a real pool when available and explicit assertions about request state transitions and memory reservations.

## Worked scenario

Fixture: three requests [101:2, 202:2, 303:1], two available K/V stores. Admit 101 and 202; third admission encounters backpressure. Dispatch/acknowledge 101,202,101,202; then admit and finish 303. This verifies the sequence [101,202,101,202,303], total five acknowledgements and three completed requests.

## Boundary conditions and failure modes

A test that compares only the final number of completed requests can miss an unfair selection policy. Preserve and inspect the exact intermediate order, stale-ticket rejection, memory budget and idle-store counters. A test double must never be reported as genuine full-Framework integration.

## Practical native Framework exercise

Turn the fixture into a table with columns Event, Queued, Ready, InFlight, PoolActive and ExpectedStatus. Add a failing admission and confirm caller-owned output is byte-for-byte unchanged.

### Relevant native interfaces

The established `UmiAiTrainingStackedKvPool` owns K/V allocations. The additive `UmiAiTrainingStackedKvScheduler` manages queue metadata, admission and cooperative dispatch; its `Dispatch` result is **not** a sampled token. Use `UmiAiTrainingStackedKvSchedulerSubmit`, `AdmitNext`, `Dispatch` and `Acknowledge` under the borrowed-pool lifetime contract. Correct model execution remains inside the canonical stacked decoder and its K/V services.

## Check your understanding

**Question:** Which counters prove exact fairness?

<details><summary>Show worked answer</summary>

Counters alone do not. The recorded dispatch sequence and the defined slot-rotation policy establish ordering for the fixture.

</details>

## Mathematics connection

See [Unit 227](../11-maths-for-ai/227-understand-generation-count-identity-limits.md).

## External research for context

- [Orca: iteration-level scheduling for Transformer serving (OSDI 2022)](https://www.usenix.org/conference/osdi22/presentation/yu)
- [vLLM: PagedAttention and LLM serving (2023)](https://arxiv.org/abs/2309.06180)

## Continue learning

[HTML study route](../../courses/llm-from-scratch/kv-scheduling-learning-path.html) · [Previous lesson](368-cancel-queued-and-ready-sessions-safely.md)

*Service to Many Leads to Greatness.*
