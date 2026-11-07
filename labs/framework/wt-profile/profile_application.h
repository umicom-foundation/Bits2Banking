/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/framework/wt-profile/profile_application.h
 *
 * PURPOSE:
 *   Expose the Wt application factory while keeping validation in Framework C.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
#ifndef BTB_WT_PROFILE_APPLICATION_H
#define BTB_WT_PROFILE_APPLICATION_H
#include <Wt/WApplication.h>
#include <memory>
std::unique_ptr<Wt::WApplication> CreateProfileApplication(const Wt::WEnvironment &environment);
#endif
