<!--
Umicom Bits2Banking
File: content/lessons/04-web/angularjs-legacy-statements/01-read-a-legacy-component.md

PURPOSE:
Find a component and its input in an AngularJS 1.x template before you change an established screen.

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

# Read a legacy statement component

[Course contents](index.md) · [Next · Follow entry identities and empty states](02-follow-entry-identities-and-empty-states.md) · [Browser edition](../../../courses/angularjs-legacy-statements/lessons/01-read-a-legacy-component.html)

Find a component and its input in an AngularJS 1.x template before you change an established screen.

## Observe the data and the display

Use fictional entries 101, 102 and 103 in this order. The C23 reporter counts posted entries 101 and 102. Their 2600 and −850 cents sum to 1750. Entry 103 contributes 500 cents only to the pending rows displayed on the page.

A template describes where each label and value should appear. AngularJS uses directives, attributes with special meaning, to connect the template to data. A component gives one piece of the screen a name, inputs and a template. Use a read-only training snapshot from the C reporter.

- [C23 statement reporter](../../../labs/native/web-statement-contract/statement-report.c)
- [Three-row practice snapshot](../../../labs/native/web-statement-contract/statement-report.json)
- [AngularJS support status](https://docs.angularjs.org/misc/version-support-status)

## Read one-way data binding

This exercise assumes an existing AngularJS 1.x lesson module with a parent controller that supplies `page.report`. Add this child component in that approved local practice copy. The name written in the HTML is hyphenated, and the JavaScript registration uses camel case.

```javascript
angular.module("trainingStatement").component("statementSummary", {
  // The parent hands the child one checked native result.
  bindings: { report: "<" },
  templateUrl: "statement-summary.html",
});
```

```html
<section aria-labelledby="training-summary">
  <h2 id="training-summary">Posted summary</h2>
  <p ng-if="$ctrl.report">
    {{$ctrl.report.postedCents}} cents in {{$ctrl.report.postedCount}} posted entries.
  </p>
</section>
```

```html
<statement-summary report="page.report"></statement-summary>
```

1. Save the component template as `statement-summary.html`. Register the component in the same module the offline practice page already loads.
2. Locate the parent markup and add the final element inside the existing controller. Keep the data object assigned to `page.report` in that controller.
3. With the three-row snapshot, predict 1750 cents in 2 posted entries. Without a report, AngularJS leaves the paragraph out. Use your existing local preview only if the archived environment is approved.

One-way input means the parent chooses what value to send. An object can still contain mutable fields. Treat this input as read-only and prepare a fresh validated object for each successful import.

## Connect it to Umicom

Use this as a source-reading exercise for a synthetic old Bank screen. Circle the one native result passed into the page. Keep all money arithmetic behind the application boundary.

- [AngularJS component guide](https://docs.angularjs.org/guide/component)
- [AngularJS support status](https://docs.angularjs.org/misc/version-support-status)

## Follow another path

- [Node.js and Native Statement Reports](../../../courses/nodejs-native-reporting/index.html)
- [React and Native Statement Data](../../../courses/react-native-statements/index.html)
- [Applied native courses](../../../start/applied-native-courses.md)
- [AngularJS support status](https://docs.angularjs.org/misc/version-support-status)
- [Angular component reference](https://angular.dev/api/core/Component)

[Course contents](index.md) · [Next · Follow entry identities and empty states](02-follow-entry-identities-and-empty-states.md) · [Browser edition](../../../courses/angularjs-legacy-statements/lessons/01-read-a-legacy-component.html)
