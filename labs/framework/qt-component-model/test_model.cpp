/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/framework/qt-component-model/test_model.cpp
 *
 * PURPOSE:
 *   Check model roles, copied ownership, refused edits and insertion signal ordering.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include "component_model.h"
#include <QAbstractItemModelTester>
#include <QPersistentModelIndex>
#include <QSignalSpy>
#include <QTest>
#include <QVariant>

class ComponentModelTest final : public QObject {
    Q_OBJECT
private slots:
    void rolesAndCopiedOwnership();
    void refusalsPreserveRows();
    void utf8ByteBoundary();
    void signalsObserveOldAndNewOwners();
    void refusalNotificationRejectsReentry();
    void fullRegistryKeepsDuplicatePrecedence();
};

void ComponentModelTest::rolesAndCopiedOwnership()
{
    ComponentModel model;
    QAbstractItemModelTester consistency(&model,
        QAbstractItemModelTester::FailureReportingMode::QtTest);
    QString id = QStringLiteral("save");
    QString label = QStringLiteral("Save");
    QCOMPARE(model.appendButton(id, label), UMI_STATUS_OK);
    id.fill(QChar('x'));
    label.fill(QChar('x'));
    QCOMPARE(model.rowCount(), 1);
    const QModelIndex row = model.index(0, 0);
    QCOMPARE(model.data(row, ComponentModel::IdRole).toString(), QStringLiteral("save"));
    QCOMPARE(model.data(row).toString(), QStringLiteral("Save"));
    QCOMPARE(model.data(row, ComponentModel::TextRole), model.data(row));
    QCOMPARE(model.data(row, ComponentModel::KindRole).toInt(), int(UMI_UI_COMPONENT_BUTTON));
    QCOMPARE(model.roleNames().value(ComponentModel::IdRole), QByteArray("componentId"));
    QCOMPARE(model.roleNames().value(ComponentModel::TextRole), QByteArray("componentText"));
    QCOMPARE(model.roleNames().value(ComponentModel::KindRole), QByteArray("componentKind"));
    QCOMPARE(model.rowCount(row), 0);
    QVERIFY(!model.data(QModelIndex()).isValid());
    QVERIFY(!model.data(model.index(2, 0)).isValid());
    QVERIFY(!model.data(model.index(0, 1)).isValid());
    QVERIFY(!model.data(row, Qt::UserRole + 90).isValid());
    ComponentModel other;
    QCOMPARE(other.appendButton("other", "Other"), UMI_STATUS_OK);
    QVERIFY(!model.data(other.index(0, 0)).isValid());
    QPersistentModelIndex persistent(row);
    QCOMPARE(model.appendButton("cancel", "Cancel"), UMI_STATUS_OK);
    QCOMPARE(persistent.data().toString(), QStringLiteral("Save"));
}

void ComponentModelTest::refusalsPreserveRows()
{
    ComponentModel model;
    QAbstractItemModelTester consistency(&model,
        QAbstractItemModelTester::FailureReportingMode::QtTest);
    QCOMPARE(model.appendButton("save", "Save"), UMI_STATUS_OK);
    QSignalSpy about(&model, &QAbstractItemModel::rowsAboutToBeInserted);
    QSignalSpy inserted(&model, &QAbstractItemModel::rowsInserted);
    QSignalSpy refused(&model, &ComponentModel::editRefused);
    QVERIFY(about.isValid() && inserted.isValid() && refused.isValid());
    QCOMPARE(model.appendButton("save", "Replacement"), UMI_STATUS_ALREADY_EXISTS);
    QCOMPARE(model.appendButton("", "Empty ID"), UMI_STATUS_INVALID_ARGUMENT);
    QCOMPARE(model.appendButton(QString(UMI_UI_COMPONENT_ID_CAPACITY, QChar('i')), "Long"),
             UMI_STATUS_CAPACITY_EXCEEDED);
    QCOMPARE(model.appendButton("long-text", QString(UMI_UI_COMPONENT_TEXT_CAPACITY, QChar('t'))),
             UMI_STATUS_CAPACITY_EXCEEDED);
    QString hidden = QStringLiteral("valid");
    hidden.append(QChar(0));
    hidden.append(QStringLiteral("hidden"));
    QCOMPARE(model.appendButton(hidden, "Hidden ID"), UMI_STATUS_INVALID_ARGUMENT);
    QCOMPARE(model.appendButton("hidden-text", hidden), UMI_STATUS_INVALID_ARGUMENT);
    QCOMPARE(about.count(), 0);
    QCOMPARE(inserted.count(), 0);
    QCOMPARE(refused.count(), 6);
    QCOMPARE(refused.at(0).at(0).toInt(), int(UMI_STATUS_ALREADY_EXISTS));
    QCOMPARE(model.rowCount(), 1);
    QCOMPARE(model.data(model.index(0, 0)).toString(), QStringLiteral("Save"));
    QCOMPARE(model.appendButton("recovery", "Recovered"), UMI_STATUS_OK);
    QCOMPARE(model.rowCount(), 2);
}

