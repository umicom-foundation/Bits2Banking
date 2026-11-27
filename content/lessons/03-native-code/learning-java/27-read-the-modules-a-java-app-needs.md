# Read the modules a Java app needs

![Umicom](../../../assets/branding/umicom-wordmark.svg)

Compare the modules used by three small programs. A module is a named group of Java packages. The JDK includes a tool called `jdeps` that reads compiled classes and reports which modules those classes refer to.

Use JDK 21 or later and PowerShell. Open the Bits2Banking checkout, where you can see the `content` folder. If you are new to compiling Java, start with [Package a report as a module](20-package-a-report-as-a-module.md).

## 1. Check your tools

Type `javac --version`, then `jdeps --version`. Each command should print a version. If a command is missing, open the terminal where you configured the JDK and try again.

## 2. Inspect a small addition program

Compile the addition example into its own folder. Run `jdeps` on that folder.

```powershell
javac --release 21 -d build/java-deps-arithmetic content/labs/java-path/AddReadings.java
jdeps --print-module-deps build/java-deps-arithmetic
```

The output is `java.base`. It contains core classes such as `String` and `System`. This method uses a whole-number addition and writes the result with `System.out`.

## 3. Inspect the HTTP example

Repeat for the [local HTTP example](24-test-a-local-java-http-route.md).

```powershell
javac --release 21 -d build/java-deps-http content/labs/java-path/LocalReadingServer.java
jdeps --print-module-deps build/java-deps-http
```

The output is `java.base,java.net.http,jdk.httpserver`. Find the client import `java.net.http.HttpClient` and the server import `com.sun.net.httpserver.HttpServer` in the source. These commands inspect the classes without starting the server.

## 4. Inspect the JDBC example

Repeat for the [database example](23-read-a-local-database-with-jdbc.md).

```powershell
javac --release 21 -d build/java-deps-jdbc content/labs/java-path/LocalReadingDatabase.java
jdeps --print-module-deps build/java-deps-jdbc
```

The output is `java.base,java.sql`. The source uses the standard JDBC interfaces. When you run the database program, you still supply the H2 driver JAR described in the JDBC lesson. A dependency loaded at runtime can be absent from this static report.

## 5. Record what you need to run the program

Keep each output with its source file when handing the program to someone else. Record runtime files and configuration separately. The same distinction helps when you package an application with the Umicom Framework SDK. Record the libraries the linker sees and the resources the installed application needs at runtime.

If `jdeps` reports extra modules, check that each folder contains only the class files from that example. Use a new output folder and rerun the two commands if you previously compiled another program there.

You can now use a module report to answer a concrete question before packaging. Which JDK modules does this program refer to, and what else must be supplied to run it?

[Previous lesson](26-read-a-method-in-bytecode.md) · [Java course](index.md) · [JDK jdeps reference](https://docs.oracle.com/en/java/javase/21/docs/specs/man/jdeps.html)
