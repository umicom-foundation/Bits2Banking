<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/120-read-equivalent-signed-local-types.md

PURPOSE:
Read equivalent signed local types

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Read equivalent signed local types

Imagine a tally with 45 items added and 3 removed. You can write the removal as `-3`, a negative whole number. A **signed integer** can hold a negative number, zero or a positive number. You will read which words choose that type and which word prevents an accidental change.

## Read the words before the first name

In a declaration, the words before the first name describe the names that follow. In this Umicom C example, the comma introduces a second name. Each name has its own **initializer**, the expression that gives it a starting value.

~~~c
int main(void)
{
    /* One type and qualifier apply to both names in the declaration list. */
    signed const int low = -3, high = 45;
    return low + high;
}
~~~

1. Underline `signed const int`. Read `signed` and `int` together as the signed whole-number type. Circle `const`, which makes each local read-only after it receives its initial value.
2. Draw a box for `low` and enter `-3`. Draw another box for `high` and enter `45`. Mark both boxes read-only.
3. Add their contents. Starting from 45, moving three places to the left on a number line lands at 42. `return` gives this result to the interpreter's caller.

**Pseudocode** describes the same actions in plain language so you can follow the program on paper.

~~~text
CREATE read-only integer low with starting value -3
CREATE read-only integer high with starting value 45
RETURN low + high
~~~

## Compare the short spellings

In these initialized local declarations, `int`, `signed` and `signed int` select the same signed 32-bit type in Umicom C. The compiler accepts each of `int`, `signed` and `const` once in any order, with at least `int` or `signed` present. Try reading these declarations as separate versions of the same source line.

| Declaration | Value of `low + high` | Later update to `high` |
| --- | --- | --- |
| `int low = -3, high = 45;` | 42 | Allowed |
| `signed low = -3, high = 45;` | 42 | Allowed |
| `const int low = -3, high = 45;` | 42 | Refused |
| `signed const int low = -3, high = 45;` | 42 | Refused |

An explicit `signed` leaves the type and the sum unchanged. Adding `const` changes which later uses the compiler accepts. These local declarations run when the interpreter reaches them. The earlier `constexpr` exercise set a compile-time value during source admission.

Ordinary C23 uses the same equivalent type spellings. The 32-bit width in this exercise belongs to Umicom C's checked profile. Other C implementations choose their supported `int` representation. [WG14 N3220, section 6.7.3.1](https://www.open-std.org/jtc1/sc22/wg14/www/docs/n3220.pdf)

This lesson covers initialized integer locals inside a block. The tests also check that the profile refuses repeated specifiers such as `signed signed` and forms such as `signed long` or `unsigned int`. Broader C type rules are explained in the language reference.

## Check the second name

The compiler checks the source before it starts the interpreter. The following separate test asks for `b++`, which means increase `b` by one. The condition `0` would skip that block during execution. The source still has to pass the read-only check.

~~~c
int main(void){
int signed const a=1,b=2;
if(0){b++;}
return a;}
~~~

The fixture checks that the compiler reports a `read-only` diagnostic at line 3, column 7, where the `b` update starts. It also checks that the reported instruction count is zero. Trace both names back to the same declaration to see why `const` applies to `b`.

## Practise with the Umicom C tool

1. In a terminal at the Umicom C repository root, open `examples/signed_local_specifiers.uc` in Umicom Studio or a text editor. If you are working from the offline lesson, you can save the first example as `signed_local_specifiers.uc` and use that filename in the commands instead.
2. Run `umicom-c check examples/signed_local_specifiers.uc` with the current compiler on your path. Then run `umicom-c interpret examples/signed_local_specifiers.uc`. Expect `Result: 42`. The declaration list is one reached source statement, even though it creates two locals.
3. In a practice copy, add `high++;` before the return and run `umicom-c check` on that copy. Find the `read-only` diagnostic at the update. Restore the copy and replace `signed const int` with `const int`. The two boxes and their sum stay the same.
4. For a paper-only extension, replace the type words with plain `int` and keep `high++;` in the practice copy. Predict the result and explain why. The answer is 43 because `high` can now change from 45 to 46.

The compiler fixtures compare the operations and results of the equivalent spellings and check the refusal above. The shipped example returned 42 as a native program in the focused checks. The interpreter command in this exercise presents 42 as the program's result.

[Course contents](index.md) · [Previous lesson · Separate admission checks from source steps](119-separate-admission-checks-from-source-steps.md) · [Parse initialized declaration lists](90-parse-initialized-declaration-lists.md) · [Resolve a fixed name in its block](117-resolve-a-fixed-name-in-its-block.md) · [HTML edition](../../../courses/building-a-compiler-in-c/lessons/120-read-equivalent-signed-local-types.html)

[Next lesson · Keep the last accepted script value](121-keep-the-last-accepted-script-value.md)
