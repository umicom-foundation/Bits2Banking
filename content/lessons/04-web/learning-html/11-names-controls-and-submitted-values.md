<!--
Umicom Bits2Banking
File: content/lessons/04-web/learning-html/11-names-controls-and-submitted-values.md

PURPOSE:
Follow named controls into a form request

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Follow named controls into a form request

## Before you begin
Read the earlier HTML form lesson. Use a scratch file and synthetic values. No server is provided by this exercise; pressing Submit against a missing route does not save anything. Start by tracing the document on paper.

## Build a request vocabulary
An id joins a visible label to its control. A name identifies the value in the submitted request. Keeping those jobs distinct makes a form understandable to both its reader and its receiving C service.

~~~html
<form method="post" action="/practice/observations">
  <label for="practice-date">Observation date</label>
  <input id="practice-date" name="observed_on"
         type="date" required value="2024-02-29">
  <label for="practice-mass">Mass in grams</label>
  <input id="practice-mass" name="mass_grams"
         type="number" min="1" step="1" required value="80250">
  <button type="submit" name="intent" value="review">Review</button>
</form>
~~~

1. Write down the three names the receiving route needs: observed_on, mass_grams and intent.
2. Change only practice-mass to practice-weight in both id and label for. The request's mass_grams name remains unchanged.
3. Remove the name from the mass control in your practice copy. The visible number still exists, but it no longer contributes that named entry.
4. Restore the name before continuing. The server must reject a missing required entry; it must not substitute a previous person's value.

## Expected result
For this filled form and activated Review button, the logical entries are observed_on=2024-02-29, mass_grams=80250 and intent=review. Actual encoding and transport are separate concerns. A browser can prevent an ordinary invalid submission, but a caller can construct its own request.

## Exercise and recovery
Disable the date control, then compare its submission with a read-only text field in a separate scratch form. Record what is omitted and what remains editable. A missing date must remain a refused request. Restore the original controls when finished; do not repair a server error by weakening required fields.

## Connect to Framework
The Framework structured-form adapter has its own complete field, revision and intent contract. This three-name teaching fragment is not a drop-in replacement for the generated controls. Inspect include/umicom/web/structured_form.h before wiring a real route.

The [HTML forms specification](https://html.spec.whatwg.org/multipage/forms.html) explains the browser contract. A network request trace, server validation and an acknowledged save are different pieces of evidence.


[Course contents](index.md) · [Previous lesson](10-relative-resources-and-http.md) · [Next lesson](12-read-an-observation-table.md)
