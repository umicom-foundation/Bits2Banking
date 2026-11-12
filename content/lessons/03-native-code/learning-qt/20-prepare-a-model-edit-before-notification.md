<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-qt/20-prepare-a-model-edit-before-notification.md

PURPOSE:
Prepare an edit before publishing a Qt row

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Prepare an edit before publishing a Qt row

## Separate admission from observation

A view observing a model needs a coherent change boundary. The lab first allocates a candidate registry and copies the current owner into it. umi_ui_component_registry_add validates and changes that candidate. A duplicate, invalid specification or full registry is discovered before any insertion notification. The live model remains untouched during this preparation.

## Publish the admitted owner

~~~cpp
const int row = rowCount();
beginInsertRows(QModelIndex(), row, row);
registry_.swap(candidate);
endInsertRows();
~~~

These lines occur only after successful Framework admission. The begin notification exposes the old count; the end notification exposes the new count. The swap itself does not allocate or run another policy check. Afterwards the candidate pointer owns the old registry and releases it automatically.

## Reason about cost

Copying the bounded registry makes this example easy to inspect and keeps rollback simple. It is a tradeoff: each insertion copies the registry and validates its active entries. This is suitable for studying a small component catalogue, not a claim of high-volume performance. Measure a real workload before extending this design. Any optimization must preserve duplicate checks and the visible notification boundary.

## Exercise and worked answer

Suppose allocation were attempted between beginInsertRows and endInsertRows and failed. The view would already have been told an insertion was starting, so an ordinary early return would break the notification contract. Move fallible preparation before begin. In the supplied test, collect rowCount during both signals and verify zero then one for the first insertion. Do not edit the live C array directly to make the assertion pass.

## Reference

- [Qt model insertion contract](https://doc.qt.io/qt-6/qabstractitemmodel.html#beginInsertRows)

## Read the source

[labs/framework/qt-component-model/component_model.cpp](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/framework/qt-component-model/component_model.cpp). Use the matching local revision when offline.

## Continue learning

[Course contents](../../../courses/learning-qt/index.html) · [Previous: Keep text ownership and byte boundaries explicit](19-utf8-ownership-and-zero-characters.md) · [Next: Test that refused edits preserve the model](21-refused-edits-are-observable-contracts.md)
