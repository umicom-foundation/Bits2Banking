<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-java/37-close-resources-and-keep-the-cause.md

PURPOSE:
Teach automatic cleanup and explain what Java reports when work and cleanup both fail.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original learning material. Linked references retain their own terms.
-->

# Close resources and keep the cause

![Umicom Foundation](../../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }
<a href="../../../assets/branding/umicom.ico"><img src="../../../assets/branding/umicom-icon.svg" width="28" alt="Umicom icon"></a>

A program opens an input and a report. The read fails, and closing the report also fails. Find out which error is reported first, then change the run so you can see the other case.

Start with [Read a file and explain errors](16-read-a-file-and-explain-errors.md). Use a JDK with Java 21 support, a text editor and PowerShell.

## 1. Save and build the practice program

Save [ReadAndClose.java](../../../labs/java-path/ReadAndClose.java) in your practice folder. Open PowerShell in that folder and run:

```powershell
javac --release 21 ReadAndClose.java
java ReadAndClose
```

The example uses two practice resources that print when they open and close. A real file or database connection also has a close step. The example lets you see the order without opening files.

## 2. Follow the first run

```text
Open input
Open report
Close report
Close input
Main cause: Read input failed
Later cause: Close report failed
```

Find the two resource declarations between the parentheses after `try`. Java opens the input first and the report second. It calls `close()` on the report first, then on the input.

The read error happened in the body of `try`. Java keeps it as the main exception. The report close error is stored with that exception. Java calls the later error a *suppressed exception*. `getSuppressed()` lets the report show it.

## 3. Let the read work and compare the output

```powershell
java ReadAndClose close
```

You now see both read lines. Both closes still happen in reverse order, and `Main cause: Close report failed` is the last line. The close error becomes the main cause because the read finished.

## 4. Check the ordinary run

```powershell
java ReadAndClose ok
```

Both reads and both closes complete. The final line is `Finished`. This gives you three cases to try when you write a small test for your own file reader.

If the class cannot be loaded, run `Get-ChildItem ReadAndClose*` and check for `ReadAndClose.class`. Return to the folder where you compiled the source and rerun the command.

The Java specification defines [try-with-resources](https://docs.oracle.com/javase/specs/jls/se21/html/jls-14.html#jls-14.20.3). The API describes [getSuppressed](https://docs.oracle.com/en/java/javase/21/docs/api/java.base/java/lang/Throwable.html#getSuppressed()).

[Previous lesson](36-keep-a-reading-in-a-record.md) · [Next lesson](38-make-a-choice-with-if.md) · [Java course](index.md)
