<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/weight-management-framework/09-test-the-kilogram-boundary-with-synthetic-inputs.md

PURPOSE:
Test the kilogram boundary with synthetic inputs

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Test the kilogram boundary with synthetic inputs

Desktop, web and mobile clients should agree about the same observation. The first shared boundary is exact mass parsing. Using floating-point conversion independently in each client can introduce different rounding or syntax acceptance; the Framework contract instead returns integer grams.

## Before you begin

Read the earlier schema, exact-unit and complete-entry lessons first. Have the Framework weight_log.h header and examples/weight_log/main.c open beside this lesson. The code fragment assumes the existing C build environment and Framework target; it is not a standalone program. Use synthetic observations and retain parser status separately from output storage.

## Read the actual C interface

~~~c
uint32_t grams = 123U;
UmiStatus status = umi_weight_log_parse_kilograms("80.250", 6U, &grams);
/* On success grams is 80250. On refusal the previous output is retained. */
~~~

This fragment belongs inside a program including umicom/healthcare/weight_log.h and linked to the appropriate Framework target. It is a contract example, not an independently compiled application. The existing examples/weight_log/main.c shows full synthetic form construction and status checking.

## Predict refusal without changing output

Change the text to 80.250kg and pass its eight-byte length. The suffix is outside the grammar, so expect PARSE_ERROR and the old 123 value to remain. The retained number is not a newly parsed result: the caller must branch on status before using it.

Next test 0, an empty span, 80.2500, an embedded zero byte and a span without a trailing terminator. Zero is outside the nonzero value contract. Too many fractional digits and embedded zero bytes are syntax refusals. A valid borrowed span need not have a terminator because the explicit length defines what may be read.

## Separate units from presentation

The stored unit is mass.g. The displayed input uses kilograms. The conversion is exact within the declared capacity, with no rounding. A maximum encoding capacity is an implementation bound, not a recommended or healthy body weight. This application example logs observations and supplies no diagnosis, calorie target or weight-loss advice.

Keep the person's explicit calendar date separate from a derived UTC timestamp. The existing form reader validates the complete record before copying it out. Successful parsing alone does not validate the date, authorize access, save a record or mark a draft clean.

## Build a client qualification table

For each synthetic input, record the native status, output value, visible field message and saved-state claim. Run the same table through each actual client adapter. A platform-specific keyboard can change the characters entered, so mobile entry still needs separate observation even when the C library is shared.

Use only synthetic records in ordinary diagnostics. Avoid logging real observation text or notes while debugging parser behavior. A useful error log can name the operation and status without copying the personal payload.

## Continue toward the application

The Framework schema, parser, reader and synthetic example are authored. Their build and tests require qualification in the selected Framework environment. The full desktop, browser and mobile workflows also need approved layouts, persistence, authorization, recovery and UI evidence. Reusing this shared boundary makes those clients thinner; it does not imply that the clients already exist or passed their tests.

[Course contents](index.md) · [Previous lesson](08-qualify-the-whole-observation-workflow.md)
