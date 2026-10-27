# Lesson 393 — Design round-scoped native learning jobs

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Implementation approach:** native C23, with Assembly only after justified profiling.  
**Prerequisites:** Lessons 377–392, Mathematics Unit 245.

## Learning outcomes

Explain **design round-scoped native learning jobs**, identify the exact boundary between evidence, model arithmetic and coordination, and design at least one test that can fail. Distinguish implemented Umicom source from suggested research.

## Concept and mechanism

A federated training job is not merely a queue entry. It pins an initial model checkpoint, data-use policy, worker identity, dataset shard and numerical aggregation rule to **one** synchronisation round. All workers in an ordinary FedAvg round must begin from the same tensor layout and base state. The coordinator allocates a finite step and sample budget before any update is considered for aggregation. Different initial checkpoints produce deltas that cannot safely be combined as if they share a common origin.

A correct research system starts with the immutable experiment contract: a common base checkpoint, authorised dataset partitions, an explicit sample-count rule, a deterministic round identifier and a preregistered evaluation metric. Distributed operation also requires stated concurrency, failure and network assumptions. The mathematical candidate resulting from averaging does not become an approved model checkpoint without an independent quality gate.

## Worked scenario

Consider three workers, each given checkpoint hash **A**, 12 local steps and one authorised shard. Worker B returns a delta labelled hash **B** instead. Comparing 32 digest bytes can reject a mismatched label before the numerical stage, but cannot prove that A was honestly used. A genuine training/replay check is needed for the stronger claim.

## What can go wrong?

Treating a well-formed digest as proof of training leads to false trust. Likewise, reporting a worker count without a round identifier makes stale work indistinguishable from fresh contributions.

## Native Umicom engineering connection

The Framework's established `UmiAiTrainingFederatedRound` is the sole numeric FedAvg-delta owner. The additive `UmiAiTrainingFederatedJob` admission component tracks one round of assignments and routes accepted full FP32 deltas through that existing numeric API. It does **not** train remote workers, sign contributions, verify dataset rights, provide Byzantine resilience, implement secure aggregation or run blockchain consensus. The remaining training, checkpoint, messaging and governance functions must be composed from reviewed Framework capabilities rather than duplicated in application code.

Umicom Framework owns the job state; Studio and LLM workbenches only display its inspected state.

## Verification exercise

Reproduce the worked case using synthetic inputs. Then reject an invalid, stale, mismatched or adversarial input without changing the accepted aggregate. Report the exact result and a separate list of work **not measured**: real network RTT, GPU hours, held-out model improvement and privacy guarantee.

**Question:** What must be pinned before a round can combine three workers?

<details><summary>Reveal the worked answer</summary>
<p>The shared base checkpoint and tensor schema, training configuration, permitted dataset shards and a defined round identity. Authorisation and real worker computation are separately checked.</p>
</details>

## Mathematics connection

[Mathematics for AI — Unit 245](../11-maths-for-ai/245-reserve-bytes-for-concurrent-worker-assignments.md) provides a quantitative counterpart.

## Primary reading

- [Federated Averaging — McMahan et al., AISTATS 2017](https://proceedings.mlr.press/v54/mcmahan17a.html)
- [DiLoCo — Distributed Low-Communication Training](https://arxiv.org/abs/2311.08105)

## Continue

[392 — previous lesson](392-capstone-three-node-native-federated-research.md) · [394 — next lesson](394-admit-workers-through-scoped-tickets.md) · [HTML study route](../../courses/llm-from-scratch/federated-job-learning-path.html) · [Introduction to Distributed Learning](../12-distributed-learning/013-bind-one-worker-to-one-round.md)

*Service to Many Leads to Greatness.*
