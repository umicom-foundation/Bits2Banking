/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/framework/order-lifecycle/identity_lifetime.c
 *
 * PURPOSE:
 *   Demonstrate bounded watchlist lookup, zero-time quotas and per-instrument chart navigation through the installed C SDK.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "umicom/trading/trading.h"

#define REQUIRE(expression) do { \
    if (!(expression)) { \
        fprintf(stderr, "%s:%d: %s\n", __FILE__, __LINE__, #expression); \
        goto cleanup; \
    } \
} while (0)

/* Only synthetic input construction belongs here. All admission, quota and
 * navigation behavior stays in Framework so other clients share its rules. */
static UmiInstrument instrument(const char *id)
{
    UmiInstrument value = {0};
    (void)snprintf(value.instrument_id.value, sizeof(value.instrument_id.value), "%s", id);
    (void)snprintf(value.symbol, sizeof(value.symbol), "%s", "LAB");
    (void)snprintf(value.venue, sizeof(value.venue), "%s", "LOCAL");
    (void)snprintf(value.currency.code, sizeof(value.currency.code), "%s", "USD");
    value.multiplier = 1.0;
    return value;
}

static int watchlist_scenario(void)
{
    static UmiWatchlist list;
    static UmiWatchlist before;
    int result = EXIT_FAILURE;
    const UmiInstrument a = instrument("LAB.A"), b = instrument("LAB.B");
    umi_watchlist_init(&list);
    REQUIRE(umi_watchlist_add(&list, &a) == UMI_STATUS_OK);
    REQUIRE(umi_watchlist_add(&list, &b) == UMI_STATUS_OK);
    size_t index = SIZE_MAX;
    REQUIRE(umi_watchlist_find(&list, "LAB.A", &index) == UMI_STATUS_OK && index == 0U);
    /* A public caller-owned struct can hold bad retained data. The lab makes
     * one deliberate defect; applications must not bypass owner admission. */
    memset(list.instruments[1].symbol, 'x', sizeof(list.instruments[1].symbol));
    memcpy(&before, &list, sizeof(before));
    index = SIZE_MAX;
    REQUIRE(umi_watchlist_find(&list, "LAB.A", &index) == UMI_STATUS_INVALID_STATE);
    REQUIRE(index == SIZE_MAX);
    REQUIRE(umi_watchlist_add(&list, &a) == UMI_STATUS_INVALID_STATE);
    REQUIRE(memcmp(&before, &list, sizeof(before)) == 0);
    puts("A later malformed record refuses lookup and insertion without changing storage.");
    result = EXIT_SUCCESS;
cleanup:
    return result;
}

static int query_scenario(void)
{
    static UmiWatchlist list;
    int result = EXIT_FAILURE;
    const UmiInstrument a = instrument("LAB.A");
    umi_watchlist_init(&list);
    REQUIRE(umi_watchlist_add(&list, &a) == UMI_STATUS_OK);
    size_t index = SIZE_MAX;
    char query[UMI_FINANCE_ID_CAPACITY];
    memset(query, 'q', sizeof(query));
    REQUIRE(umi_watchlist_find(&list, query, &index) == UMI_STATUS_CAPACITY_EXCEEDED);
    REQUIRE(index == SIZE_MAX);
    REQUIRE(umi_watchlist_find(&list, "LAB.A", &list.count) == UMI_STATUS_INVALID_ARGUMENT);
    REQUIRE(list.count == 1U);
    REQUIRE(umi_watchlist_find(&list, "LAB.A", &index) == UMI_STATUS_OK && index == 0U);
    const UmiInstrument selected = list.instruments[index];
    REQUIRE(strcmp(selected.instrument_id.value, "LAB.A") == 0);
    puts("An unterminated query preserves output; an admitted lookup identifies LAB.A.");
    result = EXIT_SUCCESS;
cleanup:
    return result;
}

static int quota_scenario(void)
{
    int result = EXIT_FAILURE;
    UmiOrderThrottle throttle = {0};
    umi_order_throttle_init(&throttle, 2U, 1000);
    REQUIRE(umi_order_throttle_accept(&throttle, 0));
    REQUIRE(umi_order_throttle_accept(&throttle, 0));
    UmiOrderThrottle before;
    memcpy(&before, &throttle, sizeof(before));
    REQUIRE(!umi_order_throttle_accept(&throttle, 0));
    REQUIRE(!umi_order_throttle_accept(&throttle, 999));
    REQUIRE(memcmp(&before, &throttle, sizeof(before)) == 0);
    REQUIRE(umi_order_throttle_accept(&throttle, 1000));
    puts("Two attempts at zero are admitted; the third waits for the next window.");
    result = EXIT_SUCCESS;
cleanup:
    return result;
}

static int same_view(UmiChartNavigation a, UmiChartNavigation b)
{
    return a.visible_bars == b.visible_bars && a.anchor_ms == b.anchor_ms &&
           a.pinned == b.pinned && a.interval_ms == b.interval_ms;
}

static int navigation_scenario(void)
{
    int result = EXIT_FAILURE;
    UmiTradingWorkspace *workspace = NULL;
    const UmiTradingWorkspaceConfig config = umi_trading_workspace_config_default();
    const UmiInstrument a = instrument("LAB.A"), b = instrument("LAB.B");
    const UmiChartNavigation selected = {9U, 3000, 1, 900000U};
    const UmiChartNavigation defaults = {0};
    UmiChartNavigation observed = {0};
    REQUIRE(umi_trading_workspace_create(&config, &workspace) == UMI_STATUS_OK);
    REQUIRE(umi_trading_workspace_add_instrument(workspace, &a) == UMI_STATUS_OK);
    REQUIRE(umi_trading_workspace_add_instrument(workspace, &b) == UMI_STATUS_OK);
    REQUIRE(umi_trading_workspace_select_instrument(workspace, "LAB.B") == UMI_STATUS_OK);
    REQUIRE(UmiTradingWorkspaceSetChartNavigation(workspace, "LAB.B", &selected) == UMI_STATUS_OK);
    REQUIRE(umi_trading_workspace_remove_instrument(workspace, "LAB.A") == UMI_STATUS_OK);
    REQUIRE(UmiTradingWorkspaceGetChartNavigation(workspace, "LAB.B", &observed) == UMI_STATUS_OK);
    REQUIRE(same_view(observed, selected));
    REQUIRE(umi_trading_workspace_add_instrument(workspace, &a) == UMI_STATUS_OK);
    REQUIRE(umi_trading_workspace_select_instrument(workspace, "LAB.A") == UMI_STATUS_OK);
    REQUIRE(UmiTradingWorkspaceGetChartNavigation(workspace, "LAB.A", &observed) == UMI_STATUS_OK);
    REQUIRE(same_view(observed, defaults));
    puts("The surviving instrument keeps its chart view; the new instrument starts with defaults.");
    result = EXIT_SUCCESS;
cleanup:
    umi_trading_workspace_destroy(workspace);
    return result;
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        fputs("Usage: btb-identity-lifetime watchlist|query|quota|navigation\n", stderr);
        return EXIT_FAILURE;
    }
    if (strcmp(argv[1], "watchlist") == 0) return watchlist_scenario();
    if (strcmp(argv[1], "query") == 0) return query_scenario();
    if (strcmp(argv[1], "quota") == 0) return quota_scenario();
    if (strcmp(argv[1], "navigation") == 0) return navigation_scenario();
    fputs("Unknown scenario. Use watchlist, query, quota or navigation.\n", stderr);
    return EXIT_FAILURE;
}
