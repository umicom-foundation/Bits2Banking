<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/automated-testing-with-umicom/05-qualify-each-platform-separately.md

PURPOSE:
Qualify each platform separately

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Qualify each platform separately

A host is the machine running the test. The target is the place where the application behavior is being observed. A host can verify compiled arithmetic and data boundaries. Interface and device tests need evidence from the target they describe.

## Build a small matrix

| Target | Example action to observe | Evidence to retain |
| --- | --- | --- |
| Desktop | Open a sample document and read its visible title | Product build, UI backend, observation and result |
| Mobile | Rotate a practice view and read its retained value | Device or simulator identity, layout observation and result |
| Web | Open a local fixture and read a report label | Browser version, fixture revision and observable result |
| Embedded | Read a bounded diagnostic message from a prepared test target | Target hardware or model identity, firmware version and observed text |

All four experiments can begin with the same expected result. The result of one row belongs to that run. A compiler-only check gives evidence for the compiled rule and can help prepare the other rows.

~~~text
FOR each approved platform
    RECORD the fixture and build identity
    RECORD whether the runner launched the operation
    STORE the outcome observed on that platform
END FOR
~~~

## Check a simple supported-operation rule

D and FreeBASIC can express the same mask test as C. In each fragment, bit value 4 stands for one declared operation. Use a single supported-operation value for the exercise.

~~~d
uint allowed = 4;
uint supported = 0;
bool available = (allowed & supported & 4u) != 0;
~~~

~~~basic
Dim allowed As ULong = 4
Dim supported As ULong = 0
Dim available As Boolean = ((allowed And supported And 4UL) <> 0)
~~~

The expected result is false. Change `supported` to 4 and predict true. The native C lab in this course uses Framework’s target constants and the real callback-free admission call. The D and FreeBASIC fragments let you compare spelling without selecting a real target.

1. Mark the target platform on the row before a test runs.
2. Choose a fixture and environment with the operation it needs.
3. Keep target evidence separate from the compiler, source review and hosted model checks.
4. After changing a runtime dependency, capture its observed identity with the new result.

Umicom Studio can display test and device choices while Framework owns reusable target, plan and report contracts.

[Course contents](index.md) · [Previous lesson · Read one test evidence row](04-read-one-evidence-row.md) · [Next lesson · Keep the fixture permissions small](06-keep-the-fixture-permissions-small.md) · [HTML edition](../../../courses/automated-testing-with-umicom/lessons/05-qualify-each-platform-separately.html) · [Native C23 lab source](../../../labs/native/automated-testing-preview/main.c) · [SDK build description](../../../labs/native/automated-testing-preview/CMakeLists.txt)
