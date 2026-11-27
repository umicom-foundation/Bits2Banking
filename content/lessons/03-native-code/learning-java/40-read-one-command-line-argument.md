<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-java/40-read-one-command-line-argument.md

PURPOSE:
Read one value at launch and distinguish a normal result from invalid input.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original learning material. Linked references retain their own terms.
-->

# Read one command-line argument

![Umicom Foundation](../../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }
<a href="../../../assets/branding/umicom.ico"><img src="../../../assets/branding/umicom-icon.svg" width="28" alt="Umicom icon"></a>

You can check a different reading each time you run a program. Pass the value after the class name and let Java check it before making the decision.

Start with [Make a choice with if](38-make-a-choice-with-if.md). Use a JDK with Java 21 support, your practice folder and PowerShell.

## 1. Save and compile the example

Save [ReadingArgument.java](../../../labs/java-path/ReadingArgument.java) in your practice folder and run the compiler there.

```powershell
javac --release 21 ReadingArgument.java
```

The compiler writes `ReadingArgument.class`. Keep it in the same folder for the next steps.

## 2. Run with two different readings

```powershell
java ReadingArgument 8
java ReadingArgument 10
$LASTEXITCODE
```

The first run prints `Review the reading.` The second prints `Minimum reached.` PowerShell shows exit code 0 for the last successful run.

`args` contains the words supplied after the class name. `args.length` counts them. After checking you supplied exactly one, the program reads `args[0]` and converts it from text to an integer. The last `if` uses the same less-than test from the earlier lesson to choose a message.

## 3. Give the program text it cannot convert

```powershell
java ReadingArgument ten
$LASTEXITCODE
```

The program prints `Enter a whole number that fits in an int.` and PowerShell shows 2. An exception tells the program that conversion failed. The `catch` block turns it into a message the person running the program can act on.

Try `java ReadingArgument` without a reading. This time the message asks for one value. Both refusals return 2, which a script can use to detect that a choice needs correction.

If PowerShell stops as soon as Java returns 2, check `$LASTEXITCODE` at the next prompt. If it cannot find `ReadingArgument`, return to the directory where you compiled the file.

[Previous lesson](39-put-two-java-files-in-a-package.md) · [Next lesson](41-choose-a-report-period-with-switch.md) · [Java course](index.md)
