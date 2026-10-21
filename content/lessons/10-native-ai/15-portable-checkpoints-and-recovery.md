# Lesson 15 — Portable Model Checkpoints and Exact Resume

**Bits to Banking · Build Your Own LLM from Scratch · Umicom Foundation**  
**Author:** Sammy Hegab  
**Implementation:** Native C23 checkpoint codec and file publisher in Umicom Framework  
**Prerequisites:** Lessons 13–14, binary representation, memory ownership and filesystem errors.

## Why checkpoints matter

A trained model is not the source code that implements a neural network. It is the **numerical parameter state** produced by training. Restarting the application with the same code but newly seeded weights would discard the work learned during training.

A checkpoint preserves the architecture configuration, completed-step counter and every learned parameter so the model can be reloaded. It also gives us a stable artifact to compare across evaluations or recover after an interruption.

The checkpoint work belongs to Umicom Framework, not separately to Umicom LLM, Studio or a future expert application.

## 1. What exactly is stored?

The first `UMIDEC04` format is a deliberately small, documented binary contract:

```text
8 bytes       magic: UMIDEC04
4 bytes       format version (1)
5 × 4 bytes   vocabulary, context, channels, hidden, attention heads
8 bytes       original random seed
8 bytes       completed optimiser step count
4 bytes       number of parameter tensors (15)
for each tensor:
    4 bytes   rows
    4 bytes   columns
    N × 4     IEEE754 binary32 parameter values (row-major)
8 bytes       FNV-1a64 checksum over all preceding bytes
```

All integers are explicitly **little-endian**, not raw in-memory C structures. We must not serialise C pointers, padding bytes, opaque handles or endianness-dependent struct images. On import, the Framework derives expected tensor shapes from the model configuration, then checks every stored shape and every floating-point value before constructing a new model.

The model's public `UmiAiTrainingDecoderConfig` and the private parameter order are intentionally separate. Applications never manipulate the internal parameter slots directly.

## 2. Exact capacity and failure-atomic memory encoding

`UmiAiTrainingDecoderCheckpointSize` returns the exact number of bytes the current model requires. `UmiAiTrainingDecoderCheckpointEncode` writes into a caller-owned byte buffer with explicit capacity.

```c
size_t required = 0U;
size_t written = 0U;
UmiStatus status = UmiAiTrainingDecoderCheckpointSize(model, &required);
/* Verify status and allocate required bytes before calling Encode. */
status = UmiAiTrainingDecoderCheckpointEncode(model, bytes,
                                              required, &written);
```

This is a signature demonstration; the complete calling sequence and allocation/error handling are in the working native lab. The encoder assembles data in temporary storage and publishes output only on success. A too-small caller buffer is not partially overwritten.

The decoder rejects truncated, oversized, extra-byte, unsupported-version, inconsistent-shape and non-finite parameter data. Corrupt data never replaces a previously valid model pointer.

## 3. Why the checksum is not a signature

FNV-1a64 provides simple, reproducible detection of accidental byte changes. It does **not** authenticate who created the file. Anyone able to change a file can recompute its checksum.

Therefore checkpoint loading requires normal Framework security policy, trusted source selection and appropriate file permissions. Later model distribution should add signed hashes and provenance records. **Never describe a CRC or FNV checksum as cryptographic security.**

## 4. Publishing a new model generation safely

For the educational local filesystem, the Framework provides:

```c
UmiStatus UmiAiTrainingDecoderCheckpointSaveNewFile(
    const UmiAiTrainingDecoder *model, const char *path);

UmiStatus UmiAiTrainingDecoderCheckpointLoadFile(
    const char *path, UmiAiTrainingDecoder **outModel);
```

`SaveNewFile` writes to a same-directory exclusive staging file, flushes it and then publishes a **new** destination without intentionally overwriting an existing checkpoint. Reusing the same destination returns `UMI_STATUS_ALREADY_EXISTS`. The file publisher is not yet integrated with Umicom's complete Data Server or release-signing services.

A power failure may still leave a staging file, and the implementation does not claim fully durable, transactional filesystem commits. Under Linux it uses a hard-link publication step; on Windows it uses a native no-replace move. Filesystems have different guarantees and must be tested in the target environment.

## 5. Train, save, reload and compare

After merging Batch 04, build as described in Lesson 13 and run:

```powershell
Set-Location "C:\umicom\Umicom-Applications"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"

New-Item -ItemType Directory -Force "C:\umicom\_local\models" | Out-Null

& ".\build\windows-ucrt64-native-llm-debug\umicom-native-llm-decoder-demo.exe" `
  "C:\umicom\_local\models\umicom-native-decoder-experiment-01.umidec"
```

This saves the model **outside Git**. Choose another filename for the next experiment; the save command intentionally rejects replacement of an existing checkpoint. The demonstration reloads the model and checks that it produces the identical greedy next-token prediction.

The accompanying `framework.ai.training.checkpoint` CTest also round-trips the exact bytes, checks the completed-step counter and refuses damaged input and a duplicate filename.

## 6. What counts as reproducible continuation?

For a deterministic training loop, continuing from a checkpoint should produce the same next parameter values if the model, training samples, order, learning rate and numerical environment are the same. Our first optimiser is plain SGD and stores **no momentum state**; we also use no dropout or random data augmentation after initialisation. The checkpoint therefore contains the model weights, initial seed and completed steps, but it does **not** contain a corpus cursor or an independent dataset digest.

A future AdamW checkpoint will additionally require first/second-moment buffers, optimisation counters and learning-rate schedule state. A production trainer also needs corpus fingerprinting, shuffling RNG and loader positions. Do not claim the present checkpoint can resume every conceivable training configuration exactly.

## 7. Practical inspection and exercises

Examine these native source files:

```text
include/umicom/ai/training/checkpoint.h
src/ai/training/checkpoint.c
src/ai/training/decoder_private.h
src/ai/training/decoder.c
tests/ai_training/test_training_checkpoint.c
learning/native-llm/train_decoder.c
```

Then perform these experiments:

1. Record the exact checkpoint size. Use the dimensions to calculate the number of float values manually. Why are there 15 tensors?
2. Deliberately request a buffer one byte too small. Confirm that the output buffer is unchanged.
3. Modify a copy of one checkpoint byte. Verify import fails and the destination model remains unchanged. Restore the original before continuing.
4. Save to the same path a second time. Explain why refusing replacement protects an approved model generation.
5. Reload a model and run one more identical training step on both the original and restored copies. Compare their resulting encoded bytes. What circumstances could cause differences on other hardware?

## Next development boundary

**Batch 04 completes a bounded, one-block decoder with weights trained from scratch, stable logits, reproducible held-out partitions, checkpoint export/import and new-file publication.** It is still an educational research model. Subsequent batches can improve the tokenizer/corpus loader, multi-block depth, learning-rate scheduling and AdamW, and then introduce controlled inference sampling.

Neither a successfully reloaded model nor low training loss means that it understands Umicom C23, Framework or Calypso. Those expert models need substantially more data, independent evaluations and explicit source grounding.
