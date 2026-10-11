# 71. Use the C compiler to detect defects before testing

A compiler translates C source into machine code. Before producing a programme, it can also warn about suspicious expressions, implicit conversions and mistakes in interfaces. Some compilers offer additional analysis that explores possible paths through a function without executing it.

These tools are especially useful for Umicom Framework and Umicom Kernel, where memory lifetimes, explicit integer widths and predictable behaviour matter.

## 1. Distinguish errors, warnings and runtime failures

A **compiler error** prevents a programme from being compiled. For example, a missing declaration may stop compilation. A **warning** identifies code that the compiler can translate but which deserves review. A **runtime error** happens when a programme executes, such as reading outside an array or using a pointer after its storage has become invalid.

A successful compile does not prove that a programme is correct. Passing tests does not prove that every possible input is safe. We use several techniques together.

## 2. Enable useful warnings

The new C23 laboratories compile with:

```text
-Wall -Wextra -Wpedantic -Wconversion -Wshadow
```

`-Wall` and `-Wextra` enable many diagnostics. `-Wconversion` highlights conversions that may change values. `-Wshadow` warns when a nested declaration hides an existing name. `-Wpedantic` identifies extensions outside the requested language mode.

Do not silence a warning merely to make the log shorter. Inspect the type, the range and the reason for the conversion. An explicit cast does not make an unsafe operation safe.

## 3. Examine one checked calculation

Open `labs/native/bounded-ledger-line/ledger_line.c`. The account-number parser contains:

```c
if (account > (UINT32_MAX - digit) / 10U)
    return BTB_LEDGER_RANGE;
account = account * 10U + digit;
```

Ask what would happen if a decimal account identifier contained too many digits. Without the check, unsigned arithmetic can wrap; the parser could accept an incorrect identifier. The comparison proves that the next multiplication and addition fit the target type.

Find a similar check in the arena allocator before it calculates an aligned address. These examples show that preventing a defect is more useful than catching memory corruption after it happens.

## 4. Inspect generated Assembly

The `-S` compiler option produces Assembly instead of linking a complete executable. From the Bits2Banking root:

```powershell
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
& "C:\msys64\ucrt64\bin\gcc.exe" -std=c23 -O1 -S ".\labs\native\bounded-ledger-line\ledger_line.c" -o ".\output\ledger_line.s"
```

The `output/` folder should already exist in your checkout. Open `output/ledger_line.s` to inspect the compiler-generated instructions. Exact registers and instruction sequences vary with compiler version, architecture and optimisation flags. You are not expected to memorise every instruction at this stage.

Notice that the source-level function has been translated into instruction sequences for comparisons, arithmetic and conditional branches. Compare these with the explicit Assembly lessons in the Framework and Umicom Kernel repositories.

## 5. Run static analysis

Recent GCC compilers support an extra `-fanalyzer` pass:

```powershell
& "C:\msys64\ucrt64\bin\gcc.exe" -std=c23 -fanalyzer -Wall -Wextra -fsyntax-only ".\labs\native\bounded-ledger-line\ledger_line.c"
```

`-fsyntax-only` checks the translation unit without producing an executable. The analyser attempts to follow selected program paths and may identify problems such as invalid pointer use. It can report false positives and it cannot prove complete memory safety.

Clang provides its own analyser; on a machine with Clang installed, try `clang --analyze -std=c23 labs/native/bounded-ledger-line/ledger_line.c` from the repository root. If the installed compiler does not recognise a flag, inspect its version and supported options rather than assuming the test ran.

## 6. Test what the analyser cannot prove

Build the ledger-line laboratory and run its CTest suite. The deterministic mutation test supplies 20,000 different byte sequences and checks that rejected input never changes the destination row.

The tests exercise actual code paths; static analysis reasons about source without running it. A sanitizer build can add checks for certain memory errors on supported toolchains. These methods complement one another.

## 7. Connect this to Umicom Kernel

Umicom Kernel is built from freestanding C23 and architecture-specific Assembly. Its build must not assume that the normal application runtime, heap or operating-system services already exist.

Read the [Kernel build instructions](https://github.com/umicom-foundation/umicom-kernel/blob/main/docs/BUILD_AND_TEST.md), then the [first-boot explanation](https://github.com/umicom-foundation/umicom-kernel/blob/main/docs/FIRST_BOOT.md). Notice how the Kernel uses a specific target architecture and QEMU execution environment, unlike an ordinary Windows console programme.

**Exercise:** Choose a checked arithmetic expression in `ledger_line.c`. Explain the input that would overflow without that check. Then locate the branch generated for a compiler build and describe, in plain English, what condition makes it jump to the error path.
