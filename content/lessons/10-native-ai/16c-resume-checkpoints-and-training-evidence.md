# Supplement 16C — Resume Native Training and Verify Its Evidence

**Bits to Banking · Build Your Own LLM from Scratch · Umicom Foundation**  
**Author and project originator:** Sammy Hegab  
**Primary implementation:** C23 in Umicom Framework

## Learning objective

Demonstrate the difference between saving a trained model and **reproducing the exact continuation of its training**. Verify that an interrupted-and-resumed run produces identical parameter bytes to uninterrupted training when the complete plan and source data remain unchanged.

## 1. A checkpoint is more than a model file

A checkpoint stores enough decoder state to restore its parameters and completed optimisation-step count. The Framework's existing `UmiAiTrainingDecoderCheckpointEncode`, `Decode`, `SaveNewFile` and `LoadFile` functions own the binary format, bounds checks and checksum.

Batch 07 does not invent another model format. Instead, `UmiAiTrainingExperimentResume` first validates the supplied checkpoint's architecture, clones the existing decoder **through the established codec**, and continues training the independent clone.

The caller's checkpoint model remains unchanged. This matters because the original checkpoint is evidence of the earlier state and must remain available for inspection and comparison.

## 2. Why the absolute step number matters

In the source-code experiment, a sample is determined from the immutable dataset, partition, seed and *absolute optimiser-step number*.

An uninterrupted four-step run samples batches for steps 0, 1, 2 and 3 (zero-based sampling indexes). If we save after two optimiser steps, the resumed model must sample **batch numbers 2 and 3**. Restarting at batch number 0 would silently change the experiment, even if all other parameters were identical.

The Framework uses the current checkpoint step count to preserve that order. In a deterministic CPU experiment, it can therefore compare two complete checkpoint files byte-for-byte after the same number of total optimisation steps.

## 3. What a checkpoint cannot prove

The current educational checkpoint contains model state, but it **does not bind the original dataset manifest, source-file fingerprints, learning rate, training seed or evaluation seed**. Therefore the application or operator must establish that these have not changed before approving a resume.

This is a real engineering limitation; we should not disguise it. A future native experiment receipt can record and verify these identities before resumption is authorised. A noncryptographic checksum is not a digital signature; it cannot prove that a checkpoint came from a trustworthy source.

Never resume from an untrusted checkpoint, nor claim deterministic replay across unrelated hardware, compilers or floating-point backends without comparing those environments experimentally.

## 4. Exercise: save a new checkpoint

Start with the same reviewed fixture plan described in [Supplement 16B](16b-reproducible-native-training-experiments.md). Use an output path that does **not already exist**:

```powershell
Set-Location "C:\umicom\Umicom-Applications"

& ".\build\windows-ucrt64-native-llm-debug\umicom-native-llm-experiment.exe" `
  ".\framework\learning\native-llm\fixtures\experiment.conf" `
  "C:\umicom\_local\experiments\source-model-32-steps.umi"
```

Create the `C:\umicom\_local\experiments` directory first if it does not exist. The `SaveNewFile` contract rejects an existing destination instead of silently overwriting your earlier model.

## 5. Exercise: resume from an earlier checkpoint

For a controlled comparison, first create a **16-step** plan and save a checkpoint named `source-model-16-steps.umi`. Prepare a second plan with identical settings except `steps=32`.

The CLI accepts the extended native invocation:

```powershell
& ".\build\windows-ucrt64-native-llm-debug\umicom-native-llm-experiment.exe" `
  ".\framework\learning\native-llm\fixtures\experiment.conf" `
  "C:\umicom\_local\experiments\source-model-resumed-32-steps.umi" `
  "C:\umicom\_local\experiments\source-model-16-steps.umi"
```

The second argument is a **new output**; the third is an **existing input checkpoint**. Running this command does not modify the original input checkpoint.

Compare the new resumed checkpoint with an uninterrupted 32-step checkpoint from the same plan. With the same CPU toolchain, source data and all settings preserved, their bytes should match exactly:

```powershell
Get-FileHash "C:\umicom\_local\experiments\source-model-32-steps.umi" -Algorithm SHA256
Get-FileHash "C:\umicom\_local\experiments\source-model-resumed-32-steps.umi" -Algorithm SHA256
```

`Get-FileHash` is an interactive verification command; checkpoint persistence and training remain native C23 Framework functions.

**Important:** Saving a snapshot does not automatically save a complete *experiment identity*. Keep the reviewed plans and authorised corpus revisions alongside the run record in your local, controlled experiment workspace. Source code that is private or otherwise sensitive must not be committed to public GitHub repositories.

## 6. Tests provide stronger evidence than narrative

The Batch 07 automated test `framework.ai.training.experiment_run` performs both a direct and interrupted/resumed training sequence. It encodes checkpoints with the same Framework codec and compares their exact bytes, then verifies the original checkpoint has not been modified.

Other tests reject duplicate configuration keys, invalid manifest paths, oversized configurations and cancelled experiments. Returning `UMI_STATUS_CANCELLED` from an observer must not publish a partially trained decoder to the caller.

The isolated laboratory now has **36 registered CTest cases** when Batches 01–07 are combined. These are local native laboratory tests, not evidence that the entire Umicom Applications integration has passed on Windows.

## 7. Review questions

1. Why must a resumed experiment choose its next training batch using the *absolute* step number?
2. What is the difference between an unchanged checkpoint input and a newly trained output model?
3. Why is an FNV-1a checksum insufficient to establish checkpoint authenticity?
4. Which dataset and optimiser settings are not currently stored inside the checkpoint?
5. Why is identical checkpoint data a stronger claim than merely observing similar printed loss values?

**Next course milestone:** Lesson 17 will cover inference and controlled token sampling, while later lessons extend genuine model evaluation and expert specialisation.
