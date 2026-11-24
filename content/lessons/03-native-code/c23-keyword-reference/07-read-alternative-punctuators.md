<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/c23-keyword-reference/07-read-alternative-punctuators.md

PURPOSE:
  Teach every alternate punctuation token in C using short independent examples.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Read alternative C punctuators

[Previous lesson](06-read-optional-and-older-forms.md) · [Course contents](index.md) · [HTML edition](../../../courses/c23-keyword-reference/lessons/07-read-alternative-punctuators.html)

A compiler reads your program in pieces called **tokens**. A punctuator is a token such as an opening brace or a bracket. C has alternate spellings for six punctuators. Some documentation calls them digraphs. Each spelling must stay together without a space.

| Alternate | Usual | Where the example uses it |
| --- | --- | --- |
| `<%` | `{` | Start a block or a list of initial values. |
| `%>` | `}` | End the block or list. |
| `<:` | `[` | Begin an array size or index. |
| `:>` | `]` | End the size or index. |
| `%:` | `#` | Start a preprocessor directive or turn a macro argument into text. |
| `%:%:` | `##` | Join two tokens inside a macro. |

## Trace a short block

Save this first example as `brace-blocks.c`. Follow the variable named `checks` on paper.

~~~c
int main(void)
<%
    int checks = 4;
    if (checks < 5)
    <%
        checks = checks + 3;
    %>
    return checks;
%>
~~~

Copy these steps into a notebook.

~~~text
Set checks to 4.
If checks is less than 5:
    Add 3 to checks.
Return checks.
~~~

The final value is 7. In the source, the plain `<` in the condition compares numbers. The following two characters `<%` elsewhere in the source open a block. The next character helps the compiler identify the token.

If a supported Umicom C interpreter is already on your path, use `umicom-c interpret brace-blocks.c`. The program should return 7. To practise using only the hosted C23 compiler, keep this example and the following ones in separate files, then run `gcc -std=c23 -Werror -fsyntax-only brace-blocks.c` or the same command with `clang`. A successful syntax check exits with status zero. It creates no executable.

## Read an array with alternate brackets

Save this example as `three-values.c`.

~~~c
int samples<:3:> = <% 3, 4, 5 %>;
static_assert(sizeof samples / sizeof samples<:0:> == 3U);
~~~

The declaration holds three integers. The first is numbered zero. The assertion divides the full array's size by the size of its first element and requires the answer to be three. Run the hosted C23 syntax check for this file, then try changing the asserted count to four. The assertion should fail at compile time. Restore three before the next step.

## Follow the preprocessor

The **preprocessor** works on tokens before the compiler checks declarations and statements. A macro is a named replacement rule. The first macro below puts two tokens together to form one name. The second keeps the argument's spelling in a quoted string.

Save the example as `what-the-preprocessor-sees.c`.

~~~c
%:define JOIN_NAMES(left, right) left %:%: right
%:define SPELLING(token) %:token
enum { sample_3 = 11 };

static_assert(JOIN_NAMES(sample_, 3) == 11);
static_assert(sizeof SPELLING(<:) == 3U);
static_assert(sizeof SPELLING([) == 2U);
~~~

Use `gcc -std=c23 -E -P what-the-preprocessor-sees.c` or replace `gcc` with `clang`. Look for `sample_3` in the first assertion. The next two assertions see `"<:"` and `"["`. Each string also contains a terminating zero, so their sizes are three and two. The two spellings act like the same bracket during parsing, and the preprocessor can show which spelling you entered.

## Diagnose a split token

Save this example separately as `separated-punctuators.c`. A hosted C23 compiler should refuse it.

~~~c
int main(void)
< %
    return 7;
% >
~~~

The spaces split the block markers into separate tokens. Remove the spaces from the marked pairs, then run the syntax check again. If a diagnostic points to the first symbol, compare the spelling with `brace-blocks.c` one character at a time.

The direct Umicom C source interpreter uses the brace pair in this lesson. Use a hosted C23 compiler for the array and preprocessing exercises. In Umicom Studio IDE, these examples also make a useful lexer exercise. A lexer recognises the token and tracks where the original characters appeared. A diagnostic can then highlight the correct source spelling.

[WG14 working draft N3220, section 6.4.6](https://www.open-std.org/jtc1/sc22/wg14/www/docs/n3220.pdf#page=82)

[Continue with the C++20 alternate token comparison](../cpp20-keyword-reference/08-alternative-operator-tokens.md)
