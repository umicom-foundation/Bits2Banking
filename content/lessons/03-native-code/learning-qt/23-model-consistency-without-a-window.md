<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-qt/23-model-consistency-without-a-window.md

PURPOSE:
Check model consistency without launching a GUI

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Check model consistency without launching a GUI

## Use two complementary observers

QAbstractItemModelTester checks general model consistency as the model changes. The explicit Qt Test cases check the laboratory’s domain expectations: copied input, duplicate precedence, byte limits and callback behavior. Neither replaces the other. A structurally valid model could still return the wrong component label.

## Attach the consistency observer

~~~cpp
ComponentModel model;
QAbstractItemModelTester consistency(&model,
    QAbstractItemModelTester::FailureReportingMode::QtTest);
QCOMPARE(model.appendButton("save", "Save"), UMI_STATUS_OK);
~~~

The observer lives for the test scope and is destroyed before the model. QTEST_GUILESS_MAIN supplies a QCoreApplication for the suite. No widget or platform window is constructed. QSignalSpy captures notifications so tests can inspect counts and values without inventing a GUI journey.

## Check stable indexes

The rolesAndCopiedOwnership case keeps a QPersistentModelIndex to the first row, appends another row, and reads the original label again. The model still has only one column and no children. Foreign indexes and unsupported roles are checked explicitly. These cases make the contract useful to future views while leaving their visual design untouched.

## Exercise and evidence

Run the named CTest entry after a successful build and retain the full Qt Test output. Identify the six test methods separately from setup and cleanup. If one fails, report its assertion and source revision; do not summarize an incomplete run as a pass. A successful headless suite establishes no visible font, accessibility, focus or DPI behavior. Those remain separate native interface observations.

## Reference

- [QAbstractItemModelTester](https://doc.qt.io/qt-6/qabstractitemmodeltester.html)
- [QSignalSpy](https://doc.qt.io/qt-6/qsignalspy.html)

## Read the source

[labs/framework/qt-component-model/test_model.cpp](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/framework/qt-component-model/test_model.cpp). Use the matching local revision when offline.

## Continue learning

[Course contents](../../../courses/learning-qt/index.html) · [Previous: Keep model mutation on its owner thread](22-owner-thread-and-reentrant-callbacks.md) · [Next: Qualify the model lab and record its limits](24-qualify-the-installed-model-lab.md)
