<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/101-read-adjacent-assertion-messages.md

PURPOSE:
Read adjacent assertion messages

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Read adjacent assertion messages

An assertion is a check that a stated condition holds. A **static assertion** checks a fixed condition while the compiler prepares the program. If the condition fails, the compiler can show the message attached to it and report the source location.

## Follow the quotation marks

Think of `"The record "` and `"contains 42 fields"` as two parts of one sentence. In hosted C23, adjacent quoted string fragments are combined during translation. A comment or line break between the closing quote and the next opening quote can make a long message easier to read. The space after `record` is inside the first fragment so it becomes part of the sentence.

The checked Umicom C profile accepts ordinary ASCII quoted fragments in a static assertion. It preserves their source spelling for diagnosis. The quotes still help you see which fragments were written. This lesson uses assertion messages and does not require an ordinary string variable or a string-processing runtime.

~~~c
int main(void)
{
    /* The compiler checks the fixed condition before preparing execution. */
    static_assert(6 * 7 == 42, "The record " /* Keep the phrase readable. */
                              "contains 42 fields");
    return 42;
}
~~~

## Read a correct source and a refusal

1. Open `labs/native/compiler-source-boundaries/assertion_message.c` in the Bits2Banking checkout. Find the fixed calculation and the two quoted fragments.
2. Run `umicom-c interpret labs/native/compiler-source-boundaries/assertion_message.c`. Expect `Result: 42` from the program’s return statement.
3. Join the two fragments into `"The record contains 42 fields"` in a practice copy. Repeat the run. On this example the same two execution instructions produce 42. The message belongs to preparation.
4. In another copy, compare `6 * 7` with 41. Use `umicom-c interpret` on that copy with `--check-only`. Expect the assertion diagnostic to begin at the first opening quote. Restore the comparison before you move on.

## Keep the exact place where spelling failed

The component that recognizes source tokens is the **lexer**. It first checks each quoted fragment’s end and valid characters. After a fragment, it may skip permitted whitespace and comments and look for another opening quote. It leaves the next ordinary token for the parser. A malformed later fragment should identify that later location. A well-formed message attached to a false condition can identify the message’s start.

~~~text
READ one complete quoted fragment
LOOK across permitted whitespace and comments
WHILE there is another opening quote
    READ and check the next fragment
KEEP the original range for a diagnostic
~~~

If no space appears between two words, check the quoted text itself. Whitespace between the two closing and opening quotes does not supply a character to the resulting sentence in hosted C.

[C23 working draft, string literals and translation](https://www.open-std.org/jtc1/sc22/wg14/www/docs/n3220.pdf#page=80)

[Course contents](index.md) · [Previous: Align the fields in a record](100-align-record-fields.md) · [Next: Require a complete debugger command](102-require-a-complete-debugger-command.md) · [HTML edition](../../../courses/building-a-compiler-in-c/lessons/101-read-adjacent-assertion-messages.html)
