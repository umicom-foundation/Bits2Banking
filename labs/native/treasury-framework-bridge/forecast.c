/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: forecast.c
 *
 * PURPOSE:
 *   Adapt a bounded decimal command to the existing Framework treasury service.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
#include <inttypes.h>
#include <stdio.h>
#include <stdint.h>
#include "umicom/finance/treasury/cash_forecast.h"

/* Transport grammar is deliberately narrower than strtoll: ASCII digits only,
 * no signs, whitespace or locale-dependent separators. Finance validation and
 * the calculation remain in Framework. */
static int read_minor(const char *text, int64_t *out)
{
    if (!text || !*text) return 0;
    uint64_t value = 0;
    for (size_t i = 0; text[i]; ++i) {
        if (i >= 19 || text[i] < '0' || text[i] > '9') return 0;
        const unsigned digit = (unsigned)(text[i] - '0');
        if (value > ((uint64_t)INT64_MAX - digit) / 10) return 0;
        value = value * 10 + digit;
    }
    *out = (int64_t)value;
    return 1;
}
int main(int argc, char **argv)
{
    int64_t inflow = 0, outflow = 0;
    if (argc != 3 || !read_minor(argv[1], &inflow) || !read_minor(argv[2], &outflow)) {
        fputs("Expected two nonnegative int64 amounts in the same currency and horizon.\n", stderr);
        return 2;
    }
    UmiTreasuryCashForecast forecast;
    if (umi_treasury_cash_forecast_init(&forecast, "classroom", 0, inflow, outflow) != UMI_STATUS_OK)
        return 3;
    if (printf("%" PRId64 "\n", umi_treasury_cash_forecast_net_minor(&forecast)) < 0)
        return 4;
    return fflush(stdout) == 0 ? 0 : 4;
}
