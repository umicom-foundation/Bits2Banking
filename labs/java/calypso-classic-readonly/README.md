# Classic Calypso read-only SDK lab

This original lab follows the classic Java API described in Sammy Hegab's *Introduction to Treasury Management Systems Development: A Developer's Guide to Calypso Development*. Licensed client libraries are required. No vendor binaries, credentials, server connection or replacement vendor classes are supplied. Compilation and server behaviour remain unqualified.

## Read the adapter

ClassicTradeReader accepts an already authenticated DSConnection and 1–256 distinct positive integer IDs. It validates the complete request before calling getRemoteTrade().getTrade(id), then copies Trade.getId() into an immutable result. The caller owns connection lifetime. Null means only that no record was returned; exceptions propagate. The adapter does not save trades, apply workflow actions, price products or acknowledge events.

The integer request follows the classic guide. The Long result can hold either an int or long getId return. Add business fields only after checking SDK types, permissions, currency and lifecycle meanings. The request bound limits calls and memory, not remote execution time or consistency between calls.

## Inspect your licensed SDK

Use the JDK certified for your Calypso release. V14/V15 documentation is the reference baseline, not a claim that modern releases use identical extensions. From this lab folder in PowerShell:

~~~powershell
$CalypsoSdkClasspath = 'C:\CalypsoSDK\lib\*'
javap -classpath $CalypsoSdkClasspath com.calypso.tk.service.DSConnection
javap -classpath $CalypsoSdkClasspath com.calypso.tk.service.RemoteTrade
javap -classpath $CalypsoSdkClasspath com.calypso.tk.core.Trade
New-Item -ItemType Directory -Force out
javac -cp $CalypsoSdkClasspath -d out ClassicTradeReader.java
~~~

Replace the sample classpath with your approved SDK. Stop on errors. Confirm getRemoteTrade(), getTrade(int), and getId() using javap and Javadoc. A long-parameter overload may accept integer widening, but permissions and return semantics still require review. Record release, patch, Java version and JAR hashes privately.

Compile ClassicTradeExample.kt with kotlinc using out plus the approved individual JAR filenames as its classpath. Java wildcard expansion is not guaranteed in Kotlin compiler options. Separate Windows classpath entries with semicolons. This adapter library has no main method that guesses login arguments.

## Qualify in an approved sandbox session

1. Obtain an existing read-only DSConnection and one approved trade ID from the host application.
2. Call read(new int[] { approvedId }). Compare its identity with an authorized application view.
3. Try zero and a duplicate ID. Both must be refused before remote calls.
4. Use an approved missing-ID case. Record null versus exception; absence does not prove permission.
5. Make the service unavailable through supported test-environment controls. Preserve the exception instead of reporting an empty success.
6. Change a trade between two reads. Explain why this batch is not a database snapshot.

Configure timeouts through the release's supported client settings. Cancelling a Java Future alone does not prove remote work stopped. Production authorization and deployment are separate requirements.

## Extend the boundary

Study workflow transactions and engines before adding writes. The guide distinguishes remote clients from server callbacks receiving an existing transaction. Never commit that borrowed transaction or acknowledge an event merely because this read-only example succeeded. Kotlin reuses this Java adapter. C/C++ integration requires a reviewed process or service boundary; this course does not invent a vendor C SDK.
