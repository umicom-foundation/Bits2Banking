# Supplement 19I — Learning-Rate Schedules and Reproducible Resume

**Bits to Banking · Umicom Foundation · Sammy Hegab**  
**Implementation:** Native C23, Umicom Framework

## Learning objective

Learn to control how quickly model parameters change over a training run and how to repeat the exact updates after an interruption. This lesson builds on the existing Framework experiment runner and uses the same reviewed source-data manifest, decoder, seeded sampler and checkpoint writer.

A **learning-rate schedule** changes the optimiser's step size as training proceeds. It does not change a model's architecture or teach it additional programming concepts by itself. The advantage is experimental control: we can compare different schedules while keeping the dataset, model initialisation and evaluation policy fixed.

## 1. Why a fixed rate can be inconvenient

Suppose our model learns C23 source-code patterns using a fixed rate of `0.025`. Early in training, that rate may be useful for making larger improvements. Later, the same rate may move parameters past a useful solution. A schedule can increase the rate gently at the beginning and reduce it towards the end.

A learning-rate schedule is therefore a function of the **absolute optimiser-step number**. A microbatch is not a separate optimiser step: several small gradients can be accumulated before one update. The step counter advances **once per complete effective batch**.

## 2. Three schedules

The Framework provides three deterministic policies. `peak` is the largest planned rate, `minimum` is the final decay floor, `warmup` is the number of rising steps and `total` is the originally approved training horizon.

| Policy | Behaviour after warmup | Typical reason to study it |
| --- | --- | --- |
| Constant | Keep the peak rate | Control experiment and simple baseline |
| Linear decay | Reduce steadily towards the minimum | Understand a predictable reduction |
| Cosine decay | Follow a half-cosine curve towards the minimum | Study a smooth reduction near the end |

**Warmup** increases the rate according to `rate = peak × step / warmup`, for steps between 1 and the end of warmup. When warmup is zero, the schedule starts directly with its main policy. Invalid or non-finite rates are rejected.

For the post-warmup stage, let `p = (step − warmup) / (total − warmup)`. The linear schedule is:

```text
rate = peak + (minimum − peak) × p
```

The cosine schedule is:

```text
rate = minimum + (peak − minimum) × [1 + cos(pi × p)] / 2
```

For example, with `peak = 0.1`, `minimum = 0.01`, `warmup = 2` and `total = 6`, the rates at steps 1, 2, 4 and 6 in the cosine experiment are approximately `0.05`, `0.1`, `0.055` and `0.01`. These four values appear in the native schedule regression test.

## 3. A subtle requirement for exact continuation

Imagine that a planned experiment contains 32 optimiser steps but training is interrupted after 16. A correctly resumed run must calculate the rate for step 17 using the **original 32-step horizon**. Defining a new 16-step decay for the first half would change the rates before the interruption, and the two runs would no longer be equivalent.

The Framework therefore accepts a schedule object separately from the existing experiment configuration. It checks that the plan's current run length does not exceed the schedule's planned horizon. The scheduled APIs leave the established fixed-rate SGD APIs unchanged.

This applies to both ordinary SGD training and the Framework's gradient-accumulation path. Both modes use absolute step numbers for learning rates and dataset draws. Regression tests compare complete checkpoint bytes from uninterrupted and split/resumed scheduled experiments.

**Important limitation:** the existing decoder checkpoint does not authenticate the original schedule, dataset identity, learning rate, seeds or microbatch settings. Exact continuation is reproducible **when those settings are kept identical and reviewed**; the checkpoint alone cannot prove they were. For stateful AdamW, exact process-restart continuation is not yet supported because AdamW moment state is not persisted.

## 4. Inspect the Framework contracts

The public declarations are in `include/umicom/ai/training/optimizer.h`, `include/umicom/ai/training/experiment.h` and `include/umicom/ai/training/experiment_accumulation.h`. The implementations are `src/ai/training/optimizer.c` and `src/ai/training/experiment.c`.

Observe that the standard `UmiAiTrainingExperimentRun` and `UmiAiTrainingExperimentResume` remain callable. The opt-in scheduled alternatives delegate to the **same training path**. No new tokenizer, source sampler or transformer implementation is introduced.

