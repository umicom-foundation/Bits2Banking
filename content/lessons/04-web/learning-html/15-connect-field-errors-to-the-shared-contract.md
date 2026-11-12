<!--
Umicom Bits2Banking
File: content/lessons/04-web/learning-html/15-connect-field-errors-to-the-shared-contract.md

PURPOSE:
Connect field errors to the shared contract

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Connect field errors to the shared contract

A form error should explain which input needs attention while preserving the person's draft. Color alone is insufficient. This lesson connects a small HTML teaching fragment to the existing Framework kilogram parser; it does not introduce a new application layout.

## Before you begin

Complete the earlier lessons on named controls and saved-state messages. Keep a disposable HTML exercise separate from a production endpoint, and read the kilogram parser contract in the Framework header. Use synthetic values only. A browser and keyboard are needed for the later presentation checks; source inspection alone cannot verify announcements or focus.

## Use one validation contract

The shared C function umi_weight_log_parse_kilograms accepts a bounded ASCII span. For this contract, 80.250 means 80250 grams. A comma decimal separator, exponent, sign, spaces or a kg suffix is refused. The web client must communicate that input format and still submit through the shared validation boundary.

Client hints can make entry easier. They cannot replace server-side or host-side validation. A request can arrive without using your form at all.

## Associate text with its control

~~~html
<label for="mass">Observation in kilograms</label>
<p id="mass-help">Use a dot and up to three fractional digits, for example 80.250.</p>
<input id="mass" name="mass_kg" type="text" inputmode="decimal"
       value="80,250" aria-invalid="true"
       aria-describedby="mass-help mass-error">
<p id="mass-error">Use a dot instead of a comma. Your entry has not been saved.</p>
~~~

This is an error-state example. In a real response, escape the preserved value as an HTML attribute through the shared output adapter. Never insert an untrusted value directly into this string. inputmode is an input hint; it does not enforce the C grammar.

## Plan the response sequence

1. Keep the entered value in the draft.

2. Validate it through the shared native contract.

3. On refusal, return a stable field identifier and useful text, without claiming a save.

4. Associate the error text with the control and provide an error summary for a multi-field form.

5. Let the person correct the entry and submit again. Only an acknowledged persistence result can support “saved.”

The W3C [form-notification guidance](https://www.w3.org/WAI/tutorials/forms/notifications/) describes identifying errors and associating messages with controls. Browser, keyboard and assistive-technology behavior still needs actual qualification.

## Exercise and expected observations

Try 80.250, 80,250, an empty value and 80.250kg in a synthetic test plan. Only the first matches the parser's valid nonzero kilogram grammar. Date, authorization and persistence remain separate checks even for that accepted mass.

Explain what happens if the request times out after submission. “No response received” is accurate; “not saved” may be wrong if the server completed the write. Recovery must inspect the authorized record state before retrying a create operation.

## Keep branding and scope intact

Use the approved Umicom SVG wordmark, ICO and shared typography when the fragment is integrated into the approved page design. This lesson's source editions already use those course assets. It does not prove a browser rendered them, supply a production endpoint, or provide a completed mobile or desktop application.

[Course contents](index.md) · [Previous lesson](14-distinguish-a-draft-from-a-saved-record.md) · [Next lesson](16-test-published-table-structure.md)
