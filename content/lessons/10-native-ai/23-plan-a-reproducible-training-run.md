# Lesson 23 — Plan a Reproducible Native Training Experiment

**Level:** intermediate • **Estimated time:** 18 minutes • **Tools:** PowerShell, CMake and the existing C23 training laboratory

## What makes an experiment reproducible?

A credible training result needs a precise record of **which model**, **which source files**, **which training schedule** and **which random choices** produced it. Without those records, a later model run may be impossible to compare with the first.

Umicom's experiment plan is a reviewed, bounded `key=value` text file. It is **not a shell script**. The native Framework parser rejects unknown or duplicated keys and malformed values.

## Read a real plan

The repository contains `framework/learning/native-llm/fixtures/experiment.conf`. Its teaching values are:

```text
UMICOM-AI-EXPERIMENT-1
manifest=manifest.txt
steps=32
eval_interval=8
eval_batches=4
batch_sequences=1
learning_rate=0.025
model_seed=20261021
train_seed=4477
eval_seed=5544
context=8
channels=8
hidden_channels=16
attention_heads=2
```

The `manifest` path is resolved relative to the plan's own directory, not the program's current working directory. The parser deliberately does not expand environment variables or run commands.

## Understand each setting

| Setting | Meaning |
|---|---|
| `steps=32` | Perform 32 optimiser updates. This is not 32 epochs over every source file. |
| `eval_interval=8` | Evaluate at the baseline and after selected steps including the final step. |
| `eval_batches=4` | Sample four deterministic held-out batches per evaluation observation. |
| `batch_sequences=1` | Use one independently sampled sequence per ordinary training/evaluation batch. |
| `learning_rate=0.025` | Training step size for the plan's supported optimiser. |
| `model_seed` | Initialise the model consistently. |
| `train_seed` | Choose repeatable training windows. |
| `eval_seed` | Choose a stable, separate evaluation sample. |
| `context=8` | Each training sequence has eight input positions. |

The evaluator uses the same selected held-out windows at each observation. That makes successive results comparable **within one reviewed plan**, but they are still sampled estimates, not exhaustive tests of all available code.

## Build the existing native laboratory

Run these PowerShell commands on a verified local checkout. They invoke an existing Framework-owned C23 implementation; they do not introduce a second trainer:

```powershell
Set-Location 'C:\umicom\Umicom-Applications'
$env:Path = 'C:\msys64\ucrt64\bin;' + $env:Path
cmake -S '.\framework\learning\native-llm' -B '.\build\windows-ucrt64-native-llm-debug' -G Ninja -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTING=ON
cmake --build '.\build\windows-ucrt64-native-llm-debug' --parallel 2
```

**Windows security caution:** Earlier Umicom experiment executables were quarantined by McAfee. If your security product is still blocking an executable, **do not restore, exclude or execute it** merely to complete this exercise. Collect its detection name, hash and provenance and obtain a security review first. You can study the plan and run the other non-blocked exercises in the meantime.

When cleared, launch the experiment with its plan file:

```powershell
& '.\build\windows-ucrt64-native-llm-debug\umicom-native-llm-experiment.exe' '.\framework\learning\native-llm\fixtures\experiment.conf'
```

This invocation has no checkpoint output argument, so it prints progress and returns; it does not create a new checkpoint file.

## A stronger comparison

Run two independently reviewed plans with the **same evaluation source files and seeds**. Change only one experimental variable, such as the number of training steps. A surprising improvement could still be statistical noise or memorisation, so repeat and document the result rather than declaring success after a single run.

<details><summary>Knowledge check: are seeds enough?</summary><p>No. Equal random seeds do not guarantee comparable training if the source files, file order, model configuration, optimiser, compiler environment or training plan changes. Reproducibility depends on the entire recorded experimental context.</p></details>

**Next:** learn what a checkpoint actually proves and what it does not.
