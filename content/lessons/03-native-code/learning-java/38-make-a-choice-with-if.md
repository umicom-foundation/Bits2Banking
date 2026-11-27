<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-java/38-make-a-choice-with-if.md

PURPOSE:
Teach a first Java decision and check the exact point where its result changes.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original learning material. Linked references retain their own terms.
-->

# Make a choice with if

![Umicom Foundation](../../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }
<a href="../../../assets/branding/umicom.ico"><img src="../../../assets/branding/umicom-icon.svg" width="28" alt="Umicom icon"></a>

A meter reading should reach 10. Write a program that tells you whether the reading has reached that minimum.

You can do this after [Install the JDK and run a class](11-install-the-jdk-and-run-a-class.md). Use the same editor and PowerShell window.

## 1. Write the rule in everyday words

Read the number. If it is below the minimum, ask for a review. Otherwise, show that the minimum has been reached.

```text
Set the reading to 8
Set the minimum to 10
If the reading is less than the minimum
    Show Review the reading.
Otherwise
    Show Minimum reached.
```

This is pseudocode, a way to write the steps before writing a program.

## 2. Save the example and run it

Save [CheckReading.java](../../../labs/java-path/CheckReading.java) in the folder where you practice. Open that folder in PowerShell.

```powershell
javac --release 21 CheckReading.java
java CheckReading
```

The program prints `Review the reading.`

## 3. Follow each part of the program

- `int reading = 8;` gives the name `reading` to the whole number 8.
- `int minimum = 10;` names the minimum.
- `reading < minimum` asks whether the first value is less than the second.
- `if` runs the first pair of braces when that question is true.
- `else` runs the other pair when the question is false.

## 4. Check the exact minimum

Change `int reading = 8;` to `int reading = 10;` and save the file. Run both commands again. Expect `Minimum reached.` The value 10 is equal to the minimum, so the less-than test is false.

Now try 12. Predict the output before recompiling and running. The answer is still `Minimum reached.`

If the output stays the same after you change from 8 to 10, check that you saved the source and that `javac` completed without errors. `java CheckReading` reads the compiled class from the current folder.

[Add values in a loop](12-add-values-in-a-loop.md) · [Previous lesson](37-close-resources-and-keep-the-cause.md) · [Next lesson](39-put-two-java-files-in-a-package.md) · [Java course](index.md)
