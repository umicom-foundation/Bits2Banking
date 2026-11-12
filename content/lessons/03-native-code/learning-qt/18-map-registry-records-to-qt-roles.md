<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-qt/18-map-registry-records-to-qt-roles.md

PURPOSE:
Map registry records to rows and roles

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Map registry records to rows and roles

## Describe one row

The laboratory exposes one row per admitted component. Its row order follows insertion order. Each row has three custom roles: componentId, componentText and componentKind. A role is a named question about a row. Qt::DisplayRole returns the same label as componentText, allowing a conventional view to display useful text without knowing the custom roles.

## Read through the adapter

~~~cpp
ComponentModel model;
const UmiStatus status = model.appendButton("save", "Save");
if (status == UMI_STATUS_OK) {
    const QModelIndex row = model.index(0, 0);
    const QString id = model.data(row, ComponentModel::IdRole).toString();
    const QString label = model.data(row).toString();
}
~~~

The returned QString owns its value independently of the registry. The adapter never returns a writable pointer to a component. This is why future model edits cannot turn a previously returned label into a dangling pointer. The registry stays private and its accepted count is bounded by Framework capacity.

## Refuse meaningless indexes

Read the first branch in data. An invalid index, an index from another model, a nonzero column or a row outside the current count returns an empty QVariant. A valid parent has no children in this flat model, so rowCount(parent) returns zero. These checks prevent an interface mistake from becoming an out-of-range C array access.

## Exercise and worked answer

After adding save and cancel, request componentId at row one, then request an unsupported role. Expect cancel for the first query and an invalid QVariant for the second. An unsupported role is not an empty string: the absence of a value is distinguishable. Add a read-only tooltip role as an exercise using the existing component field, while keeping the storage and validity rules in Framework.

## Reference

- [QAbstractListModel contract](https://doc.qt.io/qt-6/qabstractlistmodel.html)

## Read the source

[labs/framework/qt-component-model/component_model.cpp](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/framework/qt-component-model/component_model.cpp). Use the matching local revision when offline.

## Continue learning

[Course contents](../../../courses/learning-qt/index.html) · [Previous: Use the C registry directly from a Qt adapter](17-c-linkage-and-the-installed-sdk.md) · [Next: Keep text ownership and byte boundaries explicit](19-utf8-ownership-and-zero-characters.md)
