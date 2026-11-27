# Read a local database with JDBC

![Umicom Foundation](../../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }
<a href="../../../assets/branding/umicom.ico"><img src="../../../assets/branding/umicom-icon.svg" width="28" alt="Umicom icon"></a>

Read two confirmed measurements and one trial measurement from a small database. You will see how a Java program sends SQL values and decides which changes to keep. Read [Read a file and explain errors](16-read-a-file-and-explain-errors.md) first if `try` with resources is unfamiliar.

## Run the example

1. Save [LocalReadingDatabase.java](../../../labs/java-path/LocalReadingDatabase.java) in a practice folder.
2. Download the H2 2.4.240 JAR from the linked Maven Central release and save `h2-2.4.240.jar` beside the Java source. This is the driver that connects Java to the embedded database. [H2 2.4.240 release](https://central.sonatype.com/artifact/com.h2database/h2/2.4.240)
3. In PowerShell, open that folder and enter these commands. The semicolon separates the compiled class folder from the JAR on the Windows classpath.

```powershell
javac --release 21 LocalReadingDatabase.java
java -cp ".;h2-2.4.240.jar" LocalReadingDatabase
```

Expected output

```text
Confirmed north units: 20
During the trial: 23
After rollback: 20
Unlisted site: 0
```

## Follow the data

1. JDBC is Java's interface for talking to a database. The connection URL starts an in-memory H2 database. The whole practice database disappears when its last connection closes.
2. The `CREATE TABLE` command defines a short site name and an integer number of units for each row.
3. A prepared statement keeps SQL instructions and values separate. `setString(1, site)` fills the first `?` with text. `setInt(2, units)` fills the second with a whole number.
4. The first `commit()` keeps the three confirmed rows. The next insert adds three units and shows 23 in the same connection. `rollback()` undoes that trial, so the total returns to 20.
5. `COALESCE(SUM(units), 0)` gives a zero when a site has no readings. The `try` blocks close the query, its rows and the connection when each is finished.

## Practise and recover

1. Change the trial reading from `3` to `7`. Compile and run again. Only the `During the trial` result should change, to 27.
2. Try running without the JAR on the classpath. Java should report that it cannot find a suitable driver. Restore the quoted classpath and rerun.
3. Explain why a report can show a trial total inside a transaction before that trial has been confirmed.

In an Umicom application, separate the database connection and transaction ownership from the code that displays the report. You can then use the same report rules from a command-line test and an interface.

[Return to Learning Java](index.md) · [Copy between typed lists](22-copy-between-typed-lists.md) · [JDBC prepared statement reference](https://docs.oracle.com/en/java/javase/21/docs/api/java.sql/java/sql/PreparedStatement.html) · [H2 in-memory databases](https://www.h2database.com/html/features.html#in_memory_databases)
