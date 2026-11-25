<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/123-measure-a-boolean-literal-without-reading-its-value.md

PURPOSE:
Measure a Boolean literal without reading its value

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Measure a Boolean literal without reading its value

Two labels on the same model of light switch can read “on” and “off.” The labels describe different states, and the switches still have the same dimensions. In C23, `true` and `false` are constants of the same type, `bool`. Their values are `1` and `0`. A `sizeof` query asks how many bytes their type occupies. The checked Umicom C profile uses one byte for that type. [WG14 N3220, sections 6.4.4.6 and 6.5.4.4](https://www9.open-std.org/JTC1/SC22/WG14/www/docs/n3220.pdf)

## Ask for the size in two ways

Here is the complete example used by the compiler regression. An assertion asks the compiler to check a fact before the program runs. The named constant `WIDTH` records the size of `false` for use in source.

~~~c
static_assert(sizeof(true) == sizeof(bool));
constexpr int WIDTH = sizeof false;
int main(void) { return 40 + sizeof true + sizeof(false); }
~~~

| Source | Value or number of bytes |
| --- | --- |
| `true` | Value `1` |
| `false` | Value `0` |
| `sizeof true` or `sizeof(false)` | `1` byte each |
| `sizeof(17)` or `sizeof('A')` | `4` bytes each in this profile |

The parentheses in `sizeof(false)` surround one literal. The spelling `sizeof(bool)` surrounds a type name. Write the type name with parentheses. The compiler puts the numeric size into the program directly.

~~~text
Recognize true as a Boolean constant
Look up the size of its source type and use 1
Recognize false as a Boolean constant
Look up the same source type size and use 1
Return 40 + 1 + 1
~~~

## Predict what a change will do

1. Work out the sum on paper. To try it with a build that includes this feature, save the program as `literal-size.c` and run `umicom-c interpret literal-size.c`. Expect `Result: 42`.
2. In a copy, change `sizeof(false)` to `sizeof(true)`. Predict `42` again because the type stays `bool`. Then change it to plain `false`. This time you add the literal’s value and expect `41`.
3. In another copy, change `sizeof(false)` to `sizeof(false + 1)`. Run `umicom-c interpret literal-size.c --check-only` on that copy. This checked profile still refuses a compound expression in this position. Restore the single literal and repeat the check.

Older Umicom C builds accepted `true` and `false` in ordinary arithmetic but refused these size queries. The earlier compiler also passed the ordinary size check. If the complete example is refused, check that you are invoking a build with Boolean literal sizing. `alignof(bool)` remains a type query in this profile. `alignof(true)` is still refused. The separate `script` command keeps its previous rules, so it accepts `return sizeof(17);` and refuses `return sizeof(true);`.

To follow the same distinction in Umicom C’s API, start with `docs/language.md` in the compiler checkout. `include/umicom_c/umicom_c.h` describes `umc_compile` and `umc_execute`. `include/umicom_c/interpreter.h` describes the source-step API used to run the same example.

[Course contents](index.md) · [Previous lesson · Store a true-or-false value in a local](122-store-a-true-or-false-value-in-a-local.md) · [Count bytes from an admitted type](99-count-bytes-from-an-admitted-type.md) · [Lower Boolean words without changing the VM](93-lower-boolean-words-without-changing-the-vm.md) · [Next lesson · Store a value in an unsigned byte](124-store-a-value-in-an-unsigned-byte.md) · [HTML edition](../../../courses/building-a-compiler-in-c/lessons/123-measure-a-boolean-literal-without-reading-its-value.html)
