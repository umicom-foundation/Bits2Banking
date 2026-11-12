<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-qt/21-refused-edits-are-observable-contracts.md

PURPOSE:
Test that refused edits preserve the model

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Test that refused edits preserve the model

## Specify both result and state

A status alone is insufficient evidence for an edit. A function could return ALREADY_EXISTS after accidentally replacing a label. The laboratory therefore checks the returned status, existing row values, row count and emitted notifications. Start with one save row and request a second save row with different text.

## Observe insertion separately from refusal

~~~cpp
QSignalSpy inserted(&model, &QAbstractItemModel::rowsInserted);
QSignalSpy refused(&model, &ComponentModel::editRefused);
QVERIFY(inserted.isValid());
QVERIFY(refused.isValid());
QCOMPARE(model.appendButton("save", "Replacement"), UMI_STATUS_ALREADY_EXISTS);
QCOMPARE(inserted.count(), 0);
QCOMPARE(refused.count(), 1);
QCOMPARE(model.data(model.index(0, 0)).toString(), QStringLiteral("Save"));
~~~

The refusal signal carries the numeric Framework status as an int. This keeps the signal argument simple while preserving the actual cause. The test reads the captured argument, rather than treating any signal as proof of the right error. Do not convert every failure into a duplicate warning; capacity and invalid input need different recovery.

## Check the boundary cases

The supplied cases cover empty IDs, oversized IDs and labels, embedded zero characters, and a full registry. At full capacity, an existing ID still returns ALREADY_EXISTS; a new ID returns CAPACITY_EXCEEDED. This precedence belongs to Framework and the adapter retains it.

## Exercise and recovery

After each refused request, issue one valid request and verify that it succeeds when capacity permits. This catches a guard that was never released. If the refusal emits an insertion signal, inspect where candidate preparation and beginInsertRows occur. If the label changes despite refusal, inspect ownership and writes to the live registry. Preserve the smallest input and signal trace when reporting a failure.

## Reference

- [QSignalSpy](https://doc.qt.io/qt-6/qsignalspy.html)

## Read the source

[labs/framework/qt-component-model/test_model.cpp](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/framework/qt-component-model/test_model.cpp). Use the matching local revision when offline.

## Continue learning

[Course contents](../../../courses/learning-qt/index.html) · [Previous: Prepare an edit before publishing a Qt row](20-prepare-a-model-edit-before-notification.md) · [Next: Keep model mutation on its owner thread](22-owner-thread-and-reentrant-callbacks.md)
