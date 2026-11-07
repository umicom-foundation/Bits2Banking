<!--
Umicom Bits2Banking
File: content/lessons/02-programming/learning-algorithms/index.md

PURPOSE:
Introduce a course, its prerequisites, tool setup and ordered lessons.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Learning Algorithms

## About this course
Find and order values, trace each operation, and compare the work different algorithms perform.

## Before you begin
You should recognise an array and a loop. A short recap and the linked programming course provide a route back.

## Reading order
1. [Linear search and counting work](01-linear-search-and-cost.md)
2. [Insertion sort and a promise kept at every step](02-insertion-sort-and-invariants.md)
3. [Binary search and its sorted-input promise](03-binary-search-and-preconditions.md)


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
5. Read the files under labs/native/collections. Run one command at a time and stop on an error. Check $LASTEXITCODE immediately after a native command; zero reports success.
~~~powershell
cmake -S labs/native/collections -B build/collections -G Ninja -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTING=ON
cmake --build build/collections --parallel 2
ctest --test-dir build/collections --output-on-failure --no-tests=error
& ".\build\collections\btb-collections.exe"
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
cmake -S labs/native/collections -B build/collections -G Ninja -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTING=ON
cmake --build build/collections --parallel 2
ctest --test-dir build/collections --output-on-failure --no-tests=error
./build/collections/btb-collections
~~~

## Understand the result
The program prints 2 2 7 9 and then 7 is at index 2. The checks cover full and empty structures, queue wraparound, sorting and searching.
The -S argument selects source; -B selects a separate build directory. Building again in that same directory normally updates changed inputs and their dependencies. Testing is a separate step. A successful compile does not establish that the tests or a user workflow passed.

## If setup fails
A missing command means its tool is not installed or not on PATH. A compiler-mode error means you need a compiler that supports the requested C mode. A missing build.ninja file means configuration did not finish successfully. Read the first diagnostic before repeating later commands. Keep source separate from generated build files.

For a slower explanation, use [Learning C](../../learning-c/index.md). The [CMake command manual](https://cmake.org/cmake/help/latest/manual/cmake.1.html) explains configuration and build options.


## What to practise next
Use [Safer C Programming](../../03-native-code/safer-c-programming/index.md) and [Building a Text Editor in C](../../05-engineering/building-a-text-editor/index.md) to apply the ideas. The [compiler course](../../05-engineering/building-a-compiler-in-c/index.md) offers a separate language project.

## Scope
These are introductory chapters and practical labs. Further topics remain to be developed. Successful reading or compilation alone does not establish runtime correctness; compare expected results with your own checks.

## Further practical lessons

- [Test sorting without trusting another sort](04-test-order-and-preservation.md)
- [Choose a search strategy for the work you actually do](05-choose-search-for-a-workload.md)

- [Find the first matching duplicate](06-find-the-first-duplicate.md)

- [Prove a search loop makes progress](07-prove-a-search-loop-makes-progress.md)

- [Check that duplicates survive sorting](08-check-duplicates-survive-sorting.md)

- [Use idempotence as an extra check](09-use-idempotence-as-an-extra-check.md)
