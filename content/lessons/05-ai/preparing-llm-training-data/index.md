![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Preparing Data for LLM Training


## Foundations and practice

Distinguish retrieval from training, review documents, choose record formats and preserve independent evaluation groups before tokenization.

A text editor is enough for the early exercises. The native group-partition lab needs CMake, a C23 compiler and the matching Framework source checkout; no model download is required.

1. [Choose retrieval, fine-tuning or training from scratch](01-choose-retrieval-or-training.md)
1. [Turn documents into reviewed text without losing provenance](02-turn-documents-into-reviewed-text.md)
1. [Read JSON, JSONL and conversational records](03-json-jsonl-and-chat-records.md)
1. [Review quality, duplicates and allowed use](04-quality-deduplication-and-rights.md)
1. [Keep related sources out of different partitions](05-split-sources-before-chunking.md)
1. [Run a native Framework dataset-partition lab](06-run-the-framework-group-lab.md)
1. [Understand tokens, chat templates and loss masks](07-tokenization-templates-and-masks.md)
1. [Plan batches, epochs and memory before training](08-batches-epochs-and-memory.md)
1. [Choose a fine-tuning method and save recoverable state](09-fine-tuning-adapters-and-checkpoints.md)
1. [Evaluate changes and publish a reproducible dataset package](10-evaluate-and-publish-a-dataset.md)

## Native input validation

11. [Validate training records with native Framework code](11-read-jsonl-with-native-framework.md)

## Further practical exercises

1. [Count bytes, rows and source groups before tokenization](12-count-bytes-rows-and-source-groups.md)

1. [Inspect a local JSONL file before choosing a trainer](13-inspect-a-local-jsonl-file.md)

1. [Turn reviewed source IDs into a reproducible partition](14-partition-jsonl-by-source.md)

1. [Turn reviewed partitions into complete JSONL buffers](15-serialize-reviewed-partitions.md)

1. [Choose which predictions contribute to loss](16-choose-which-predictions-contribute-to-loss.md)

1. [Follow data ownership during import](17-follow-data-ownership-during-import.md)

1. [Train selected decoder targets without hiding the prompt](18-train-selected-decoder-targets.md)

1. [Keep memory observations honest before training](19-keep-memory-observations-honest.md)

1. [Plan context capacity after fixed memory costs](20-plan-context-capacity-after-fixed-memory-costs.md)

1. [Separate attention masks from loss masks](21-separate-attention-and-loss-masks.md)

1. [Train a decoder with padded examples](22-train-a-decoder-with-padded-examples.md)

1. [Keep optimizer memory when training selected tokens](23-keep-optimizer-memory-for-selected-tokens.md)

1. [Accumulate uneven selected microbatches without changing their weight](24-accumulate-uneven-selected-microbatches.md)

1. [Shuffle an epoch without changing the split](25-shuffle-an-epoch-without-changing-the-split.md)

1. [Count selected predictions before calculating percentages](26-count-selected-predictions-before-percentages.md)

1. [Prepare a byte pair without shifting twice](27-prepare-a-byte-pair-without-shifting-twice.md)

1. [Find repeated pairs across training and evaluation](28-find-repeated-pairs-across-training-and-evaluation.md)

1. [Check context fit before training a byte model](29-check-context-fit-before-training-a-byte-model.md)

1. [Stream records without retaining the whole file](30-stream-records-without-retaining-the-whole-file.md)

1. [Review one snapshot before using a split](31-review-one-snapshot-before-using-a-split.md)

1. [Measure token loss with the right denominator](32-measure-token-loss-with-the-right-denominator.md)

1. [Aggregate evaluation with checked summaries](33-aggregate-evaluation-with-checked-summaries.md)
