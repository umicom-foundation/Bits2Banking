# Checked progress batches in D

Start with `progress.d`, which contains `remainingLessons`, its unit tests and a main function. `batches.d` imports that existing calculation and applies it to several courses. These are language exercises, not a replacement for Framework's shared learning services.

## Prepare and run

Install DMD for your operating system. In PowerShell or bash, confirm `dmd --version`. Open this laboratory directory and compile both files:

~~~text
dmd -unittest -of=progress-checks progress.d batches.d
~~~

On Windows PowerShell, run `./progress-checks.exe`. On Linux or macOS bash, run `./progress-checks`. Successful unit tests are normally silent; the existing main function then prints `Remaining lessons: 3`. A failed assertion stops the program. Do not use release options that disable checks for this exercise.

The `-unittest` switch includes the unittest blocks from both modules. Compiling only progress.d does not run the new batch checks. Keep the existing source file name because the import names that module.

## Trace the data

For totals `[4, 0, 6]` and completed `[1, 0, 6]`, write the expected result `[3, 0, 0]`. The function first compares list lengths, allocates a new result, and calls remainingLessons for each index. An index is a position, starting at zero.

The result has its own elements. Changing result[0] must not change either input. The tests check that property as well as invalid counts and unequal lengths. Failure on the second pair does not return a partly filled result.

D dynamic arrays describe a length and an element range. A copied slice can refer to the same elements, so copying an array variable does not by itself promise independent storage. This function explicitly allocates new storage. See the [D array reference](https://dlang.org/spec/arrays.html).

## Extend the experiment

Add `[10, 10]` and `[10, 0]` to the unittest block, expecting `[0, 10]`. Add a case with a negative completed value in the final position and expect an exception. Keep the original checks. Record the compiler version, command and observed result separately from your prediction.

A module-not-found error means batches.d cannot find progress.d from the selected source paths. A missing executable may mean compilation failed; read the first compiler error before trying to launch. Memory-safety annotations do not establish that every business rule is correct: explicit count checks are still required.

