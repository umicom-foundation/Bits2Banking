<!--
Umicom Bits2Banking
File: content/lessons/04-web/react-native-statements/03-show-loading-empty-and-error-states.md

PURPOSE:
Render three different outcomes from the native snapshot boundary and trace a complete screen check.

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

# Show loading, empty and error states

[Course contents](index.md) · [Previous · Filter rows without changing the posted total](02-filter-without-changing-the-posted-total.md) · [Browser edition](../../../courses/react-native-statements/lessons/03-show-loading-empty-and-error-states.html)

Render three different outcomes from the native snapshot boundary and trace a complete screen check.

## Decide what each screen means

- Loading means the application has asked for a response and is still waiting.
- Ready with an empty rows array means the request succeeded and there are no entries.
- Error means the snapshot could not be accepted, for example because its version is unknown or its source failed. Review the full report in the native reporting course.

```jsx
import StatementRows from "./StatementRows.jsx";

export function ReportView({ result }) {
  // Require a checked snapshot before either child can render money.
  if (result.kind === "loading")
    return <p role="status">Loading statement.</p>;
  if (result.kind !== "ready")
    return <p role="alert">Statement unavailable.</p>;
  const { snapshot } = result;
  if (snapshot.rows.length === 0)
    return <p role="status">No entries in this statement.</p>;
  return <><p>{snapshot.postedCents} posted cents.</p>
    <StatementRows snapshot={snapshot} /></>;
}
```

1. Pass `{ kind: "loading" }` and predict the message before observing the screen.
2. Pass `{ kind: "ready", snapshot: emptyReport }` using the empty fixture. Expect No entries in this statement.
3. Pass `{ kind: "error" }` and expect Statement unavailable. A failed request must not appear as a valid zero total.
4. Pass `{ kind: "ready", snapshot: trainingReport }` using the three-row fixture already checked by the adapter. Expect 1750 posted cents and all three rows visible until the checkbox changes.

This component receives an already checked snapshot. Supply the result from a trusted boundary adapter. On a refreshed page keep a late response from replacing a newer request by cancelling or ignoring the older request in that adapter.

## Apply it to Umicom Automated Testing

Use the four outcomes above as an acceptance checklist. A check is complete when it records what the test supplied, what the screen showed, and whether keyboard focus remained usable. Ask a second learner to distinguish pending and posted rows without relying on colour.

- [Three-row practice snapshot](../../../labs/native/web-statement-contract/statement-report.json)
- [Empty practice snapshot](../../../labs/native/web-statement-contract/statement-report-empty.json)
- [Node.js and Native Statement Reports](../../../courses/nodejs-native-reporting/index.html)
- [Thinking in React](https://react.dev/learn/thinking-in-react)

## Follow another path

- [Learning React](../../../courses/learning-react/index.html)
- [Node.js and Native Statement Reports](../../../courses/nodejs-native-reporting/index.html)
- [AngularJS and Legacy Statement Screens](../../../courses/angularjs-legacy-statements/index.html)
- [Practical Web and Data Foundations](../../../courses/practical-web-and-data-foundations/index.html)
- [Applied native courses](../../../start/applied-native-courses.md)

[Course contents](index.md) · [Previous · Filter rows without changing the posted total](02-filter-without-changing-the-posted-total.md) · [Browser edition](../../../courses/react-native-statements/lessons/03-show-loading-empty-and-error-states.html)
