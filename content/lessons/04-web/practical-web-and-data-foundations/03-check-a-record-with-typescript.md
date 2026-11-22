<!--
Umicom Bits2Banking
File: content/lessons/04-web/practical-web-and-data-foundations/03-check-a-record-with-typescript.md

PURPOSE:
Check a record with TypeScript in the Bits2Banking web and data course.

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

# Check a record with TypeScript

[Course contents](index.md) · [Previous lesson · Put the entries on a web page](02-put-rows-on-a-web-page.md) · [Next lesson · Read a local statement with Node.js](04-read-the-file-with-node.md)

Describe the values a statement may contain and predict a type error before running the program.

## Compare actual and expected values

What if someone writes `"waiting"` when they mean `"pending"`? A human reader can ask what they meant. A program needs an exact rule. TypeScript lets you describe a rule for the kinds of values, called types, that your source code is allowed to put into a field.

A type checker reads source text and reports certain mistakes before the program runs. The following type `Status` permits one of two exact strings, which means values made of text. TypeScript writes that choice using `|`.

## Define an entry and read it back

The colon separates a field name from its type. Here each field is required. `id` and `cents` take `number`. `status` takes one `Status` value.

```typescript
type Status = "posted" | "pending";

type Entry = {
  id: number;
  status: Status;
  cents: number;
};

const entry: Entry = {id: 3, status: "pending", cents: 500};

// Print a predictable message for this known practice entry.
console.log(entry.status + " " + entry.cents);
```

Read `const entry: Entry` aloud as “give the name entry a value of type Entry”. `number` covers more than whole cents. A later check still has to enforce that real input is a safe whole number.

## Try the checker

Predict the output for the valid example. If you already have the TypeScript compiler and Node.js on your computer, save the code as `entry.ts` and run these commands from the directory that contains it. You can still do the prediction and check on paper.

```text
tsc --strict --noEmitOnError entry.ts
node entry.js
```

The valid output is `pending 500`. Now change the word `pending` in the value assigned to `entry` to `waiting`. Leave the type definition as it is. The checker should say that `waiting` is not one of the allowed values. With `--noEmitOnError`, a failing compilation writes no new JavaScript file. If `entry.js` exists from an earlier successful run, it still contains that earlier result.

## Connect to Umicom

In a Studio project, try writing a test expectation beside a declaration. The type checker can catch the wrong source text, while an input check can catch an unexpected value in a saved file at run time. Both checks protect an import exercise.

- [Compare how languages declare and check ideas](../../../courses/programming-across-languages/index.html)
- [TypeScript strict checking](https://www.typescriptlang.org/tsconfig/#strict)

[Open the HTML edition](../../../courses/practical-web-and-data-foundations/lessons/03-check-a-record-with-typescript.html)
