/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/local-ai-routing/lab.h
 *
 * PURPOSE:
 *   Declare thin learning clients of existing Framework AI services.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
#ifndef BTB_LOCAL_AI_LAB_H
#define BTB_LOCAL_AI_LAB_H
int LabOffline(const char *scenario);
int LabLocal(const char *port, const char *model, const char *prompt);
#endif
