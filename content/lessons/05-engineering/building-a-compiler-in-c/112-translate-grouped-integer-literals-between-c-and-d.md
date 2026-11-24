<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/112-translate-grouped-integer-literals-between-c-and-d.md

PURPOSE:
Translate grouped integer literals between C and D

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Translate grouped integer literals between C and D

A long number can be hard to read when all its digits run together. A **digit separator** makes groups easier to see. The group marks change the spelling. The number keeps its value as it moves between C23 and D.

## Read the parts of a number

A **literal** is a value written directly in source code. A **radix**, also called a base, tells you what each position means. Decimal is base ten. The digits in `1042` stand for one thousand, four tens and two ones. Hexadecimal is base sixteen. Its letter `A` represents ten, so `2A` is two sixteens plus ten. Binary is base two. Its places are worth 1, 2, 4, 8, 16 and 32, starting at the right.

| Radix | C23 spelling | D spelling | Decimal value |
| --- | --- | --- | --- |
| Decimal | `1'042` | `1_042` | 1042 |
| Hexadecimal | `0x2'A` | `0x2_A` | 42 |
| Binary | `0b10'1010` | `0b10_1010` | 42 |

The prefixes `0x` and `0b` choose hexadecimal and binary. Cover the separator with a pencil and read the remaining digits. In the binary example, the ones are in the 32, 8 and 2 places.

## Trace the value before running anything

The name `total_2` identifies a local variable, which stores a number during a function call. The underscore in this name is part of the identifier. It stays exactly where it is when the program is translated.

~~~text
STORE 1042 in total_2
SUBTRACT 1000 from total_2       total_2 is 42
ADD the hexadecimal value 42    total_2 is 84
RETURN total_2 minus the binary value 42
~~~

The returned value is 42. The local still contains 84 at the last line because that line calculates a result without assigning it back to the local.

## Translate the checked function

### 1. Save the C23 version

Save the following in a new practice folder as `grouped.c`. Use an Umicom C compiler that supports grouped integers in both C and D translation directions.

~~~c
int answer(void) {
    int total_2 = 1'042;
    total_2 -= 1'000;
    total_2 += 0x2'A;
    return total_2 - 0b10'1010;
}
~~~

### 2. Read the D result

Run these commands in PowerShell. Use new output names if either destination already exists. Stop if the first command reports an error.

~~~powershell
umicom-c translate c-to-d grouped.c grouped.d
umicom-c translate d-to-c grouped.d grouped-roundtrip.c
~~~

Here is the expected D text. In each number, one D underscore stands in the same place as one C apostrophe. The name `total_2` uses the same spelling in both files.

~~~d
int answer() {
    int total_2 = 1_042;
    total_2 -= 1_000;
    total_2 += 0x2_A;
    return total_2 - 0b10_1010;
}
~~~

### 3. Check the result in the regenerated C file

Open `grouped-roundtrip.c`. The C function header and its digit groups should match the original example. The editor and the translator can use different line endings.

If you have GCC with C23 support, save this caller in the practice folder as `verify-grouped.c`. It prints the result of the regenerated function and returns exit code zero for a match.

~~~c
#include <stdio.h>
int answer(void);
int main(void) { const int value=answer(); printf("%d\n",value); return value==42?0:1; }
~~~

~~~powershell
gcc -std=c23 -Wall -Wextra -Werror verify-grouped.c grouped-roundtrip.c -o verify-grouped.exe
if ($LASTEXITCODE -ne 0) { throw 'C compilation failed.' }
.\verify-grouped.exe
$LASTEXITCODE
~~~

Expect 42 followed by exit code 0. If the compiler cannot find the function, confirm that the command names both source files. This check runs the regenerated C program. Running the D program calls for a separate D compiler check.

## Find the same byte after checking a number

A processor can count the position of each character in the ASCII source file as a **byte offset**. It starts counting at zero. In the small expression `1_000 + 4/0`, the slash is at offset 9 within the expression. If the checker changes the underscore to an apostrophe in its private copy, the slash is still at offset 9.

~~~text
READ a decimal, hexadecimal or binary number
CHECK that each separator is between two digits of that base
MAKE a private copy for arithmetic checking
CHANGE each admitted D separator to one apostrophe in the copy
USE the original source offsets when reporting a problem
PUBLISH the complete translation after the checked result and output fit
~~~

Copy the one-line expression on paper and number its characters. Changing a separator to another single byte preserves the later positions. In a full file, the diagnostic also counts the bytes before that expression.

## Try a spelling outside the shared rules

The shared profile accepts one separator between adjacent digits of the same radix. Try these predictions before running the translator.

| Source expression | Reason for refusal |
| --- | --- |
| D `1__042` | A second separator follows the first, where a digit is needed. |
| D `0x_2A` | A separator occupies the first digit position after the prefix. |
| D `1_` | The separator has no following digit. |
| D `0b1_2` | Binary uses the digits 0 and 1. |
| C `0'17` | A leading zero begins an octal constant in C23. The shared profile refuses this spelling. |

Save `int answer() { return 0x_2A; }` as `grouped-refusal.d`. Run the next command with a fresh destination.

~~~powershell
umicom-c translate d-to-c grouped-refusal.d refused.c
~~~

Expect a syntax diagnostic identifying the underscore and check that the fresh output remains absent. D’s full grammar has additional placements for underscores. The current feature covers the shared checked C and D profile. C and Java translations continue to use their earlier integer spelling rules.

A Studio translation view can use the original byte offset to highlight the relevant character in the source file. The learner can compare both successful outputs and return to the original file when a spelling is refused.

[C23 integer constants, section 6.4.4.2](https://www.open-std.org/jtc1/sc22/wg14/www/docs/n3220.pdf) · [D integer literal grammar](https://dlang.org/spec/lex.html)

[Course contents](index.md) · [Previous lesson · Translate checked shifts between C and D](111-translate-checked-shifts-between-c-and-d.md) · [Related lesson · Translate hexadecimal and binary](105-translate-hexadecimal-and-binary.md) · [HTML edition](../../../courses/building-a-compiler-in-c/lessons/112-translate-grouped-integer-literals-between-c-and-d.html) · [C23 keyword reference](../../03-native-code/c23-keyword-reference/index.md) · [D keyword reference](../../03-native-code/d-keyword-reference/index.md)

[Next lesson · Compare signed integers between C and D](113-compare-signed-integers-between-c-and-d.md)
