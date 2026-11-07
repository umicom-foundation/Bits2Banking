<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/safer-c-programming/39-keep-failed-output-unchanged.md

PURPOSE:
Keep caller output unchanged when a request fails

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Keep caller output unchanged when a request fails

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


## Why a refusal needs a state contract

A result code answers whether an operation succeeded. The caller also needs to know what happened to its previous data. A rejected corpus window must leave the output arrays unchanged. This lets an editor or training inspector keep its previous valid view after an invalid request.

The function validates every precondition before entering the loop that writes tokens. There are no failure-return branches inside that final loop. This design makes the publication boundary clear: checks first, then writes.

## Observe the state, not only the code

The regression fills a real array with known values and copies it before calling the function. After the call it checks both the result and every byte of the array.

```c
memcpy(before, slots, sizeof(slots));
status = UmiAiCorpusWindow(corpus, 0U, 4U, slots + 1U, slots + 3U, 4U);
/* Check INVALID_ARGUMENT, then compare the complete array. */
if (memcmp(before, slots, sizeof(slots)) != 0) {
    /* A failed request changed caller-owned storage. */
}
```
memcpy copies a specified number of bytes between nonoverlapping regions. Here before and slots are separate arrays. memcmp compares their object bytes and returns zero when they match. Comparing the full array also catches accidental writes to guard elements outside the requested region.

## Practise reviewing the boundary

1. Find the first assignment to inputs[i] in the active implementation.
2. List all conditions checked before it.
3. Confirm that insufficient capacity is handled before any writes.
4. Find the overlap checks and confirm they also precede the writes.
5. Locate each failure check in the regression.

This contract does not make the operation atomic between threads. Another thread writing the same array can still cause a data race. Give each operation exclusive access or use an appropriate synchronization policy. Unchanged-on-error and concurrency safety are different properties, and both need explicit designs.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-framework/blob/main/tests/ai_training/test_training_corpus_ranges.c).

## Continue learning

[Course contents](../../../courses/safer-c-programming/index.html) · [Previous: Recognise overlap between distinct pointers](38-recognise-overlapping-output-ranges.md) · [Next: Follow corpus and output lifetimes](40-own-the-corpus-and-borrow-the-window.md)
