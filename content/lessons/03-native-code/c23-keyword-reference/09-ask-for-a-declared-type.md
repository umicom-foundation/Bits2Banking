<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/c23-keyword-reference/09-ask-for-a-declared-type.md

PURPOSE:
  Compare const and unqualified C23 type queries with a deliberate compiler refusal.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Ask for a declared type

[Previous lesson](08-initialize-scalar-and-record-values.md) · [Course contents](index.md) · [Next lesson](10-check-an-integer-field-width.md) · [HTML edition](../../../courses/c23-keyword-reference/lessons/09-ask-for-a-declared-type.html)

A type tells C what values a variable can hold. A qualifier adds a rule to that type. The qualifier const means you cannot assign another value through that variable. Two declarations can use the same base type and still have different permissions.

## Read the C23 declaration

~~~c
const unsigned char channel = {6};
typeof(channel) original = {channel};
typeof_unqual(channel) next = {};
next = original * 7;
~~~

Both type queries use the type of the earlier channel. Their initializers choose their own starting values. The first declaration retains const, while the second makes next an editable unsigned char. Its new value is 42.

## Trace the steps in plain language

~~~text
Read the type of channel without changing channel.
Make a read-only original initialized to 6.
Make an editable next initialized to zero.
Calculate original times seven and save 42 in next.
Check that original is still 6.
~~~

## Compare a type query with a function call

The hosted expression example asks for the type of Sample(). The function returns an int and its type is fixed, so the query leaves the call count zero. The later ordinary call changes the count to one. This exercise uses the fixed-type case. C has a separate evaluation rule for operands of variably modified type.

- [Named scalar source](https://github.com/umicom-foundation/Bits2Banking/blob/main/content/labs/native/c23-type-and-value/named_type.c)
- [Assignment refusal source](https://github.com/umicom-foundation/Bits2Banking/blob/main/content/labs/native/c23-type-and-value/const_assignment.c)
- [Hosted expression source](https://github.com/umicom-foundation/Bits2Banking/blob/main/content/labs/native/c23-type-and-value/expression_type.c)

## Run the focused lab

Use a terminal in the Bits2Banking checkout with a recent GCC or Clang that supports C23. Run each command separately. A failed command stops the exercise until you resolve the diagnostic.

~~~powershell
cmake -S content/labs/native/c23-type-and-value -B build/c23-type-and-value -G Ninja -DBUILD_TESTING=ON
cmake --build build/c23-type-and-value
ctest --test-dir build/c23-type-and-value --output-on-failure --no-tests=error -R '^btb[.]education[.]c23[.](named_type|const_assignment|expression_type)$'
~~~

CTest should report every selected check passed. Each passing native example verifies its result and exits with status zero.

## Try the checked interpreter

If a current Umicom C interpreter with the checked scalar features is on your path, try the same source. Look for the Result: 0 line followed by the instruction count.

~~~powershell
umicom-c interpret content/labs/native/c23-type-and-value/named_type.c
~~~

## Predict a change

Read the refusal source first. Predict which variable the compiler will identify. Run the syntax-only check with CTest. A passing check means the compiler reported the forbidden assignment to original. The checked Umicom C example queries an already declared scalar, while the hosted compiler can also inspect the function expression.

[C23 working draft, section 6.7.2.5 on typeof specifiers](https://www.open-std.org/jtc1/sc22/wg14/www/docs/n3096.pdf)
