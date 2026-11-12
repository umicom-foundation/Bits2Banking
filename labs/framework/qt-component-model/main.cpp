/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/framework/qt-component-model/main.cpp
 *
 * PURPOSE:
 *   Demonstrate the Framework-backed Qt model without launching a window.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include "component_model.h"
#include <QCoreApplication>
#include <QTextStream>
#include <QVariant>

int main(int argc, char **argv)
{
    QCoreApplication application(argc, argv);
    QCoreApplication::setApplicationName("Umicom component model laboratory");
    ComponentModel model;
    if (model.appendButton(QStringLiteral("save"), QStringLiteral("Save")) != UMI_STATUS_OK)
        return 1;
    QTextStream output(stdout);
    output << model.data(model.index(0, 0), ComponentModel::IdRole).toString()
           << ": " << model.data(model.index(0, 0)).toString() << '\n';
    const UmiStatus duplicate =
        model.appendButton(QStringLiteral("save"), QStringLiteral("Overwrite"));
    output << "Duplicate status: " << static_cast<int>(duplicate)
           << "; rows: " << model.rowCount() << '\n';
    return duplicate == UMI_STATUS_ALREADY_EXISTS && model.rowCount() == 1 ? 0 : 2;
}
