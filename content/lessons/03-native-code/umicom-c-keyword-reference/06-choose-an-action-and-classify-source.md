<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/umicom-c-keyword-reference/06-choose-an-action-and-classify-source.md

PURPOSE:
Choose an action and classify source

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Choose an action and classify source

## Make a choice, then decide what to do

A condition asks a question with two possible answers. In a practice version
of Umicom Bank, imagine that a reviewer flags entries numbered 3 and higher.
The question is whether the entry number is at least 3. The action might
increase a counter or display a message. Use each language's own words for
the action.

| Language | Start a choice | Display the word Review |
| --- | --- | --- |
| Hosted C23 | `if (entry >= 3)` | `puts("Review");` from `<stdio.h>` |
| D | `if (entry >= 3)` | `writeln("Review");` from `std.stdio` |
| Java | `if (entry >= 3)` | `System.out.println("Review");` |
| FreeBASIC | `If entry >= 3 Then` | `Print "Review"` |
| Python | `if entry >= 3:` | `print("Review")` on an indented line |
| PHP | `if ($entry >= 3)` | `echo "Review";` |

These are fragments for reading. A complete example needs to define the
entry and place the action in the body of the choice. PHP's `echo` writes
the given text without adding a line break. Printing or displaying text
uses an output operation. Returning a number gives a result to a caller.

## Count four entries in Umicom C

Write down 1, 2, 3 and 4. Start this exercise at 40. Add one for each entry
that meets the condition. For example, entry 2 leaves the total at 40.
Entry 3 increases it to 41. In everyday pseudocode the plan reads like this.

~~~text
SET review total to 40
FOR each entry from 1 through 4
    IF entry is at least 3
        ADD 1 to review total
RETURN review total
~~~

The pseudocode describes the steps on paper. Save the following program as
`review-entries.uc` in a fresh directory for the practical exercise.

~~~c
int main(void) {
    int review_total = 40;
    /* The stop value is exclusive. This loop visits entries 1 through 4. */
    for (int entry = 1; entry < 5; ++entry) {
        if (entry >= 3) {
            ++review_total;
        }
    }
    return review_total;
}
~~~

1. Go to that directory in a terminal. Use an Umicom C build that lists
   `interpret`, `compile`, `exec` and `regions` in `umicom-c --help`.
2. Run the first command below. Look for `Result: 42` in the trace. The
   command reports the number returned by the program.
3. Run the next two commands. The compiler creates `review-entries.umcb`,
   a file of instructions for the Umicom bytecode runner. Use `exec` for
   this file to see the result 42 again.
4. Change the stop condition to `entry < 4` and run `interpret` again.
   Predict which entries count and check your prediction against 41.
   Restore `entry < 5` before continuing.

~~~text
umicom-c interpret review-entries.uc
umicom-c compile review-entries.uc review-entries.umcb
umicom-c exec review-entries.umcb
~~~

If the result differs, trace the entry values first. The less-than sign makes
the stop value exclusive. The expression `++entry` adds one after each visit,
even when the condition inside the loop is false. If the terminal cannot find
`umicom-c`, use the full path to your tool and keep the working directory
where you saved the exercise.

## Print the result and return it

Keep the file name `review-entries.uc`. In the same program, add these
two statements just above `return review_total;`. Keep that return
statement so the caller still receives the result.

~~~c
    /* Display the checked total and a Boolean before returning. */
    print(review_total);
    print(true);
~~~

1. Run `umicom-c run review-entries.uc`. The program writes the two
   lines `42` and `true`. The command then reports `Result: 42`.
2. Run `umicom-c interpret review-entries.uc --jsonl`. Find the two
   records whose `event` is `print`. Their `valueType` fields are
   `integer` and `boolean`. Their `value` fields hold the same two
   results. A reader can use those types without guessing from the text.
3. Run the original `compile` and `exec` commands again. Expect the
   same two displayed lines and final result from the new bytecode.

`print` displays a value at that point in the program. `return` completes
the function and passes the result back. This exercise uses integer and
Boolean values. Keep the `.uc` extension when using this output feature.

## Find seven tagged source regions

Save this second sample as `review-regions.umc`. A tag starts with `<?`,
an exact lowercase language name and whitespace. Close each region with
`?>`. A region describes the language and byte span of one piece of text.

~~~text
<?umicom return 42; ?>
<?c23 puts("Review"); ?>
<?d writeln("Review"); ?>
<?java System.out.println("Review"); ?>
<?basic Print "Review" ?>
<?python print("Review") ?>
<?php echo "Review"; ?>
~~~

1. Run `umicom-c regions review-regions.umc`. The first three tagged languages
   are `umicom`, `c23` and `d`. Next come `java`, `basic`, `python`
   and `php`. Line breaks between tags appear as separate `umicom` rows.
2. Look at the `offset` and `bytes` columns. These values locate the text in
   the original file for a tool such as Umicom Studio IDE. Line endings
   affect the number of bytes in the rows between tags.
3. Temporarily remove the last `?>` and run the same command. Expect a
   diagnostic about the missing closing delimiter and an empty region list.
   Restore the delimiter.

<!-- Retain the earlier design marker for review. The native .uc exercise
above now has checked scalar output. The .uf manifest is still a proposal.
The command only classifies source. To check syntax and execute a complete
program, save it in a separate source file and use that language's compiler
or interpreter. A checked Umicom C display operation and a shared `.uf`
project manifest are design ideas for later lessons.
-->
The regions command classifies source spans. Save complete programs in
their own language files and use their compiler or interpreter to check
and execute them. A shared `.uf` project manifest remains a design idea.

[Course contents](index.md) · [Previous lesson](05-guard-calculations-with-and-or.md) · [HTML edition](../../../courses/umicom-c-keyword-reference/lessons/06-choose-an-action-and-classify-source.html) · [Programming across languages](../../../courses/programming-across-languages/index.html)

[Next lesson](07-compare-negative-division.md)
