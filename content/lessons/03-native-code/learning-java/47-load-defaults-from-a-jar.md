<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-java/47-load-defaults-from-a-jar.md

PURPOSE:
Package and verify defaults loaded from the same Java archive as the report class.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original learning material. Linked references retain their own terms.
-->

# Load defaults from a JAR

![Umicom Foundation](../../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }
<a href="../../../assets/branding/umicom.ico"><img src="../../../assets/branding/umicom-icon.svg" width="28" alt="Umicom icon"></a>

An application can ship a set of defaults inside the same JAR as its code. The report can use those settings from any launch folder. In this exercise you build the archive, inspect its entries, and verify which copy of the settings the program reads.

Use PowerShell and a JDK that supports Java 21. [Test the runnable JAR](09-test-the-runnable-jar.md) checks an entry point. Here you check the data that travels with the class. [Read report settings without rebuilding](30-read-report-settings.md) uses settings supplied as a separate file.

## 1. Put the resource under the class’s package

Make a new practice folder and open PowerShell there. Save [PackagedReportDefaults.java](../../../labs/java-path/packaged-defaults/PackagedReportDefaults.java) in that folder. Create the output and resource folders.

```powershell
New-Item -ItemType Directory -Path .\classes, .\resources\training\report -Force | Out-Null
```

Save [defaults.properties](../../../labs/java-path/packaged-defaults/defaults.properties) as `resources/training/report/defaults.properties`. Its settings are `title=Harbour readings` and `period=weekly`. Keep the file in UTF-8 and check that the editor keeps its `.properties` extension.

## 2. Build and inspect the JAR

Run each line in order. Continue after each command succeeds.

```powershell
javac --release 21 -Xlint:all -Werror -d classes PackagedReportDefaults.java
jar --create --file report-defaults.jar -C classes . -C resources .
jar --list --file report-defaults.jar
```

Find these two entries in the listing. The archive may also list directories and a manifest.

```text
training/report/PackagedReportDefaults.class
training/report/defaults.properties
```

The class belongs to the `training.report` package. It calls `getResourceAsStream("defaults.properties")` with a name relative to that package, so the resource name inside the JAR is `training/report/defaults.properties`. The reader decodes its bytes as UTF-8. Closing the reader also closes the underlying stream.

## 3. Run from another folder

Use the full path to the JAR and put a different settings file in a separate launch folder. The disk copy uses the same relative path and gives different settings so you can tell the two sources apart.

```powershell
$reportJar = (Resolve-Path -LiteralPath .\report-defaults.jar).Path
New-Item -ItemType Directory -Path .\run-check\training\report -Force | Out-Null
Set-Content -LiteralPath .\run-check\training\report\defaults.properties -Encoding ascii -Value 'title=Unpacked copy', 'period=daily'

Push-Location -LiteralPath .\run-check
try {
    java -cp $reportJar training.report.PackagedReportDefaults
} finally {
    Pop-Location
}
```

```text
Title Harbour readings
Period weekly
```

The classpath given by `-cp` contains the JAR. The program reads the settings packaged beside the class, so the disk copy in the launch folder does not change the report.

## 4. Check the failure when packaging omits the resource

Create a separate JAR with just the compiled class. Keep the complete JAR from the earlier step.

```powershell
jar --create --file report-without-defaults.jar -C classes .
$incompleteJar = (Resolve-Path -LiteralPath .\report-without-defaults.jar).Path
Push-Location -LiteralPath .\run-check
try {
    java -cp $incompleteJar training.report.PackagedReportDefaults
    $LASTEXITCODE
} finally {
    Pop-Location
}
```

```text
Missing packaged resource training/report/defaults.properties.
2
```

The loose file is still in the launch folder. The program reports the missing JAR entry and exits with code 2. If PowerShell stops the command block when Java exits with code 2, check `$LASTEXITCODE` at the next prompt.

If the complete JAR gives the same message, repeat `jar --list --file report-defaults.jar` and check the exact entry name. It should start at `training/`. When you build with `-C resources .`, `jar` adds the contents of `resources` at the archive root.

[Java resource name resolution](https://docs.oracle.com/en/java/javase/21/docs/api/java.base/java/lang/Class.html#getResourceAsStream%28java.lang.String%29) · [Previous lesson](46-read-record-components-at-run-time.md) · [Java course](index.md) · [Next lesson](48-set-a-deadline-for-a-virtual-thread-task.md)
