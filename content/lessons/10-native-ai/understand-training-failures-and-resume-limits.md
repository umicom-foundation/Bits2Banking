# Training Failures, Early Stopping and Why Resume Needs More Than a Receipt

**Bits to Banking · Umicom Foundation · Sammy Hegab**

## A one-step transaction is not a whole-run transaction

The Framework's existing `UmiAiTrainingSgdStepMany` validates a candidate update before committing all selected adapter weights. That protects one update. It does **not** mean a fifty-step experiment is automatically rolled back when step fifty fails.

The supervised experiment deliberately publishes its aggregate report only on complete success, but successful earlier SGD updates **remain in memory if a later step or evaluation fails**. To determine the true state, query `UmiAiTrainingDecoderProjectionAdapterInspect` and read `completedAdapterSteps`.

An engineering report must not say “the training run was atomically rolled back” merely because the result structure remained unchanged.

## Two scenarios

**Scenario A:** Ten updates are planned. The first seven succeed and the eighth fails due to a numerical rejection. The adapter is already at seven successful updates. The experiment returns an error and leaves the caller's *report output* unchanged, but the adapter has changed. Restarting blindly from the same original seed would not be an exact continuation.

**Scenario B:** Held-out loss falls below a declared threshold after four epochs. The trainer stops early and returns a successful report. That decision measures the **currently available weights**; it does not automatically restore whichever earlier epoch had the best score.

Early stopping and best-checkpoint selection are two separate features.

## A genuine exact-resume contract

An exact restartable training checkpoint needs enough state to continue as if the interruption never occurred. Depending on the optimiser and training design, that can include:

- The frozen base checkpoint and architecture identity.
- Trainable adapter parameter values, projection selection and ranks.
- Optimiser moments for AdamW, or the clearly identified stateless SGD policy.
- Completed optimiser step count, schedule position and loss-scaling policy.
- Source-locked dataset identity and the exact evaluation split.
- Example permutation state, epoch and next-record cursor.
- Checkpoint publication integrity and separately trusted publisher approval.

A receipt containing only counters and loss metrics has none of the missing parameter values. It therefore cannot be promoted into a restore API by renaming it.

## A safe progression for Umicom AI applications

First establish native, deterministic, end-to-end source-to-evaluation behaviour with independent held-out evidence. Next build portable adapter-state snapshots bound to the frozen decoder. Then add exact optimiser-state serialization and replay verification. Finally require trusted publication and regression gates before exposing trained models to Umicom Studio, Trader, Treasury or Banking applications.

Never permit an experimental model to perform live orders, payments or security decisions merely because it completed fine-tuning.

## Practice questions

1. Seven of ten updates succeed before failure. How many updates are retained? **Seven.**
2. Does `outReport` remaining untouched imply the model state is untouched? **No.**
3. Does early stopping restore the lowest-loss checkpoint? **Not without a separate snapshot-and-restore mechanism.**
4. Does an SGD-only resume need AdamW moment tensors? **No, but it still needs adapter weights, precise step/schedule and deterministic data cursor state.**

See [the training epoch lesson](train-with-deterministic-epochs.md) and [receipt evidence](bind-run-receipts-to-source-and-model.md).
