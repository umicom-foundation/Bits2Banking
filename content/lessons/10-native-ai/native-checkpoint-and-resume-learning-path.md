# Learning Path — Native Adapter Checkpoints and Resumable C23 Training

**Bits to Banking · Umicom Foundation · Sammy Hegab**

This reading path takes a learner from the existing native decoder through supervised adapter fine-tuning, secure source admission and exact training continuation. All reusable model and data operations are implemented by **Umicom Framework**; these Markdown pages teach the contracts and calculations without introducing an application-local training runtime.

## Begin with the native foundations

Learn why a frozen decoder and trainable low-rank adapters have different lifetimes in [Transformer projection adaptation](adapt-attention-and-feed-forward-projections.md) and [training the actual decoder](train-transformer-projections-with-response-only-loss.md). Review [response-only training windows](prepare-assistant-response-training-windows.md) so prompts and padding do not contribute to selected loss. [Mathematics Unit 25](../11-maths-for-ai/25-loss-masks-and-next-token-alignment.md) introduces the alignment one token at a time.

## Follow the complete source-to-evidence route

The [reviewed-data preparation lesson](101-review-documents-and-media-for-training.md) explains the authorisation, digest and train/evaluation controls. The companion [native dataset lesson](from-approved-jsonl-to-training-windows.md) shows how approved examples become immutable training windows. The [training experiment lesson](train-with-deterministic-epochs.md) introduces the existing Framework training/evaluation pipeline. These pages describe capabilities, not permission to ingest arbitrary personal, licensed or private material.

## Learn exact checkpoints and restarts

Study the next eight numbered chapters in order:

| Lesson | Concept |
|---|---|
| [95](95-what-an-adapter-checkpoint-must-save.md) | Separate frozen model, adapter and cursor |
| [96](96-build-portable-snapshot-records.md) | Define portable records and checksums |
| [97](97-resume-deterministic-sgd-mid-epoch.md) | Reproduce exact seeded SGD order |
| [98](98-handle-training-failures-and-incomplete-epochs.md) | Handle partial in-memory work and recovery |
| [99](99-verify-restored-training-against-uninterrupted.md) | Compare uninterrupted and resumed results |
| [100](100-run-a-native-checkpoint-and-restart-demo.md) | Build and test the C23 Framework laboratory |
| [101](101-review-documents-and-media-for-training.md) | Prepare and approve training sources |
| [102](102-qualify-model-results-before-promotion.md) | Interpret held-out quality and release limits |

Use [Mathematics Units 33–38](../11-maths-for-ai/index.md) when you need slower explanations of cursor arithmetic, SHA-256 digests, SGD versus AdamW state, weighted loss or byte-count safety.

## Distinguish the claims

The present Framework continuation is an **experimental stateless-SGD** pipeline for the bounded single-block native decoder and selected projection adapters. It is not a large language model, a persistent AdamW trainer, a trusted publisher signature or a fully qualified financial assistant. Run the actual Framework tests before describing a build as integrated and independently authenticate any external checkpoint before restoring it.

For group teaching, use the [adapter checkpoint narration](../../videos/scripts/llm-from-scratch/native-adapter-checkpoint-and-restart.md) and the [document/media review storyboard](../../videos/scripts/llm-from-scratch/review-documents-and-media-before-ai-training.md).
