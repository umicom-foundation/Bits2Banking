/*-----------------------------------------------------------------------------
 * Bits2Banking | Umicom Foundation
 * File: labs/native/http-loopback-server/test_progress.c
 * PURPOSE: Verify response accounting on HEAD, partial writes and disconnect.
 * AUTHOR: Sammy Hegab | LICENCE: MIT
 *---------------------------------------------------------------------------*/
#include "response_progress.h"
#include <stdio.h>
#include <string.h>
#define CHECK(condition) do { if (!(condition)) { \
    fprintf(stderr, "FAIL %s:%d: %s\n", __FILE__, __LINE__, #condition); return 1; \
} } while (0)
static int Completion(void)
{
    BtbResponseProgress p = {0};
    CHECK(!BtbResponseProgressBegin(&p, 0U, 0U));
    CHECK(BtbResponseProgressBegin(&p, 80U, 20000U));
    CHECK(!BtbResponseProgressComplete(&p));
    CHECK(BtbResponseProgressAdvance(&p, BTB_RESPONSE_HEADER_PART, 30U));
    CHECK(!BtbResponseProgressAdvance(&p, BTB_RESPONSE_BODY_PART, 1U));
    CHECK(!BtbResponseProgressAdvance(&p, BTB_RESPONSE_HEADER_PART, 51U));
    CHECK(p.sentHeaders == 30U);
    CHECK(BtbResponseProgressAdvance(&p, BTB_RESPONSE_HEADER_PART, 50U));
    CHECK(p.phase == BTB_RESPONSE_BODY);
    CHECK(BtbResponseProgressAdvance(&p, BTB_RESPONSE_BODY_PART, 8192U));
    CHECK(!BtbResponseProgressComplete(&p));
    CHECK(BtbResponseProgressAdvance(&p, BTB_RESPONSE_BODY_PART, 11808U));
    CHECK(BtbResponseProgressComplete(&p));
    CHECK(!BtbResponseProgressAdvance(&p, BTB_RESPONSE_BODY_PART, 1U));
    BtbResponseProgressFail(&p);
    CHECK(BtbResponseProgressComplete(&p));
    /* HEAD advertises the full Content-Length, but has zero wire-body bytes. */
    CHECK(BtbResponseProgressBegin(&p, 82U, 0U));
    CHECK(BtbResponseProgressAdvance(&p, BTB_RESPONSE_HEADER_PART, 82U));
    CHECK(BtbResponseProgressComplete(&p));
    CHECK(p.sentBody == 0U);
    return 0;
}
static int Disconnect(void)
{
    BtbResponseProgress p = {0};
    CHECK(BtbResponseProgressBegin(&p, 60U, 2048U));
    CHECK(BtbResponseProgressAdvance(&p, BTB_RESPONSE_HEADER_PART, 60U));
    CHECK(BtbResponseProgressAdvance(&p, BTB_RESPONSE_BODY_PART, 100U));
    BtbResponseProgressFail(&p);
    CHECK(p.phase == BTB_RESPONSE_FAILED);
    CHECK(!BtbResponseProgressComplete(&p));
    CHECK(!BtbResponseProgressAdvance(&p, BTB_RESPONSE_BODY_PART, 1948U));
    CHECK(p.sentBody == 100U);
    CHECK(BtbResponseProgressBegin(&p, 50U, 0U));
    BtbResponseProgressFail(&p);
    CHECK(!BtbResponseProgressComplete(&p));
    CHECK(!BtbResponseProgressAdvance(&p, BTB_RESPONSE_HEADER_PART, 50U));
    return 0;
}
int main(int argc, char **argv)
{
    if (argc != 2) return 2;
    if (strcmp(argv[1], "completion") == 0) return Completion();
    if (strcmp(argv[1], "disconnect") == 0) return Disconnect();
    return 2;
}
