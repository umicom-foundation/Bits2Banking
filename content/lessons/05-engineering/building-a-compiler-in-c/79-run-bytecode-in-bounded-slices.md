<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/79-run-bytecode-in-bounded-slices.md

PURPOSE:
Run bytecode in bounded slices

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Run bytecode in bounded slices

[Course contents](index.md)
A program can take several instructions to finish. If a host executes all of them in one long call, it cannot handle another event until that call returns. A slice is a small allowance of instructions. The virtual machine executes up to that allowance, saves its state, and gives control back to its caller. This lesson uses Umicom C's existing integer bytecode machine; it does not introduce a new machine-code compiler.


## 1. Read the four-instruction example

~~~text
PUSH 7
PUSH 6
MULTIPLY
RETURN
~~~

PUSH places a number on the machine's stack, a list where the most recently added item is used first. MULTIPLY consumes the two top numbers and leaves their product. RETURN marks a finished computation. The program counter, called pc in the source, identifies the next instruction. A slice allowance of two stops after the two PUSH operations. A second call multiplies and returns 42. No native thread is created.


## 2. Separate two limits

Lifetime fuel is the maximum number of instructions this admitted program may execute altogether. The slice budget limits a single call. Fuel prevents endless execution; slices let the owner regain control regularly. Returning to the host does not restore fuel. RETURN itself consumes one instruction. Four instructions therefore need fuel of at least four, even when each slice has a budget of two.

~~~text
lifetime fuel = 4
slice budget  = 2

call 1: executed 2, finished 0, total executed 2
call 2: executed 2, finished 1, total executed 4
result: 42
~~~


## 3. Inspect the public API

Open include/umicom_c/machine.h. UmcMachine contains the admitted program and its execution frame. UmcSliceResult reports instructions executed by the current call and whether RETURN completed. The owner supplies these structures, so the slice function needs no heap allocation. Keep the machine, report, diagnostic and optional trace storage separate. Do not edit machine fields or share one machine between concurrent callers.

~~~c
UmcSliceResult report;
UmcStatus status = umc_machine_run_slice(
    &machine, 2, &report, NULL, &diagnostic);
if (status != UMC_OK) {
    /* Stop here and display diagnostic; no result is available. */
}
/* UMC_OK plus report.finished == 0 means paused, not complete. */
~~~

This fragment assumes machine was successfully initialized. It is an API reading exercise, not a complete program. The executable regression example is tests/test_machine_slices.c. Read its sizes function to see initialization, repeated calls and result publication together.


## 4. Build and check the runtime

1. Open PowerShell in the umicom-c repository. Confirm that gcc, cmake and ninja are available on PATH.
2. Run each command below separately. If a command reports an error, stop and read the first diagnostic.
3. The selected tests should pass. Read the test names and counts printed by your own build; this page does not establish that your checkout has passed.

~~~powershell
cmake -S . -B build/slices-debug -G Ninja -DCMAKE_C_COMPILER=gcc -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTING=ON
cmake --build build/slices-debug --parallel 2
ctest --test-dir build/slices-debug -R machine.slices --output-on-failure --no-tests=error
~~~


## 5. Explain the boundary

An instruction allowance is not a time guarantee: host scheduling and instruction cost still vary. This VM's operations are bounded, but an instruction budget should never be advertised as a measured latency in milliseconds. A real editor must schedule another slice after returning to its event loop. A tight while loop that drains all slices still blocks its caller until completion.

Exercise: predict the number of calls for budgets one, two, three and four. The answers are four, two, two and one. The total executed instruction count stays four. If your observation differs, first check whether the compiled program contains extra loads, stores or branches.


[Previous lesson](78-add-binary-bitwise-operators.md)

[Next lesson](80-preserve-progress-when-a-slice-fails.md)
