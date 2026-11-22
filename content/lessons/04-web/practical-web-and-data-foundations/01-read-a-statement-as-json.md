<!--
Umicom Bits2Banking
File: content/lessons/04-web/practical-web-and-data-foundations/01-read-a-statement-as-json.md

PURPOSE:
Read a statement as JSON in the Bits2Banking web and data course.

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

# Read a statement as JSON

[Course contents](index.md) · [Next lesson · Put the entries on a web page](02-put-rows-on-a-web-page.md)

Read a small text record and identify each field, each entry and the group they belong to.

## Start with the information

A statement lists changes to an amount of money over time. Imagine this one belongs to a fictional reserve account. The first entry adds 2,600 cents. The second removes 850 cents. Both are posted, which means they have been recorded for this exercise. The last entry of 500 cents is pending. Leave it out of the posted calculation.

A field is one named piece of information. An entry in this lesson has an ID, a status and an amount. The ID is a number used to recognise that entry. Use cents so each amount is a whole number.

## Read the same record as text

JSON is a text format for exchanging information. Braces `{}` surround an object, which groups named fields. Square brackets `[]` surround an array, which lists values in order. Double quotes surround each field name and each piece of text. Numbers such as `-850` have no quotes.

```json
{
  "entries": [
    {"id": 1, "status": "posted", "cents": 2600},
    {"id": 2, "status": "posted", "cents": -850},
    {"id": 3, "status": "pending", "cents": 500}
  ]
}
```

Start at the outer braces. Find the field named `entries`, then count its three items. The second item pairs `cents` with `-850`. A comma separates entries. A standard JSON document has no comma after the last entry.

## Try it on paper

Imagine a fourth posted item for 100 cents. Draw its object before editing the text. Which three fields must appear? What is the new posted total?

Check yourself by adding `{"id": 4, "status": "posted", "cents": 100}` as a fourth item, with a comma after the previous item. The posted total becomes `2600 - 850 + 100 = 1850` cents. Restore the original three entries before moving to the next exercise.

For the later Node.js exercise, save the original example as plain text in a new practice folder. Name it `statement.json`. If your editor saves `statement.json.txt`, rename the file and keep the `.json` ending.

## Connect to Umicom

A file importer in a practice edition of Umicom Bank could read these fields before deciding whether their values are suitable. The structure tells an importer where the fields are. A separate rule checks whether each value is allowed.

- [Read JSON, JSONL and chat records](../../../courses/preparing-llm-training-data/lessons/03-json-jsonl-and-chat-records.html)
- [JSON format specification](https://www.rfc-editor.org/rfc/rfc8259.html)

[Open the HTML edition](../../../courses/practical-web-and-data-foundations/lessons/01-read-a-statement-as-json.html)
