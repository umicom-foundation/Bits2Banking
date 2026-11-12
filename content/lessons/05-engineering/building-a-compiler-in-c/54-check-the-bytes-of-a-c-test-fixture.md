<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/54-check-the-bytes-of-a-c-test-fixture.md

PURPOSE:
Check the bytes of a C test fixture

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Check the bytes of a C test fixture

## Preparation and outcome

Build the c-library-composition lab from the previous lesson. Open fixture_test.c and select the hex-boundary and utf8-octets cases. You will separate the source spelling of a string from the bytes stored in the resulting array. This matters whenever a parser test uses escapes to construct input.

## A greedy hexadecimal escape

A C hexadecimal escape begins with backslash-x and consumes the following hexadecimal digits. The letter c is a hexadecimal digit. Writing a backtick escape followed immediately by the language label c therefore changes the escape itself. The compiler can warn that the value is out of range; the parser then receives different data from the fixture author's intention.

End the escape with a string-literal boundary:

~~~c
const unsigned char fence[] = "\x60\x60\x60" "c\n";
const unsigned char expected[] = {96U, 96U, 96U, 99U, 10U, 0U};
~~~

Adjacent string literals are concatenated into one string. The closing quote ends the hexadecimal escape before concatenation. The array therefore contains three backticks, c, a newline and a terminating zero. The explicit expected array provides an independent representation; writing the same mistaken escape in both actual and expected strings would hide the defect.

## Verify length and content

1. Compare sizeof fence with sizeof expected. Here both include the terminating zero because both operands are arrays.
2. Compare all expected bytes with memcmp. A text-only comparison could overlook bytes after an embedded zero.
3. Check the parser output in a separate regression. Correct input construction does not establish correct parsing.

Run the focused lab case:

~~~powershell
ctest --test-dir build/c-library-composition -R hex-boundary --output-on-failure --no-tests=error
~~~

Expect one pass. If the test fails, inspect the first differing numeric byte and the array size. Do not change the expected output until you have independently established the intended input.

## A UTF-8 byte view

The second case stores cafe with an accented final letter as a ten-byte path. The accented letter occupies two UTF-8 octets. The byte positions are checked through a const unsigned char pointer:

~~~c
const char path[] = "caf\xc3\xa9/tool";
const unsigned char *octets = (const unsigned char *)path;
~~~

This view neither copies nor modifies the array. It makes octet values explicit even on implementations where plain char is signed. The pointer retains const because the caller still owns read-only input. A cast alone does not validate UTF-8 or prove that a string is terminated. The Framework preflight code first finds a terminator inside its fixed storage, then passes the exact bounded extent to the existing UTF-8 validator.

Run the utf8-octets test and expect one pass. Its purpose is representation, not a complete UTF-8 validator. Framework's tool metadata regressions separately include malformed byte sequences and valid multibyte paths.

## Exercise and recovery

In a scratch copy, change the following language label from c to x. Explain why x stops a hexadecimal escape while c does not. Restore the maintained fixture afterward. Next compare strlen(path), sizeof path and the number of displayed characters. Record the units for each result and explain why a displayed glyph count cannot safely become a buffer byte capacity.

A warning in a fixture is still a defect worth investigating. It can invalidate what the test claims to exercise even when the production parser compiled successfully.

[Course contents](index.md) · [Previous lesson](53-give-private-helpers-a-linker-namespace.md) · [Next lesson](55-keep-regression-observations-type-correct.md)
