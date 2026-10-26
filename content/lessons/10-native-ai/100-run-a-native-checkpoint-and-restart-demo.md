# Lesson 100 — Run a Native C23 Fine-Tuning and Restart Demonstration

**Bits to Banking · Umicom Foundation · Sammy Hegab**

## Learning objectives

Configure an optional native Umicom Framework learning project, interpret its output and understand where ordinary shell commands stop and Framework functionality begins.

## 1. Locate the native implementation

The implementation is Framework-owned: `framework/src/ai/training/decoder_projection_adapter.c` contains the adapter's owned tape and checkpoints; `framework/src/ai/training/supervised_continuation.c` tracks deterministic training order and serialises the combined state; `framework/src/ai/training/supervised_quality.c` checks quality thresholds.

The educational demonstration itself is `framework/learning/native-ai-resumable/continuation_demo.c`. It passes wholly synthetic teaching examples to **existing** source-admission and dataset services. It is not a second trainer.

## 2. Configure in PowerShell

```powershell
Set-Location 'C:\umicom\Umicom-Applications'
$env:Path = 'C:\msys64\ucrt64\bin;' + $env:Path
cmake -S '.\framework\learning\native-ai-resumable' `
    -B '.\build\windows-ucrt64-ai-resume-debug' -G Ninja `
    -DCMAKE_C_COMPILER='C:\msys64\ucrt64\bin\gcc.exe' `
    -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTING=ON
if ($LASTEXITCODE -ne 0) { throw 'Configure failed' }
cmake --build '.\build\windows-ucrt64-ai-resume-debug' --parallel 2
if ($LASTEXITCODE -ne 0) { throw 'Build failed' }
ctest --test-dir '.\build\windows-ucrt64-ai-resume-debug' `
    -R '^framework\.ai\.(continuation|supervised|adaptation)\.' `
    --output-on-failure --no-tests=error
if ($LASTEXITCODE -ne 0) { throw 'Regression failed' }
```

The build should compile the original Framework tensor and decoder services together with the additive checkpoint/continuation module. Do not call this successful until **your** configured checkout reports passing tests.

## 3. Follow the demo data flow

The demonstration creates its own fictional public learning sources, validates the source-review evidence, constructs a small dataset and creates a frozen decoder plus two selected low-rank projection adapters. It trains **one** approved example, exports its combined adapter and cursor snapshot, destroys the original adapter and restores a newly owned adapter. It then completes the remaining epochs and reports aggregate held-out losses.

It does **not** write a checkpoint file to a fixed path or load arbitrary internet models. Applications that need durable snapshots use approved Framework storage and identity controls.

## 4. Check the three key results

Observe the restored cursor and completed steps. Confirm the final steps match the number of training examples multiplied by completed epochs. Confirm that the frozen decoder checkpoint remains unchanged. Finally, compare independent resumed and uninterrupted runs in the CTest regression: their final snapshot bytes must match on the same build.

A runnable native demonstration is not proof of a useful general-purpose language model. The current teaching decoder is intentionally small and bounded. The goal here is correct training ownership, deterministic state and honest evaluation evidence.

## Practice

**Question:** Why don't we copy the Transformer mathematics into the educational CLI? **Answer:** The Framework is the single numerical authority. The CLI constructs synthetic inputs, calls published Framework APIs and presents results, making the same components reusable in Studio and later Umicom AI applications.

Continue with [preparing real authorised sources](101-review-documents-and-media-for-training.md).

---

*Service to Many Leads to Greatness. Educational C23 examples; not a production financial or model-training certification.*
