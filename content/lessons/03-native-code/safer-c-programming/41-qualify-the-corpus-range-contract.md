<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/safer-c-programming/41-qualify-the-corpus-range-contract.md

PURPOSE:
Turn a range contract into focused regression checks

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Turn a range contract into focused regression checks

Learn how two valid pointers can still describe conflicting output storage. The exercise follows the Umicom Framework corpus service from a small caller through its contract, boundary checks and regression coverage.

## Prepare the laboratory

A corpus is a collection of example data. A token is a number that represents a piece of that data. This laboratory turns six bytes into pairs of tokens. It does not train a model or use the network.

Read the lesson without installing anything. To run the example, use a C23 compiler, CMake 3.24 or newer, Ninja, and the Umicom Framework checkout containing the corpus-range laboratory. A terminal accepts typed commands. The compiler translates C into machine code; CMake describes targets; Ninja builds them; CTest runs registered checks.

1. Find the Framework folder in your checkout.
2. Open PowerShell or Bash. Substitute your chosen checkout location below.
3. Configure a separate learning build. It does not replace your application build.
4. Build the two named targets, then run only the two named checks.
5. Stop on an error and read the first diagnostic before continuing.

```powershell
Set-Location "C:\umicom\Umicom-Applications\framework"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S learning/native-llm -B build/corpus-ranges -G Ninja -DBUILD_TESTING=ON
cmake --build build/corpus-ranges --target umicom-native-llm-corpus-ranges umicom-ai-training-corpus-ranges-test --parallel 2
ctest --test-dir build/corpus-ranges -R "^framework\.ai\.training\.corpus_ranges(_demo)?$" --output-on-failure --no-tests=error
& ".\build\corpus-ranges\umicom-native-llm-corpus-ranges.exe"
```
```bash
cd ~/umicom/Umicom-Applications/framework
cmake -S learning/native-llm -B build/corpus-ranges -G Ninja -DBUILD_TESTING=ON
cmake --build build/corpus-ranges --target umicom-native-llm-corpus-ranges umicom-ai-training-corpus-ranges-test --parallel 2
ctest --test-dir build/corpus-ranges -R '^framework\.ai\.training\.corpus_ranges(_demo)?$' --output-on-failure --no-tests=error
./build/corpus-ranges/umicom-native-llm-corpus-ranges
```
If CMake cannot find the C compiler, check its installation and PATH. If the target is unknown, confirm that the learning source and its CMakeLists.txt are from the same checkout. A missing executable means the build has not produced it. Test success must come from the commands on your machine; the expected output below is not an execution record.

For a longer language introduction, see [Learning C](../../../courses/learning-c/index.html). This lesson explains the concepts it uses.


## Build a test table

A regression check is a repeatable example that would catch a defect returning later. A useful table includes accepted boundaries as well as refused inputs.

| Case | Expected result | Output requirement |
| --- | --- | --- |
| Same output start | INVALID_ARGUMENT | Unchanged |
| Partial overlap in either direction | INVALID_ARGUMENT | Unchanged |
| Adjacent ranges in either direction | OK | Exact token pairs |
| Capacity smaller than count | CAPACITY_EXCEEDED | Unchanged |
| Source start outside corpus | INVALID_ARGUMENT | Unchanged |
| Last source byte with no following target | INVALID_ARGUMENT | Unchanged |
| Last valid one-pair window | OK | Correct last pair |

## Read the loop as a set of examples

The displacement loop tries offsets zero through three for a four-element window. These produce exact aliasing and every possible partial overlap at those element-aligned distances. A separate check tries offset four, which is the adjacent valid boundary. This small enumeration has a reason; adding many renamed copies of the same test would not improve it.

1. Run the focused build and CTest commands in the setup section.
2. Confirm that both intended tests are discovered. --no-tests=error makes an empty selection fail.
3. Read any failure's line number and expression.
4. Compare the tested executable's build source with the source you edited.
5. Rerun after a repair and retain the actual output with your environment details.

The regression uses explicit checks that remain active even when NDEBUG disables standard assert expressions. Returning a nonzero process exit code tells CTest that a check failed.

## Extend with a reason

If the API later accepts another token type, review the byte-size arithmetic and supported address model. If it becomes asynchronous, add lifetime and cancellation coverage. If it accepts external files, qualify file import separately. None of those behaviours is established by passing this in-memory range test.

Continue into [LLM from Scratch](../../llm-from-scratch/index.html) to see how corpus windows feed dataset sampling and decoder training. This range repair strengthens that input boundary; it does not establish model quality or secure distributed learning.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-framework/blob/main/tests/ai_training/test_training_corpus_ranges.c).

## Continue learning

[Course contents](../../../courses/safer-c-programming/index.html) · [Previous: Follow corpus and output lifetimes](40-own-the-corpus-and-borrow-the-window.md)
