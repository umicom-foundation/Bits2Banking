<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/safer-c-programming/37-elements-bytes-and-capacity.md

PURPOSE:
Distinguish elements, bytes and writable capacity

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Distinguish elements, bytes and writable capacity

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


## Three measurements

An array element is one stored value. A byte count measures storage size. Capacity describes how many elements the caller has made available for a function to write. The three numbers can differ.

The laboratory declares uint32_t storage[12]. It holds twelve token values. On the supported eight-bit-byte hosts each value occupies four bytes, so the array occupies 48 bytes. storage + 1 points at the second element, four bytes after the start. C pointer arithmetic uses the pointed-to type; adding one does not always advance one byte.

```c
uint32_t storage[12];
UmiAiCorpusWindow(corpus, 0U, 4U, storage + 1U, storage + 5U, 4U);
```
Read the arguments in order: corpus; source start offset zero; four input/target pairs; input destination; target destination; capacity of each destination measured in uint32_t elements. The function writes four elements to each range. It does not write all twelve elements of the array.

## Draw the allocation

```text
element:  0 | 1 2 3 4 | 5 6 7 8 | 9 10 11
purpose: guard inputs   targets    untouched
```
1. Draw twelve boxes and number them from zero.
2. Mark the four input elements, then the four target elements.
3. Count each group. Both have capacity for the requested four values.
4. Change the final argument to 3U in an exercise copy.
5. Observe that the Framework returns CAPACITY_EXCEEDED before writing the arrays.

Passing 4U is a promise by the caller. C cannot discover the actual allocation length from an ordinary pointer. If a caller lies about capacity, an API cannot generally repair that mistake. Allocate sufficient storage, retain its lifetime and pass the true available count.

## Arithmetic before writing

When converting a count to bytes, first check count <= SIZE_MAX / sizeof(*inputs). Multiplying before this check could wrap around for a very large count. A wrapped small result would not describe the real requested range. This guard complements the corpus source bounds; it does not replace them.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/ai/training/corpus.h).

## Continue learning

[Course contents](../../../courses/safer-c-programming/index.html) · [Previous: Read a next-token pair from bytes](36-read-next-token-pairs.md) · [Next: Recognise overlap between distinct pointers](38-recognise-overlapping-output-ranges.md)
