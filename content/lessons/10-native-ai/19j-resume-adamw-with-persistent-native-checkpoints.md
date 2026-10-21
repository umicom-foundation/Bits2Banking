# Supplement 19J — Resume AdamW Training with a Portable Native Checkpoint

**Author:** Sammy Hegab · **Organisation:** Umicom Foundation · **Licence:** MIT  
**Level:** Intermediate native AI engineering · **Implementation language:** C23

## The engineering problem

We have taught our small Umicom language model to train on reviewed C23 source
files. It can now use multiple source-code sequences and the AdamW optimiser.
Suppose the computer shuts down after four training steps and we want to
continue from step five. Merely loading the saved neural-network weights is
not sufficient for AdamW.

Every AdamW update depends on information accumulated during the *previous*
steps. AdamW keeps a moving average of gradients (first moments) and a moving
average of squared gradients (second moments). It also needs the number of
completed steps to calculate bias correction.

If we rebuild AdamW from zeros when resuming, we get a **different model**,
even when the source code and initial random seed are identical. This lesson
explains how to preserve all necessary native state without changing the
existing Umicom decoder checkpoint format.

## Understand the optimiser's memory

Our teaching decoder contains 4,792 scalar parameters in one of the standard
lesson configurations. It stores each model parameter as an FP32 number.
AdamW in the current Umicom Framework uses FP64 numbers for both moments.

| Stored data | Formula | Payload |
|---|---:|---:|
| Model parameter values | `P × 4` bytes | 19,168 bytes |
| First moments | `P × 8` bytes | 38,336 bytes |
| Second moments | `P × 8` bytes | 38,336 bytes |
| Total values and moment payload | `P × 20` bytes | 95,840 bytes |

These numbers exclude checkpoint headers, tensor dimensions, gradients,
application objects and allocator overhead. A checkpoint envelope must store
both moments as well as the original parameters.

## Review the mathematics

For an update at step `t`, with training gradient `g`:

```text
m_t = beta1 * m_(t-1) + (1 - beta1) * g
v_t = beta2 * v_(t-1) + (1 - beta2) * (g * g)

corrected_first  = m_t / (1 - beta1^t)
corrected_second = v_t / (1 - beta2^t)

weight_next = weight_current - learning_rate *
   (corrected_first / (sqrt(corrected_second) + epsilon)
    + weight_decay * weight_current)
```

Pay attention to the exponent `t`. Restoring the moment arrays but restarting
`t` at one would still change the result. The complete checkpoint therefore
stores the previous steps and verifies that they match the embedded decoder.

## Follow our Framework implementation

The existing `UMIDEC04` format continues to represent the decoder alone.
Our new `UMIADW01` envelope wraps that complete decoder checkpoint and adds
AdamW-specific state. The source is in these Framework-owned files:

- `include/umicom/ai/training/optimizer_checkpoint.h`
- `src/ai/training/optimizer_checkpoint.c`
- `src/ai/training/optimizer_internal.h`
- `src/ai/training/optimizer.c`
- `src/ai/training/decoder.c`

The combined checkpoint has one versioned header, stored parameter dimensions,
AdamW configuration, an embedded decoder checkpoint, all moment values, and a
trailing checksum.

### A safe ownership example

The following excerpt shows the handle discipline; actual error handling is
illustrated in the Framework's tests and laboratory executable.

```c
UmiAiTrainingDecoder *restored = NULL;
UmiAiTrainingAdamW *optimizer = NULL;

UmiStatus status = UmiAiTrainingAdamWCheckpointLoadFile(
    approvedLocalPath, &restored, &optimizer);

if (status == UMI_STATUS_OK) {
    /* Continue with the identical reviewed dataset and learning-rate plan. */
    UmiAiTrainingAdamWDestroy(optimizer);
    UmiAiTrainingDecoderDestroy(restored);
}
```

The optimiser borrows the decoder's parameter handles, so destroy the
optimiser first. Invalid and damaged inputs leave both output pointers
unchanged. The loader never executes bytes from the checkpoint.

## Run our native regression tests

From the Umicom Applications directory:

```powershell
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"

cmake -S ".\framework\learning\native-llm" `
  -B ".\build\windows-ucrt64-native-llm-debug" `
  -G Ninja -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTING=ON

cmake --build ".\build\windows-ucrt64-native-llm-debug" --parallel 2

ctest --test-dir ".\build\windows-ucrt64-native-llm-debug" `
  --output-on-failure -R 'adamw_(resume|checkpoint)'
```

The tests compare uninterrupted training with interrupted-and-restored
training. Equal complete checkpoint bytes provide much stronger evidence of
reproducibility than merely comparing the last reported training loss.

## Design lessons

1. **Bound memory before reading:** the file header cannot force an unlimited
   allocation. The current envelope has a fixed upper size.
2. **Validate all dimensions:** a valid checksum alone cannot tell us whether
   the supplied parameters match the expected decoder architecture.
3. **Avoid partial publication:** neither model nor optimiser escapes from a
   failed restore, and no existing checkpoint is overwritten during saving.
4. **Preserve the old format:** SGD experiments and existing applications can
   still load model-only `UMIDEC04` checkpoints.
5. **Preserve external evidence:** the same training plan, source-code files,
   seeds, schedule and batch sequence are needed for exact scientific repeats.

## Security does not disappear because software is educational

Our checksum detects accidental file damage. It is not a cryptographic
signature and cannot establish a trusted publisher. Only load approved local
checkpoints whose source can be verified. Do not run executables quarantined by
Windows or McAfee before reviewing the security product's exact detection and
obtaining a clean determination. The Windows-specific incident response is
documented in `framework/learning/native-llm/WINDOWS_TEST_SECURITY.md`.

## Practical exercises

**Exercise A:** Explain why the AdamW first moment at step five cannot be
reconstructed solely from the model's weights at step four.

**Exercise B:** Calculate the payload required to preserve two FP64 moments
for a model with 120,000 scalar parameters. Compare this with its FP32 weight
storage; explain why total process memory would still be higher.

**Exercise C:** Modify the reviewed experiment's training-rate schedule in a
copy of your test plan. Explain why the resulting training run must not be
reported as an *exact resume* of the original experiment.

**Exercise D:** Use the new regression tests to demonstrate that a damaged
checkpoint is rejected without overwriting existing handles or a previous
checkpoint file.

## What comes next

The combined state is now recoverable. The next engineering step is to bind
this state to an approved, fingerprinted training plan and complete dataset
identity, integrate it into controlled multi-step AdamW experiments, and only
then increase training duration and model capacity. Our small model does not
yet understand general C23 or Calypso programming tasks reliably.
