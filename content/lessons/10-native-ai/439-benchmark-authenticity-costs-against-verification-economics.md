# LLM from Scratch — Lesson 439: Benchmark authenticity costs against verification economics

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Language:** UK English · **Native implementation:** C23/Assembly where technically justified

## Learning outcome

Compute and report the overhead of framing, SHA/HMAC verification and quality checks separately.

## Concept and mechanism

HMAC validation is generally far cheaper than model-training replay, but actual CPU cost must be measured. Its total protocol cost also includes bytes sent, secret management and repeated transport retries. Replay of an expensive training step is a different research question from cryptographic message authentication and may dominate verification cost.

## Guided reasoning

1. Measure checksum/HMAC cycles in Release builds.
2. Compare whole-message and per-byte costs.
3. Record packet overhead and RTT at fixed payload sizes.
4. Separately measure independent held-out evaluation and optional training-step replay.
5. Report confidence intervals with seeds and benchmark reproducibility details.

## Worked example

The UMFA wrapper adds 52 bytes. For a two-float result carried by a 224-byte inner UMFW frame, the total is 276 bytes; wrapper overhead is 52/276 ≈ 18.84% of transmitted application payload bytes.

## How this connects to a native software system

The authoritative AI, identity, messaging, cryptographic and numeric contracts belong in **Umicom Framework**. Applications such as Umicom LLM, Studio, RAG and Education consume those capabilities through established APIs, rather than implementing independent maths, secret stores or message parsers. Where a specialised feature is not present, it is an explicitly scoped research or future-development topic—not a claim that all components exist today.

## Correctness and research boundary

Cryptographic overhead measured on a desktop CPU cannot be assumed to match resource-limited RISC-V or a high-concurrency accelerator server.

## Test your understanding

**Question:** Why can a low HMAC verification time coexist with a very expensive useful-learning verifier?

<details><summary>Reveal the worked answer</summary>

HMAC only checks a byte/key relation; usefulness may require held-out model evaluation, robust aggregation or replaying training steps, which are separate computational workloads.

</details>

## Reading and source

- [Proof of Learning: An Incentive-Compatible Blockchain Consensus Mechanism](https://arxiv.org/abs/2007.15145)

## Continue learning

[Course study route](../../courses/llm-from-scratch/authenticated-federated-learning.html)

*Service to Many Leads to Greatness.*
