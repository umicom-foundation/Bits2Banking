<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/126-keep-the-accepted-value-during-a-console-preview.md

PURPOSE:
Keep the accepted value during a console preview

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Keep the accepted value during a console preview

Imagine a classroom timer with an accepted setting and a trial setting. You want to try turning the flag off, then look at the accepted setting again. The Umicom C console gives a line beginning with `:preview ` a detached copy of the accepted session. A detached copy starts with the same values and can be changed separately.

## 1. Trace the accepted and trial values

Save the following four lines as `typed-preview.ucs`. The first declaration stores `1`, because `-7` is nonzero. The next two lines begin with the console directive `:preview`. Keep the space immediately after the directive.

~~~text
bool flag=-7;
:preview flag=0;
:preview return 40+flag+sizeof(bool);
return 40+flag+sizeof(bool);
~~~

~~~powershell
Get-Content -Raw -LiteralPath './typed-preview.ucs' | umicom-c script --typed --stdin
~~~

The corrected console check matched this exact output.

~~~text
ok
preview ok
preview 42
42
~~~

1. `ok` means the declaration was accepted. The live `flag` is `1`.
2. `preview ok` means the trial assignment succeeded. It set the copy to `0`. The accepted `flag` is still `1`.
3. The next preview starts from the accepted session again. It reads `1`, adds the one-byte size of `bool`, and displays `preview 42`.
4. The ordinary return also reads the accepted flag. Its result is `42`.

## 2. Model a preview on paper

~~~text
MAKE a copy of the accepted local values and their types
APPLY the preview line to that copy
SHOW the preview reply
DISCARD the copy
BEGIN the next line with the accepted session
~~~

## 3. Change what is accepted

For a paper exercise, change the second line to `flag=0;`. This time the assignment is submitted to the live session. Predict both final replies. The calculation becomes `40 + 0 + 1`, so the predicted final replies are `preview 41` and `41`. When writing a console test, keep both the preview reply and the later live reply. Together they show which value stayed in the session.

[Course contents](index.md) · [Previous lesson · Choose typed values in the C console](125-choose-typed-values-in-the-c-console.md) · [Next lesson · Submit a typed script as one block](127-submit-a-typed-script-as-one-block.md) · [Keep the last accepted script value](121-keep-the-last-accepted-script-value.md) · [HTML edition](../../../courses/building-a-compiler-in-c/lessons/126-keep-the-accepted-value-during-a-console-preview.html)
