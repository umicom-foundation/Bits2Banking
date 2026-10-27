# Distributed Learning — Lesson 06: Network latency, bandwidth and compressed updates

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Track:** Introduction to Distributed Learning and Verifiable AI

## Learning objective

Explain **network latency, bandwidth and compressed updates** in plain English, perform a small worked calculation or thought experiment, and distinguish a research hypothesis from a demonstrated system behaviour.

## Understand the idea

Poor Internet links favour methods that take more local steps before synchronising and exchange smaller updates. DiLoCo, OpenDiLoCo and GeoMesh each study aspects of this problem.

Three essential questions guide every distributed-learning design: *What useful model change was attempted?* *How were data, compute and communication coordinated?* *What evidence supports the final claim?* A training protocol, a blockchain ledger and a model-evaluation procedure answer different questions.

## Worked practical example

A 128 KiB payload on an effective 10 Mbps link takes ~105 ms to serialize before protocol overhead. An additional 150 ms RTT raises the idealised transaction to ~255 ms.

A learner can reproduce the arithmetic using a calculator and study the relevant native C23 model-delta laboratory. Where a complete distributed protocol is not implemented, the example is explicitly a simulation or design exercise rather than a claim of running remote worker nodes.

## Build the conceptual model

1. Identify the starting model/checkpoint and what the worker actually receives.
2. Separate source permissions, sample counts and numerical parameters.
3. Name the expected output and its ownership: a delta, a candidate model or an evidence receipt.
4. Introduce one realistic failure: stale updates, packet loss, heterogeneous hardware, adversarial claims or evaluation leakage.
5. Decide what the native Framework can validate automatically and what demands a trusted reviewer or independent experiment.

## Think about privacy and trust

A source checksum, signature, network message and model-quality score are separate pieces of evidence. Private or financial data cannot be admitted for training merely because a worker has access to it. Federated learning does not, by itself, guarantee that a released update reveals nothing about local data.

## Self-assessment

**Question:** Why may more local steps still worsen the result despite lower network traffic?

<details><summary>Reveal the answer and reasoning</summary>

Worker models can drift under non-IID data; fewer messages do not guarantee equivalent or faster quality convergence.

</details>

## Further reading

- [DiLoCo — Douillard et al. (2023 preprint)](https://arxiv.org/abs/2311.08105)
- [GeoMesh: Workload-Balanced Geo-Distributed Training (Findings EMNLP 2026)](https://aclanthology.org/2026.findings-emnlp.720/)

## Follow the connected course

[LLM Lesson 381](../10-native-ai/381-compare-local-sgd-diloco-and-sync-cadence.md) · [Mathematics learning route](../../courses/maths-for-ai/distributed-ai-mathematics.html) · [Distributed Learning course homepage](../../courses/distributed-learning/index.html)

*Service to Many Leads to Greatness.*
