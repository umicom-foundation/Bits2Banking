# Use one native treasury service from Java and Kotlin

## Reuse through a process

Java and Kotlin run on the JVM in this lab. Both call NativeForecast.net, which launches the same trusted C executable. The native service owns the financial calculation. The JVM adapter owns argument conversion, waiting and response validation.

Using ProcessBuilder with separate arguments avoids shell interpretation. An absolute executable path makes the chosen program explicit. This does not make arbitrary executables safe: use the built calculator, which launches no child processes.

## Follow the response

The adapter closes stdin because no input stream is expected. A separate reader drains stdout into at most 128 bytes. The caller waits ten seconds for process completion, checks exit status, then waits up to two seconds for the reader. The response must be one signed decimal line and fit Java long.

The small program returns -15000 for the fixture. Kotlin delegates to the Java adapter and checks the same expected result. There is no Java or Kotlin subtraction formula to drift away from Framework.

## Try the boundaries

1. Run the C demonstration first using the lab README.
2. Compile NativeForecast.java and ForecastDemo.java.
3. Run the Java program with the absolute native executable path.
4. Compile ForecastDemo.kt against the Java output.
5. Run it with the same executable.
6. Record compiler identities, command results and the Framework SDK used.

Expected outputs are specified in the lab; they have not been observed here.

## Exercise and answer

The process writes a correct number and then an extra debug line to stdout. Should the adapter accept the first line? Answer: no. That would conceal a protocol change. Keep diagnostics on stderr and reject the malformed response.

## Understand the limits

This boundary does not provide a payment protocol, credentials, persistent audit, process-tree containment or a high-throughput server. It teaches ownership and reuse. Calypso integration is a separate step: use the documented Java SDK to obtain approved fields, validate their currency and units, then connect the mapped values to this service. A successful offline calculation does not qualify the vendor read or business mapping.

[Course contents](index.md)
