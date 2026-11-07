# Safer C Programming

Start with the first module and follow its lessons in order. Later project modules build on the earlier ideas. Each exercise identifies the source files, setup, expected result and recovery steps; keep your practice work in a separate folder.

## Bounds, ownership and representations

Read explicit input and failure contracts before composing stateful examples.

1. [Bounds and preserving state on failure](01-bounds-and-failure-preservation.md)
1. [Overlapping memory and ownership](02-overlap-and-ownership.md)
1. [Numbers, file writes and useful checks](03-numbers-files-and-checks.md)
1. [Define a failure boundary for a borrowed stream](04-borrowed-streams-and-failure-boundaries.md)
1. [Check representations before crossing a platform boundary](05-untrusted-sizes-and-representations.md)

## Project: a transactional record

Use allocation failures and stale revisions to check complete replacement and borrowed-pointer lifetime.

1. [Replace two fields as one complete change](06-two-fields-one-commit.md)
1. [Make memory allocation observable through a callback](07-allocator-context-and-test-doubles.md)
1. [Separate a byte span from a terminated string](08-spans-terminators-and-text-policy.md)
1. [Reject an edit based on an older revision](09-revisions-and-stale-writers.md)
1. [Know when a borrowed pointer stops being valid](10-borrowed-pointers-after-replacement.md)
1. [Make repeated cleanup harmless](11-destruction-and-idempotence.md)
1. [Design checks that prove rejected calls preserve state](12-failure-matrix-and-sentinels.md)
1. [Review a teaching model before using a Framework service](13-review-before-sharing-a-model.md)

## Project: a bounded arena

Measure space, alignment and output ownership, then rewind a temporary allocation scope.

1. [Borrow storage for a temporary report](14-borrow-storage-for-a-report.md)
1. [Reserve space for the end of a string](15-request-space-for-a-terminator.md)
1. [Understand alignment and padding](16-understand-alignment-padding.md)
1. [Check subtraction before using the result](17-subtract-only-after-checking.md)
1. [Preserve results when allocation fails](18-preserve-output-on-allocation-failure.md)
1. [Receive an allocation through the correct pointer type](19-use-a-real-void-pointer-output.md)
1. [Rewind a group of temporary allocations](20-rewind-a-temporary-allocation-scope.md)
1. [Review a bounded allocator as a complete contract](21-review-the-arena-contract.md)

## Project: checked money arithmetic

Choose integer units and validate both sides of a transfer before changing either balance.

1. [Choose a unit before doing arithmetic](22-choose-a-unit-before-doing-arithmetic.md)
1. [Check addition before performing it](23-check-addition-before-performing-it.md)
1. [Guard multiplication with division](24-guard-multiplication-with-division.md)
1. [Reject underflow as a domain result](25-reject-underflow-as-a-domain-result.md)
1. [Calculate a candidate before publishing](26-calculate-a-candidate-before-publishing.md)
1. [Validate both sides of a transfer](27-validate-both-sides-of-a-transfer.md)
1. [Refuse aliasing accounts explicitly](28-refuse-aliasing-accounts-explicitly.md)
1. [Test refusal with preserved state](29-test-refusal-with-preserved-state.md)

<!-- The module guide above owns the reading order. Earlier explanations and reference links remain available for readers following existing material. -->

<details markdown="1">
<summary>Additional explanations and reference links</summary>

<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/safer-c-programming/index.md

PURPOSE:
Introduce a course, its prerequisites, tool setup and ordered lessons.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Safer C Programming

## About this course
Practise bounds, overlapping memory, explicit ownership, failure preservation and honest safety claims.

## Before you begin
Basic C syntax helps. Each lesson defines the memory concepts it uses and links to Learning C for a slower introduction.

## Reading order
1. [Bounds and preserving state on failure](01-bounds-and-failure-preservation.md)
2. [Overlapping memory and ownership](02-overlap-and-ownership.md)
3. [Numbers, file writes and useful checks](03-numbers-files-and-checks.md)


## Prepare a development environment
A compiler translates C source. CMake describes which files belong to a program. Ninja performs the build work. CTest runs registered checks. An editor changes the source text. You may use a plain text editor before learning an IDE.

