<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-java/16-read-a-file-and-explain-errors.md

PURPOSE:
  Teach read a file and explain errors with a small runnable example.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom Foundation](../../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }
<a href="../../../assets/branding/umicom.ico"><img src="../../../assets/branding/umicom-icon.svg" alt="Umicom icon" width="28"></a>

# Read a file and explain errors

Read three numbers stored in a text file. A useful program distinguishes the result from two common failures, a missing file and a line that cannot be read as an integer.

Complete the previous lesson before trying this one. Use the same JDK and a writable practice folder.

## Try it

1. Save `ReadShiftLog.java` and `shift-numbers.txt` in the same folder. The data file contains 4, 3 and 2, on separate lines.
2. Compile and run with the data file’s name after the class name. That final word becomes the first command argument.
3. Try a missing file name. The program should write a short error and return exit status 1.
4. Make a practice copy of the data file, replace the middle line with `three` and run again. The program should explain the input requirement.

## Example files

### ReadShiftLog.java

[Open ReadShiftLog.java](../../../labs/java-path/ReadShiftLog.java)

~~~java
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;

public class ReadShiftLog {
    static void report(Path file) throws IOException {
        long total = 0;
        // The language closes the reader even when parsing or reading fails.
        try (var input = Files.newBufferedReader(file, StandardCharsets.UTF_8)) {
            for (String line; (line = input.readLine()) != null;) {
                total += Integer.parseInt(line.strip());
            }
        }
        System.out.println("Total: " + total);
    }

    public static void main(String[] args) {
        if (args.length != 1) {
            System.err.println("Usage: java ReadShiftLog FILE");
            System.exit(2);
        }
        try {
            report(Path.of(args[0]));
        } catch (NumberFormatException error) {
            System.err.println("Input must contain one integer on each line.");
            System.exit(1);
        } catch (IOException error) {
            System.err.println("Could not read the input file.");
            System.exit(1);
        }
    }
}
~~~

### shift-numbers.txt

[Open shift-numbers.txt](../../../labs/java-path/shift-numbers.txt)

~~~text
4
3
2
~~~

## Run it

~~~text
javac ReadShiftLog.java
java -cp . ReadShiftLog shift-numbers.txt
java -cp . ReadShiftLog missing-input.txt
~~~

The program output to check is shown below.

~~~text
Total: 9
Could not read the input file.
~~~

## Read the result

The try-with-resources block closes the reader. `readLine()` returns `null` at the end. A `NumberFormatException` means the text did not represent an integer. An `IOException` concerns opening or reading the file. Use `$LASTEXITCODE` in PowerShell or `echo $?` in a POSIX shell immediately after a run to see its exit status.

## Practise

With a valid file, add a fourth line containing 6. Expect `Total: 15`. Leave a blank line in a separate copy and observe the invalid-input response.

## Fix a problem

Check the current folder and file name first. Save the data as UTF-8. A line containing only whitespace becomes empty after `strip` and does not meet this example’s format.

## Reference

- [Java file API and UTF-8 reader](https://docs.oracle.com/en/java/javase/21/docs/api/java.base/java/nio/file/Files.html)

[Previous · Group deliveries with collections](15-group-deliveries-with-collections.md) · [Next · Test and debug a boundary](17-test-and-debug-a-boundary.md)
