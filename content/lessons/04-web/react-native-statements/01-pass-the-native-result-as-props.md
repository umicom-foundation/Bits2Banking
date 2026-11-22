<!--
Umicom Bits2Banking
File: content/lessons/04-web/react-native-statements/01-pass-the-native-result-as-props.md

PURPOSE:
Draw a summary card on paper, then make React show the fields calculated by a native C program.

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

# Pass the native result as props

[Course contents](index.md) · [Next · Filter rows without changing the posted total](02-filter-without-changing-the-posted-total.md) · [Browser edition](../../../courses/react-native-statements/lessons/01-pass-the-native-result-as-props.html)

Draw a summary card on paper, then make React show the fields calculated by a native C program.

## Trace the receipt first

Use fictional entries 101, 102 and 103 in this order. The C23 reporter counts posted entries 101 and 102. Their 2600 and −850 cents sum to 1750. Entry 103 contributes 500 cents only to the pending rows displayed on the page.

C produces a snapshot, a fixed record of one known result. A React component is a function that describes one part of a page. Its props are the inputs from a parent component. Keep the calculation in the C reporter and pass its ready-to-display fields to the web view.

- [C23 statement reporter](../../../labs/native/web-statement-contract/statement-report.c)
- [Three-row practice snapshot](../../../labs/native/web-statement-contract/statement-report.json)
- [Empty practice snapshot](../../../labs/native/web-statement-contract/statement-report-empty.json)

## Create a local component

```jsx
import report from "./statement-report.json";

function PostedSummary({ postedCents, postedCount }) {
  // Render the amounts supplied by the native statement owner.
  return <section aria-labelledby="posted-heading">
    <h2 id="posted-heading">Posted summary</h2>
    <p>{postedCents} cents in {postedCount} posted entries.</p>
  </section>;
}

export default function StatementPage() {
  return <PostedSummary postedCents={report.postedCents}
                        postedCount={report.postedCount} />;
}
```

1. Use a new practice copy of an existing React project. Save the three-row snapshot as `statement-report.json` beside your `StatementPage.jsx` file.
2. Put the example in `StatementPage.jsx`. Import the default export into your existing project entry and render `<StatementPage />` once.
3. Use your local project’s normal preview. Look for the heading Posted summary and the line `1750 cents in 2 posted entries.`. If JSON import is unsupported in that setup, start with the same already parsed object passed as props.

## Try the empty report

Predict what should appear if there are no rows. In your practice copy substitute the empty snapshot. The expected text is `0 cents in 0 posted entries.`. Keep the difference between a successful zero and a failure for the next lessons.

For an Umicom Bank practice exercise, write down the signed total, unit and row count that a read-only Framework client must receive. The React component needs only the fields it displays.

- [Thinking in React](https://react.dev/learn/thinking-in-react)
- [Learning React](../../../courses/learning-react/index.html)

## Follow another path

- [Learning React](../../../courses/learning-react/index.html)
- [Node.js and Native Statement Reports](../../../courses/nodejs-native-reporting/index.html)
- [AngularJS and Legacy Statement Screens](../../../courses/angularjs-legacy-statements/index.html)
- [Practical Web and Data Foundations](../../../courses/practical-web-and-data-foundations/index.html)
- [Applied native courses](../../../start/applied-native-courses.md)

[Course contents](index.md) · [Next · Filter rows without changing the posted total](02-filter-without-changing-the-posted-total.md) · [Browser edition](../../../courses/react-native-statements/lessons/01-pass-the-native-result-as-props.html)
