<!--
Umicom Bits2Banking
File: content/lessons/05-ai/preparing-llm-training-data/09-fine-tuning-adapters-and-checkpoints.md

PURPOSE:
Choose a fine-tuning method and save recoverable state

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Choose a fine-tuning method and save recoverable state

[Course contents](index.md)
Fine-tuning starts from an existing model. Full fine-tuning updates its selected base weights directly. Adapter methods add or train a smaller set of parameters. LoRA, low-rank adaptation, represents certain updates through smaller matrices. It can reduce trainable state, but it still needs the base model and working memory.

1. Record the base model identifier and exact revision, license, tokenizer and template.
2. Choose the task and compatible trainer. Verify that its target modules and adapter format match the architecture.
3. Prepare training and validation partitions and run a formatting/tokenization check on a few examples.
4. Run a short experiment with recorded seed, precision, learning rate and update count.
5. Save model or adapter state together with enough configuration to load it. For exact training resumption, preserve the required optimizer, scheduler, random-generator and data-position state too.
6. Reload in a separate verification step and evaluate held-out examples. A file existing on disk does not prove it can resume or generate correctly.

A checkpoint is a saved state. An adapter checkpoint is not a complete standalone base model. Merging an adapter changes the deployment artifact and may require separate memory and numeric checks. Some inference quantization formats are unsuitable as direct full-training inputs. Compatibility is architecture- and tool-specific.

Learning rate controls update size. Too large can destabilize training; too small can make progress slow. A scheduler changes that rate over time. Loss is a training objective value, not a universal quality score. Overfitting means learning training examples in a way that does not generalize to held-out inputs.


## Exercise

Write a manifest for a hypothetical adapter with base revision, tokenizer revision, dataset version, group-split record and training settings. Leave actual values unknown until measured or selected. Do not invent a “trained successfully” result for a planned experiment.


## Continue learning

[Previous: Plan batches, epochs and memory before training](08-batches-epochs-and-memory.md) · [Course contents](index.md) · [Next: Evaluate changes and publish a reproducible dataset package](10-evaluate-and-publish-a-dataset.md)
