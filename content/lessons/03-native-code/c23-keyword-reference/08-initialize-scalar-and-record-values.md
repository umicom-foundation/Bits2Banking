<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/c23-keyword-reference/08-initialize-scalar-and-record-values.md

PURPOSE:
  Use C23 empty braces for a scalar or a record, then verify the individual values.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Initialize a value before reading it

[Previous lesson](07-read-alternative-punctuators.md) · [Course contents](index.md) · [Next lesson](09-ask-for-a-declared-type.md) · [HTML edition](../../../courses/c23-keyword-reference/lessons/08-initialize-scalar-and-record-values.html)

A freshly declared local variable needs a known value before you read it. An initializer supplies that value when the object is created. Think of a report that starts with no work recorded.

## Read the C23 declaration

~~~c
int processed = {};
bool retry = {};
unsigned char channel = {42,};
~~~

The integer starts at zero and the truth value starts false. The last line provides one value, 42. Its final comma adds no value. Read the opening and closing braces as the boundary of the initializer.

## Trace the steps in plain language

~~~text
Start the processed count at zero.
Start retry at false.
Set channel to 42.
Copy channel into processed.
Check that processed equals 42 and retry is still false.
~~~

## Check a whole report

The hosted record example has a total, a truth value and an array of three amounts. Check each declared member of the empty report before comparing it with the reviewed report. In the reviewed report, the initializer supplies only one amount. The next two entries and the omitted total start at zero.

- [Scalar source](https://github.com/umicom-foundation/Bits2Banking/blob/main/content/labs/native/c23-type-and-value/empty_scalar.c)
- [Report record source](https://github.com/umicom-foundation/Bits2Banking/blob/main/content/labs/native/c23-type-and-value/empty_record.c)

## Run the focused lab

Use a terminal in the Bits2Banking checkout with a recent GCC or Clang that supports C23. Run each command separately. A failed command stops the exercise until you resolve the diagnostic.

~~~powershell
cmake -S content/labs/native/c23-type-and-value -B build/c23-type-and-value -G Ninja -DBUILD_TESTING=ON
cmake --build build/c23-type-and-value
ctest --test-dir build/c23-type-and-value --output-on-failure --no-tests=error -R '^btb[.]education[.]c23[.]empty_'
~~~

CTest should report every selected check passed. Each passing native example verifies its result and exits with status zero.

## Try the checked interpreter

If a current Umicom C interpreter with the checked scalar features is on your path, try the same source. Look for the Result: 0 line followed by the instruction count.

~~~powershell
umicom-c interpret content/labs/native/c23-type-and-value/empty_scalar.c
~~~

## Predict a change

Change the reviewed record so its first amount is 17, then predict which check fails. After reviewing the failed test, restore 42. A correct field value leaves the test successful. A C record may contain extra padding, so these checks use the members themselves when validating a report.

[C23 working draft, section 6.7.9 on initialization](https://www.open-std.org/jtc1/sc22/wg14/www/docs/n3096.pdf)
