<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/117-resolve-a-fixed-name-in-its-block.md

PURPOSE:
Resolve a fixed name in its block

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Resolve a fixed name in its block

In lesson 98 you named a fixed number before the entry function. The supported Umicom C profile also accepts `constexpr int` inside a block, a group of statements between braces. Choose a block when a fixed number belongs to that part of a calculation.

## Give each calculation its own name

Trace the two blocks below as parts of a practice stock count. The saved compiler fixture uses the same declarations and additions.

~~~c
int main(void) {
    int sum = 0;
    if (1) {
        // The first part is a fixed number for this block.
        constexpr int PART = 20;
        sum += PART;
    }
    {
        // The earlier PART is out of scope, so this block can reuse the name.
        constexpr int PART = 22;
        sum += PART;
    }
    return sum;
}
~~~

1. Draw a box for each pair of inner braces. Put `PART = 20` in the first and `PART = 22` in the second. Each box says where that name is available.
2. Start the running `sum` at zero. In the first box the addition makes it 20. In the second box the addition makes it 42. The return reads `sum` from the outer block.
3. Change the return to `return PART;` on paper. The lookup is refused because both `PART` declarations finished their scope. To use a fixed number after a block, declare it in a scope that includes that later use.

The `constexpr int` initializer is checked while the compiler prepares the source. The additions to `sum` happen during execution. In this profile, the fixed name has no mutable interpreter slot. The compiler can use its integer value directly where the name is allowed.

## Read the name that is visible at each line

Here an earlier source assertion reads a fixed file-scope value. The declaration inside `main` then introduces an ordinary local with the same spelling. Use the three marked lines to follow the lookup.

~~~c
constexpr int VALUE = 1;

int main(void) {
    static_assert(VALUE == 1);
    int VALUE = 42;
    return VALUE;
}
~~~

| Line you are reading | What `VALUE` means here |
| --- | --- |
| `static_assert(VALUE == 1);` | The earlier file-scope constant, so the assertion passes. |
| `int VALUE = 42;` | This declaration introduces an ordinary local. |
| `return VALUE;` | The ordinary local, so the result is 42. |

Now insert `constexpr int COPY = VALUE;` after `int VALUE = 42;`. Predict whether `COPY` can use the file-scope `VALUE`. The compiler finds the visible ordinary local first, and the fixed-value initializer is refused. The earlier file-level value stays hidden at that line. Insert the new declaration before the local instead and `COPY` can hold 1.

Use this distinction when reading a fixed setting and an adjustable count in an Umicom Studio source example. Mark the braces, then identify the visible declaration at the line reading the name. The checked profile admits a single signed integer initializer per `constexpr int` declaration. The full language defines additional declaration forms. [C23 object definitions with `constexpr`](https://open-std.org/jtc1/sc22/wg14/www/docs/n3018.htm)

[Course contents](index.md) · [Previous lesson · Read the instruction budget at a pause](116-read-the-instruction-budget-at-a-pause.md) · [Next lesson · Number enumeration members inside a block](118-number-enumeration-members-inside-a-block.md) · [Name values before the entry](98-name-values-before-the-entry.md) · [Parse standalone blocks with one scope owner](83-parse-standalone-blocks-with-one-scope-owner.md) · [HTML edition](../../../courses/building-a-compiler-in-c/lessons/117-resolve-a-fixed-name-in-its-block.html)
