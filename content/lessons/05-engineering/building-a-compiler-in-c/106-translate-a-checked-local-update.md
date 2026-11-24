<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/106-translate-a-checked-local-update.md

PURPOSE:
Translate a checked local update

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Translate a checked local update

A **local variable** belongs to a function. It can hold a running count while the function works. In this exercise a workshop has 40 labels already printed. It prints two more and returns the updated count.

## Follow one value through three steps

| Step | Action | Value of total |
| --- | --- | --- |
| 1 | Create the local and initialize it | 40 |
| 2 | Add two and save the result back to the same local | 42 |
| 3 | Return the updated value to the caller | 42 |

~~~text
SET total TO 40
ADD 2 TO total
RETURN total
~~~

The operator <code>+=</code> is called a **compound assignment**. For this ordinary local, <code>total += 2</code> has the same value effect as <code>total = total + 2</code>. Write the two characters together. The shared checked profile starts with a declaration using plain <code>=</code>.

~~~c
int answer() { int total = 40; total += 2; return total; }
~~~

The Java method goes inside the class. Compare its two assignment spellings with the C23 function.

~~~java
public final class UmicomAnswer {
    public static int answer() {
        int total = 40;
        total += 2;
        return total;
    }
}
~~~

## Translate and compare

1. Save the C23 example as <code>answer.c</code> in a new practice folder. Keep the Java listing in your notes so the translator can create a new file.
2. Run both translation commands using the current Umicom C tool. Open the two output files. Check that the declaration, update and return all appear in the original order.
3. Trace the value on paper. Then use the practice caller from the earlier lesson to check that the generated C and Java functions both return 42.

~~~powershell
umicom-c translate c-to-java answer.c UmicomAnswer.java
umicom-c translate java-to-c UmicomAnswer.java answer-roundtrip.c
~~~

## Diagnose a refused update

Make a separate input where <code>total</code> starts at 2147483647 and the program tries <code>total += 1</code>. Ask for a new output name. The checked arithmetic reports a range failure and leaves the earlier files available. Try <code>total /= 0</code> with a valid starting value. This also gives a diagnostic. Restore the original exercise and translate to a new filename.

The shared profile allows <code>+=</code>, <code>-=</code>, <code>*=</code>, <code>/=</code>, <code>%=</code>, <code>&amp;=</code>, <code>^=</code> and <code>|=</code> for initialized integer locals. These operations keep both languages in the same checked range. Use the earlier signed mask exercise to predict how a bitwise update such as <code>total &amp;= 63</code> changes a count.

An application such as Studio can call the same translator to obtain the generated source and its diagnostics. When it shows a refusal, the learner should still be able to open the earlier valid result.

[C23 assignment rules](https://www.open-std.org/jtc1/sc22/wg14/www/docs/n3096.pdf) · [Java compound assignment rules](https://docs.oracle.com/javase/specs/jls/se25/html/jls-15.html#jls-15.26.2)

[Course contents](index.md) · [Previous lesson · Translate hexadecimal and binary](105-translate-hexadecimal-and-binary.md) · [Related lesson · Translate whitespace that both languages admit](103-translate-whitespace-that-both-languages-admit.md) · [Earlier lesson · Execute instructions with checked arithmetic](04-checked-execution.md) · [HTML edition](../../../courses/building-a-compiler-in-c/lessons/106-translate-a-checked-local-update.html)

[Next lesson · Count reached source statements](107-count-reached-source-statements.md)
