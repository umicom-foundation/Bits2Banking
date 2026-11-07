# Java journal and decimal laboratory

This laboratory extends `LedgerDemo.java` from Learning Java. It studies Java values and checks; it is not an accounting service. Umicom's reusable financial services belong in Framework. No account or real money is needed.

## Prepare the tools

1. Install a JDK with Java 17 or newer. A JDK supplies the `javac` compiler as well as the `java` runtime. The journal uses Java records.
2. In PowerShell or bash, run `java --version` and `javac --version`. Both must be from compatible installations.
3. Open a terminal in this laboratory directory. Keep the three Java source files together; they use the same unnamed package.
4. Make an output directory and compile:

~~~text
mkdir out
javac -d out LedgerDemo.java LedgerChecks.java DecimalChecks.java
java -cp out LedgerDemo
java -cp out LedgerChecks
java -cp out DecimalChecks
~~~

If `out` already exists, continue with compilation. `-d out` selects the directory for compiled classes. `-cp out` tells the runtime where to find those classes. These commands work in both shells. After a failed command, correct the problem before continuing. PowerShell exposes the last native exit code as `$LASTEXITCODE`; bash uses `$?`.

## Read the results

The demonstration prints `Journal balanced: true`. LedgerChecks ends with a journal arithmetic message; DecimalChecks ends with a decimal representation message. A failed requirement throws AssertionError and terminates with a failure status. The checks use explicit requirements, so Java's optional `-ea` switch is not needed.

Write a table of predictions before running. Match 25.10 against 25.1, remove the credit, duplicate the debit, and reverse the posting order. Equal totals must remain equal when reordered. A missing or duplicate posting changes the totals.

An empty journal and equal negative totals also balance numerically. That is a deliberate observation about the small existing function, not approval to book such journals. A production entry requires separate rules for account identity, currency, permissions, posting state and business validity.

## Read a decimal decision

`compareTo` compares numeric values. `equals` also distinguishes the scale: 25.10 and 25.1 have different decimal representations. Rounding is explicit in the division and tie examples. HALF_EVEN is used to demonstrate a rule; it is not a universal financial policy.

Read the [Java BigDecimal reference](https://docs.oracle.com/en/java/javase/21/docs/api/java.base/java/math/BigDecimal.html) for the API contract. Trace the eight explicit requirements in DecimalChecks against the source before extending it.

## Troubleshoot

“Cannot find symbol LedgerDemo” means the source or compiled class is missing from the selected compilation. “Could not find or load main class” usually means the current directory or class path differs from the commands above. A compiler rejection of records means the selected JDK is too old. Do not change a failed expected value just to obtain a passing message; first check the input and the stated rule.

