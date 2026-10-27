# Lesson 406 — Compare full FedAvg with federated LoRA weight-space deltas

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Implementation approach:** native C23, with Assembly only after justified profiling.  
**Prerequisites:** Lessons 377–392, Mathematics Unit 254.

## Learning outcomes

Explain **compare full fedavg with federated lora weight-space deltas**, identify the exact boundary between evidence, model arithmetic and coordination, and design at least one test that can fail. Distinguish implemented Umicom source from suggested research.

## Concept and mechanism

LoRA changes a dense matrix with a low-rank product ΔW=B·A. When separately trained workers use factor pairs Aᵢ,Bᵢ, the correct combined delta is Σpᵢ(BᵢAᵢ), not generally (ΣpᵢBᵢ)(ΣpᵢAᵢ). The distinction matters even when factor shapes and ranks match. A production federated adapter must also pin the base checkpoint, target projections and scale convention.

A correct research system starts with the immutable experiment contract: a common base checkpoint, authorised dataset partitions, an explicit sample-count rule, a deterministic round identifier and a preregistered evaluation metric. Distributed operation also requires stated concurrency, failure and network assumptions. The mathematical candidate resulting from averaging does not become an approved model checkpoint without an independent quality gate.

## Worked scenario

Worker 1 uses A1=+1,B1=+1 and worker 2 A2=−1,B2=−1. Each has ΔW=+1. Averaging the *products* yields +1. Averaging factors yields A=0,B=0, hence ΔW=0. A very small example exposes a serious aggregation error.

## What can go wrong?

Treating every adapter as a free-standing model may produce incompatible target modules or hidden scale differences. Never promise that heterogeneous ranks merge by naive elementwise averaging.

## Native Umicom engineering connection

The Framework's established `UmiAiTrainingFederatedRound` is the sole numeric FedAvg-delta owner. The additive `UmiAiTrainingFederatedJob` admission component tracks one round of assignments and routes accepted full FP32 deltas through that existing numeric API. It does **not** train remote workers, sign contributions, verify dataset rights, provide Byzantine resilience, implement secure aggregation or run blockchain consensus. The remaining training, checkpoint, messaging and governance functions must be composed from reviewed Framework capabilities rather than duplicated in application code.

Umicom Framework’s federated-round API already accepts full weight-space deltas; advanced rank-aware compression is future research.

## Verification exercise

Reproduce the worked case using synthetic inputs. Then reject an invalid, stale, mismatched or adversarial input without changing the accepted aggregate. Report the exact result and a separate list of work **not measured**: real network RTT, GPU hours, held-out model improvement and privacy guarantee.

**Question:** Which quantity is safe to average under a declared FedAvg weight-space objective?

<details><summary>Reveal the worked answer</summary>
<p>Compatible, properly scaled weight-space deltas from the same base model; raw low-rank factors require a mathematically justified aggregation protocol.</p>
</details>

## Mathematics connection

[Mathematics for AI — Unit 254](../11-maths-for-ai/254-derive-lora-product-vs-factor-average.md) provides a quantitative counterpart.

## Primary reading

- [LoRA — Low-Rank Adaptation, Hu et al.](https://arxiv.org/abs/2106.09685)
- [SDFLoRA — Selective Decoupled Federated LoRA (IJCAI 2026)](https://ijcai.org/proceedings/2026/533)

## Continue

[405 — previous lesson](405-evaluate-verification-challenges-and-replay-cost.md) · [407 — next lesson](407-reproduce-lan-wan-training-with-authorised-fixtures.md) · [HTML study route](../../courses/llm-from-scratch/federated-job-learning-path.html) · [Introduction to Distributed Learning](../12-distributed-learning/013-bind-one-worker-to-one-round.md)

*Service to Many Leads to Greatness.*