void ComponentModelTest::utf8ByteBoundary()
{
    ComponentModel model;
    // U+00E9 occupies two UTF-8 bytes. Add one ASCII byte to reach 255 bytes.
    const QString exact = QString(127, QChar(0x00e9)) + QStringLiteral("x");
    QCOMPARE(exact.toUtf8().size(), qsizetype(UMI_UI_COMPONENT_TEXT_CAPACITY - 1U));
    QCOMPARE(model.appendButton("exact", exact), UMI_STATUS_OK);
    QCOMPARE(model.data(model.index(0, 0)).toString(), exact);
    QCOMPARE(model.appendButton("too-long", exact + "x"), UMI_STATUS_CAPACITY_EXCEEDED);
    QCOMPARE(model.rowCount(), 1);
    const QString exactId(UMI_UI_COMPONENT_ID_CAPACITY - 1U, QChar('i'));
    QCOMPARE(model.appendButton(exactId, ""), UMI_STATUS_OK);
    QCOMPARE(model.data(model.index(1, 0), ComponentModel::IdRole).toString(), exactId);
}

void ComponentModelTest::signalsObserveOldAndNewOwners()
{
    ComponentModel model;
    QAbstractItemModelTester consistency(&model,
        QAbstractItemModelTester::FailureReportingMode::QtTest);
    QSignalSpy refused(&model, &ComponentModel::editRefused);
    int oldCount = -1, newCount = -1, firstRow = -1, lastRow = -1;
    UmiStatus nestedBefore = UMI_STATUS_OK, nestedAfter = UMI_STATUS_OK;
    connect(&model, &QAbstractItemModel::rowsAboutToBeInserted, &model,
        [&](const QModelIndex &parent, int first, int last) {
            QVERIFY(!parent.isValid());
            oldCount = model.rowCount();
            firstRow = first;
            lastRow = last;
            nestedBefore = model.appendButton("nested-before", "Nested");
        });
    connect(&model, &QAbstractItemModel::rowsInserted, &model,
        [&](const QModelIndex &, int, int) {
            newCount = model.rowCount();
            nestedAfter = model.appendButton("nested-after", "Nested");
        });
    QCOMPARE(model.appendButton("outer", "Outer"), UMI_STATUS_OK);
    QCOMPARE(oldCount, 0);
    QCOMPARE(newCount, 1);
    QCOMPARE(firstRow, 0);
    QCOMPARE(lastRow, 0);
    QCOMPARE(nestedBefore, UMI_STATUS_BUSY);
    QCOMPARE(nestedAfter, UMI_STATUS_BUSY);
    QCOMPARE(refused.count(), 0);
    QCOMPARE(model.data(model.index(0, 0)).toString(), QStringLiteral("Outer"));
}

void ComponentModelTest::refusalNotificationRejectsReentry()
{
    ComponentModel model;
    QCOMPARE(model.appendButton("save", "Save"), UMI_STATUS_OK);
    int notifications = 0;
    UmiStatus nested = UMI_STATUS_OK;
    connect(&model, &ComponentModel::editRefused, &model, [&](int) {
        ++notifications;
        nested = model.appendButton("new-id", "New");
    });
    QCOMPARE(model.appendButton("save", "Again"), UMI_STATUS_ALREADY_EXISTS);
    QCOMPARE(nested, UMI_STATUS_BUSY);
    QCOMPARE(notifications, 1);
    QCOMPARE(model.rowCount(), 1);
    QCOMPARE(model.appendButton("new-id", "New"), UMI_STATUS_OK);
}

void ComponentModelTest::fullRegistryKeepsDuplicatePrecedence()
{
    ComponentModel model;
    for (unsigned index = 0; index < UMI_UI_COMPONENT_REGISTRY_CAPACITY; ++index)
        QCOMPARE(model.appendButton(QStringLiteral("item-") + QString::number(index), "Item"),
                 UMI_STATUS_OK);
    QSignalSpy inserted(&model, &QAbstractItemModel::rowsInserted);
    QCOMPARE(model.appendButton("item-0", "Again"), UMI_STATUS_ALREADY_EXISTS);
    QCOMPARE(model.appendButton("overflow", "Overflow"), UMI_STATUS_CAPACITY_EXCEEDED);
    QCOMPARE(model.rowCount(), int(UMI_UI_COMPONENT_REGISTRY_CAPACITY));
    QCOMPARE(inserted.count(), 0);
}

QTEST_GUILESS_MAIN(ComponentModelTest)
#include "test_model.moc"
