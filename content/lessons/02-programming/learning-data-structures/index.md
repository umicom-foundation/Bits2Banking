# Learning Data Structures

Start with the first module and follow its lessons in order. Later project modules build on the earlier ideas. Each exercise identifies the source files, setup, expected result and recovery steps; keep your practice work in a separate folder.

## Arrays, stacks and queues

Start with occupied length, capacity and the order in which values are read.

1. [Arrays, length and capacity](01-arrays-length-and-capacity.md)
1. [Stacks and the order of undo](02-stacks-and-undo.md)
1. [Queues and wraparound storage](03-queues-and-wraparound.md)

## Container contracts

Follow full queues, identity, undo history and producer/consumer ownership.

1. [Handle a full queue without losing work](04-queue-backpressure.md)
1. [Check the promises that keep a container valid](05-container-invariants.md)
1. [Trace a producer and a consumer](06-trace-a-producer-and-consumer.md)
1. [Separate storage slots from job identity](07-separate-slot-and-job-identity.md)
1. [Reserve undo history before changing state](08-reserve-undo-before-changing-state.md)
1. [Design a container caller contract](09-design-a-container-caller-contract.md)

## Project: a work pipeline

Compose queues while retaining completion capacity, cancellation results and conservation rules.

1. [Compose a work pipeline from existing queues](10-compose-a-work-pipeline.md)
1. [Stop work when its completion cannot be delivered](11-completion-backpressure.md)
1. [Treat cancellation as a terminal result](12-cancellation-is-a-result.md)
1. [Keep a delivered receipt independent of queue storage](13-own-a-receipt-after-release.md)
1. [Give one dispatch turn a finite work budget](14-budget-a-dispatch-turn.md)
1. [Stop admission before draining a service](15-quiesce-then-drain.md)
1. [Use conservation rules to check a pipeline](16-count-invariants.md)
1. [Understand what a diagnostic digest proves](17-digests-and-meaning.md)

## Project: an event ring

Keep recent observations in bounded storage and expose a complete chronological snapshot.

1. [Store recent events in a fixed ring](18-store-recent-events-in-a-ring.md)
1. [Read events in chronological insertion order](19-separate-storage-order-from-reading-order.md)
1. [Account for overwritten observations](20-account-for-overwritten-observations.md)
1. [Distinguish event sequence from event time](21-distinguish-sequence-from-time.md)
1. [Treat sequence exhaustion explicitly](22-treat-sequence-exhaustion-explicitly.md)
1. [Preserve an address-stable owner](23-preserve-address-stable-owners.md)
1. [Publish a snapshot after validation](24-publish-a-snapshot-after-validation.md)
1. [Design a diagnostic view contract](25-design-a-diagnostic-view-contract.md)

<!-- The module guide above owns the reading order. Earlier explanations and reference links remain available for readers following existing material. -->

<details markdown="1">
<summary>Additional explanations and reference links</summary>

<!--
Umicom Bits2Banking
File: content/lessons/02-programming/learning-data-structures/index.md

PURPOSE:
Introduce a course, its prerequisites, tool setup and ordered lessons.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Learning Data Structures

## About this course
Organise values in arrays, stacks and queues, and learn how to keep each structure valid.

## Before you begin
You should recognise a variable, a function and a loop. The first lesson recaps these and links to Introduction to Programming.

## Reading order
1. [Arrays, length and capacity](01-arrays-length-and-capacity.md)
2. [Stacks and the order of undo](02-stacks-and-undo.md)
3. [Queues and wraparound storage](03-queues-and-wraparound.md)


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

- [Handle a full queue without losing work](04-queue-backpressure.md)
- [Check the promises that keep a container valid](05-container-invariants.md)

- [Trace a producer and a consumer](06-trace-a-producer-and-consumer.md)

- [Separate storage slots from job identity](07-separate-slot-and-job-identity.md)

- [Reserve undo history before changing state](08-reserve-undo-before-changing-state.md)

- [Design a container caller contract](09-design-a-container-caller-contract.md)

- [Compose a work pipeline from existing queues](10-compose-a-work-pipeline.md)

- [Stop work when its completion cannot be delivered](11-completion-backpressure.md)

- [Treat cancellation as a terminal result](12-cancellation-is-a-result.md)

- [Keep a delivered receipt independent of queue storage](13-own-a-receipt-after-release.md)

- [Give one dispatch turn a finite work budget](14-budget-a-dispatch-turn.md)

- [Stop admission before draining a service](15-quiesce-then-drain.md)

- [Use conservation rules to check a pipeline](16-count-invariants.md)

- [Understand what a diagnostic digest proves](17-digests-and-meaning.md)

- [Store recent events in a fixed ring](18-store-recent-events-in-a-ring.md)

- [Read events in chronological insertion order](19-separate-storage-order-from-reading-order.md)

- [Account for overwritten observations](20-account-for-overwritten-observations.md)

- [Distinguish event sequence from event time](21-distinguish-sequence-from-time.md)

- [Treat sequence exhaustion explicitly](22-treat-sequence-exhaustion-explicitly.md)

- [Preserve an address-stable owner](23-preserve-address-stable-owners.md)

- [Publish a snapshot after validation](24-publish-a-snapshot-after-validation.md)

- [Design a diagnostic view contract](25-design-a-diagnostic-view-contract.md)

</details>
