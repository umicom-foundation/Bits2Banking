/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/framework/wt-profile/main.cpp
 *
 * PURPOSE:
 *   Start the Wt HTTP host with a separate application for each session.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
#include "profile_application.h"
int main(int argc, char **argv)
{
    return Wt::WRun(argc, argv, CreateProfileApplication);
}
