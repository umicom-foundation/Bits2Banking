<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/118-number-enumeration-members-inside-a-block.md

PURPOSE:
Number enumeration members inside a block

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Number enumeration members inside a block

Suppose a Studio IDE practice program uses three numbered check stages. The previous lesson gave one fixed value a name with `constexpr int`. An **enumeration** groups several named constants in one declaration. In this exercise the opening brace follows `enum` immediately. This form is called an **anonymous enumeration**. The member names describe the stages.

## 1. Fill in the numbers before the program runs

Read this program from top to bottom and write a number beside each member.

~~~c
constexpr int BASE=39;
int main(void) {
    enum { FIRST=BASE+1, SECOND, THIRD, };
    static_assert(THIRD == 42);
    return THIRD;
}
~~~

`BASE` is already visible when the compiler checks the block. The member `FIRST` gets 40 from its explicit calculation. With no value written for `SECOND` or `THIRD`, each takes the preceding member’s value plus one. The final comma is permitted. Your list should read 40, 41, 42. Lesson 98 uses the same numbering rule before the function. This example declares the member names inside the function body. [WG14 N3220, enumeration specifiers](https://www9.open-std.org/JTC1/SC22/WG14/www/docs/n3220.pdf)

The static assertion checks 42 during source admission, when the compiler decides whether it can prepare the program. Lesson 119 follows the first reached line and the two instructions the compiler prepares for this example.

## 2. Follow a name through two blocks

Draw a box around the function body and another for the smaller block inside it. Mark the lines where `FIRST` and `LAST` are available.

~~~c
int main(void) {
    enum { FIRST=40 };
    {
        // The inner group can use a constant from the enclosing block.
        enum { LAST=FIRST+2 };
        return LAST;
    }
    return 0;
}
~~~

`FIRST` is visible in the smaller box, so `LAST` receives 42 and the inner return can read it. Move that return to the outer block on paper, replacing `return 0;`. The inner braces close before the new return. That use of `LAST` is out of scope, so admission refuses it.

This Umicom C profile counts up to 32 visible enumeration members and `constexpr` names together. Try writing `constexpr int VALUE=42;` followed by `enum { VALUE };` in the same block. The second declaration is refused because the first name is still visible. The two declaration forms share the same space for names.

## 3. Stop when the next value exceeds the range

Replace the member list with `enum { LAST=2147483647, OVER };` and predict `OVER` on paper. It would be 2,147,483,648. The checked Umicom C profile stores these values as signed 32-bit integers, whose largest value is 2,147,483,647. The compiler refuses the declaration during source admission and reports an output instruction count of zero. A full C23 implementation can select a wider type under the enumeration rules. [WG14 N3220, enumeration specifiers](https://www9.open-std.org/JTC1/SC22/WG14/www/docs/n3220.pdf)

[Course contents](index.md) · [Previous lesson · Resolve a fixed name in its block](117-resolve-a-fixed-name-in-its-block.md) · [Next lesson · Separate admission checks from source steps](119-separate-admission-checks-from-source-steps.md) · [Name values before the entry](98-name-values-before-the-entry.md) · [Give branch locals a lexical scope](82-give-branch-locals-a-lexical-scope.md) · [HTML edition](../../../courses/building-a-compiler-in-c/lessons/118-number-enumeration-members-inside-a-block.html)
