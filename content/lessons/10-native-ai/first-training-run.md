# LLM from Scratch: run and inspect the first training experiment

## Goal and prerequisites

Build the existing three-token example, retain its output and connect each
stage to the shared Framework implementation. Complete
[one next-token prediction](first-next-token-model.md) first. Prepare the
Windows toolchain described in [Learning Visual Studio](../05-engineering/learning-visual-studio.md).
Visual Studio is optional for this experiment; a text editor and PowerShell suffice.

## 1. Choose the small project

The source is inside Framework, but it has its own CMake entry point. This
avoids configuring every application simply to study one numerical experiment.
It still uses the real Framework services, not copied lesson-only maths.

```text
learning/native-llm/train_bigram.c    thin example
          |
include/umicom/ai/training/tape.h     public contracts
          |
src/ai/training/tape.c               numerical operations and owned storage
          |
tests/ai_training/test_training_bigram.c   behavioural regression
```

## 2. Configure and compile

Run these in PowerShell, one at a time. The paths keep source, generated files
and logs separate. Stop after a nonzero `$LASTEXITCODE` and inspect the log.

```powershell
Set-Location "C:\umicom\Umicom-Applications"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
$LogRoot = "C:\umicom\_local\logs\first-llm-$(Get-Date -Format yyyyMMdd-HHmmss)"
New-Item -ItemType Directory -Force $LogRoot
cmake -S ".\framework\learning\native-llm" -B ".\build\learning-bigram" -G Ninja -DCMAKE_BUILD_TYPE=Debug -DCMAKE_C_COMPILER="C:/msys64/ucrt64/bin/gcc.exe" -DBUILD_TESTING=ON 2>&1 | Tee-Object "$LogRoot\configure.log"
$LASTEXITCODE
cmake --build ".\build\learning-bigram" --target umicom-native-llm-train umicom-ai-training-bigram-test --parallel 2 2>&1 | Tee-Object "$LogRoot\build.log"
$LASTEXITCODE
ctest --test-dir ".\build\learning-bigram" -R "^framework\.ai\.training\.bigram$" --output-on-failure --no-tests=error --output-log "$LogRoot\tests.log"
$LASTEXITCODE
```

CMake creates build rules, Ninja compiles their dependencies, and CTest runs
the named regression. `--no-tests=error` prevents a misspelled test filter from
looking like success. A test pass applies to that check and source version;
it does not prove the entire Framework or an LLM product works.

If the selected build directory already contains another compiler's cache,
choose a new directory name consistently. Do not erase unrelated work.

## 3. Run and read the output

```powershell
& ".\build\learning-bigram\umicom-native-llm-train.exe" 2>&1 | Tee-Object "$LogRoot\training-run.log"
$LASTEXITCODE
```

The example announces a one-hot bigram model with 3-by-3 weights. It prints
loss at selected epochs, then learned next-token predictions. Expected final
pairs are:

```text
umicom     -> framework
framework  -> trains
trains     -> umicom
```

Record actual loss values from your run instead of copying a success transcript.
Starting equal logits give a loss near 1.099 for this corpus. Training should
reduce it. Small floating-point differences can depend on the toolchain;
a crash, non-finite value or wrong transition needs investigation.

## 4. Trace one call

Find `UmiAiTrainingMatmul` in the example, its declaration in `tape.h` and its
definition in `tape.c`. The caller supplies the input and weight tensors; the
Framework checks their dimensions and returns a result owned by the tape.
A **declaration** tells a caller how a function can be used. A **definition**
contains the code that performs it. Keeping reusable maths in Framework lets
other applications use the same checked implementation.

Follow `TRAIN_CHECK` in the example. It stops after an error, prints the failing
operation and destroys the tape. Continuing with a missing result could turn
one failed operation into unrelated memory errors.

## 5. Keep a small observation record

Write down the source revision, whether local source differs, compiler version,
test result, first loss, last loss and printed transitions. Use a folder you
choose. This record is about a local experiment; it is not a model publication,
distributed-training receipt or proof of useful language ability.

**Exercise:** explain why the printed transition can be correct before the
loss reaches zero. **Answer:** the correct token only needs the largest score
to win. Loss also measures how much probability it receives, not just which
token is largest.

**Exercise:** should increasing the learning rate always improve training?
**Answer:** no. Larger updates can overshoot or become unstable. Keep the
original example and use a separate reviewed experiment for such changes.

Next follow [the LLM course map](../../courses/llm-from-scratch/course-map.html).
Proceed from numerical foundations to attention before the specialised
distributed-learning or cryptographic-attestation studies. Those are later
topics and are not prerequisites for understanding this first model.
