<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/programming-across-languages/09-keep-a-signed-difference-in-range.md

PURPOSE:
Keep a signed difference in range

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Keep a signed difference in range

A signed 32-bit integer can describe values from −2,147,483,648 through 2,147,483,647. Two inputs may both fit while their difference falls outside that interval. For example, subtracting one from the lowest input needs a result one step below the minimum.

## Keep the boundary visible in each language

C23 widens both inputs to 64 bits before subtracting. If the mathematical value fits the old width, the program can pass the original inputs to the assembly leaf and publish its result.

~~~c
const int64_t wide = (int64_t)received - (int64_t)booked;
if (wide < INT32_MIN || wide > INT32_MAX) {
    return false;
}
*out = UmiLessonBalanceDelta(received, booked);
~~~

D has a fixed 32-bit `int` and a 64-bit `long`. The following comparison can be placed inside a function that takes `int received` and `int booked` and returns `bool`.

~~~d
long wide = cast(long) received - cast(long) booked;
if (wide < int.min || wide > int.max) {
    return false;
}
~~~

A D consumer can use `extern(C) int UmiLessonBalanceDelta(int received, int booked);` when it links with a compatible C ABI toolchain. This is a source-level comparison. The native lab below uses C and Assembly. [D language ABI](https://dlang.org/spec/abi.html)

In FreeBASIC, choose `Long` for the 32-bit inputs and `LongInt` for the check. Expand the type before doing the arithmetic. [FreeBASIC Long](https://www.freebasic.net/wiki/KeyPgLong)

~~~basic
Dim received As Long = 120
Dim booked As Long = 78
Dim wide As LongInt = CLngInt(received) - CLngInt(booked)
If wide < -2147483648LL OrElse wide > 2147483647LL Then
    Print "Outside the signed 32-bit range"
Else
    Print CLng(wide)
End If
~~~

The FreeBASIC example prints 42 for these two inputs. Other BASIC dialects can use different width names.

~~~text
WIDEN both counts to signed 64 bits
SUBTRACT booked from received
IF the result lies outside the 32-bit interval THEN refuse
OTHERWISE publish the 32-bit result
~~~

## Check what a refusal leaves behind

1. Run the linked C and Assembly lab as shown in the previous lesson.
2. Open `main.c`. Find the row with `INT32_MAX` and `-1`. Predict the mathematical difference, then compare it to the largest signed 32-bit result.
3. Find the value 77 used for the output before each row. Confirm that both rejected rows expect 77 after the call. This checks that the old result remains available.
4. Add a row with `received` equal to `INT32_MIN + 1` and `booked` equal to 1. Expect the exact bottom of the range to succeed.

A Umicom Bank or Trader calculation can check a range at its Framework boundary before any native calculation publishes a result. Whole pennies make the exercise exact. An actual product must also decide which currency and scale each input uses.

[Course contents](index.md) · [Previous lesson · Pass two integers through the C ABI](08-pass-two-integers-through-the-c-abi.md) · [HTML edition](../../../courses/programming-across-languages/lessons/09-keep-a-signed-difference-in-range.html) · [Check a signed difference in C23](../../../labs/native/shared-signed-delta/main.c) · [Subtract two signed inputs in Windows x64 Assembly](../../../labs/native/shared-signed-delta/delta_win64.S)
