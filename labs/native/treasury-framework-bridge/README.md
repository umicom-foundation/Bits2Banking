# One treasury calculation, four language consumers

The C and C++ programs call Umicom Framework's cash_forecast API. Java and Kotlin start the C executable through the same Java adapter. They do not reimplement the net-cash calculation. A separate process avoids coupling the JVM to a compiler-specific native library ABI, at the cost of startup overhead. This small classroom protocol is not a production payment service.

Amounts are nonnegative signed 64-bit integers in minor units, with one agreed currency and horizon. For a currency with two decimal places, 125000 means 1250.00. The example gives inflow 125000 and outflow 140000, so expected net is -15000. This is a forecast gap, not an instruction to borrow or settle money. Zero horizon is a classroom sentinel, not a date inferred from the machine clock.

## Build against an installed SDK

First install a compatible Framework SDK using its own build guide. In PowerShell, replace the example prefix with that SDK's actual location. Run each command separately and stop after an error.

~~~powershell
Set-Location C:\umicom\Umicom-Bits2Banking
cmake -S labs/native/treasury-framework-bridge -B build/treasury-framework-bridge -G Ninja -DCMAKE_PREFIX_PATH=C:/umicom/installed/framework
cmake --build build/treasury-framework-bridge
ctest --test-dir build/treasury-framework-bridge --output-on-failure
& .\build\treasury-framework-bridge\treasury-forecast.exe 125000 140000
& .\build\treasury-framework-bridge\treasury-forecast-cpp.exe
~~~

Expected stdout from each demonstration is -15000. CTest covers zero, signed-limit inputs, overflow, a negative input, leading whitespace, decimal notation and empty text. Refused requests return exit 2 and no stdout. These are expected outcomes, not executed results.

If CMake cannot find UmicomFrameworkConfig.cmake, check the installation prefix and finance target. If linking fails, compare SDK compiler, architecture and runtime with your consumer. Do not copy individual libraries from unrelated builds. A dynamic installation may require its bin folder on PATH.

## Java and Kotlin

JDK 8 or later is sufficient for NativeForecast.java itself; choose a compatible Kotlin/JDK combination. These JVM examples do not load Calypso libraries.

~~~powershell
Set-Location C:\umicom\Umicom-Bits2Banking\labs\java\treasury-framework-bridge
New-Item -ItemType Directory -Force out
javac -d out NativeForecast.java ForecastDemo.java
java -cp out ForecastDemo C:\umicom\Umicom-Bits2Banking\build\treasury-framework-bridge\treasury-forecast.exe
kotlinc ForecastDemo.kt -classpath out -d out-kotlin
kotlin -classpath "out;out-kotlin" ForecastDemoKt C:\umicom\Umicom-Bits2Banking\build\treasury-framework-bridge\treasury-forecast.exe
~~~

The adapter uses separate process arguments, closes stdin, limits stdout to 128 bytes and waits at most ten seconds for the process, then two seconds for complete output. It rejects a nonzero exit or malformed signed decimal line. Stderr is inherited for diagnostics. It runs a trusted calculator that creates no child processes; this is not process-tree containment for arbitrary executables. Currency conversion, authentication, persistent audit and request multiplexing are intentionally outside this protocol.

## Exercise and recovery

Predict the result for 9000 and 12000, then change the Java and Kotlin fixtures. Expected result: -3000. Try replacing the executable path with a missing file: the adapter must refuse before launch. Replace an input with -1: the Java precondition must refuse it; the native CTest separately exercises direct command refusal. Keep those two boundaries distinct.

When a result differs, first compare actual arguments and units, then the loaded Framework SDK identity, then stdout and exit status. Do not change the expected value to make a regression disappear. The lab sources and tests are authored; compiler, JVM and installed-consumer qualification remain to be run.
