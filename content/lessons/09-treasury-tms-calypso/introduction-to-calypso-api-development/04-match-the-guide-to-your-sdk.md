# Match the guide to your licensed SDK

## What you will learn

An API is a contract between your program and a library. A class name that looks familiar is not enough: parameter types, return types, exceptions and execution context matter. The Treasury developer guide describes classic Calypso services, while later training documents also contain illustrative examples. Treat those two kinds of evidence separately.

This module uses the original guide's DSConnection, RemoteTrade and Trade examples as its baseline. It does not claim certification for an unspecified release. The [SDK lab](https://github.com/umicom-foundation/Bits2Banking/tree/main/labs/java/calypso-classic-readonly) supplies original adapter code without licensed JARs.

## Build a compatibility record

1. Write down the installed Calypso release, patch and certified JDK.
2. Identify the approved client libraries and their distribution licence.
3. Inspect the three classes with javap or the matching Javadoc.
4. Record the descriptor of getRemoteTrade(), getTrade and getId().
5. Compile the adapter before connecting it to any environment.

~~~powershell
javap -classpath $CalypsoSdkClasspath com.calypso.tk.service.RemoteTrade
javap -classpath $CalypsoSdkClasspath com.calypso.tk.core.Trade
~~~

The classpath variable must identify your licensed SDK, as explained in the lab. A compiler error about a missing class means your dependency inventory is incomplete; it does not prove the financial operation is unsupported. A method mismatch may instead identify a release difference.

## Worked example

Suppose the guide shows getTrade(int), but your SDK accepts long. Java can widen an int argument, yet that does not establish permission semantics or missing-record behaviour. Record the difference and qualify those behaviours explicitly. Never create a class called com.calypso.tk.core.Trade merely to make compilation pass: that would test a substitute.

## Exercise and answer

A colleague says a fake-repository unit test proves server integration. What additional evidence is needed? Answer: compilation against identified vendor libraries, an authorized server session, a controlled record, observed result and retained failure cases. The fake remains useful for your own control logic, but it cannot establish the vendor boundary.

## Reading

Continue from the [sources and licensing guide](../../../lessons/09-treasury-tms-calypso/sources-and-licensing.md). The classic material is a teaching baseline; current architecture also has release-specific deployment differences.

[Course contents](index.md)
