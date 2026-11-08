<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/safer-c-programming/36-read-next-token-pairs.md

PURPOSE:
Read a next-token pair from bytes

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Read a next-token pair from bytes

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


## What the program represents

A byte is a small integer. In this example the bytes spell abcdef. The model input at one position is paired with the following byte as its target: the input a is paired with b, then b with c. A training system can use these pairs to learn to predict what follows. The laboratory only prepares pairs.

The corpus copies the six bytes into storage it owns. UmiAiCorpusCreate receives the address of the first byte, the byte count and the address of a variable where it returns the corpus handle. A handle identifies an object managed by the library. Check its UmiStatus result before using it.

```c
const uint8_t source[] = {'a', 'b', 'c', 'd', 'e', 'f'};
UmiAiCorpus *corpus = NULL;
UmiStatus status = UmiAiCorpusCreate(source, sizeof(source), &corpus);
```
The array has six elements and no automatic string terminator because it uses an explicit initializer. sizeof(source) is the number of bytes in that array. uint8_t names an unsigned eight-bit integer on the supported hosts. NULL means the handle does not yet identify an object.

## Follow the numbers

Framework reserves four token identifiers. Its byte tokenizer represents each ordinary byte as its numeric value plus UMI_AI_BYTE_OFFSET, which is four. For this laboratory, a has byte value 97, so its token is 101. The first target b becomes 102. These are byte tokens; they do not claim to be words or to understand a sentence.

1. Run the laboratory.
2. Find the four pair lines after the two range messages.
3. Compare them with the expected pairs 101/102, 102/103, 103/104 and 104/105.
4. Inspect byte_tokenizer.h to find the reserved-token definitions.
5. Change the source letters in a separate exercise copy, rebuild and predict the new output before running it.

## Check your understanding

Why does a four-pair window need five source bytes? Pair four uses the fifth byte as its target. Predicting the next byte requires one more source byte than the input count. A request starting at the final byte cannot produce even one next-byte pair.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-framework/blob/main/learning/native-llm/inspect_corpus_ranges.c).

## Continue learning

[Course contents](../../../courses/safer-c-programming/index.html) · [Next: Distinguish elements, bytes and writable capacity](37-elements-bytes-and-capacity.md)

<!-- Course metadata owns the reading order; retain the existing lesson and add its missing continuation. -->
[Previous lesson](35-review-and-qualify-a-boundary-fix.md)

[Written course contents](index.md)
