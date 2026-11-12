<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/weight-management-framework/02-convert-kilograms-without-rounding.md

PURPOSE:
Convert kilogram text into exact grams

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Convert kilogram text into exact grams

## Before you begin
Read the observation contract and understand a byte span: a pointer plus an explicit length. Use synthetic values such as 80.250. No personal measurements are required.

## Trace the actual parser
The shared parser accepts ASCII digits, an optional dot and up to three fractional digits. It rejects a comma, exponent, sign, suffix, spaces and embedded NUL bytes. That narrow contract is deliberate: a localized interface must explicitly translate its own input rules before calling the canonical service.

~~~c
uint32_t grams = 19U;
UmiStatus status = umi_weight_log_parse_kilograms("80.250", 6U, &grams);
if (status == UMI_STATUS_OK) {
    /* grams is 80250U. */
}
~~~

1. Accumulate the whole part, 80.
2. Accumulate the fraction, 250.
3. Compute 80 * 1000 + 250 using bounded unsigned integer arithmetic.
4. Publish the result only after syntax and capacity admission succeed.

For 80.2, the parser scales the fraction to 200 grams. It does not approximate a binary floating-point value. For 80.2501, it refuses the extra precision rather than rounding without consent.

## Expected result
The example returns OK and replaces 19 with 80250. A refused parse leaves 19 intact. The input length excludes any terminator; a buffer can contain additional bytes after the admitted span without making them part of the input.

## Exercise
Trace 0.001, 80, 80.25, 80,25 and 8e1. Predict each status and output. Then read the decimal, syntax and range groups in tests/healthcare/test_weight_log.c. These tests include a non-terminated span and embedded NUL, so they check more than ordinary string input.

## Recovery
A PARSE_ERROR means the text did not match this grammar. INVALID_ARGUMENT covers required null pointers or a numeric value outside the positive encoding range. Do not show a previously valid number as if the latest invalid entry was accepted. Keep the visible draft and ask the user to correct it.

The service's maximum is 1,000,000,000 grams. That value prevents a storage overflow; it is not a suggested weight or a health judgement. Display units explicitly whenever a client converts the canonical integer for presentation.


[Course contents](index.md) · [Previous lesson](01-define-the-observation-contract.md) · [Next lesson](03-edit-and-read-a-native-form.md)
