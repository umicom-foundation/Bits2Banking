# Distributed Learning — Lesson 11: Design a LAN/WAN learning experiment

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Track:** Introduction to Distributed Learning and Verifiable AI

## Learning objective

Explain **design a lan/wan learning experiment** in plain English, perform a small worked calculation or thought experiment, and distinguish a research hypothesis from a demonstrated system behaviour.

## Understand the idea

Begin with three simulated local workers, then expand to authorised hosts on a LAN, and then test WAN limitations. Record trained-token counts, quality loss, bytes, elapsed time, failures and power when directly measured.

Three essential questions guide every distributed-learning design: *What useful model change was attempted?* *How were data, compute and communication coordinated?* *What evidence supports the final claim?* A training protocol, a blockchain ledger and a model-evaluation procedure answer different questions.

## Worked practical example

For equal tasks finishing in 20, 50 and 90 seconds, a synchronous coordinator waits at least 90 seconds before accounting for network exchange. Report straggler idle and compare a fair allocation policy.

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

**Question:** Why must a network benchmark measure time to a fixed quality target?

<details><summary>Reveal the answer and reasoning</summary>

Shorter per-step runtime can still correspond to slower or worse learning; quality-normalised time tests the actual training objective.

</details>

## Further reading

- [GeoMesh: Workload-Balanced Geo-Distributed Training (Findings EMNLP 2026)](https://aclanthology.org/2026.findings-emnlp.720/)
- [DiLoCo — Douillard et al. (2023 preprint)](https://arxiv.org/abs/2311.08105)

## Follow the connected course

[LLM Lesson 391](../10-native-ai/391-build-a-falsifiable-low-bandwidth-training-experiment.md) · [Mathematics learning route](../../courses/maths-for-ai/distributed-ai-mathematics.html) · [Distributed Learning course homepage](../../courses/distributed-learning/index.html)

*Service to Many Leads to Greatness.*
