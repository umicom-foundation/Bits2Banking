# Distributed Learning — Lesson 04: Understand model merging and non-IID data

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Track:** Introduction to Distributed Learning and Verifiable AI

## Learning objective

Explain **understand model merging and non-iid data** in plain English, perform a small worked calculation or thought experiment, and distinguish a research hypothesis from a demonstrated system behaviour.

## Understand the idea

Separately trained models can have incompatible parameter interpretations. Federated learning normally coordinates updates from an identical base; non-IID datasets can still make useful updates disagree.

Three essential questions guide every distributed-learning design: *What useful model change was attempted?* *How were data, compute and communication coordinated?* *What evidence supports the final claim?* A training protocol, a blockchain ledger and a model-evaluation procedure answer different questions.

## Worked practical example

If A sees 90% programming and B 90% finance, a global score may improve even while finance quality regresses. Preserve per-domain evaluation before accepting a new checkpoint.

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

**Question:** Why should a finance adapter not be blindly averaged with an independently initialised OS model?

<details><summary>Reveal the answer and reasoning</summary>

Their parameters need not represent the same functions or starting state; valid federation requires a declared compatibility and aggregation contract.

</details>

## Further reading

- [FedAvg — McMahan et al. (AISTATS 2017)](https://proceedings.mlr.press/v54/mcmahan17a.html)
- [Federated Low-Rank Adaptation Survey (IJCAI 2025)](https://ijcai.org/proceedings/2025/1196)

## Follow the connected course

[LLM Lesson 380](../10-native-ai/380-understand-non-iid-client-data-and-bias.md) · [Mathematics learning route](../../courses/maths-for-ai/distributed-ai-mathematics.html) · [Distributed Learning course homepage](../../courses/distributed-learning/index.html)

*Service to Many Leads to Greatness.*
