/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/framework/qt-profile/test_window.cpp
 *
 * PURPOSE:
 *   Exercise Qt input events through the real C validation callback.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
#include "profile_window.h"
#include <QApplication>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTest>
#include <QWidget>
#include <cstdio>

/* This checks widget event dispatch and displayed outcomes. It does not prove
 * packaging, operating-system focus or accessibility behaviour on every host. */
int main(int argc, char **argv)
{
    QApplication application(argc, argv);
    QWidget window;
    PopulateProfileWindow(&window);
    window.show();
    QLineEdit *input = window.findChild<QLineEdit *>("profile-input");
    QPushButton *check = window.findChild<QPushButton *>("profile-check");
    QLabel *result = window.findChild<QLabel *>("profile-result");
    if (!input || !check || !result) return 1;
    input->setFocus();
    QTest::keyClicks(input, "Alice_7");
    QTest::mouseClick(check, Qt::LeftButton);
    if (result->text() != "Accepted name: alice_7") return 2;
    input->setText("../../other");
    QTest::keyClick(input, Qt::Key_Return);
    if (!result->text().startsWith("Name rejected.")) return 3;
    input->setText(QString(48, QChar('A')));
    check->click();
    if (result->text() != QString("Accepted name: ") + QString(48, QChar('a'))) return 4;
    input->setText(QString(49, QChar('A')));
    check->click();
    if (!result->text().startsWith("Name rejected.")) return 5;
    input->setText(QString::fromUtf8("Al\xc3\xa9"));
    check->click();
    if (!result->text().startsWith("Name rejected.")) return 6;
    input->clear();
    check->click();
    if (!result->text().startsWith("Name rejected.")) return 7;
    std::puts("Profile widget event checks passed");
    return 0;
}
