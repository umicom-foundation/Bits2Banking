/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/framework/qt-profile/profile_window.cpp
 *
 * PURPOSE:
 *   Translate Qt input into the shared C profile-name contract without duplicating validation.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
#include "profile_window.h"
/* The narrow contract avoids importing native account storage into this view.
 * Retain the former include for source comparison; the called API is unchanged. */
#if 0
#include "umicom/security/local_profile.h"
#endif
#include "umicom/security/profile_name.h"
#include <QByteArray>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

/* Qt owns the controls through their parent window. The connection context is
 * the same window, so closing its lifetime disconnects the callback. C++ is
 * confined to this Qt adapter; all name policy remains in Framework C. */
void PopulateProfileWindow(QWidget *window)
{
    window->setWindowTitle("Umicom - Profile name laboratory");
    QVBoxLayout *layout = new QVBoxLayout(window);
    QLabel *instruction = new QLabel("Choose a profile name: 3 to 48 ASCII letters, digits, - or _. Start with a letter.", window);
    instruction->setWordWrap(true);
    QLineEdit *input = new QLineEdit(window);
    input->setObjectName("profile-input");
    input->setAccessibleName("Profile name");
    QPushButton *check = new QPushButton("Check name", window);
    check->setObjectName("profile-check");
    QLabel *result = new QLabel("Enter a name, then choose Check name.", window);
    result->setObjectName("profile-result");
    result->setTextFormat(Qt::PlainText);
    result->setWordWrap(true);
    layout->addWidget(instruction);
    layout->addWidget(input);
    layout->addWidget(check);
    layout->addWidget(result);
    QObject::connect(check, &QPushButton::clicked, window, [input, result]() {
        const QByteArray bytes = input->text().toUtf8();
        char canonical[UMI_LOCAL_PROFILE_NAME_CAPACITY];
        const UmiStatus status = UmiLocalProfileNameBytes(bytes.constData(),
            static_cast<size_t>(bytes.size()), canonical);
        if (status == UMI_STATUS_OK) {
            result->setText(QString("Accepted name: ") + QString::fromUtf8(canonical));
        } else {
            result->setText("Name rejected. Use 3 to 48 ASCII letters, digits, - or _, starting with a letter.");
        }
    });
    QObject::connect(input, &QLineEdit::returnPressed, check, &QPushButton::click);
}
