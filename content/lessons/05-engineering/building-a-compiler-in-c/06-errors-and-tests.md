# Explain failures and test the boundaries

A useful failure report tells you what failed and where to start investigating. A **diagnostic** is structured information about a problem. Umicom C records a status, source offset, line, column and a static message. A diagnostic is not the same as a successful result.

## Separate failure stages

| Input or condition | Stage | Reason |
| --- | --- | --- |
| return 2 + ; | Compilation | A value is missing |
| ADD without two stack values | Bytecode validation | The instruction sequence is malformed |
| return 12 / 0; | Execution | Arithmetic cannot complete |

Checking only that the parser succeeded would miss division by zero. Running only successful arithmetic examples would miss damaged bytecode handling. A good test collection covers each boundary independently.

## Read the actual regression groups

1. `tests/test_compiler.c` checks supported syntax, precedence, input bounds and rejected programs.
2. `tests/test_vm.c` checks instruction shape, arithmetic and execution budgets.
3. `tests/test_bytecode.c` checks encoding and malformed input.
4. `tests/test_comparison.c` separates operation changes from source-location changes.
5. `tests/test_roundtrip_corpus.c` sends a deterministic collection of bounded expressions through compilation, encoding, decoding and execution.
6. `tests/test_wire_contract.c` checks fixed transport bytes independently of the compiler.

**Deterministic** means that the same inputs produce the same sequence of cases, so a failure can be repeated. The corpus uses a separately computed native answer as an **oracle**, meaning the expected answer against which the implementation is compared. An oracle must avoid the same bug it is supposed to detect.

## Preserve failure evidence

After building the test executables, this command runs the Umicom C tests from the repository directory:

```text
New-Item -ItemType Directory -Force ./_local/logs
ctest --preset windows-ucrt64-debug --output-on-failure --no-tests=error --output-log ./_local/logs/compiler-tests.log
```

Use a private log directory when retaining reports. Record the source revision, compiler, configuration and test command. A passing result from an earlier executable does not qualify a new source change. If no tests are discovered, investigate the configure step instead of calling the run successful.

## Exercise

A result object still contains 42 after a division-by-zero error. Is this proof that division succeeded?

<details>

<summary>Explanation</summary>

No. The runtime deliberately leaves a result unchanged on failure. The caller must check the status. A user interface must also avoid displaying the old value as the result of the failed attempt. The shared Framework preview service tracks the phase and clears stale display data before starting.

</details>

A test suite is evidence about the cases and environment actually exercised. It is not a guarantee that every compiler, machine or future change is correct.

## Find the implementation

Open `umicom-c/tests/test_roundtrip_corpus.c` in your Umicom source collection. Read the named functions alongside this lesson. Source reading and the expected outcomes below are not evidence of an executed build.

---

[Read this lesson in HTML](../../../courses/building-a-compiler-in-c/lessons/06-errors-and-tests.html) · [Learning sequence](../../../start/learning-sequence.md)
