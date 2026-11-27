# Keep a valid total in a class

![Umicom](../../../assets/branding/umicom-wordmark.svg)

Add two readings to a report, then try one that the report must refuse. A Java class can keep the data and the rules for changing it together. This class owns a single total and accepts only readings that keep it valid.

Use JDK 21 or later and PowerShell. Open the Bits2Banking checkout so you can see the `content` directory. If you have just started with methods, read [Total an array with a method](13-total-an-array-with-a-method.md) first.

## 1. Open the example

Find `content/labs/java-path/ReadingTotal.java`. Look for `private int total = 0`. Each new `ReadingTotal` object starts at zero. The word `private` keeps callers from assigning to the field directly.

Next, find `add`. It checks the new reading before it changes the field. `value` returns the current total. You can follow this idea in plain words.

```text
Start the total at zero.
For each reading, check that it is a valid number to add.
Add a valid reading to the total.
Keep the old total when a reading is refused.
Show the total when asked.
```

## 2. Build and run

```powershell
javac --release 21 -d build/java-reading-class content/labs/java-path/ReadingTotal.java
java -cp build/java-reading-class ReadingTotal
```

You should see these three lines.

```text
Total: 20
Accepted negative reading: false
Total after refusal: 20
```

`new ReadingTotal()` created the report. The next two calls added 12 and 8. The negative reading returned `false`, and the last line shows that the saved total stayed at 20.

## 3. Change one reading

Copy `ReadingTotal.java` into your own practice folder and change `report.add(8)` to `report.add(3)`. Recompile the copy using its path in the first command. Run the second command again. The first and third lines should now show 15.

The method also checks whether the next sum will fit in an `int`. A C23 module can follow the same policy by owning its data in a structure and checking proposed changes before it assigns a new value. Use the [Java and C23 file exercise](21-verify-a-java-and-c23-file-contract.md) for a comparison between the two languages.

If Java still prints 20 after your edit, check the path passed to `javac` and make sure it compiled your edited copy. The `-cp` option should point to that same output directory.

[Previous lesson](30-read-report-settings.md) · [Next lesson](32-save-a-copy-of-a-growing-list.md) · [Java course](index.md)
