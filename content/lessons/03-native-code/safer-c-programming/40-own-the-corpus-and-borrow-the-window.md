<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/safer-c-programming/40-own-the-corpus-and-borrow-the-window.md

PURPOSE:
Follow corpus and output lifetimes

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Follow corpus and output lifetimes

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


## Ownership answers who releases storage

The caller owns the source array and the output array. UmiAiCorpusCreate copies the source into a separate owned corpus. The Framework owns that internal allocation until UmiAiCorpusDestroy releases it. The caller holds a handle while the corpus is alive.

The output pointers are borrowed for one synchronous call. The corpus service writes into the supplied arrays but does not keep their addresses for later work. The arrays must exist, be writable and have enough elements for the complete call.

## Walk through the lifetime

```text
create local source -> create corpus copy -> request output windows
                    -> inspect outputs -> destroy corpus -> return
```
1. Find corpus = NULL at the start of main.
2. Check the return from Create before any Window call.
3. Follow the error paths after successful creation. Each destroys the corpus before returning.
4. Follow the success path. It prints the output, destroys the corpus and returns zero.
5. Confirm that no later statement uses the destroyed handle.

A dangling pointer still contains an old address after the object it referred to has ended its lifetime. Destroying a corpus does not automatically clear every copy of its handle elsewhere. Set your local handle to NULL when that helps subsequent control flow, and avoid making unnecessary aliases. A NULL assignment cannot update other copies.

## A safe application boundary

A Studio lesson viewer can request a token preview from a Framework service. It should own the view's output buffer and release or replace it only when the synchronous request ends. For asynchronous requests, the design needs explicit retention and cancellation so the worker cannot write into a view that has closed.

Do not infer those asynchronous guarantees from this synchronous API. The small laboratory teaches the lifetime boundary that a larger interface must preserve.

## Review question

Can source[] go out of scope after successful corpus creation? Yes, the corpus stores a copy. Can corpus be used after Destroy? No. Can the output array be read after Destroy? Yes, while the caller's own array remains alive; its token values were written into caller-owned storage.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-framework/blob/main/learning/native-llm/inspect_corpus_ranges.c).

## Continue learning

[Course contents](../../../courses/safer-c-programming/index.html) · [Previous: Keep caller output unchanged when a request fails](39-keep-failed-output-unchanged.md) · [Next: Turn a range contract into focused regression checks](41-qualify-the-corpus-range-contract.md)
