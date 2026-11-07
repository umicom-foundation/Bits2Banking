<!--
Umicom Bits2Banking
File: content/lessons/02-programming/learning-pascal/05-share-a-unit-and-preserve-state.md

PURPOSE:
Explain the lesson: Share a unit and preserve state on failure.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Share a unit and preserve state on failure

## Separate the public contract from its implementation

A Pascal unit packages declarations and code that several programs can use. The interface section declares the available types and functions. The implementation section supplies their bodies.

LessonProgress owns the arithmetic used by the original terminal example and the new record example. The old local function remains disabled in progress.pas for comparison; active callers now use the unit.

## Setup recap

Use the [records lab](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/languages/pascal-progress/RECORDS.md). Install Free Pascal, CMake and Ninja, then configure with BUILD_TESTING=ON. The guide supplies commands for PowerShell and bash. No earlier course is required, but read the record declaration before following the update functions.

## Follow a rejected update

~~~text
existing record
      |
check total and completed
      |
invalid? -> return False, keep both fields
      |
valid -> assign both fields, return True
~~~

`TryCreateProgress` first calls RemainingLessons to validate the proposed values. It writes the fields only after validation succeeds. A failed attempt must not erase a valid record that the caller already owns.

`TryCompleteLesson` checks the record again. Its fields are public, so a caller could have modified them directly. A creation function alone cannot protect every later operation.

## Lab

1. Build and run the registered Pascal tests.
2. Read progress_checks.pas and find the saved Before record.
3. Follow the invalid creation cases and the unchanged-field checks.
4. Find the empty-course case and explain why completion is refused.
5. Find the High(Integer) case and explain why the last increment is safe.
6. Confirm that the next increment is rejected rather than wrapping.

If Completed is below Total and Total fits in Integer, incrementing Completed by one cannot exceed Total. The code establishes that condition before calling Inc.

## Modules and build outputs

A compiler creates intermediate files for a unit. The CMake project gives each program a separate output directory for these files. Two compilers must not write the same unit artifacts simultaneously during a parallel build.

## Exercise and explanation

Does returning False prove the record was preserved? No. The check must compare its fields with the saved values. A function can report failure after partially modifying state unless its implementation prevents that.

## Further work

A reusable production application should delegate domain behaviour to Framework. This unit teaches Pascal modules and contracts; it does not introduce a second production learner-progress service. The [Free Pascal record reference](https://www.freepascal.org/docs-html/ref/refsu15.html) also explains why raw record layout is unsuitable as an assumed portable file format.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/languages/pascal-progress/lessonprogress.pas). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](04-group-values-in-records.md)


[Next: Build a small course notebook](06-build-a-course-notebook.md)
