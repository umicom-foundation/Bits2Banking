/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/framework/qt-component-model/component_model.cpp
 *
 * PURPOSE:
 *   Translate Qt values and publication signals around the shared C component registry.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include "component_model.h"
#include <QByteArray>
#include <QScopedValueRollback>
#include <QThread>
#include <QVariant>
#include <new>

ComponentModel::ComponentModel(QObject *parent)
    : QAbstractListModel(parent),
      registry_(new (std::nothrow) UmiUiComponentRegistry)
{
    if (registry_) umi_ui_component_registry_init(registry_.get());
}

ComponentModel::~ComponentModel() = default;

int ComponentModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid() || !registry_) return 0;
    return static_cast<int>(registry_->count);
}

QVariant ComponentModel::data(const QModelIndex &index, int role) const
{
    if (!registry_ || !index.isValid() || index.model() != this ||
        index.column() != 0 || index.row() < 0 || index.row() >= rowCount())
        return {};
    const UmiUiComponentSpec &spec = registry_->items[index.row()];
    switch (role) {
    case Qt::DisplayRole:
    case TextRole: return QString::fromUtf8(spec.text);
    case IdRole: return QString::fromUtf8(spec.id);
    case KindRole: return static_cast<int>(spec.kind);
    default: return {};
    }
}

QHash<int, QByteArray> ComponentModel::roleNames() const
{
    auto roles = QAbstractListModel::roleNames();
    roles.insert(IdRole, "componentId");
    roles.insert(TextRole, "componentText");
    roles.insert(KindRole, "componentKind");
    return roles;
}

UmiStatus ComponentModel::refuse(UmiStatus status)
{
    emit editRefused(static_cast<int>(status));
    return status;
}

UmiStatus ComponentModel::appendButton(const QString &id, const QString &text)
{
    if (QThread::currentThread() != thread()) return UMI_STATUS_INVALID_STATE;
    if (publishing_) return UMI_STATUS_BUSY;
    /* Guard refusal notifications too: a listener must not turn a refused edit
     * into a different mutation before this operation has returned. */
    QScopedValueRollback<bool> publication(publishing_, true);
    if (!registry_) return refuse(UMI_STATUS_OUT_OF_MEMORY);
    /* The C setters accept terminated text. Reject embedded zeroes before
     * conversion so a valid prefix cannot hide the rest of a Qt string. */
    if (id.contains(QChar(0)) || text.contains(QChar(0)))
        return refuse(UMI_STATUS_INVALID_ARGUMENT);
    const QByteArray idBytes = id.toUtf8();
    const QByteArray textBytes = text.toUtf8();
    UmiUiComponentSpec spec = umi_ui_component_spec_default(UMI_UI_COMPONENT_BUTTON);
    UmiStatus status = umi_ui_component_spec_set_id(&spec, idBytes.constData());
    if (status == UMI_STATUS_OK)
        status = umi_ui_component_spec_set_text(&spec, textBytes.constData());
    if (status != UMI_STATUS_OK) return refuse(status);

    /* Prepare a separate owner. Framework performs admission before Qt announces
     * an insertion. Large registry storage stays off the call stack. */
    std::unique_ptr<UmiUiComponentRegistry> candidate(
        new (std::nothrow) UmiUiComponentRegistry(*registry_));
    if (!candidate) return refuse(UMI_STATUS_OUT_OF_MEMORY);
    status = umi_ui_component_registry_add(candidate.get(), &spec);
    if (status != UMI_STATUS_OK) return refuse(status);

    const int row = rowCount();
    beginInsertRows(QModelIndex(), row, row);
    registry_.swap(candidate); // No fallible policy work between the two signals.
    endInsertRows();
    // candidate now owns the old snapshot and releases it after notification.
    return UMI_STATUS_OK;
}
