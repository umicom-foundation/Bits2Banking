<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-freebasic/02-names-values-and-number-types.md

PURPOSE:
Names, values and number types

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Names, values and number types

[Course contents](index.md)
Memory holds values while a program runs. A variable gives a value a name and a type. The type tells the compiler how much storage to reserve and which operations make sense. Declaring a variable is not the same as printing it. In the fb dialect, declare your variables rather than relying on undeclared names.

~~~basic
Dim As Long items = 3
Dim As Long centsEach = 125
Dim As Long totalCents = items * centsEach
Const As Long maximumItems = 100
Print totalCents
Print maximumItems
~~~

1. Save the example as values.bas and compile with fbc -lang fb -w all values.bas -x values.exe.
2. Run .\values.exe. Expect the numeric values 375 and 100; console spacing is not significant here.
3. Change items to 4. Predict 500 before recompiling.
4. Change maximumItems in an assignment after its declaration. Observe that a constant cannot be assigned a new value. Restore the original program.

Dim declares storage. As connects the name to its type. The equals sign initializes or assigns a value in these statements. Const declares a value you intend to keep fixed. Multiplication uses *. FreeBASIC names are case insensitive, so items and ITEMS refer to the same identifier. Use one spelling consistently for people reading your code.

Long is a signed 32-bit integer in FreeBASIC. Integer follows the compiler target’s native integer size; do not assume it always matches C int. LongInt is signed 64-bit. Unsigned types cannot represent negative values. Single and Double approximate real numbers using floating point. Currency examples here use integer cents and small values so rounding is visible and overflow is avoidable; they are not a complete financial arithmetic library.

Overflow occurs when a result does not fit its type. A bigger input does not automatically make the calculation safer. Validate permitted ranges before multiplying. If you use a wider result, widen an operand before the multiplication rather than after an already overflowing expression. For production finance, reuse Framework’s reviewed money and rounding contracts.


## Exercise and answer

With 7 items at 250 cents, the expected total is 1750 cents. Explain why the number 17.50 is not stored in totalCents: the unit is cents, not whole currency units. Add a comment recording that unit. Units are part of a data contract even when the compiler sees only an integer.


## Choose a representation deliberately

| Type | Meaning | Use here |
| --- | --- | --- |
| Long / ULong | 32-bit signed / unsigned | Explicit C ABI width after verification |
| LongInt / ULongInt | 64-bit signed / unsigned | Larger bounded counts |
| Integer / UInteger | Target-native integer width | Local loop counters; verify exported ABI |
| Single / Double | Floating-point approximation | Measurements, not automatic exact money |

## Continue learning

[Previous: From typed text to a running FreeBASIC program](01-from-text-to-a-running-program.md) · [Course contents](index.md) · [Next: Text input, strings and validation](03-text-input-and-validation.md)
