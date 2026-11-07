<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/safer-c-programming/38-recognise-overlapping-output-ranges.md

PURPOSE:
Recognise overlap between distinct pointers

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Recognise overlap between distinct pointers

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


## Different starts can share elements

Aliasing means more than one expression refers to the same storage. The expression inputs == targets detects identical starting addresses. It does not detect partially overlapping ranges.

```text
element: 0 1 2 3 4 5 6 7 8
inputs:    [1 2 3 4]
targets:       [3 4 5 6]
shared:         3 4
```
Both pointers can be inside a valid array and still conflict. When the function writes an input token and a target token to the same element, one value replaces another. Even if a particular text produces equal values in some positions, the API cannot rely on that coincidence.

## A useful range convention

Represent a range by its start and the first position after its end. This is a half-open interval. Four elements beginning at index 1 occupy [1,5). Four beginning at index 5 occupy [5,9). The ranges touch but do not overlap. The end itself is excluded.

For ordered integer addresses, two nonempty ranges overlap when left_start < right_end and right_start < left_end. Both conditions must hold. The implementation checks that adding the byte length will not overflow before calculating either end.

The conversion to uintptr_t uses the flat-address model of the supported targets. It is not a universal pointer-validity test for every imaginable C architecture. Ordinary pointer comparison and subtraction across unrelated allocations also have language restrictions. Keep the supported platform assumption explicit.

## Trace both directions

1. Mark inputs at index 1 and targets at index 3, each with length four.
2. List the shared elements: 3 and 4.
3. Exchange the two starting positions.
4. List the shared elements again. They are still 3 and 4.
5. Move the second start to 5. There are no shared elements.

The regression exercises these directions with real arrays. It does not invent an invalid address and dereference it. The intended result for overlap is INVALID_ARGUMENT and unchanged storage.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-framework/blob/main/src/ai/training/corpus.c).

## Continue learning

[Course contents](../../../courses/safer-c-programming/index.html) · [Previous: Distinguish elements, bytes and writable capacity](37-elements-bytes-and-capacity.md) · [Next: Keep caller output unchanged when a request fails](39-keep-failed-output-unchanged.md)
