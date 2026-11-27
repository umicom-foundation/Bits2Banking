<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-java/20-package-a-report-as-a-module.md

PURPOSE:
  Teach package a report as a module with a small runnable example.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom Foundation](../../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }
<a href="../../../assets/branding/umicom.ico"><img src="../../../assets/branding/umicom-icon.svg" alt="Umicom icon" width="28"></a>

# Package a report as a module

A package gives related classes a name. A module declares a named group of packages and its dependencies. You will launch one small program from a module and from a JAR, then inspect its bytecode.

Complete the previous lesson before trying this one. Use the same JDK and a writable practice folder.

## Try it

1. Copy the `module` lab directory into your practice area. Keep `module-info.java` at the top and `ModuleReport.java` in `org/umicom/learning/report`.
2. From that directory, compile both files into `out`. Run the named module with the full class name after the slash.
3. Package the same `out` directory into `report.jar`. Give the JAR its entry point with `--main-class` and launch it with `java -jar`.
4. Inspect the class with `javap -c`. Find the call to `println`. The bytecode listing shows how the compiler represented the instruction in the class file.

## Example files

### module-info.java

[Open module-info.java](../../../labs/java-path/module/module-info.java)

~~~java
// The report uses java.base, which every named module reads automatically.
module org.umicom.learning.report {
}
~~~

### org/umicom/learning/report/ModuleReport.java

[Open org/umicom/learning/report/ModuleReport.java](../../../labs/java-path/module/org/umicom/learning/report/ModuleReport.java)

~~~java
package org.umicom.learning.report;

public class ModuleReport {
    public static void main(String[] args) {
        // The same entry point can be launched as a class, module or JAR.
        System.out.println("Report module ready");
    }
}
~~~

## Run it

~~~text
javac --release 21 -d out module-info.java org/umicom/learning/report/ModuleReport.java
java --module-path out -m org.umicom.learning.report/org.umicom.learning.report.ModuleReport
jar --create --file report.jar --main-class org.umicom.learning.report.ModuleReport -C out .
java -jar report.jar
javap -classpath out -c org.umicom.learning.report.ModuleReport
~~~

The program output to check is shown below.

~~~text
Report module ready
~~~

## Read the result

Both launch commands print the same line. The modular launch provides a module path and a qualified class name. The runnable JAR stores its main-class declaration in archive metadata. A JAR is a Java archive. A WAR for a web application is built to a different contract and is deployed to a servlet container rather than launched like this report.

## Practise

Create a small runtime image with `jlink --module-path out --add-modules org.umicom.learning.report --output report-runtime`. Use a fresh output directory name. Run `./report-runtime/bin/java -m org.umicom.learning.report/org.umicom.learning.report.ModuleReport` on macOS/Linux, or `& .\report-runtime\bin\java.exe -m org.umicom.learning.report/org.umicom.learning.report.ModuleReport` in PowerShell. Both should print the same report.

## Fix a problem

Read the package declaration and folder spelling if the JVM cannot find the class. Run the compile command from the folder that contains `module-info.java`, and verify that `out` is the module path.

## Reference

- [JDK modules and runtime images](https://dev.java/learn/organizing/modules/)
- [jlink options and module path](https://docs.oracle.com/en/java/javase/21/docs/specs/man/jlink.html)
- [Continue with a Java web request](../../../courses/learning-spring-framework/lessons/01-a-java-web-request.html)
- [Deploy a WAR on Tomcat](../../04-web/learning-web-servers/04-deploy-a-war-on-tomcat.md)

[Previous · Collect results from virtual threads](19-collect-results-from-virtual-threads.md) · [Next · Verify a Java and C23 file contract](21-verify-a-java-and-c23-file-contract.md)
