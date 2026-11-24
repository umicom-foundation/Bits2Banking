<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/109-translate-an-initialized-local-between-c-and-d.md

PURPOSE:
Translate an initialized local between C and D

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Translate an initialized local between C and D

A local variable holds a value while a function runs. This exercise adds
an initialized integer and a checked update to the earlier example. In
both programs, the computer starts at 32 and adds 10. Write down the
expected answer before translating.

~~~text
SET total TO 32
ADD 10 TO total
RETURN total
~~~

## Follow the same value through C and D

Save this as `with-local.c` in a fresh practice folder.

~~~c
int answer(void) {
    int total = 0x20;
    total += 0b1010;
    return total;
}
~~~

1. In PowerShell, run the two translations with the current Umicom C CLI.
   Choose fresh output names if a file already exists.
2. Check that the D output uses `int answer()` and keeps all three body
   statements. The C file regenerated from D uses `int answer(void)`.
3. Use the earlier C caller to check the regenerated function. Its value
   is 42, so the caller should exit with code 0.

~~~powershell
umicom-c translate c-to-d with-local.c with-local.d
umicom-c translate d-to-c with-local.d with-local-roundtrip.c
~~~

## Check a name before choosing it

Some words have a special meaning in one language. Rename `total` to
`alias` at all three places in another copy. Try translating it to a
fresh D file. Expect a syntax diagnostic from the translation and check
that a new output was not created. D reserves that word for declarations.

Choose `aliasCount` instead and try again. The longer name is a
complete, different word. The expected value remains 42. Repeat the C
caller check to verify it.

The exercise uses one function, initialized integer locals and checked
assignments. Keep the body free of comments during this C and D exercise.
An editor can show both outputs and surface the diagnostic before a
learner opens the generated file. [D declarations](https://dlang.org/spec/declaration.html#VariableDeclarations) · [D keywords](https://dlang.org/spec/lex.html#keywords)

[Course contents](index.md) · [Previous lesson · Translate one return between C and D](108-translate-one-return-between-c-and-d.md) · [Next lesson · Inspect paused integer slots](110-inspect-paused-integer-slots.md) · [Related lesson · Count reached source statements](107-count-reached-source-statements.md) · [HTML edition](../../../courses/building-a-compiler-in-c/lessons/109-translate-an-initialized-local-between-c-and-d.html) · [D keyword reference](../../03-native-code/d-keyword-reference/index.md)
