<!--
Umicom Bits2Banking
File: content/lessons/07-practical-domains/framework-and-finance/banking-and-payments/24-test-events-without-touching-user-data.md

PURPOSE:
Test native events while isolating persistent storage

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Test native events while isolating persistent storage

Build a small desktop host around Framework banking services, then follow how an explicit filename becomes an owned workspace.

## Start here

You can read this lesson without prior banking or GTK knowledge. To run the exercise, obtain the Bits2Banking sources, install a C23 compiler, CMake, Ninja and GTK4, and install a matching Umicom Framework SDK with bank_operations_gtk4. A terminal is a window where you type commands; a build translates source files into an executable program. Follow the [Bank workspace lab setup](../../../../../labs/framework/bank-workspace/README.md) for complete PowerShell and Bash commands and expected behaviour. The lab uses practice records only.


## What the regression fixture proves

A test fixture prepares controlled starting conditions. The Bank native fixture uses the production launcher, widgets and financial command handlers. Only UmiBankOperationsOpenSqlite is replaced with a function that opens a memory service. A memory service loses its data when destroyed.

The fixture counts open calls and copies the filename it receives. This lets it check that blank input and selection alone do not open storage, valid Unicode text reaches the boundary unchanged, a failed open can be retried, and an already-open workspace is not redirected.

## Read and run the focused coverage

1. Open Framework's tests/bank_operations/test_native_commands.c.
2. Find IsolatedOpen, OpenCalls and FailOpen. Explain what each controls.
3. Find the storage-selection and open-retry branches. Each assertion checks an observable state change.
4. After building the matching Framework test target, run the focused tests from its build directory:

```powershell
ctest --test-dir build/windows-ucrt64-all-debug -R "^framework\.bank_operations\.native\." --output-on-failure --no-tests=error
```
The example build directory is relative to Umicom-Applications. Use the build directory you actually configured. A missing executable means it has not been built; a skip because no display is available is not a pass.

## What remains to test

This fixture does not prove persistence across application restarts, chooser cancellation in the installed desktop environment, or compatibility with an older database. Run storage tests and manual selected-file workflows separately. Record the source revision and runtime version with actual results.

## Exercise

Describe a faulty implementation that these tests would catch: for example, opening storage as soon as SetPath is called. Then describe one they would not catch: for example, a missing SQLite runtime in a packaged application.

## Read the source

[Open the example source](../../../../labs/framework/bank-workspace/README.md).

## Continue learning

[Course contents](../../../courses/framework-and-finance/banking-and-payments/index.html) · [Previous: Recover from a failed open without replacing user data](23-recover-from-a-failed-open.md)
