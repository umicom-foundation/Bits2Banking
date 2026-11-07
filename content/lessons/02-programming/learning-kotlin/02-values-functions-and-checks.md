# Calculate progress and check the result

This lesson turns a simple requirement into a function: given a total number of lessons and a completed number, calculate how many remain. A requirement describes what a program must do. A check compares its observed behaviour with that requirement.

## Setup recap

Install a JDK and the Kotlin command-line compiler. Open PowerShell or bash and confirm `java -version` and `kotlinc -version`. Create an empty practice folder, then save [Progress.kt](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/languages/kotlin-first-program/Progress.kt) there using that exact filename. A `.kt` file is Kotlin source. The [first lesson](01-tools-and-first-program.md) gives the complete installation and file-creation steps.

## 1. Read the requirement before the code

A valid total is zero or more. A completed count must be between zero and the total, including both ends. For valid input the answer is `total - completed`. Invalid input must be reported instead of becoming a negative remaining count.

| Total | Completed | Expected behaviour |
| --- | --- | --- |
| 4 | 1 | Return 3 |
| 4 | 4 | Return 0 |
| 0 | 0 | Return 0 |
| 4 | 5 | Reject the input |

## 2. Follow the function

```kotlin
fun remainingLessons(total: Int, completed: Int): Int {
    require(total >= 0) { "Total must not be negative" }
    require(completed in 0..total) { "Completed must be between zero and total" }
    return total - completed
}
```

`total` and `completed` are parameters: names for values received by a function. `Int` describes a signed integer. The `: Int` after the parameter list describes the result type. `>=` means greater than or equal to. `0..total` creates an inclusive range, and `in` asks whether the value belongs to it.

`require` throws an exception if its condition is false. An exception transfers control out of the ordinary calculation to an error handler; it is not a normal numerical result. The text in braces supplies an explanation. Only valid inputs reach `return`, which sends the difference to the caller. Validating first also makes the subtraction fit this nonnegative integer range.

## 3. Read the caller

In `main`, `val total = 4` introduces a value that cannot be reassigned through that name. Kotlin infers its integer type. `remainingLessons(total, completed)` calls the function with two arguments. The expression `${remainingLessons(total, completed)}` inserts the calculated result into a string.

The example then uses `check` for facts that must hold. `check(remainingLessons(0, 0) == 0)` compares the result with zero; `==` means equality. `runCatching { ... }` runs a block and captures its success or failure. `.isFailure` lets the example check that invalid input was rejected. This introductory check verifies rejection, not the exact exception type or message.

## 4. Compile and run all the checks

```text
kotlinc Progress.kt -include-runtime -d progress.jar
java -jar progress.jar
```

Expected application output:

```text
Remaining lessons: 3
All progress checks passed.
```

Stop if the compiler reports an error. A failing check ends the program with an exception rather than printing the final success line. Read the first error and its source location; the line number may differ if you added comments.

## 5. Investigate an intentional mistake

Make a separate copy of the source for this exercise. Change `return total - completed` to `return total + completed`. Predict the result before running. The first printed result becomes 5, and the all-completed check fails because 4 + 4 is 8, not 0. Restore subtraction, recompile and run again. Keep both source and observed output if you want to explain the repair later.

## Connection to Umicom

Compare this example with [the C progress contract](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/first-c-programs/counts.c). C reports a status and writes a result through an output parameter; this Kotlin example reports invalid input using an exception. Both start with the same questions: what is valid, what is returned, and what happens on failure? These are teaching examples, not a production mobile binding to Framework.

## Exercise and answer

Add `check(remainingLessons(6, 2) == 4)` to `main`. It should pass because both inputs satisfy the contract and 6 − 2 is 4. Add `check(runCatching { remainingLessons(6, -1) }.isFailure)` to check the lower boundary. A passing normal example alone would not check that invalid boundary.

[Previous lesson](01-tools-and-first-program.md) · [Course contents](index.md) · [Android Development](../../15-mobile-development/learning-android/index.md)

[Continue: Convert command-line text into checked values](03-convert-command-line-text.md)
