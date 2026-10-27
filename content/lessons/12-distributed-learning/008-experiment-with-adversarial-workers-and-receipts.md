# Distributed Learning — Lesson 08: Experiment with adversarial workers and receipts

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Track:** Introduction to Distributed Learning and Verifiable AI

## Learning objective

Explain **experiment with adversarial workers and receipts** in plain English, perform a small worked calculation or thought experiment, and distinguish a research hypothesis from a demonstrated system behaviour.

## Understand the idea

A contributor can submit a duplicate, stale, nonfinite, scaled or poisoned update. Each attack needs an explicit detection and rejection test and a defined threat model.

Three essential questions guide every distributed-learning design: *What useful model change was attempted?* *How were data, compute and communication coordinated?* *What evidence supports the final claim?* A training protocol, a blockchain ledger and a model-evaluation procedure answer different questions.

## Worked practical example

The C23 round rejects a duplicate worker identity and mismatched base digest; it does not detect a well-formed poisoned delta. A complete evaluation would add independent hold-out tests and cryptographically verified identities.

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

**Question:** Is a finite vector within the L2 norm limit automatically safe?

<details><summary>Reveal the answer and reasoning</summary>

No. A small harmful update can satisfy the norm constraint while degrading held-out quality.

</details>

## Further reading

- [Practical Secure Aggregation — Bonawitz et al. (CCS 2017)](https://research.google/pubs/practical-secure-aggregation-for-privacy-preserving-machine-learning/)
- [Proof-of-Learning with Incentive Security (2024 preprint)](https://arxiv.org/abs/2404.09005)

## Follow the connected course

[LLM Lesson 384](../10-native-ai/384-defend-against-duplicate-stale-and-poisoned-updates.md) · [Mathematics learning route](../../courses/maths-for-ai/distributed-ai-mathematics.html) · [Distributed Learning course homepage](../../courses/distributed-learning/index.html)

*Service to Many Leads to Greatness.*
