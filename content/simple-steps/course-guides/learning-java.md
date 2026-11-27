<!--
Umicom Bits2Banking
File: content/simple-steps/course-guides/learning-java.md

PURPOSE:
Provide practical first steps and a result to check for Learning Java.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Learning Java

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

## Run your first Java class

Use this sequence when you want the next practical step. Each linked lesson includes the expected result and a way to recover if something goes wrong.

1. Open a terminal and type `javac -version`. Follow the setup lesson if the terminal cannot find the compiler.
2. [Save, compile and run a class](../../lessons/03-native-code/learning-java/11-install-the-jdk-and-run-a-class.md). Look for `Receipt ready`.
3. [Add values in a loop](../../lessons/03-native-code/learning-java/12-add-values-in-a-loop.md). Trace the total on paper and run the class to check it.
4. [Move the calculation into a method](../../lessons/03-native-code/learning-java/13-total-an-array-with-a-method.md). Confirm the total and test an empty array.
5. [Find a boundary error](../../lessons/03-native-code/learning-java/17-test-and-debug-a-boundary.md). Use the test result to decide which comparison needs checking.
6. [Check the same file with Java and C23](../../lessons/03-native-code/learning-java/21-verify-a-java-and-c23-file-contract.md). Compare output and failure codes.

[Open all Java lessons](../../lessons/03-native-code/learning-java/index.md) · [Continue to packages and JARs](../../lessons/03-native-code/learning-java/20-package-a-report-as-a-module.md)

## Follow the original journal exercise

1. Open `LedgerDemo.java`. Write down the debit and credit amounts in its two `Posting` records. [Records and a journal](../../courses/learning-java/lessons/01-records-and-a-journal.html)
2. Add the two sides separately and compare each total with the result of `IsBalanced`. [Records and a journal](../../courses/learning-java/lessons/01-records-and-a-journal.html)
3. On paper, change the credit amount from 25.10 to 24.10 and repeat the comparison. [Decimal values and checks](../../courses/learning-java/lessons/02-decimal-values-and-checks.html)

**Check your result.** The original debit and credit totals both equal 25.10. With the changed credit, the balance check is false.

[Continue in the full course](../../courses/learning-java/index.html) · [All course guides](index.md)
