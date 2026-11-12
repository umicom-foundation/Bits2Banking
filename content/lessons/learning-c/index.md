# Learning C

Start with First programs. Leave the systems-programming studies until you understand arrays, pointers and separate source files.

[Beginner sequence](../../start/learning-sequence.md) · [Browser course](../../courses/learning-c/index.html)

## First programs

Read, build, calculate, choose, repeat and call functions.

1. [Your first C program](01-read-your-first-program.md)
2. [Build and run your first C program](02-build-and-run-one-step.md)
3. [Variables and simple calculations](03-values-and-calculations.md)
4. [Making decisions with if](04-decisions-and-valid-input.md)
5. [Repeating work with a loop](05-repeat-with-a-boundary.md)
6. [Writing and calling a function](06-functions-with-a-contract.md)
7. [Test what you promised and understand failures](07-check-results-and-errors.md)

## Working with more information

Learn arrays, structures, pointers and separate source files after the first programs.

1. [Keep several values in an array](09-arrays-and-valid-positions.md)
2. [Group related values in a structure](12-structures-and-complete-results.md)
3. [Let a function read memory you still own](10-pointers-and-borrowing.md)
4. [Connect declarations, source files and the linker](15-headers-objects-and-linking.md)

## Further study: systems programming

Optional source studies after the introductory modules. These are not required to finish your first C programs.

1. [Connect borrowed memory to bounded system input](11-bounded-spans-and-rejection.md)
2. [Pass a function to separate policy from mechanism](13-function-pointers-and-test-doubles.md)
3. [Storage duration and freestanding code](14-storage-duration-and-freestanding-code.md)
4. [Keep counts, offsets and progress separate](16-counts-offsets-and-progress.md)
5. [Represent bytes with bits and hexadecimal](17-bits-and-hexadecimal.md)
6. [Check a function at its boundaries](18-check-a-function-at-its-boundaries.md)
7. [Move from small programs to OS and Kernel source](08-connect-to-systems-lessons.md)

## Practise with the source

The small examples are in `labs/native/first-c-programs`. Begin with `hello.c`. Read each example, predict its result, then try it in your own practice folder.


## Course outline: later topics

Text parsing, ownership, error handling and a complete console project.

[Choose another subject](../../start/course-series.md).

## Step-by-step practical labs

Each lab includes a setup recap, commands, expected results and a repair exercise. Work in a practice folder.

- [Create, compile and run C in a terminal](terminal-lab.md)
- [Call an Assembly function from C](terminal-assembly-lab.md)
- [Continue the same project in Visual Studio](terminal-to-visual-studio.md)

## Practical labs: read, change and check

Follow these after the introductory lessons. Each lab includes its own setup recap and explains the expected result.

- [Length, capacity and the end of a string](19-length-capacity-and-terminators.md)
- [Allocation outputs and lifetimes](20-allocation-outputs-and-lifetimes.md)

## Continue with a practical source study

A function can refuse a request. The caller must know whether a result was produced before using it. This lab follows one small C function from input checks to output assignment, then designs checks for its boundary.

- [Follow a rejected function call](21-follow-a-rejected-call.md)


## Further practical lessons

- [Open, read and close a file](22-open-read-and-close-a-file.md)
- [Read a file in bounded chunks](23-chunks-eof-and-read-errors.md)
- [Return a status and publish one complete result](24-status-values-and-complete-results.md)
- [Check a result using known answers and another tool](25-check-file-digests-independently.md)


## Follow C from source to executable

Continue with preprocessing, assembly, object files, linking and incremental builds using a small consumer of Umicom C.

1. [Read the map from source to executable](26-read-the-build-map.md)
1. [Inspect the source after preprocessing](27-inspect-preprocessed-source.md)
1. [Inspect generated assembly without guessing its meaning](28-inspect-generated-assembly.md)
1. [Understand object files and unresolved symbols](29-object-files-and-symbols.md)
1. [Link a program with an existing native SDK](30-link-with-a-native-sdk.md)
1. [Read diagnostics at the stage that produced them](31-read-diagnostics-by-stage.md)
1. [Observe which files an incremental build rebuilds](32-observe-incremental-rebuilds.md)
1. [Review and extend a complete native consumer](33-review-a-complete-native-consumer.md)
