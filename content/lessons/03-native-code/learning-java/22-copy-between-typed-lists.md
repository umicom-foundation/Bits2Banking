# Copy between typed lists

![Umicom Foundation](../../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }
<a href="../../../assets/branding/umicom.ico"><img src="../../../assets/branding/umicom-icon.svg" width="28" alt="Umicom icon"></a>

Copy two whole-number readings into a report that already contains a decimal reading. This exercise uses one reusable method and asks the compiler to check that the destination accepts the items. Start with [Group deliveries with collections](15-group-deliveries-with-collections.md) if `List` is new to you.

## Run the example

1. Save [CopyReadings.java](../../../labs/java-path/CopyReadings.java) in a practice folder.
2. Open your terminal in that folder. Use the same JDK from the course and enter the two commands below.
3. Compare the two output lines. The first shows the report after copying. The second shows the original source list.

```powershell
javac --release 21 CopyReadings.java
java CopyReadings
```

Expected output

```text
[2.5, 12, 8]
[12, 8]
```

## Read the method one part at a time

```java
static <T> void appendAll(List<? extends T> source, List<? super T> destination) {
    for (T reading : source) {
        destination.add(reading);
    }
}
```

1. `<T>` introduces a type chosen for this call. When you read from the source, each item can be treated as `T`.
2. `? extends T` allows a source whose items are `T` or a more specific type. `Integer` is one kind of `Number`.
3. `? super T` allows a destination whose element type can hold a `T`. A list of `Number` can accept each `Integer` reading.
4. The loop adds each reading in source order. The destination must support addition, and the two lists should be separate. Type checking and those runtime conditions are separate checks.

## Ask the compiler to catch a mistake

1. Add `List<String> labels = new ArrayList<>();` just below `report.add(2.5);`.
2. Change the call to `appendAll(newReadings, labels);` and compile again. The compiler reports incompatible bounds because this copy would put numbers into a list of text. Read the diagnostic near `appendAll`.
3. Restore the original call, remove the added `labels` line and compile before running again. A failed compile can leave the earlier class file in place.

In Umicom Studio IDE, the same `javac` check belongs to the Java build task. Confirm the build succeeded before using the previous output to judge a source edit.

[Return to Learning Java](index.md) · [Verify a Java and C23 file contract](21-verify-a-java-and-c23-file-contract.md) · [Java Language Specification on type arguments](https://docs.oracle.com/javase/specs/jls/se21/html/jls-4.html#jls-4.5.1)
