<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/c23-keyword-reference/10-check-an-integer-field-width.md

PURPOSE:
  Find the range of a nine-bit number and test deliberate unsigned conversion.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Check an integer field width

[Previous lesson](09-ask-for-a-declared-type.md) · [Course contents](index.md) · [HTML edition](../../../courses/c23-keyword-reference/lessons/10-check-an-integer-field-width.html)

Some device fields and file formats specify a number of bits. A bit is one position with two possible values. A nine-bit unsigned field holds integers from zero through 511.

## Read the C23 declaration

~~~c
typedef unsigned _BitInt(9) ChannelBits;
const ChannelBits lastChannel = 511;
const unsigned int nextValue = (unsigned int)lastChannel + 1U;
const ChannelBits wrapped = (ChannelBits)nextValue;
~~~

The wider variable can hold 512. Converting it to the nine-bit unsigned type reduces it modulo 512, giving zero. Keep the wider value when a program needs to reject overflow before conversion.

## Trace the steps in plain language

~~~text
Write 511 as the largest nine-bit channel.
Add one in a wider type to obtain 512.
Convert 512 to the nine-bit unsigned type.
Check that the converted value is zero.
~~~

## Keep numeric width separate from storage

The source checks that enough storage bits exist to hold the value. A wider storage size can still represent a nine-bit value type. When talking to Kernel device code or writing a binary record, define byte order and range checks explicitly. The example imposes no fixed storage size or byte order.

- [Nine-bit conversion source](https://github.com/umicom-foundation/Bits2Banking/blob/main/content/labs/native/c23-type-and-value/bit_width.c)

## Run the focused lab

Use a terminal in the Bits2Banking checkout with a recent GCC or Clang that supports C23. Run each command separately. A failed command stops the exercise until you resolve the diagnostic.

~~~powershell
cmake -S content/labs/native/c23-type-and-value -B build/c23-type-and-value -G Ninja -DBUILD_TESTING=ON
cmake --build build/c23-type-and-value
ctest --test-dir build/c23-type-and-value --output-on-failure --no-tests=error -R '^btb[.]education[.]c23[.]bit_width$'
~~~

CTest should report every selected check passed. Each passing native example verifies its result and exits with status zero.

## Predict a change

Predict the output values if you use 510 instead of 511. The wider result is 511 and conversion can still hold it. Restore the source before running the original test again. If the compiler does not recognise _BitInt in C23 mode, use a hosted compiler with that support and confirm the selected compiler in the CMake output.

[C23 working draft, sections 6.2.5 and 6.3.1.3 on integer types and conversions](https://www.open-std.org/jtc1/sc22/wg14/www/docs/n3096.pdf)
