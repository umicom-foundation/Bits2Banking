/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/framework/qt-profile/main.cpp
 *
 * PURPOSE:
 *   Run the optional Qt profile-name laboratory with an ordinary event loop.
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
#include <QWidget>
int main(int argc, char **argv)
{
    QApplication application(argc, argv);
    QWidget window;
    PopulateProfileWindow(&window);
    window.resize(520, 220);
    window.show();
    return application.exec();
}
