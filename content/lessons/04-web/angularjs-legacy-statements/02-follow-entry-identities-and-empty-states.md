<!--
Umicom Bits2Banking
File: content/lessons/04-web/angularjs-legacy-statements/02-follow-entry-identities-and-empty-states.md

PURPOSE:
Trace AngularJS ngRepeat identities and read the empty-state branch with an unchanged native report.

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

# Follow entry identities and empty states

[Course contents](index.md) · [Previous · Read a legacy statement component](01-read-a-legacy-component.md) · [Next · Plan a host migration around the native contract](03-plan-a-host-migration.md) · [Browser edition](../../../courses/angularjs-legacy-statements/lessons/02-follow-entry-identities-and-empty-states.html)

Trace AngularJS ngRepeat identities and read the empty-state branch with an unchanged native report.

## Use a stable key

A stable identity is a name for one item that remains the same when its position changes. AngularJS 1.x uses `ng-repeat` to display one copy of a row template per entry. The `track by` expression tells the framework which row identity it should use. The C lab requires ascending positive IDs before producing a snapshot.

```html
<p ng-if="$ctrl.report && !$ctrl.report.rows.length" role="status">
  No entries in this statement.
</p>
<table ng-if="$ctrl.report && $ctrl.report.rows.length">
  <caption>Fictional statement entries</caption>
  <thead><tr><th scope="col">Entry</th><th scope="col">Cents</th>
    <th scope="col">State</th></tr></thead>
  <tbody>
    <tr ng-repeat="row in $ctrl.report.rows track by row.id">
      <th scope="row">{{row.id}}</th><td>{{row.cents}}</td><td>{{row.status}}</td>
    </tr>
  </tbody>
</table>
```

1. Below the summary in `statement-summary.html`, add the sample table and empty message.
2. Trace the supplied three-row snapshot. Predict IDs 101, 102 and 103, including the visibly pending row. The caption tells the reader what the table represents.
3. Pass the empty version 1 snapshot. The empty message should appear and the table should be absent.
4. Draw a refusal box for a missing snapshot, then a separate box for a successful empty one. The parent must report a failed read separately.

The template interpolates the cents and state as text. Keep unchecked source data away from HTML-producing directives. Upstream admission should refuse an unsupported version or a repeated key before replacing the last valid screen result.

## Write a regression note

For a migration of your Umicom Bank teaching example, record the row IDs, cents, column names and empty message. A person reviewing the replacement can now compare the two views without access to the original business implementation.

- [Three-row practice snapshot](../../../labs/native/web-statement-contract/statement-report.json)
- [Empty practice snapshot](../../../labs/native/web-statement-contract/statement-report-empty.json)
- [AngularJS ngRepeat reference](https://docs.angularjs.org/api/ng/directive/ngRepeat)
- [Node.js and Native Statement Reports](../../../courses/nodejs-native-reporting/index.html)

## Follow another path

- [Node.js and Native Statement Reports](../../../courses/nodejs-native-reporting/index.html)
- [React and Native Statement Data](../../../courses/react-native-statements/index.html)
- [Applied native courses](../../../start/applied-native-courses.md)
- [AngularJS support status](https://docs.angularjs.org/misc/version-support-status)
- [Angular component reference](https://angular.dev/api/core/Component)

[Course contents](index.md) · [Previous · Read a legacy statement component](01-read-a-legacy-component.md) · [Next · Plan a host migration around the native contract](03-plan-a-host-migration.md) · [Browser edition](../../../courses/angularjs-legacy-statements/lessons/02-follow-entry-identities-and-empty-states.html)
