# Run a held-out multi-layer training experiment

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Licence:** MIT  
**Level:** Progressive native C23 / AI engineering

## Why training loss is insufficient

A decoder can learn to reproduce the small examples it sees repeatedly, yet fail to predict tokens in a different document. This is why the Umicom training workflow separates sources into training and held-out evaluation partitions. The existing Framework admission and reviewed-corpus services are the authority for data-rights approval and source-integrity checks.

The new `UmiAiTrainingStackedExperimentRun` accepts **already reviewed** caller-owned token windows. It checks model shape, token ranges and selected target masks. It also rejects identical original-source SHA-256 values assigned to both train and evaluation; this prevents one exact original source from leaking across partitions. It does not detect semantic paraphrases or grant training rights.

## Repeatable epochs

A local Framework RNG produces a deterministic permutation of training-example indices for each epoch. Held-out examples are never put in that permutation. The experiment evaluates the held-out partition before training, then after each epoch, recording a token-weighted average loss. A short example with three response targets should have three times the weight of a single-target example when combining average cross-entropies.

`UmiAiTrainingStackedExperimentReport` contains aggregate counts and loss measurements, plus an ordered SHA-256 identity for the *supplied token windows*. No prompts, customer details or original filenames are emitted.

## Failure semantics

Preflight rejection performs no training. A failure **after** several updates may leave those valid SGD updates committed; the whole multi-epoch experiment is not automatically transactional. Applications needing all-or-nothing training should snapshot an approved model before running and restore through Framework services upon a reviewed failure.

## Practice

Two examples have mean selected-token losses 1.0 (one target) and 3.0 (three targets). What is the combined selected-token mean?

<details><summary>Worked answer</summary>

Use target counts as weights: `(1 × 1.0 + 3 × 3.0) / (1 + 3) = 10/4 = 2.5`. Averaging the two example means equally would give 2.0 and misrepresent their different target counts.

</details>

---

[Native stacked Transformer reading path](stacked-transformer-learning-path.md) · [Mathematics for AI](../11-maths-for-ai/stacked-transformer-mathematics.md)
