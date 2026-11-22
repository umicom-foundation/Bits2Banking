<!--
Umicom Bits2Banking
File: content/lessons/04-web/bootstrap-native-statements/03-display-native-validation-feedback.md

PURPOSE:
Read Bootstrap form feedback with explicit text and trace a FreeBASIC version of a checked native addition.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original learning material. Linked references retain their own terms.
-->

<picture>
  <source srcset="../../../assets/branding/umicom-wordmark-on-dark.svg" media="(prefers-color-scheme: dark)">
  <img src="../../../assets/branding/umicom-wordmark.svg" width="220" alt="Umicom Foundation">
</picture>

# Display native validation feedback

[Course contents](index.md) · [Previous · Export the page from C23](02-export-the-page-from-c.md) · [Browser edition](../../../courses/bootstrap-native-statements/lessons/03-display-native-validation-feedback.html)

Read Bootstrap form feedback with explicit text and trace a FreeBASIC version of a checked native addition.

## Start with the amount and its unit

A fictional correction is entered as whole cents. The text 250.50 is rejected for this input because cents must be a whole number. The form should tell the reader which field needs attention and how to correct it. This source-reading fragment shows the invalid state after a native parser refused the input.

```html
<label class="form-label" for="correction">Correction in whole cents</label>
<input class="form-control is-invalid" id="correction" name="correction"
       value="250.50" aria-invalid="true" aria-describedby="correction-error">
<p class="invalid-feedback" id="correction-error">
  Enter a whole number of cents, such as -250 or 250.
</p>
```

Bootstrap changes how the validation state looks. The label and described error carry the meaning, including with styles removed. A signed amount needs a keyboard that can enter a minus sign.

## Compare the native arithmetic in FreeBASIC

This language comparison begins after the text input has already been parsed to a signed 32-bit integer. A BYREF output is one that the function may update in the caller. Keep that output untouched if the checked addition fails.

```freebasic
FUNCTION TryAddCents(BYVAL leftCents AS LONG, BYVAL rightCents AS LONG, BYREF result AS LONG) AS INTEGER
    ' Use a 64-bit temporary so the bounds check can observe the signed sum.
    DIM AS LONGINT candidate = CLNGINT(leftCents) + rightCents
    IF candidate < CLNGINT(-2147483647) - 1 OR candidate > 2147483647 THEN RETURN 0
    result = CLNG(candidate)
    RETURN 1
END FUNCTION
```

1. Trace 2600 plus −850. The FreeBASIC result is 1750 with success status 1.
2. Trace 2147483647 plus 1 with the caller’s result previously set to 42. The function returns 0 and leaves 42.
3. State the difference between a decimal-text rejection and a signed-range rejection. The form can show a useful message for either while leaving the last admitted value intact.

In an Umicom Automated Testing exercise, write checks for label and error association, keyboard reading order, signed cents and overflow preservation. Use the C23 rule in the reusable native layer. Apply Bootstrap only where a web interface needs visible feedback.

- [Bootstrap 5.3 form validation styles](https://getbootstrap.com/docs/5.3/forms/validation/)
- [FreeBASIC whole-number conversion](https://www.freebasic.net/wiki/KeyPgClngint)
- [Native Statement Calculations](../../../courses/native-statement-calculations/index.html)
- [Applied native courses](../../../start/applied-native-courses.md)

## Follow another path

- [Learning Bootstrap](../../../courses/learning-bootstrap/index.html)
- [Native Statement Calculations](../../../courses/native-statement-calculations/index.html)
- [React and Native Statement Data](../../../courses/react-native-statements/index.html)
- [Native statement lab on Umicom WebServer](../../../umicom/native-statement-web-lab.md)
- [Applied native courses](../../../start/applied-native-courses.md)

[Course contents](index.md) · [Previous · Export the page from C23](02-export-the-page-from-c.md) · [Browser edition](../../../courses/bootstrap-native-statements/lessons/03-display-native-validation-feedback.html)
