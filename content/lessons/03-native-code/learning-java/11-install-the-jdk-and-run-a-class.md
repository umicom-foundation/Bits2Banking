<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-java/11-install-the-jdk-and-run-a-class.md

PURPOSE:
  Teach install the JDK and run a class with a small runnable example.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom Foundation](../../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }
<a href="../../../assets/branding/umicom.ico"><img src="../../../assets/branding/umicom-icon.svg" alt="Umicom icon" width="28"></a>

# Install the JDK and run a class

Start here if you have never written a program. You will save one text file, turn it into a class file, and ask Java to run it. A terminal is a window where you type commands. The JDK is the set of tools that includes the compiler and launcher.

Use the official installation instructions for Windows, macOS or Linux. The examples use standard Java 21 language and library features.

## Try it

1. Open the official Java setup guide and choose a JDK for your operating system. Install JDK 21 or newer for these lessons. Open a fresh terminal after setup.
2. Type `javac -version` and `java -version`. Both commands should report Java 21 or newer. Check they come from the same installation if the version numbers disagree.
3. Create a practice folder and open it in your terminal. Save the example as `FirstReceipt.java` using plain text. Match the uppercase `F` in the class name.
4. Run `javac FirstReceipt.java`, then run `java -cp . FirstReceipt`. The compiler normally returns to the prompt quietly and creates `FirstReceipt.class`.

## Create the practice folder

PowerShell commands for Windows.

~~~powershell
New-Item -ItemType Directory -Path JavaPractice
Set-Location -LiteralPath JavaPractice
~~~

Terminal commands for macOS and Linux.

~~~sh
mkdir JavaPractice
cd JavaPractice
~~~

Use a plain text editor to save the practice file. In a Windows editor, check that the name did not become `FirstReceipt.java.txt`.

## Example files

### FirstReceipt.java

[Open FirstReceipt.java](../../../labs/java-path/FirstReceipt.java)

~~~java
public class FirstReceipt {
    public static void main(String[] args) {
        // main is where the Java launcher starts this program.
        System.out.println("Receipt ready");
    }
}
~~~

## Run it

~~~text
javac -version
java -version
javac FirstReceipt.java
java -cp . FirstReceipt
~~~

The program output to check is shown below.

~~~text
Receipt ready
~~~

## Read the result

`public class FirstReceipt` names the program’s class. `main` is where the launcher begins. The text between double quotes is the message. `System.out.println` prints it and ends the line. The `-cp .` argument tells the launcher to look in the current folder.

## Practise

Change the text to `Report ready`. Compile again and run the same class. You should see the new line after the new compilation.

## Fix a problem

If `javac` is missing, find the installed JDK rather than a runtime-only installation. In PowerShell, `Get-Command java, javac` shows the tools being selected. On macOS or Linux, use `command -v java` and `command -v javac`. If the launcher cannot find the class, check the file name, folder and successful compile before running.

## Reference

- [Java setup and first program](https://dev.java/learn/first-steps/first-java-code/)

[Course guide](index.md) · [Next · Add values in a loop](12-add-values-in-a-loop.md)
