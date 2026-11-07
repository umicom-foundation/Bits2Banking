# Lab: keep training and evaluation sequences separate

Training changes a model using examples. Evaluation measures it on examples reserved for assessment. If the model has already seen the assessment answers, a good score can be misleading. This lab follows Framework's deterministic sequence partitioner and then examines what that function cannot detect.

## Setup recap

You need a C23 compiler, CMake, Ninja and Framework sources. [The byte tokeniser lab](byte-tokenizer-contract-lab.md) explains the existing `learning/native-llm` project. The commands below configure that project with `BUILD_TESTING=ON` and build one selected check. No training run or downloaded dataset is required here. See [terminal setup](../learning-c/terminal-lab.md) if the compiler or CMake is unavailable.

## 1. Describe the partition before coding

Suppose there are 12 sequences, identified by numbers 0–11. Reserve three for evaluation. Framework's `UmiAiTrainingSplitSequences` returns a permutation: all 12 IDs in a reordered list, without omissions or repetitions. The first nine belong to training; the remaining three belong to evaluation.

```text
12 complete sequence IDs → seeded permutation → first 9 train | last 3 evaluate
```

The seed selects a repeatable ordering. It is a parameter used to reproduce an experiment, not a password. The function keeps whole sequence IDs intact; it does not inspect the text those IDs represent.

## 2. Build and run the selected check

PowerShell:

```powershell
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S 'C:/umicom/Umicom-Applications/framework/learning/native-llm' -B 'C:/umicom-learning/native-llm' -G Ninja -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTING=ON
cmake --build 'C:/umicom-learning/native-llm' --target umicom-ai-training-dataset-split-test --parallel 2
ctest --test-dir 'C:/umicom-learning/native-llm' -R '^framework\.ai\.training\.dataset_split$' --output-on-failure --no-tests=error
```

Bash:

```bash
cmake -S "$HOME/umicom/Umicom-Applications/framework/learning/native-llm" -B "$HOME/umicom-learning/native-llm" -G Ninja -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTING=ON
cmake --build "$HOME/umicom-learning/native-llm" --target umicom-ai-training-dataset-split-test --parallel 2
ctest --test-dir "$HOME/umicom-learning/native-llm" -R '^framework\.ai\.training\.dataset_split$' --output-on-failure --no-tests=error
```

One case should run. Its success text is `Whole-sequence split: passed`, visible with verbose CTest output. These commands build the selected test and its dependencies, not every application.

## 3. Read the evidence

Open `tests/ai_training/test_training_dataset_split.c` beside `include/umicom/ai/training/dataset_split.h`. The test first provides capacity 11 for 12 IDs and verifies refusal without changing its sentinel-filled output. It rejects evaluation groups of zero or all 12 sequences. It then checks that repeated calls with the same seed produce the same ordering, all IDs are in range, and none appear twice.

For the particular seeds in this test, it also checks that the order changes. Do not generalise that into a promise that every distinct seed always produces a distinct permutation; a finite set of permutations cannot provide that guarantee for arbitrarily many seeds.

## 4. Find the remaining data problem

Imagine sequence 2 and sequence 9 contain copies of the same paragraph. They have different IDs, so disjoint ID groups can still leak content across the split. Overlapping windows cut from one source file can create a similar problem.

Before training, group related examples by their original document, remove inappropriate duplicates, then reserve evaluation groups. Record the corpus revision, split method, seed and evaluation policy. Never repeatedly tune a model on the final held-out set and continue calling it unseen evaluation.

## Exercise and recovery

Write six invented document IDs on paper, with two IDs representing copies of the same document. Partition by ID, then by source document. Explain which method protects the assessment better and why. No private documents are required.

If a test fails, inspect the contract and input counts before changing the expected result. Passing this test establishes partition properties, not model quality, data rights or freedom from contamination. Continue with [the first training experiment](first-training-run.md), or return to the [LLM course](index.md).

[Next: Lab: measure a model without changing its checkpoint](checkpoint-observation-lab.md)
