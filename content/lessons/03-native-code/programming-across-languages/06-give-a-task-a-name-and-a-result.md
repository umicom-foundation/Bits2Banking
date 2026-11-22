<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/programming-across-languages/06-give-a-task-a-name-and-a-result.md

PURPOSE:
Separate a reusable calculation from how a screen displays it.

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

# Give a task a name and a result

[Course contents](index.md) · [Previous · Visit a list and skip a row](05-visit-a-list-and-skip-a-row.md) · [Next · Plan a first Umicom change](07-plan-a-first-umicom-change.md) · [Browser edition](../../../courses/programming-across-languages/lessons/06-give-a-task-a-name-and-a-result.html)

Separate a reusable calculation from how a screen displays it.

## Write a small function

A function gives a procedure a name. Its parameter is a named input. `return` gives back the result to the code that asked for it. The following examples double a count of envelopes.

```text
FUNCTION double count (count)
    RETURN count + count
END FUNCTION
SHOW double count (3)
```

```c
int double_count(int count)
{
    return count + count;
}
```

```python
def double_count(count):
    return count + count
```

```go
func doubleCount(count int) int {
    return count + count
}
```

C++, Java and D use the `return` keyword as well. Java usually declares this beginner example as a `static` method inside a class, which is a named container for methods and data.

## Specify the result first

Ask the function to double 3, 0 and 5. The expected results are 6, 0 and 10. The small function assumes a modest whole number. A real implementation checks input limits before doubling.

Put reusable calculations behind a Framework function. A product can then display the result or show an error. A focused test can call the function without opening the product window.

## Continue in another course

- [Computing from the Beginning](../../../courses/computing-from-the-beginning/index.html)
- [C23 keyword reference](../../../courses/c23-keyword-reference/index.html)
- [Python keyword reference](../../../courses/python-keyword-reference/index.html)
- [Go keyword reference](../../../courses/go-keyword-reference/index.html)
- [Go statement tools](../../../courses/go-statement-tools/index.html)
- [Umicom C and C23 statement calculations](../../../courses/native-statement-calculations/index.html)

[Course contents](index.md) · [Previous · Visit a list and skip a row](05-visit-a-list-and-skip-a-row.md) · [Next · Plan a first Umicom change](07-plan-a-first-umicom-change.md) · [Browser edition](../../../courses/programming-across-languages/lessons/06-give-a-task-a-name-and-a-result.html)
