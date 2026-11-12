<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/59-separate-instruction-fuel-from-wall-clock-time.md

PURPOSE:
Separate instruction fuel from wall-clock time

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Separate instruction fuel from wall-clock time

## Before you begin
Complete the execution-budget and source-span lessons. Open tests/check_cli_budget.cmake and tests/CMakeLists.txt. This lesson concerns test supervision as well as the interpreter's contract.

## Two budgets answer different questions
Instruction fuel counts VM operations. Wall-clock time measures elapsed time on the host. A process may spend time starting, waiting for a CPU, loading libraries or writing output before it executes the first VM operation.

The expression 6 * 7 uses four instructions in this profile: two pushes, multiply and return. A budget of four succeeds; a budget of three cannot publish a completed result. Those assertions must remain exact even on a slow machine.

~~~powershell
.\build\bin\umicom-c.exe run build\practice.uc --max-steps 4
.\build\bin\umicom-c.exe run build\practice.uc --max-steps 3
~~~

Create practice.uc first with int main(void) { return 6 * 7; }. The first command should report 42 and four instructions. The second must fail with instruction-budget exhaustion and no Result line. Do not confuse that expected refusal with a test harness killing a process for taking too long.

## Count the child processes
The CLI budget regression compiles its fixture once. For each of source run and bytecode exec it checks three accepted budgets, one exhausted budget, eight malformed budgets and one duplicate option. Finally it checks that a non-execution command refuses the execution-only option.

That is 1 + 2 * (3 + 1 + 8 + 1) + 1, or 28 processes. An aggregate thirty-second limit can expire during repeated process startup on a loaded host, even if individual commands eventually behave correctly. A timeout alone does not identify the slow invocation or prove the exact scheduling cause.

## Bound each layer
The current fixture gives each execute_process call a ten-second timeout. A timed-out child returns a non-success result to its surrounding assertion, which identifies the command and case. The enclosing CTest case allows ninety seconds for the complete sequence and its scheduling overhead.

These limits do not increase --max-steps or accept a result after exhaustion. They supervise host processes. The former aggregate limit remains in an explicit inactive CMake block for review.

1. Locate all six execute_process call sites.
2. Count how the loops expand them into 28 invocations.
3. Check that each result is examined before continuing.
4. Check that failure cases still reject any published result.
5. Find the final hashes proving that execution did not change input artifacts.

## Reproduce and diagnose carefully
After configuration and building, run:

~~~powershell
ctest --test-dir build -R "^umicom.c.cli-budget$" --output-on-failure --no-tests=error
~~~

If it times out, preserve the output and source/toolchain identity. Determine whether a child deadline or the aggregate deadline expired. Review the last reported case, host load and the selected executable. An isolated rerun can provide additional evidence, but does not erase the earlier failure.

Do not remove assertions, skip slow cases or increase VM fuel to make a wall-clock failure disappear. If a command genuinely hangs, investigate its process behavior. If many bounded successful starts consume the aggregate allowance, account for that workload explicitly and retain a finite overall deadline.

## Report what ran
A test definition is authored coverage. A successful configure means CTest can register it. An executed passing result qualifies the tested source and environment. Keep failures and reruns as separate observations so a reviewer can tell whether a repair addressed the symptom or merely changed the measurement.

[Course contents](index.md) · [Previous lesson](58-test-source-spans-without-a-terminator.md) · [Next lesson](60-record-configuration-inputs-with-honest-limits.md)
