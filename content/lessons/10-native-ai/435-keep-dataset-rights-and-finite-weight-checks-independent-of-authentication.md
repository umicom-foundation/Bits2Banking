# LLM from Scratch — Lesson 435: Keep dataset rights and finite-weight checks independent of authentication

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Language:** UK English · **Native implementation:** C23/Assembly where technically justified

## Learning outcome

Understand the ordering of security, numerical and governance gates.

## Concept and mechanism

Federated learning differs from ordinary public dataset aggregation because worker data may be confidential. A correct sender tag cannot certify source rights. The numeric delta must be finite, have the correct dimension and satisfy accepted norm limits; its expected effect on a held-out dataset must be evaluated independently before new checkpoint publication.

## Guided reasoning

1. Resolve the source manifest and data-policy scope.
2. Validate stable worker/base/shard commitments.
3. Decode only finite FP32 values.
4. Use Framework FederatedRound norm and sample-weighted aggregation.
5. Compare checkpoint quality against an immutable held-out control.

## Worked example

A legitimate worker sends a perfectly authenticated result with an infinite FP32 value. The canonical wire decoder refuses it. A worker sending a finite but adversarial +100 vector may pass the wire decoder but fail the existing norm bound.

## How this connects to a native software system

The authoritative AI, identity, messaging, cryptographic and numeric contracts belong in **Umicom Framework**. Applications such as Umicom LLM, Studio, RAG and Education consume those capabilities through established APIs, rather than implementing independent maths, secret stores or message parsers. Where a specialised feature is not present, it is an explicitly scoped research or future-development topic—not a claim that all components exist today.

## Correctness and research boundary

No such test proves statistical utility. Even a small norm update can quietly bias a model.

## Test your understanding

**Question:** Why is it necessary to check both training permissions and numerical validity?

<details><summary>Reveal the worked answer</summary>

They answer different questions: permission controls whether data and workers may participate; numeric checks control whether a submitted vector is well formed and within admissible limits.

</details>

## Reading and source

- [Bonawitz et al., Practical Secure Aggregation for Privacy-Preserving Machine Learning](https://arxiv.org/abs/1611.04482)

## Continue learning

[Course study route](../../courses/llm-from-scratch/authenticated-federated-learning.html)

*Service to Many Leads to Greatness.*
