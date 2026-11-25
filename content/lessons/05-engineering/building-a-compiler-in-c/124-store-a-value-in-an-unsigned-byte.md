<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/124-store-a-value-in-an-unsigned-byte.md

PURPOSE:
Store a value in an unsigned byte

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Store a value in an unsigned byte

Imagine a tiny counter in a message sent by a practice trading application. The counter occupies eight **bits**. A bit is a value that can be either 0 or 1. Eight bits give 256 possible patterns. Umicom C stores the patterns for an `unsigned char` local as the values 0 through 255. This lesson uses a fictional counter and ordinary integers.

## 1. Work out what fits

1. Write down 255 as the starting value. It is the largest value in the counter.
2. Add 1 to obtain 256. When the program stores the answer in the byte, a complete group of 256 is removed. The stored result is 0.
3. Add 298 to the stored 0. Remove a complete group of 256 from 298. The byte now holds 42.

The remaining part is called the **remainder**. Keeping the remainder in this range is also called working **modulo 256**. On paper, try starting from 254. After the increment the counter holds 255. Adding 298 gives 553. Removing two groups of 256 leaves 41.

## 2. Translate the steps into C

~~~text
Store 255 in the counter.
Add 1 and store its equivalent value between 0 and 255.
Add 298 to that stored value.
Store its equivalent value between 0 and 255.
Return the counter.
~~~

Save the corresponding program as `byte-local.c`.

~~~c
int main(void)
{
    unsigned char counter = 255;
    counter++;
    counter = counter + 298;
    return counter;
}
~~~

The type tells Umicom C how to store the variable. The operator `++` means “add one”. The addition on the right of `=` is evaluated before the result is stored on the left. Umicom C checks its supported integer arithmetic before doing the byte conversion. When an arithmetic operation exceeds its checked integer range, the program reports an error before that attempted store.

## 3. Check, compile and run the file

Use an existing Umicom C build with support for checked `unsigned char` locals. Replace the path with your own compiler executable. From the directory holding `byte-local.c`, choose a fresh name for the compiled bytecode.

~~~powershell
$Tool = 'C:/umicom/umicom-c/build/windows-ucrt64-debug/bin/umicom-c.exe'
if (Test-Path -LiteralPath './byte-local.umc') { throw 'Choose a fresh bytecode filename.' }
& $Tool check './byte-local.c'
if ($LASTEXITCODE -ne 0) { throw 'Read the source check before compiling.' }
& $Tool compile './byte-local.c' './byte-local.umc'
if ($LASTEXITCODE -ne 0) { throw 'Read the compile diagnostic.' }
& $Tool exec './byte-local.umc'
if ($LASTEXITCODE -ne 0) { throw 'Read the bytecode runtime diagnostic.' }
~~~

The expected result is `Result: 42`. The focused compiler checks also recorded 18 executed instructions for this exact source. If the check stops at the declaration with “assignment requires a declared local integer”, check which compiler executable you selected. An earlier release may reach that message on the same input.

## 4. Change one input

Try the counter with 0 as its initial value. Predict the result before running the file with `umicom-c run byte-local.c`. The first stored answer is 1. Adding 298 gives 299, so the remaining value is 43. In an application test, use an ordinary value, the largest byte value and the transition back to zero.

[Course contents](index.md) · [Previous lesson · Measure a Boolean literal without reading its value](123-measure-a-boolean-literal-without-reading-its-value.md) · [Group console checks by what they submit](../automated-testing-with-umicom/15-group-console-checks-by-what-they-submit.md) · [Next lesson · Choose typed values in the C console](125-choose-typed-values-in-the-c-console.md) · [HTML edition](../../../courses/building-a-compiler-in-c/lessons/124-store-a-value-in-an-unsigned-byte.html)
