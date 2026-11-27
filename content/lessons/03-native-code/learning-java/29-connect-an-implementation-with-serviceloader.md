# Connect an implementation with ServiceLoader

![Umicom](../../../assets/branding/umicom-wordmark.svg)

Give a program one task and supply a class that performs it. The application in this exercise knows that a total is 20. A separate class decides how to write that total. An interface is the agreement between them. Java's `ServiceLoader` finds a provider for that agreement at runtime.

Use JDK 21 or later and PowerShell 7. Open the Bits2Banking checkout, where you can see `content`. The earlier lesson [Read the modules a Java app needs](27-read-the-modules-a-java-app-needs.md) introduces the difference between building and running an application.

## 1. Build the agreement and the application

```powershell
$readingLab = 'content/labs/java-path/service-loader'
javac --release 21 -d build/java-reading-app "$readingLab/ReadingReporter.java" "$readingLab/ReportSample.java"
java -cp build/java-reading-app learning.readings.ReportSample
```

The result is `No reading reporter is installed.` The application compiled using the interface. It checks what is available when it runs and explains the missing provider.

## 2. Build one provider

```powershell
javac --release 21 -cp build/java-reading-app -d build/java-reading-provider "$readingLab/PlainReadingReporter.java"
java -cp "build/java-reading-app;build/java-reading-provider" learning.readings.ReportSample
```

The message stays the same. The provider class now exists on the class path. Java still needs a record that ties the class to the service. The semicolon inside the quoted class path separates the two folders on Windows.

## 3. Register the provider and run again

```powershell
$serviceFiles = 'build/java-reading-provider/META-INF/services'
New-Item -ItemType Directory -Path $serviceFiles -Force | Out-Null
Set-Content -LiteralPath "$serviceFiles/learning.readings.ReadingReporter" -Value 'learning.readings.PlainReadingReporter' -Encoding utf8
java -cp "build/java-reading-app;build/java-reading-provider" learning.readings.ReportSample
```

The result is `Total readings: 20`. The name of the file identifies the interface. The line inside the file gives the qualified name of its provider. Edit the text returned by `PlainReadingReporter.java`, recompile only that class with Step 2’s first command and run Step 3’s last command. The application now prints the new wording.

If the provider is missing or an error reports that it cannot be found, check both class-path entries and the spelling of the service filename and contents. Use a fresh output folder if you have an older registration left over from a previous attempt.

The same separation helps when building Umicom Framework applications. An application can call an agreed interface while it keeps the implementation in a selected adapter. This lab uses Java's class path and an implementation you built yourself.

[Previous lesson](28-record-a-java-program-run.md) · [Java course](index.md) · [JDK ServiceLoader reference](https://docs.oracle.com/en/java/javase/21/docs/api/java.base/java/util/ServiceLoader.html)
