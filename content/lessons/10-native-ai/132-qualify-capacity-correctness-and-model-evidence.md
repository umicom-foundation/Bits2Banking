# Qualify capacity, correctness and model evidence

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Licence:** MIT  
**Level:** Progressive native C23 / AI engineering

## Three different kinds of evidence

A larger layer count is not automatically a better language model. A trustworthy training report should distinguish **capacity evidence** (which shapes and bytes fit), **numerical evidence** (whether logits, gradients and training steps are correct), and **quality evidence** (whether a model performs better on independent, authorised held-out cases).

The Framework scaling planner estimates parameter and hypothetical KV-cache bytes for a proposed shape. The actual stacked model imposes smaller runtime limits inherited from its FP32 tape. `UmiAiTrainingStackedDecoderMemoryInspect` describes tracked tape allocations. Neither estimate alone is proof that a future 24-layer model will fit in RAM or GPU memory.

## An engineering acceptance matrix

| Gate | Meaningful observation | What remains unproved |
|---|---|---|
| Config and shape | Unsupported dimensions rejected | Large-model throughput |
| Deterministic initialisation | Same seed/config → same initial logits | Cross-platform bitwise identity |
| Causality | Shared-prefix logits invariant to later token IDs | Natural-language accuracy |
| Selected cross-entropy | Ignored targets excluded from direct loss | Safe responses |
| Snapshot round-trip | Exact parameter/logit restoration | Trusted publisher |
| Held-out split | Exact original-source collisions rejected | Near-duplicate freedom |
| Repeated rewind | Tape-owned current allocation returns to baseline | Total process/RSS leak freedom |

## Practical acceptance procedure

Run the focused CTest suite against the real Framework checkout, then rerun relevant tests with supported sanitizers. Record the compiler, operating system, model configuration, checkpoint digest, reviewed dataset identity and held-out metric definition. Preserve failures for analysis instead of replacing them with successful-looking partial reports.

No test included with this educational CPU stack certifies a model for autonomous trading, banking, payments or security-critical decisions. Umicom applications should use explicit human approval and existing Framework controls for consequential actions.

## Practice

A model reports lower training cross-entropy and an unchanged held-out loss. What can you conclude?

<details><summary>Worked answer</summary>

The declared training objective improved on training examples. The held-out metric did not show the same improvement. This is not proof of generalisation, safe behaviour or suitability for a production application.

</details>

---

[Native stacked Transformer reading path](stacked-transformer-learning-path.md) · [Mathematics for AI](../11-maths-for-ai/stacked-transformer-mathematics.md)
