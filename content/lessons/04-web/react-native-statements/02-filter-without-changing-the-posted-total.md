<!--
Umicom Bits2Banking
File: content/lessons/04-web/react-native-statements/02-filter-without-changing-the-posted-total.md

PURPOSE:
Use a checkbox, list keys and a signed-cents column without recalculating money in React.

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

# Filter rows without changing the posted total

[Course contents](index.md) · [Previous · Pass the native result as props](01-pass-the-native-result-as-props.md) · [Next · Show loading, empty and error states](03-show-loading-empty-and-error-states.md) · [Browser edition](../../../courses/react-native-statements/lessons/02-filter-without-changing-the-posted-total.html)

Use a checkbox, list keys and a signed-cents column without recalculating money in React.

## Separate the screen choice from the statement

State is a value that the component remembers while it renders. The user’s Show posted only choice is state. The native snapshot is an input. The checkbox changes which rows are visible while the supplied posted total stays 1750.

```jsx
import { useState } from "react";

export default function StatementRows({ snapshot }) {
  const [postedOnly, setPostedOnly] = useState(false);
  const visibleRows = postedOnly
    ? snapshot.rows.filter((row) => row.status === "posted")
    : snapshot.rows;

  // The checkbox owns only visibility. C owns the posted amounts.
  return <section aria-labelledby="rows-heading">
    <h2 id="rows-heading">Entries</h2>
    <label><input type="checkbox" checked={postedOnly}
      onChange={(event) => setPostedOnly(event.target.checked)} />
      Show posted only
    </label>
    <p role="status">{visibleRows.length} entries visible.</p>
    <table>
      <caption>Synthetic statement entries</caption>
      <thead><tr><th scope="col">Entry</th>
        <th scope="col">Amount in cents</th>
        <th scope="col">State</th></tr></thead>
      <tbody>{visibleRows.map((row) =>
        <tr key={row.id}><th scope="row">{row.id}</th>
          <td>{row.cents}</td><td>{row.status}</td></tr>
      )}</tbody>
    </table>
  </section>;
}
```

1. Save the example as `StatementRows.jsx` beside `StatementPage.jsx`.
2. Import `StatementRows` into the page from the previous lesson. Wrap the summary and `<StatementRows snapshot={report} />` together in one React fragment, written `<> ... </>`.
3. Predict the three visible IDs before checking the box. When checked, IDs 101 and 102 remain, the status says `2 entries visible.`, and the posted total still reads 1750.
4. Use Tab to focus the checkbox and Space to change it. Keep each row’s ID as its React key, even as the row’s position changes. If React reports duplicate keys, check the snapshot IDs.

## Compare the branch in D

A branch chooses a path. Inside the native reporter, deciding whether a pending amount contributes to a sum is a business rule. In the UI, the similar-looking branch only selects which rows to draw. Read the same original checked cents addition in D.

```d
bool tryAddCents(int left, int right, ref int output) {
    // Widen before addition and retain the previous result on failure.
    const long candidate = cast(long) left + right;
    if (candidate < int.min || candidate > int.max)
        return false;
    output = cast(int) candidate;
    return true;
}
```

Trace `tryAddCents(2600, -850, total)` to 1750. Then set `total` to 42 and trace an attempt to add 1 to `int.max`. It should return false and leave 42. A React filter should never reach this arithmetic.

- [Rendering lists](https://react.dev/learn/rendering-lists)
- [Using state](https://react.dev/reference/react/useState)
- [D integer types](https://dlang.org/spec/type.html)

## Follow another path

- [Learning React](../../../courses/learning-react/index.html)
- [Node.js and Native Statement Reports](../../../courses/nodejs-native-reporting/index.html)
- [AngularJS and Legacy Statement Screens](../../../courses/angularjs-legacy-statements/index.html)
- [Practical Web and Data Foundations](../../../courses/practical-web-and-data-foundations/index.html)
- [Applied native courses](../../../start/applied-native-courses.md)

[Course contents](index.md) · [Previous · Pass the native result as props](01-pass-the-native-result-as-props.md) · [Next · Show loading, empty and error states](03-show-loading-empty-and-error-states.md) · [Browser edition](../../../courses/react-native-statements/lessons/02-filter-without-changing-the-posted-total.html)
