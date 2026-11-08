/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: forecast_cpp.cpp
 *
 * PURPOSE:
 *   Demonstrate C++ consumption of the existing Framework C treasury contract.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
#include <cinttypes>
#include <cstdio>
#include "umicom/finance/treasury/cash_forecast.h"

/* C++ is used because this lesson teaches a C++ consumer. It introduces no
 * alternative finance implementation or ownership wrapper around this value. */
int main()
{
    UmiTreasuryCashForecast forecast{};
    if (umi_treasury_cash_forecast_init(&forecast, "cpp-classroom", 0, 125000, 140000) != UMI_STATUS_OK)
        return 1;
    const int64_t net = umi_treasury_cash_forecast_net_minor(&forecast);
    if (net != -15000) return 2;
    return std::printf("%" PRId64 "\n", net) < 0 ? 3 : 0;
}
