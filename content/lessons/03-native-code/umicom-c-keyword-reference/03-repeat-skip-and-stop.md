<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/umicom-c-keyword-reference/03-repeat-skip-and-stop.md

PURPOSE:
Trace for, continue and break over whole-number indexes.

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

# Repeat, skip and stop a counted loop

[Course contents](index.md) · [Previous · Choose with if, else, true, and false](02-choose-with-if-and-literals.md) · [Next · Read the checked input entry and its limits](04-call-the-checked-input-profile.md) · [Browser edition](../../../courses/umicom-c-keyword-reference/lessons/03-repeat-skip-and-stop.html)

Trace for, continue and break over whole-number indexes.

## Read a counted loop

```c
int main(void)
{
    int total = 0;
    for (int index = 1; index < 6; ++index) {
        if (index == 2) {
            continue;
        }
        if (index == 5) {
            break;
        }
        total += index;
    }
    return total;
}
```

- `for` starts the supported counted form. The ascending form uses an integer start, a strict less-than bound, and a prefix increment of the same name, as shown.
- `continue` advances the innermost supported loop to the next pass.
- `break` exits the innermost supported loop. At position 5, the addition is skipped and iteration ends.
- These word spellings are recognised in their statement context. In this example, the brace block contains the repeated work.

## Trace it with a pencil

```text
START total at 0
FOR each index from 1 up to, but excluding, 6
    SKIP index 2
    STOP at index 5
    ADD index to total
SHOW total
```

Save the example as `count-and-stop.uc`. If your supplied Umicom C build supports this counted profile, the selected values 1, 3 and 4 produce 8. Check the compiler version if a build refuses the loop. C23 and C++ allow wider condition and update expressions in the general for statement.

## Apply it to Studio

Write a test record with the expected three included positions. A final total alone would not prove that the right rows were included.

## Continue in another course

- [Programming across languages](../../../courses/programming-across-languages/index.html)
- [C23 keyword reference](../../../courses/c23-keyword-reference/index.html)
- [Native statement calculations](../../../courses/native-statement-calculations/index.html)
- [Building a compiler in C](../../../courses/building-a-compiler-in-c/index.html)
- [Published Umicom C language guide](https://github.com/umicom-foundation/umicom-c/blob/main/docs/language.md)

[Course contents](index.md) · [Previous · Choose with if, else, true, and false](02-choose-with-if-and-literals.md) · [Next · Read the checked input entry and its limits](04-call-the-checked-input-profile.md) · [Browser edition](../../../courses/umicom-c-keyword-reference/lessons/03-repeat-skip-and-stop.html)
