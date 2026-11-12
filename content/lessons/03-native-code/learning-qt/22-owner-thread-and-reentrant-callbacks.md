<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-qt/22-owner-thread-and-reentrant-callbacks.md

PURPOSE:
Keep model mutation on its owner thread

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Keep model mutation on its owner thread

## Distinguish two kinds of overlap

A second thread and a nested callback can both overlap an operation, but they require different reasoning. Qt model APIs belong to the object’s owning thread. This lab expects callers to queue work onto that thread. Within one thread, a signal listener can run before the original appendButton call returns and attempt another edit.

## Guard the complete operation

~~~cpp
if (QThread::currentThread() != thread()) return UMI_STATUS_INVALID_STATE;
if (publishing_) return UMI_STATUS_BUSY;
QScopedValueRollback<bool> publication(publishing_, true);
~~~

The guard begins before input conversion and remains active during success and refusal notifications. Scope exit restores the previous flag on each normal return. A nested edit returns BUSY without emitting another refusal signal. Emitting recursively could repeatedly invoke the same listener. A read-only listener can still inspect the row count or copied values.

## Respect object lifetime

The guard is not a mutex and does not make the object thread-safe. The model must remain alive for the complete call. Signal handlers must not synchronously delete it or throw through Qt notification code. Cross-thread producers should transfer owned input through the application’s queued delivery path, with lifetime management appropriate to that application.

## Exercise and worked answer

Read signalsObserveOldAndNewOwners and refusalNotificationRejectsReentry. Both nested edits should return BUSY, while a later top-level edit can succeed. If a background worker needs to propose a component, it should send the proposal to the model owner rather than call appendButton directly. The supplied tests do not stress concurrent destruction or prove a larger application’s thread shutdown protocol.

## Reference

- [Qt model thread safety](https://doc.qt.io/qt-6/qabstractitemmodel.html#thread-safety)

## Read the source

[labs/framework/qt-component-model/component_model.cpp](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/framework/qt-component-model/component_model.cpp). Use the matching local revision when offline.

## Continue learning

[Course contents](../../../courses/learning-qt/index.html) · [Previous: Test that refused edits preserve the model](21-refused-edits-are-observable-contracts.md) · [Next: Check model consistency without launching a GUI](23-model-consistency-without-a-window.md)
