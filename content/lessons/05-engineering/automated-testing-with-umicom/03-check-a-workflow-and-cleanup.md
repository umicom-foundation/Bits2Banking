<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/automated-testing-with-umicom/03-check-a-workflow-and-cleanup.md

PURPOSE:
Check a workflow and its cleanup

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Check a workflow and its cleanup

A workflow test checks more than one event in order. Give setup, observation and cleanup different responsibilities. A refusal in the work portion of a fixture should still leave you able to inspect what happened.

## Use a deterministic ledger model

For a savings-club practice fixture, keep two integers in memory. One represents an existing total. The other represents a proposed replacement. An admitted replacement becomes visible only when you commit the model.

~~~c
struct LedgerFixture {
    int committed;
    int staged;
    bool staged_valid;
};
~~~

Start with `committed` equal to 42. Stage 45, check that a read still returns 42, commit the staged value and check that a later read returns 45. Then start from 42 again, stage a request that the model refuses, and check that a read remains 42.

~~~text
OPEN a fresh fixture with committed total 42
STAGE a change
OBSERVE the committed total
IF the staged data is valid THEN commit it
CHECK the committed total again
RELEASE the fixture
~~~

A database adapter can later exercise the analogous transaction against a dedicated test database. Keep independent setup and cleanup. Use a fresh temporary fixture instead of an application’s working data.

## Write the contract for both paths

1. Give the setup its own row. State how you know it finished.
2. Create one success row where the staged value becomes visible.
3. Create one refusal row where the previous output stays visible.
4. Check cleanup in both paths. A leaked fixture can make the next test depend on earlier order.

In Umicom Framework, `UMI_UAT_SETUP`, `UMI_UAT_ASSERT` and `UMI_UAT_CLEANUP` mark different workflow phases. A target may separately declare `UMI_UAT_DATABASE_READ` and `UMI_UAT_DATABASE_WRITE`. A read-only fixture can prove a query contract while a write experiment needs its own declared permission and isolated data.

[Course contents](index.md) · [Previous lesson · Choose target operations before dispatch](02-choose-target-operations.md) · [Next lesson · Read one test evidence row](04-read-one-evidence-row.md) · [HTML edition](../../../courses/automated-testing-with-umicom/lessons/03-check-a-workflow-and-cleanup.html) · [Native C23 lab source](../../../labs/native/automated-testing-preview/main.c) · [SDK build description](../../../labs/native/automated-testing-preview/CMakeLists.txt)
