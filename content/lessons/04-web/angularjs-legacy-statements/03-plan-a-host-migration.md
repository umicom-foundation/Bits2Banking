<!--
Umicom Bits2Banking
File: content/lessons/04-web/angularjs-legacy-statements/03-plan-a-host-migration.md

PURPOSE:
Keep accounting in C and compare AngularJS 1.x templates with a modern Angular component and a D boundary check.

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

# Plan a host migration around the native contract

[Course contents](index.md) · [Previous · Follow entry identities and empty states](02-follow-entry-identities-and-empty-states.md) · [Browser edition](../../../courses/angularjs-legacy-statements/lessons/03-plan-a-host-migration.html)

Keep accounting in C and compare AngularJS 1.x templates with a modern Angular component and a D boundary check.

## Record the contract before a migration

- AngularJS 1.x uses features such as `ng-repeat` and `$ctrl` in the archived example. Official AngularJS support ended in January 2022.
- Modern Angular uses its own component and template APIs. A move to it requires a migration plan and compatible dependencies.
- The native snapshot contract records version 1, signed whole cents, ordered row identities and explicit posting state. Either interface can consume the same checked result.

## Compare a data admission check in D

A boundary is the point where a program accepts data from another component. This D function uses C calling conventions so a compatible native caller could ask about a version without involving the browser. Compile and ABI checks belong to the same target toolchain.

```d
extern(C) int knownReportVersion(int version) @nogc nothrow {
    // Keep this check deterministic and independent of the view.
    return version == 1 ? 1 : 0;
}
```

Trace `knownReportVersion(1)` to 1 and `knownReportVersion(2)` to 0. The D declaration shows a small native check. The C reporter remains the owner of the teaching sample and its arithmetic.

## Review a current template fragment

This modern Angular fragment belongs inside a compatible Angular component template with an already admitted `report`. The modern tracking expression fulfils a purpose like the old stable row key.

```html
@for (row of report.rows; track row.id) {
  <p>Entry {{row.id}}: {{row.cents}} cents, {{row.status}}.</p>
} @empty {
  <p>No entries in this statement.</p>
}
```

1. On paper, compare the old ngRepeat and new track expressions. Both use the row ID.
2. Check the same four data cases in the proposed replacement, including ready, valid empty, unknown version and absent.
3. Have a reviewer identify where a changed posted total would have to originate. Reuse the verified C snapshot while evaluating the interface migration.

For an Umicom Studio exercise, write a migration work item with two fixture paths and an expected table for each. Keep the old AngularJS environment isolated as source-reading material.

- [AngularJS support status](https://docs.angularjs.org/misc/version-support-status)
- [Angular component reference](https://angular.dev/api/core/Component)
- [Current Angular control flow](https://angular.dev/guide/templates/control-flow)
- [D linkage attributes](https://dlang.org/spec/attribute.html#linkage)

## Follow another path

- [Node.js and Native Statement Reports](../../../courses/nodejs-native-reporting/index.html)
- [React and Native Statement Data](../../../courses/react-native-statements/index.html)
- [Applied native courses](../../../start/applied-native-courses.md)
- [AngularJS support status](https://docs.angularjs.org/misc/version-support-status)
- [Angular component reference](https://angular.dev/api/core/Component)

[Course contents](index.md) · [Previous · Follow entry identities and empty states](02-follow-entry-identities-and-empty-states.md) · [Browser edition](../../../courses/angularjs-legacy-statements/lessons/03-plan-a-host-migration.html)
