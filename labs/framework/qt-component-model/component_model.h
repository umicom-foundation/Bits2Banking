/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/framework/qt-component-model/component_model.h
 *
 * PURPOSE:
 *   Declare a Qt model adapter with one privately owned Framework component registry.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#ifndef BTB_QT_COMPONENT_MODEL_H
#define BTB_QT_COMPONENT_MODEL_H

#include "umicom/ui/components/registry.h"
#include <QAbstractListModel>
#include <QString>
#include <memory>

/* Qt requires a C++ adapter; component validation and duplicate/capacity policy
 * remain in Framework C. Every model call belongs to this QObject's thread.
 * Signal handlers must not throw or synchronously destroy this object. */
class ComponentModel final : public QAbstractListModel {
    Q_OBJECT
public:
    enum Role { IdRole = Qt::UserRole + 1, TextRole, KindRole };
    Q_ENUM(Role)
    explicit ComponentModel(QObject *parent = nullptr);
    ~ComponentModel() override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    /* Refusals leave rows unchanged. A nested edit during any notification
     * returns BUSY without another signal. A wrong-thread call returns
     * INVALID_STATE without touching the registry or emitting a signal.
     * Queue work onto the model thread; this check is not a thread-safe API. */
    UmiStatus appendButton(const QString &id, const QString &text);

signals:
    void editRefused(int status);

private:
    UmiStatus refuse(UmiStatus status);
    std::unique_ptr<UmiUiComponentRegistry> registry_;
    bool publishing_ = false;
};

#endif
