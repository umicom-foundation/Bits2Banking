<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/56-read-hexadecimal-and-binary-source.md

PURPOSE:
Read hexadecimal and binary source without overflowing

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Read hexadecimal and binary source without overflowing

## Before you begin
Complete the expression and capability lessons. Build Umicom C from the same checkout you are reading. Open src/lexer.c and docs/integer-literals.md. This lesson extends a small integer language; it does not teach a complete C23 lexer.

## A spelling becomes a value
Decimal 42, hexadecimal 0x2A and binary 0b101010 describe the same integer. A radix is the number of different digits used by a spelling. Decimal has ten, binary two, hexadecimal sixteen. Hexadecimal uses A through F for digit values ten through fifteen.

Decode 0x2A by hand: start at zero, multiply by sixteen and add two, then multiply by sixteen and add ten. The result is 42. The parser should receive that value without caring which spelling produced it.

~~~c
value = value * base + part;
~~~

That line is safe only after the next value has been admitted. The implementation checks first:

~~~c
if (value > (INT32_MAX - part) / base)
    return umc_fail(diagnostic, UMC_LITERAL_RANGE, start);
~~~

Every admitted part is nonnegative and smaller than base. Subtracting it from INT32_MAX is therefore safe. Integer division gives the greatest previous value that can be extended. Try value 134217727, base 16 and part 15: the result is exactly INT32_MAX. Increasing value by one must fail before multiplication.

## Follow the boundary in source
1. Find the byte consumed at the start of umc_lex_next.
2. Find the length check before looking for x, X, b or B after zero.
3. Find the helper that consumes the prefix byte.
4. Track digits_start and explain why a bare 0x fails.
5. Find the check that rejects a digit outside the selected base.
6. Find the unchanged decimal branch below the new prefix admission.

The existing decimal branch matters. In this language 010 continues to mean ten. Silently changing it to octal would change the meaning of previously accepted programs. Explicit prefixes add new spellings without reinterpreting that older input.

## Use the actual command
From the Umicom C source directory, after building:

~~~powershell
.\build\bin\umicom-c.exe run examples\integer_literals.uc --max-steps 4
ctest --test-dir build -R "umicom.c.integer-literals.(values|refusals|decimal)" --output-on-failure --no-tests=error
~~~

The example compares two spellings of forty-two. Expect Result: 1 and Instructions: 4. The tests include mixed-case hex digits, long leading-zero sequences, signed limits, invalid binary digits and unsupported suffixes.

## Make a prediction, then check it
Create a separate practice source with return -0x80000000;. Predict a literal range error. The minus sign is a later unary operation; it cannot make the positive token fit. Rewrite it as -0x7fffffff - 1 and expect the minimum signed result.

Now try 0x1e+2. The e is a hexadecimal digit, so this is thirty plus two, not floating-point exponent notation. Try 0x1p0 and expect a syntax error because floating-point literals are outside the profile. Keep the original example unchanged.

## Recovery and limits
If an old compiler rejects the new prefix, inspect its profile output and the selected executable path. Rebuild the matching source rather than adding a silent decimal fallback. If a large constant is refused, check the signed literal range before changing arithmetic. This implementation does not provide unsigned integers, octal, suffixes or digit separators. Missing features should stay explicit.

[Course contents](index.md) · [Previous lesson](55-keep-regression-observations-type-correct.md) · [Next lesson](57-separate-source-spelling-from-wire-format.md)
