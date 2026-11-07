<!--
Umicom Bits2Banking
File: content/lessons/02-programming/learning-pascal/04-group-values-in-records.md

PURPOSE:
Explain the lesson: Group related values in a record.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Group related values in a record

## One value with named parts

A record groups related values under one type name. TLessonProgress contains Total and Completed. A variable of that type represents one course's progress; another variable can represent a different course independently.

An array stores several values of one type. The example uses an array containing two progress records. Index zero is the first record and index one is the second.

## Setup recap

Install Free Pascal, CMake and Ninja. Check them with `fpc -iV`, `cmake --version` and `ninja --version`. Follow the [records lab](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/languages/pascal-progress/RECORDS.md) in a practice directory. Keep the unit and programs together.

## Read the declaration

~~~pascal
type
  TLessonProgress = record
    Total: Integer;
    Completed: Integer;
  end;
~~~

The field names explain what each integer means. A dot selects a field: `Courses[0].Completed` selects the completed count in the first array element.

`TryCreateProgress` checks the proposed values before publishing them into the record. It returns True for success and False for rejection. A valid empty course has total zero and completed zero.

## Lab

1. Configure and build the Pascal lab.
2. Run progress_records.
3. Expect Course 1: 2 lessons remaining and Course 2: 3 lessons remaining.
4. Locate the call that advances only Courses[0].
5. Read the loop bounds, Low(Courses) and High(Courses).
6. In a practice copy, add a third initialized course and adjust the array bounds. Predict its output before running it.

Every array element must be initialized before its fields are read. A larger declared array does not automatically create valid progress values.

## Values and updates

The unit's functions receive `var State` when they need to change the caller's record. The ordinary integer parameters are inputs. This separation makes the operation's effects visible in its declaration.

The example keeps records in memory. It does not save learner progress to a file or database.

## Exercise and explanation

Why use Low and High instead of assuming the first index is always zero? Pascal arrays can declare different bounds. The loop should follow the actual array definition.

## Troubleshooting

An out-of-range error can reveal a wrong index. Keep range checking enabled while learning. Do not silence it to make an invalid access appear successful. Record fields also need domain checks: a representable integer may still be an impossible completed count.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/languages/pascal-progress/progress_records.pas). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](03-loops-and-checkable-results.md) · [Next lesson](05-share-a-unit-and-preserve-state.md)

