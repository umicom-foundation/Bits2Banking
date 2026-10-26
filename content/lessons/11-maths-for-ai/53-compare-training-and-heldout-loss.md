# Compare training loss with held-out loss

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Licence:** MIT  
**Level:** Gentle mathematics for native AI

## One curve is not enough

A model can minimise the loss on examples it sees repeatedly while becoming worse on new examples. Imagine three epochs. Training losses are 2.2, 1.9, 1.6. Held-out losses are 2.1, 2.0, 2.3. Training improves every epoch, but held-out loss becomes worse in the last epoch.

The *best observed held-out loss* here is 2.0 after the second epoch. That does not automatically mean the application should restore epoch two: the application needs an approved model-selection and checkpoint-promotion policy. The current Umicom stacked experiment reports each epoch's held-out loss; it does not silently publish the best checkpoint or run an unapproved early-stopping rule.

## Why source grouping matters

If many passages come from one original document, splitting them independently can leak nearly identical source text into training and evaluation. Group by the original source, and verify that exact source fingerprints do not cross the partition boundary. For semantic near-duplicates, additional independent review is still needed.

## Why different target counts need weighting

An example with ten selected response tokens contributes ten target losses; an example with one target contributes one. When computing a corpus-wide mean, add the total loss over all selected tokens and divide by the total number of selected tokens, not merely the number of examples.

## Practice

With held-out losses `[1.8, 1.6, 1.7]`, which epoch has the smallest observed loss, and what remains necessary before deployment?

<details><summary>Worked answer</summary>

Epoch two has the lowest observed held-out loss, 1.6. Deployment still needs meaningful quality benchmarks, source and checkpoint trust, safety controls and independent approval. A single lower loss cannot certify the model.

</details>

---

[Mathematics reading path](stacked-transformer-mathematics.md) · [Native LLM course](../10-native-ai/stacked-transformer-learning-path.md)
