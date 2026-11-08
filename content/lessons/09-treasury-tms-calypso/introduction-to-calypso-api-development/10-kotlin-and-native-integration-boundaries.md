# Connect Kotlin and native code through explicit boundaries

## Choose a language for a reason

Calypso's documented classic application API is Java. Kotlin can call JVM classes, so it can reuse the same Java adapter. C and C++ serve a different purpose: they consume Umicom Framework's native C treasury contracts. There is no invented Calypso C API in this course.

The [Kotlin example](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/java/calypso-classic-readonly/ClassicTradeExample.kt) receives the host's DSConnection and delegates to ClassicTradeReader. It explicitly handles a nullable returned identity. It does not create another session or disconnect the host's session.

## Keep financial data explicit

Before passing a value to a native calculator, define currency, minor-unit scale, sign, horizon and provenance. A Java double is not an appropriate default carrier for an exact cash amount. Convert a documented decimal amount using a reviewed rounding rule, rejecting values that cannot be represented.

The separate [Framework bridge lab](https://github.com/umicom-foundation/Bits2Banking/tree/main/labs/native/treasury-framework-bridge) already expects whole minor units. Its JVM adapter launches a trusted native executable using separate arguments and bounded output. It does not extract Calypso product amounts automatically.

## Worked mapping

An approved business mapping produces GBP receipt 1250.00 and payment 1400.00 for the same horizon. At scale two, send 125000 and 140000. Expected result is -15000. If one source amount is USD, stop: choosing the same number of decimal places does not make currencies compatible.

## Exercise and answer

Why not pass a serialized vendor Trade object into C? Answer: its Java representation, lifecycle and versioning are not a stable native wire contract. Extract only approved scalar fields into an explicit schema.

## Qualification

Compile Kotlin with the certified JVM and matching JAR classpath. Qualify the vendor read, field mapping and native calculation independently before connecting them. A correct -15000 result proves arithmetic for that fixture; it does not prove Calypso permissions, valuation, settlement or server compatibility.

[Course contents](index.md)
