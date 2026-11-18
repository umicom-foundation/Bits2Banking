<!--
Umicom Bits2Banking
File: content/lessons/05-ai/preparing-llm-training-data/08-batches-epochs-and-memory.md

PURPOSE:
Plan batches, epochs and memory before training

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Plan batches, epochs and memory before training

[Course contents](index.md)
A batch is a group of examples processed together. A training step computes predictions, measures error, computes gradients and updates parameters. A gradient describes how a small parameter change affects the objective. An optimizer applies an update rule. An epoch is one pass through the defined training dataset, though sampling and streaming can change how that is counted.

Training needs more memory than storing weights alone. Activations are intermediate values saved for gradient computation. Gradients and optimizer state also take space. The dataset loader, token buffers, decoded images and temporary workspaces add to the total. Inference estimates are not training estimates.

1. Write down available RAM and accelerator memory, model parameter representation, sequence length or image dimensions, and expected batch size.
2. Reserve headroom for the operating system, application and temporary buffers. Do not allocate to the advertised hardware maximum.
3. Start with one tiny batch and a short controlled run. Measure peak memory, step time and loss values.
4. If memory is insufficient, reduce batch size or sequence dimensions, use supported precision/checkpointing methods, or choose a smaller model.
5. Record every change. Comparing two runs with different token lengths or hardware without noting it can give a false speedup claim.

Gradient accumulation combines contributions from several microbatches before an update. It can reduce peak activation memory but does not make parameter and optimizer storage disappear. Mixed precision changes numeric representation and needs numerically appropriate handling. Activation checkpointing recomputes selected intermediates to trade time for memory.


## Check

Four accumulated microbatches are not necessarily identical to a single large batch when stochastic layers, normalization or data order differ. Keep the learning objective and optimizer settings explicit. A C implementation still needs bounded allocations and measurements; changing the implementation language does not shrink the model’s mathematical state automatically.


## A training-run worksheet

| Quantity | Example question |
| --- | --- |
| Microbatch size | How many examples are simultaneously active? |
| Sequence length | How many token positions are processed? |
| Accumulation steps | How many microbatches contribute to one update? |
| Optimizer state | Which extra arrays does this optimizer maintain? |
| Peak memory | What was measured, not merely estimated? |

## Continue learning

[Previous: Understand tokens, chat templates and loss masks](07-tokenization-templates-and-masks.md) · [Course contents](index.md) · [Next: Choose a fine-tuning method and save recoverable state](09-fine-tuning-adapters-and-checkpoints.md)
