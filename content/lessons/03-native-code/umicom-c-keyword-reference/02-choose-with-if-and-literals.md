<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/umicom-c-keyword-reference/02-choose-with-if-and-literals.md

PURPOSE:
Trace an imaginary posted flag through two checked integer branches.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original learning material. Linked references retain their own terms.
-->

<picture>
  <source srcset="../../../assets/branding/umicom-wordmark-on-dark.svg" media="(prefers-color-scheme: dark)">
  <img src="../../../assets/branding/umicom-wordmark.svg" width="220" alt="Umicom">
</picture>

# Choose with if, else, true, and false

[Course contents](index.md) · [Previous · Enter the program and return a whole number](01-enter-return-and-name-integers.md) · [Next · Repeat, skip and stop a counted loop](03-repeat-skip-and-stop.md) · [Browser edition](../../../courses/umicom-c-keyword-reference/lessons/02-choose-with-if-and-literals.html)

Trace an imaginary posted flag through two checked integer branches.

## Read an if statement

```c
int main(void)
{
    int posted = true;
    int total = 0;
    if (posted == false) {
        total = 10;
    } else {
        total = 250;
    }
    return total;
}
```

- `true` and `false` are translated by this profile to 1 and 0. This grammar does not introduce a local `bool` type.
- `if` chooses its braced branch when the condition is nonzero.
- `else` provides the fallback branch when the condition is zero.
- `==` compares two values. A single `=` sets a value. The exact spelling `if` has a special role. The longer spelling `if_value` is available as an identifier.

## Trace and verify

```text
SET posted TO true
IF posted EQUALS false
    SET total TO 10
ELSE
    SET total TO 250
SHOW total
```

Save the example as `choose-a-total.uc`. It returns 250. Change the first value to false and it returns 10. C23, Go and Python all have ways to express true and false. Their type rules and Boolean spellings vary.

## Apply the same rule

In a practice Umicom Bank summary, specify separate checks for posted and pending rows. Reuse your paper trace to say what each branch should show.

## Continue in another course

- [Programming across languages](../../../courses/programming-across-languages/index.html)
- [C23 keyword reference](../../../courses/c23-keyword-reference/index.html)
- [Native statement calculations](../../../courses/native-statement-calculations/index.html)
- [Building a compiler in C](../../../courses/building-a-compiler-in-c/index.html)
- [Published Umicom C language guide](https://github.com/umicom-foundation/umicom-c/blob/main/docs/language.md)

[Course contents](index.md) · [Previous · Enter the program and return a whole number](01-enter-return-and-name-integers.md) · [Next · Repeat, skip and stop a counted loop](03-repeat-skip-and-stop.md) · [Browser edition](../../../courses/umicom-c-keyword-reference/lessons/02-choose-with-if-and-literals.html)
