# Describe a contract and run D unit tests

A function contract describes accepted inputs, the result, and failure behaviour. A unit test exercises a small unit of code against that contract. We will calculate remaining lessons, then deliberately check inputs at the edges.

## Setup recap

Install DMD for your operating system and confirm `dmd --version` in PowerShell or bash. Create a writable practice folder. Save [progress.d](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/languages/d-first-program/progress.d) into it. The [installation lesson](01-install-and-run.md) explains the tools and file commands from the beginning. Reading and tracing the example on paper needs no installation.

## 1. Define valid inputs

The total must be zero or greater. Completed lessons must be between zero and that total. For valid inputs, subtract completed from total. For example, 4 total and 1 completed leaves 3. A completed count of 5 for a total of 4 must be rejected.

```d
int remainingLessons(int total, int completed) @safe {
    enforce(total >= 0, "Total must not be negative");
    enforce(completed >= 0 && completed <= total,
            "Completed must be between zero and total");
    return total - completed;
}
```

`int` is a signed integer type. The first `int` is the result type; the two inside parentheses describe parameters. `&&` means both conditions must hold. `enforce`, imported from `std.exception`, throws an exception when a condition is false. The caller can handle that exception rather than use an invalid count. All valid inputs make the subtraction stay between zero and the total.

`@safe` asks the D compiler to check this function against D's safe-code restrictions. It does not prove that the function calculates the right answer, nor that every dependency of an entire application is free of defects. The numerical contract still needs tests.

## 2. Read the test block

The source contains a `unittest` block. It checks ordinary input, an empty course and a completed course:

```d
assert(remainingLessons(4, 1) == 3);
assert(remainingLessons(0, 0) == 0);
assert(remainingLessons(4, 4) == 0);
```

`assert` checks a condition. `==` compares values; it does not assign a new value. The block also uses `assertThrown!Exception(...)` for three invalid inputs. The `!Exception` specifies the exception type expected by that library helper. Here it confirms rejection; a later exercise can check a more specific type and message.

## 3. Enable tests when compiling

PowerShell:

```powershell
dmd -unittest -g progress.d -of=progress.exe
.\progress.exe
$LASTEXITCODE
```

Bash:

```bash
dmd -unittest -g progress.d -of=progress
./progress
echo $?
```

Run each next command only if the previous one succeeded. `-unittest` includes the test block. The runtime executes it before `main`. After successful checks, application output includes `Remaining lessons: 3`. The runtime may also print a unit-test summary. A normal result should have completion code zero. Keep assertions enabled for this exercise; do not add `-release`.

## 4. Observe a meaningful failure

Copy the source to another practice file. Change subtraction to addition and compile with `-unittest`. The first test should fail: 4 + 1 is 5. Read the diagnostic and locate the assertion. Restore subtraction, compile and run again. This demonstrates that the check examines a result rather than merely reporting that a program started.

## 5. Relate the example to Framework

Read [the C activity contract](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-activity/activity.h) and [its implementation](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-activity/activity.c). Those files use Framework's `UmiStatus` and preserve the caller's output on failure. This D example uses exceptions. Neither mechanism excuses skipping input validation. A production D client would need an explicit native interface to the shared C service; this introductory example does not supply that binding.

## Exercise and worked answer

Add `assert(remainingLessons(8, 3) == 5);` inside `unittest`, then rebuild with `-unittest`. Add a rejection check for `remainingLessons(8, 9)` using `assertThrown!Exception`. The first checks a valid result; the second checks an invalid upper boundary. Both are needed to describe the contract's two paths.

[Previous lesson](01-install-and-run.md) · [Course contents](index.md) · [Learning C](../../learning-c/index.md)

[Next lesson: Apply an existing function to a sequence](03-apply-a-function-to-a-sequence.md)