The test `tests/ai_training/test_training_scheduled_experiment.c` provides the most important verification: compare the weights from a full scheduled run with those from two shorter runs joined through a checkpoint. Repeat the comparison with effective-batch accumulation enabled.

## 5. Run an ordinary scheduled experiment

Use your actual local repository structure:

```powershell
Set-Location "C:\umicom\Umicom-Applications"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"

cmake -S ".\framework\learning\native-llm" `
    -B ".\build\windows-ucrt64-native-llm-debug" -G Ninja `
    -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTING=ON
cmake --build ".\build\windows-ucrt64-native-llm-debug" --parallel 2
ctest --test-dir ".\build\windows-ucrt64-native-llm-debug" `
    --output-on-failure --no-tests=error

& ".\build\windows-ucrt64-native-llm-debug\umicom-native-llm-scheduled.exe" `
    ".\framework\learning\native-llm\fixtures\experiment.conf" `
    32 4 0.0025
```

The final three arguments specify the **original total horizon**, the number of warmup steps and the minimum learning rate. The reviewed plan file provides the peak learning rate through `learning_rate=`. The executable uses cosine decay and reports held-out loss at the evaluation intervals already defined in the plan.

## 6. Practice an interrupted-and-resumed run safely

Keep generated checkpoint files and experimental plan copies under `C:\umicom\_local`, not inside the Git repository. To preserve the manifest's relative source paths, copy the teaching fixtures into a separate private experiment directory:

```powershell
$sourceFixtures = "C:\umicom\Umicom-Applications\framework\learning\native-llm\fixtures"
$experimentDir = "C:\umicom\_local\training-experiment"
New-Item -ItemType Directory -Force $experimentDir | Out-Null
Copy-Item "$sourceFixtures\*" $experimentDir -Recurse -Force

# Make a private short-run plan while retaining the ORIGINAL horizon.
(Get-Content "$experimentDir\experiment.conf") `
    -replace '^steps=32$', 'steps=16' |
    Set-Content "$experimentDir\partial.conf"

Set-Location "C:\umicom\Umicom-Applications"

& ".\build\windows-ucrt64-native-llm-debug\umicom-native-llm-scheduled.exe" `
    "$experimentDir\partial.conf" 32 4 0.0025 `
    "$experimentDir\partial.umi"

# Resume to 32 optimiser steps with the SAME 32-step schedule.
& ".\build\windows-ucrt64-native-llm-debug\umicom-native-llm-scheduled.exe" `
    "$experimentDir\experiment.conf" 32 4 0.0025 `
    "$experimentDir\completed.umi" "$experimentDir\partial.umi"
```

The model writer refuses to overwrite an existing checkpoint. If either command rejects an input, read its status instead of changing the training settings arbitrarily. The run must use the same dataset and seeds throughout. These commands are interactive **PowerShell instructions**, not a scripting-language implementation of Framework functionality.

## 7. Try gradient accumulation with a schedule

The reviewed fixture `accumulated-experiment.conf` sets an effective batch larger than a single microbatch. Run it with the same command to see that the **learning rate changes once per effective optimiser step**, not once per microbatch:

```powershell
& ".\build\windows-ucrt64-native-llm-debug\umicom-native-llm-scheduled.exe" `
    ".\framework\learning\native-llm\fixtures\accumulated-experiment.conf" `
    4 1 0.0025
```

This experiment uses the existing tape and accumulation engine. Check the plan before execution; small source samples and small models do not establish general language understanding.

## 8. Review questions

1. Why does a warmup schedule use the absolute optimiser-step number rather than a local microbatch number?
2. What differs between linear and cosine decay?
3. Why must the originally planned training horizon be retained after an interruption?
4. Why can scheduled SGD resume from its model checkpoint when the source, plan and seeds are reproduced, but stateful AdamW cannot yet resume exactly?
5. How could a future training snapshot authenticate both the source dataset and the original schedule?

**Next engineering objective:** a versioned, integrity-checked optimiser-state checkpoint with model and corpus provenance, followed by independent numerical comparisons for resumed AdamW training.
