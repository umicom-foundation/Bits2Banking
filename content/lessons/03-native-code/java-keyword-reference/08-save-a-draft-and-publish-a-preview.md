<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/java-keyword-reference/08-save-a-draft-and-publish-a-preview.md

PURPOSE:
Practise static, final, transient and volatile fields in two complete Java 21 examples.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original learning material. Linked references retain their own terms.
-->

<picture>
  <source srcset="../../../assets/branding/umicom-wordmark-on-dark.svg" media="(prefers-color-scheme: dark)">
  <img src="../../../assets/branding/umicom-wordmark.svg" width="220" alt="Umicom">
</picture>

# Save a draft and publish a preview

[Course contents](index.md) · [Previous · Contextual words in module contracts](07-module-contracts.md) · [Browser edition](../../../courses/java-keyword-reference/lessons/08-save-a-draft-and-publish-a-preview.html)

A report draft has data worth keeping and display text that can be rebuilt. A report preview also needs a way to reach another thread. These two small programs give the field modifiers from [Access, storage, and shared state](04-access-and-storage.md) a job in runnable code.

Use a JDK that supports Java 21. Save both examples in one practice folder and open PowerShell there.

## 1. Save and restore a draft in memory

Save [ReportDraftStorage.java](../../../labs/java-keywords/ReportDraftStorage.java). Run the second command after the first succeeds.

```powershell
javac --release 21 -Xlint:all -Werror ReportDraftStorage.java
java -cp . ReportDraftStorage
```

```text
Original preview wide preview of 3 rows
Restored row count 3
Current class style compact
Restored cached preview null
Rebuilt preview compact preview of 3 rows
```

Java object serialisation writes an object’s saved data as bytes. This example writes its own byte array and reads that same array back in memory. The restored draft is a separate object.

`final` makes `rows` a fixed value for each draft. The original constructor sets it to 3, and default serialisation preserves that field. `static` gives the preview style one value on the class. The program changes it to `compact` before restoring the draft, and the running class keeps that current value.

The `transient` field `cachedPreview` holds display text that the class can reconstruct. Default serialisation skips that field. It starts at `null` in the restored draft, so calling `preview()` rebuilds it with the saved row count and the current class style.

Try changing `new ReportDraft(3)` to `new ReportDraft(5)` and recompile. The count and both preview lines should now report five rows. The restored cache still starts at `null`.

## 2. Publish a preview to another thread

Save [ReportPreviewHandoff.java](../../../labs/java-keywords/ReportPreviewHandoff.java) in the same folder. Compile and run it.

```powershell
javac --release 21 -Xlint:all -Werror ReportPreviewHandoff.java
java -cp . ReportPreviewHandoff
```

```text
Before publication null
Published heading Daily readings
Published row count 3
```

The worker creates one `Preview` record and writes its reference to `latest`, a `volatile` field. A reader that sees that write can use the fully constructed preview. With a string and an integer in one record, the heading and count come from the same preview.

The reader first checks `latest` before joining the worker. It tries again after a short pause if the value is still `null`. `volatile` provides visibility between the threads. The pauses limit how often the reader checks. The final `join()` waits for the worker to finish.

A counter increment has multiple steps. When workers update a pair of mutable counts, use the same lock for writing and reading both values, as in [Keep related counts in one snapshot](../../../courses/learning-java/lessons/44-keep-related-counts-in-one-snapshot.html).

## 3. Recover from a failed run

If Java cannot find either class, check that you are in the folder where its compilation succeeded. If the preview worker takes too long, the reader reports a timeout after the worker has joined. Check that `worker.start()` still runs and that `publishPreview()` still assigns `latest`.

[Java field modifiers](https://docs.oracle.com/javase/specs/jls/se21/html/jls-8.html#jls-8.3.1) · [Java default serialisable fields](https://docs.oracle.com/en/java/javase/21/docs/specs/serialization/serial-arch.html#defining-serializable-fields-for-a-class) · [Java visibility between threads](https://docs.oracle.com/javase/specs/jls/se21/html/jls-17.html#jls-17.4.5)
