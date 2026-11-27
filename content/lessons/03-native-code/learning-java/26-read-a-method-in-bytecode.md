# Read a method in bytecode

![Umicom Foundation](../../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }
<a href="../../../assets/branding/umicom.ico"><img src="../../../assets/branding/umicom-icon.svg" width="28" alt="Umicom icon"></a>

Follow the method that adds 12 and 8. Compile it, see the number 20, then open the instructions in its class file. Read [Total an array with a method](13-total-an-array-with-a-method.md) first if a Java method is new to you.

## Run and inspect the class

1. Save [AddReadings.java](../../../labs/java-path/AddReadings.java) in a practice folder.
2. Open a terminal there. Enter the three commands in order.
3. Check that the program prints `20`. Find `add(int, int)` in the listing from `javap`.

```powershell
javac --release 21 AddReadings.java
java AddReadings
javap -c AddReadings
```

The Java Virtual Machine, or JVM, reads instructions in the class file. These instructions are known as bytecode. `javap -c` lists them in a form you can read.

## Read the four instructions in `add`

```text
0: iload_0
1: iload_1
2: iadd
3: ireturn
```

The number before each instruction is its byte offset within the method. The operand stack is the JVM’s temporary storage for values during this calculation.

| Instruction | What it does for these inputs |
|---|---|
| `iload_0` | Put the first argument, 12, on the stack. |
| `iload_1` | Put the second argument, 8, above it. |
| `iadd` | Take both integers and put their sum, 20, back on the stack. |
| `ireturn` | Return the integer result to the caller. |

## Change one instruction through the source

1. In `add`, change `return first + second;` to `return first - second;`.
2. Run the three commands again. The program prints `4`, and `isub` now appears where `iadd` appeared before.
3. Restore the plus sign and rerun. If an earlier result still appears, make sure `javac` succeeded before launching the class again.

Use the same comparison when learning Umicom C. Keep one small calculation and its inputs, record the result, then inspect what the compiler produced. The JVM and Umicom C use their own instruction formats. [Compare a Java and C23 file contract](21-verify-a-java-and-c23-file-contract.md)

[Return to Learning Java](index.md) · [The javap command](https://docs.oracle.com/en/java/javase/21/docs/specs/man/javap.html) · [JVM integer addition](https://docs.oracle.com/javase/specs/jvms/se21/html/jvms-6.html#jvms-6.5.iadd)