### Windows with PowerShell
1. Install MSYS2 from [its official installation guide](https://www.msys2.org/). Use the UCRT64 environment described in [the environment guide](https://www.msys2.org/docs/environments/).
2. In the MSYS2 UCRT64 terminal, follow its update instructions, then install the C tools:
~~~bash
pacman -S --needed mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-cmake mingw-w64-ucrt-x86_64-ninja git
~~~
3. Obtain the Bits2Banking repository. If it is already present, use that checkout; do not clone into it again. In the MSYS2 terminal, an example new location is:
~~~bash
mkdir -p /c/umicom
git clone https://github.com/umicom-foundation/Bits2Banking.git /c/umicom/Umicom-Bits2Banking
~~~
4. Open PowerShell and add the tools to that terminal's PATH. PATH is the list of directories searched for commands.
~~~powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
gcc --version
cmake --version
ninja --version
~~~
5. Read the files under labs/native/text-editor. Run one command at a time and stop on an error. Check $LASTEXITCODE immediately after a native command; zero reports success.
~~~powershell
cmake -S labs/native/text-editor -B build/text-editor -G Ninja -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTING=ON
cmake --build build/text-editor --parallel 2
ctest --test-dir build/text-editor --output-on-failure --no-tests=error
& ".\build\text-editor\btb-text-editor.exe"
~~~

### Linux with Bash
1. Install Git, a C compiler with the required C23 mode, CMake 3.24 or newer, and Ninja using your distribution's documented package manager. Package names and compiler versions vary.
2. Clone into a new folder if needed:
~~~bash
mkdir -p "$HOME/umicom"
cd "$HOME/umicom"
git clone https://github.com/umicom-foundation/Bits2Banking.git Umicom-Bits2Banking
cd Umicom-Bits2Banking
~~~
3. Check cc --version, cmake --version and ninja --version. If you choose a different compiler, configure a new build directory with -DCMAKE_C_COMPILER set to that compiler.
4. Run each command separately and stop on a failure. echo $? immediately afterwards displays the previous result.
~~~bash
cmake -S labs/native/text-editor -B build/text-editor -G Ninja -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTING=ON
cmake --build build/text-editor --parallel 2
ctest --test-dir build/text-editor --output-on-failure --no-tests=error
./build/text-editor/btb-text-editor
~~~

## Understand the result
The editor prints its command summary and waits for input. Type append Hello, then show, then discard on separate lines. Expect TEXT: Hello. This is a bounded ASCII console lab with one-level undo, not a graphical production editor.
The -S argument selects source; -B selects a separate build directory. Building again in that same directory normally updates changed inputs and their dependencies. Testing is a separate step. A successful compile does not establish that the tests or a user workflow passed.

## If setup fails
A missing command means its tool is not installed or not on PATH. A compiler-mode error means you need a compiler that supports the requested C mode. A missing build.ninja file means configuration did not finish successfully. Read the first diagnostic before repeating later commands. Keep source separate from generated build files.

For a slower explanation, use [Learning C](../../learning-c/index.md). The [CMake command manual](https://cmake.org/cmake/help/latest/manual/cmake.1.html) explains configuration and build options.


## What to practise next
Use [Safer C Programming](index.md) and [Building a Text Editor in C](../../05-engineering/building-a-text-editor/index.md) to apply the ideas. The [compiler course](../../05-engineering/building-a-compiler-in-c/index.md) offers a separate language project.

## Scope
These are introductory chapters and practical labs. Further topics remain to be developed. Successful reading or compilation alone does not establish runtime correctness; compare expected results with your own checks.

## Further practical lessons

- [Define a failure boundary for a borrowed stream](04-borrowed-streams-and-failure-boundaries.md)
- [Check representations before crossing a platform boundary](05-untrusted-sizes-and-representations.md)

- [Replace two fields as one complete change](06-two-fields-one-commit.md)

- [Make memory allocation observable through a callback](07-allocator-context-and-test-doubles.md)

- [Separate a byte span from a terminated string](08-spans-terminators-and-text-policy.md)

- [Reject an edit based on an older revision](09-revisions-and-stale-writers.md)

- [Know when a borrowed pointer stops being valid](10-borrowed-pointers-after-replacement.md)

- [Make repeated cleanup harmless](11-destruction-and-idempotence.md)

- [Design checks that prove rejected calls preserve state](12-failure-matrix-and-sentinels.md)

- [Review a teaching model before using a Framework service](13-review-before-sharing-a-model.md)

- [Borrow storage for a temporary report](14-borrow-storage-for-a-report.md)

- [Reserve space for the end of a string](15-request-space-for-a-terminator.md)

- [Understand alignment and padding](16-understand-alignment-padding.md)

- [Check subtraction before using the result](17-subtract-only-after-checking.md)

- [Preserve results when allocation fails](18-preserve-output-on-allocation-failure.md)

- [Receive an allocation through the correct pointer type](19-use-a-real-void-pointer-output.md)

- [Rewind a group of temporary allocations](20-rewind-a-temporary-allocation-scope.md)

- [Review a bounded allocator as a complete contract](21-review-the-arena-contract.md)

- [Choose a unit before doing arithmetic](22-choose-a-unit-before-doing-arithmetic.md)

- [Check addition before performing it](23-check-addition-before-performing-it.md)

- [Guard multiplication with division](24-guard-multiplication-with-division.md)

- [Reject underflow as a domain result](25-reject-underflow-as-a-domain-result.md)

- [Calculate a candidate before publishing](26-calculate-a-candidate-before-publishing.md)

- [Validate both sides of a transfer](27-validate-both-sides-of-a-transfer.md)

- [Refuse aliasing accounts explicitly](28-refuse-aliasing-accounts-explicitly.md)

- [Test refusal with preserved state](29-test-refusal-with-preserved-state.md)

</details>
