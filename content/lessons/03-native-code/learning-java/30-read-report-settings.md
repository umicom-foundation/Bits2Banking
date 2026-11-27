# Read report settings without rebuilding

![Umicom Foundation](../../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }
<a href="../../../assets/branding/umicom.ico"><img src="../../../assets/branding/umicom-icon.svg" width="28" alt="Umicom icon"></a>

Suppose you run the same readings report each week. The report can read its title and row limit from a small text file. Change both settings and run the same compiled class again.

Use JDK 21 or later and open PowerShell 7 in a new practice folder. Follow [Install the JDK and run a class](11-install-the-jdk-and-run-a-class.md) if `javac -version` fails.

## 1. Write the settings file

Copy these lines into PowerShell. They create `report.properties` in your practice folder.

```powershell
@'
title=Daily readings
rows=3
'@ | Set-Content -LiteralPath report.properties -Encoding utf8NoBOM
```

On each line, the part before `=` is the setting name. The part after it is the value. This report accepts up to 20 rows so it fits its chosen display size.

## 2. Write the program

Save this code as `ReportSettings.java` in the same folder. You can also open the [source file](../../../labs/java-path/ReportSettings.java).

```java
import java.io.BufferedReader;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.Properties;

public class ReportSettings {
    public static void main(String[] args) {
        System.exit(run(args));
    }

    private static int run(String[] args) {
        if (args.length != 1) {
            return fail("Give the path to one settings file.");
        }

        // Read with an explicit encoding and close the file on every exit path.
        Properties settings = new Properties();
        try (BufferedReader reader = Files.newBufferedReader(
                Path.of(args[0]), StandardCharsets.UTF_8)) {
            settings.load(reader);
        } catch (IOException | IllegalArgumentException problem) {
            return fail("Cannot read the settings file.");
        }

        // Check that both values are usable before printing the report heading.
        String title = settings.getProperty("title", "").strip();
        if (title.isEmpty()) {
            return fail("Give the report a title.");
        }

        int rows;
        try {
            rows = Integer.parseInt(settings.getProperty("rows", "").strip());
        } catch (NumberFormatException problem) {
            return fail("Set rows to a whole number from 1 to 20.");
        }
        if (rows < 1 || rows > 20) {
            return fail("Set rows to a whole number from 1 to 20.");
        }

        System.out.println(title);
        System.out.println("Rows to show: " + rows);
        return 0;
    }

    private static int fail(String message) {
        // A separate error stream keeps failed runs out of report output.
        System.err.println(message);
        return 1;
    }
}
```

`args[0]` is the filename you give when you run the program. The `try` statement opens it and closes the reader when the block ends. `settings.load(reader)` reads the named values. Those values start as text, so `Integer.parseInt` turns `rows` into a number before the program checks its range.

## 3. Compile once and run twice

```powershell
javac --release 21 ReportSettings.java
java ReportSettings report.properties
```

You should see this output.

```text
Daily readings
Rows to show: 3
```

Open `report.properties`. Change the title to `Café readings` and `rows` to `5`. Save it as UTF-8, then repeat only the `java` command. The title and row count should both change. Your `.class` file stays the same because the values are read each time the program starts.

## 4. Check a mistake you can recognise

Change `rows` to `many`, save the file and run the program again. It prints `Set rows to a whole number from 1 to 20.` Check `$LASTEXITCODE` in PowerShell immediately afterward. It returns `1`, which a script can use to detect the failed run. Put `5` back and run again. It returns `0` and prints the heading.

If you see `Cannot read the settings file.`, use `Get-ChildItem -Name` to check that `report.properties` is in your current folder. If you see `Give the report a title.`, check that the `title` line has a value after `=`.

The [provider lesson](29-connect-an-implementation-with-serviceloader.md) changes which class writes a report. This exercise changes values that a report uses. An Umicom Framework application can use the same idea to let a user change a report preference while the application keeps calling the same renderer.

[Previous lesson](29-connect-an-implementation-with-serviceloader.md) · [Java course](index.md) · [Java in simple steps](../../../simple-steps/course-guides/learning-java.md)
