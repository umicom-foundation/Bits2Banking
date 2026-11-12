/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/framework/order-lifecycle/execution.c
 *
 * PURPOSE:
 *   Demonstrate local fills, retained execution identity and cancellation through the shared workspace.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/


#include <stdio.h>
#include <string.h>
#include "umicom/trading/trading.h"

/* Always release the opaque owner, including when a lesson assertion fails.
 * Assertions stay active in release builds so an example never silently skips
 * the Framework calls that establish its result. */
#define REQUIRE_EXECUTION(condition) do { if (!(condition)) { \
    fprintf(stderr, "Expected condition failed at line %d: %s\n", __LINE__, #condition); \
    result = 1; goto finish; \
} } while (0)

/* The original fill-only client is retained for review. The extended client can also observe a capability refusal before order creation, using the same workspace instead of duplicating its policy. The previous implementation is retained for review. */
#if 0
int main(int argc, char **argv)
{
    const char *mode = argc == 2 ? argv[1] : "";
    if (strcmp(mode, "partial") && strcmp(mode, "replay") &&
        strcmp(mode, "conflict") && strcmp(mode, "cancel") &&
        strcmp(mode, "filled") && strcmp(mode, "tiny") &&
        strcmp(mode, "overfill") && strcmp(mode, "invalid")) {
        fputs("Usage: btb-order-execution partial|replay|conflict|cancel|filled|tiny|overfill|invalid\n", stderr);
        return 2;
    }
    int result = 0;
    UmiTradingWorkspace *workspace = NULL;
    UmiTradingWorkspaceConfig config = umi_trading_workspace_config_default();
    UmiInstrument instrument = {0};
    UmiRiskDecision decision;
    UmiTradingWorkspaceSnapshot before, after;
    UmiPosition position;
    UmiExecutionReport report = {0};
    const double requested = !strcmp(mode, "tiny") ? 0x1p-40 : 2.0;
    /* Fixed synthetic identifiers include their terminating byte. Interactive
     * clients must separately validate variable input before constructing them. */
    memcpy(instrument.instrument_id.value, "LESSON.ASSET", sizeof "LESSON.ASSET");
    memcpy(instrument.symbol, "LESSON", sizeof "LESSON");
    memcpy(instrument.venue, "LOCAL", sizeof "LOCAL");
    memcpy(instrument.currency.code, "GBP", sizeof "GBP");
    instrument.multiplier = 1.0;
    config.risk_limit = (UmiRiskLimit){1000.0, 1000000.0, 1000.0, 1000000.0};
    REQUIRE_EXECUTION(umi_trading_workspace_create(&config, &workspace) == UMI_STATUS_OK);
    REQUIRE_EXECUTION(umi_trading_workspace_add_instrument(workspace, &instrument) == UMI_STATUS_OK);
    REQUIRE_EXECUTION(umi_trading_workspace_set_health(workspace, 1, 0, 1) == UMI_STATUS_OK);
    REQUIRE_EXECUTION(umi_trading_workspace_set_draft_quantity(workspace, requested) == UMI_STATUS_OK);
    REQUIRE_EXECUTION(umi_trading_workspace_set_draft_prices(workspace, 10.0, 0.0) == UMI_STATUS_OK);
    REQUIRE_EXECUTION(umi_trading_workspace_submit_order(workspace, 1000, &decision) == UMI_STATUS_OK);
    REQUIRE_EXECUTION(umi_trading_workspace_snapshot(workspace, &before) == UMI_STATUS_OK);
    memcpy(report.execution_id.value, "LESSON-FILL-1", sizeof "LESSON-FILL-1");
    /* The selected identifier is copied from an admitted Framework snapshot;
     * the report owns its bytes and does not borrow a pointer into the owner. */
    REQUIRE_EXECUTION(strlen(before.selected_order_id) < sizeof(report.client_order_id.value));
    memcpy(report.client_order_id.value, before.selected_order_id, strlen(before.selected_order_id) + 1U);
    report.fill_quantity = requested / 2.0;
    report.fill_price = 10.0; report.event_time_ms = 1001;
    REQUIRE_EXECUTION(umi_trading_workspace_record_execution(workspace, &report) == UMI_STATUS_OK);
    REQUIRE_EXECUTION(umi_trading_workspace_snapshot(workspace, &before) == UMI_STATUS_OK);
    REQUIRE_EXECUTION(before.execution_count == 1U && before.position_count == 1U);
    REQUIRE_EXECUTION(umi_trading_workspace_position_at(workspace, 0U, &position) == UMI_STATUS_OK);
    REQUIRE_EXECUTION(position.quantity == requested / 2.0 && position.average_price == 10.0);
    puts("One partial fill retained; position contains only the executed quantity.");

    UmiStatus expected = UMI_STATUS_OK;
    int publishes = 0;
    if (!strcmp(mode, "partial") || !strcmp(mode, "tiny")) goto finish;
    if (!strcmp(mode, "conflict")) { report.fill_price = 11.0; expected = UMI_STATUS_ALREADY_EXISTS; }
    else if (!strcmp(mode, "cancel")) {
        REQUIRE_EXECUTION(umi_trading_workspace_cancel_selected_order(workspace) == UMI_STATUS_OK);
        REQUIRE_EXECUTION(umi_trading_workspace_snapshot(workspace, &before) == UMI_STATUS_OK);
        REQUIRE_EXECUTION(umi_trading_workspace_cancel_selected_order(workspace) == UMI_STATUS_OK);
        REQUIRE_EXECUTION(umi_trading_workspace_record_execution(workspace, &report) == UMI_STATUS_OK);
        strcpy(report.execution_id.value, "LESSON-FILL-2");
        expected = UMI_STATUS_INVALID_STATE;
    } else if (!strcmp(mode, "filled")) {
        strcpy(report.execution_id.value, "LESSON-FILL-2"); publishes = 1;
    } else if (!strcmp(mode, "overfill")) {
        strcpy(report.execution_id.value, "LESSON-FILL-2");
        report.fill_quantity = requested; expected = UMI_STATUS_INVALID_ARGUMENT;
    } else if (!strcmp(mode, "invalid")) {
        strcpy(report.execution_id.value, "LESSON-FILL-2");
        report.fill_quantity = 0.0; expected = UMI_STATUS_INVALID_ARGUMENT;
    }
    REQUIRE_EXECUTION(umi_trading_workspace_record_execution(workspace, &report) == expected);
    REQUIRE_EXECUTION(umi_trading_workspace_snapshot(workspace, &after) == UMI_STATUS_OK);
    REQUIRE_EXECUTION(after.revision == before.revision + (publishes ? 1U : 0U));
    REQUIRE_EXECUTION(after.execution_count == before.execution_count + (publishes ? 1U : 0U));
    REQUIRE_EXECUTION(umi_trading_workspace_position_at(workspace, 0U, &position) == UMI_STATUS_OK);
    REQUIRE_EXECUTION(position.quantity == (publishes ? requested : requested / 2.0));
    if (publishes) {
        before = after;
        REQUIRE_EXECUTION(umi_trading_workspace_record_execution(workspace, &report) == UMI_STATUS_OK);
        REQUIRE_EXECUTION(umi_trading_workspace_snapshot(workspace, &after) == UMI_STATUS_OK);
        REQUIRE_EXECUTION(after.revision == before.revision && after.execution_count == 2U);
    }
    printf("Scenario %s retained the expected revision, evidence and position.\n", mode);
finish:
    umi_trading_workspace_destroy(workspace);
    if (result == 0) puts("Local demonstration complete; no broker transport or settlement was used.");
    return result;
}

#endif
int main(int argc, char **argv)
{
    const char *mode = argc == 2 ? argv[1] : "";
    if (strcmp(mode, "partial") && strcmp(mode, "replay") &&
        strcmp(mode, "conflict") && strcmp(mode, "cancel") &&
        strcmp(mode, "filled") && strcmp(mode, "tiny") &&
        strcmp(mode, "overfill") && strcmp(mode, "invalid") &&
        strcmp(mode, "policy-ioc") && strcmp(mode, "policy-fok")) {
        fputs("Usage: btb-order-execution partial|replay|conflict|cancel|filled|tiny|overfill|invalid|policy-ioc|policy-fok\n", stderr);
        return 2;
    }
    int result = 0;
    UmiTradingWorkspace *workspace = NULL;
    UmiTradingWorkspaceConfig config = umi_trading_workspace_config_default();
    UmiInstrument instrument = {0};
    UmiRiskDecision decision;
    UmiTradingWorkspaceSnapshot before, after;
    UmiPosition position;
    UmiExecutionReport report = {0};
    const double requested = !strcmp(mode, "tiny") ? 0x1p-40 : 2.0;
    /* Fixed synthetic identifiers include their terminating byte. Interactive
     * clients must separately validate variable input before constructing them. */
    memcpy(instrument.instrument_id.value, "LESSON.ASSET", sizeof "LESSON.ASSET");
    memcpy(instrument.symbol, "LESSON", sizeof "LESSON");
    memcpy(instrument.venue, "LOCAL", sizeof "LOCAL");
    memcpy(instrument.currency.code, "GBP", sizeof "GBP");
    instrument.multiplier = 1.0;
    config.risk_limit = (UmiRiskLimit){1000.0, 1000000.0, 1000.0, 1000000.0};
    REQUIRE_EXECUTION(umi_trading_workspace_create(&config, &workspace) == UMI_STATUS_OK);
    REQUIRE_EXECUTION(umi_trading_workspace_add_instrument(workspace, &instrument) == UMI_STATUS_OK);
    REQUIRE_EXECUTION(umi_trading_workspace_set_health(workspace, 1, 0, 1) == UMI_STATUS_OK);
    REQUIRE_EXECUTION(umi_trading_workspace_set_draft_quantity(workspace, requested) == UMI_STATUS_OK);
    REQUIRE_EXECUTION(umi_trading_workspace_set_draft_prices(workspace, 10.0, 0.0) == UMI_STATUS_OK);
    if (!strcmp(mode, "policy-ioc") || !strcmp(mode, "policy-fok")) {
        UmiTimeInForce tif = !strcmp(mode, "policy-ioc") ? UMI_TIF_IOC : UMI_TIF_FOK;
        REQUIRE_EXECUTION(umi_trading_workspace_set_draft_type(workspace, UMI_ORDER_LIMIT, tif) == UMI_STATUS_OK);
        REQUIRE_EXECUTION(umi_trading_workspace_snapshot(workspace, &before) == UMI_STATUS_OK);
        REQUIRE_EXECUTION(!before.can_submit_order);
        REQUIRE_EXECUTION(UmiTradingWorkspacePreviewOrderAt(workspace, 1000, &decision) == UMI_STATUS_NOT_IMPLEMENTED);
        REQUIRE_EXECUTION(!decision.allowed);
        REQUIRE_EXECUTION(umi_trading_workspace_snapshot(workspace, &after) == UMI_STATUS_OK);
        REQUIRE_EXECUTION(after.revision == before.revision + 1U);
        before = after;
        REQUIRE_EXECUTION(umi_trading_workspace_submit_order(workspace, 1000, &decision) == UMI_STATUS_NOT_IMPLEMENTED);
        REQUIRE_EXECUTION(!decision.allowed);
        REQUIRE_EXECUTION(umi_trading_workspace_snapshot(workspace, &after) == UMI_STATUS_OK);
        REQUIRE_EXECUTION(after.revision == before.revision + 1U);
        REQUIRE_EXECUTION(after.order_count == 0U && after.execution_count == 0U && after.position_count == 0U);
        REQUIRE_EXECUTION(after.draft_order.tif == tif && !after.can_submit_order);
        UmiPretradeRiskEvidence evidence;
        REQUIRE_EXECUTION(UmiTradingWorkspaceRiskEvidence(workspace, &evidence) == UMI_STATUS_OK);
        REQUIRE_EXECUTION(!evidence.decision.allowed && !evidence.hasValuation);
        puts("Unsupported local policy explained; draft retained and no order created.");
        goto finish;
    }
    REQUIRE_EXECUTION(umi_trading_workspace_submit_order(workspace, 1000, &decision) == UMI_STATUS_OK);
    REQUIRE_EXECUTION(umi_trading_workspace_snapshot(workspace, &before) == UMI_STATUS_OK);
    memcpy(report.execution_id.value, "LESSON-FILL-1", sizeof "LESSON-FILL-1");
    /* The selected identifier is copied from an admitted Framework snapshot;
     * the report owns its bytes and does not borrow a pointer into the owner. */
    REQUIRE_EXECUTION(strlen(before.selected_order_id) < sizeof(report.client_order_id.value));
    memcpy(report.client_order_id.value, before.selected_order_id, strlen(before.selected_order_id) + 1U);
    report.fill_quantity = requested / 2.0;
    report.fill_price = 10.0; report.event_time_ms = 1001;
    REQUIRE_EXECUTION(umi_trading_workspace_record_execution(workspace, &report) == UMI_STATUS_OK);
    REQUIRE_EXECUTION(umi_trading_workspace_snapshot(workspace, &before) == UMI_STATUS_OK);
    REQUIRE_EXECUTION(before.execution_count == 1U && before.position_count == 1U);
    REQUIRE_EXECUTION(umi_trading_workspace_position_at(workspace, 0U, &position) == UMI_STATUS_OK);
    REQUIRE_EXECUTION(position.quantity == requested / 2.0 && position.average_price == 10.0);
    puts("One partial fill retained; position contains only the executed quantity.");

    UmiStatus expected = UMI_STATUS_OK;
    int publishes = 0;
    if (!strcmp(mode, "partial") || !strcmp(mode, "tiny")) goto finish;
    if (!strcmp(mode, "conflict")) { report.fill_price = 11.0; expected = UMI_STATUS_ALREADY_EXISTS; }
    else if (!strcmp(mode, "cancel")) {
        REQUIRE_EXECUTION(umi_trading_workspace_cancel_selected_order(workspace) == UMI_STATUS_OK);
        REQUIRE_EXECUTION(umi_trading_workspace_snapshot(workspace, &before) == UMI_STATUS_OK);
        REQUIRE_EXECUTION(umi_trading_workspace_cancel_selected_order(workspace) == UMI_STATUS_OK);
        REQUIRE_EXECUTION(umi_trading_workspace_record_execution(workspace, &report) == UMI_STATUS_OK);
        strcpy(report.execution_id.value, "LESSON-FILL-2");
        expected = UMI_STATUS_INVALID_STATE;
    } else if (!strcmp(mode, "filled")) {
        strcpy(report.execution_id.value, "LESSON-FILL-2"); publishes = 1;
    } else if (!strcmp(mode, "overfill")) {
        strcpy(report.execution_id.value, "LESSON-FILL-2");
        report.fill_quantity = requested; expected = UMI_STATUS_INVALID_ARGUMENT;
    } else if (!strcmp(mode, "invalid")) {
        strcpy(report.execution_id.value, "LESSON-FILL-2");
        report.fill_quantity = 0.0; expected = UMI_STATUS_INVALID_ARGUMENT;
    }
    REQUIRE_EXECUTION(umi_trading_workspace_record_execution(workspace, &report) == expected);
    REQUIRE_EXECUTION(umi_trading_workspace_snapshot(workspace, &after) == UMI_STATUS_OK);
    REQUIRE_EXECUTION(after.revision == before.revision + (publishes ? 1U : 0U));
    REQUIRE_EXECUTION(after.execution_count == before.execution_count + (publishes ? 1U : 0U));
    REQUIRE_EXECUTION(umi_trading_workspace_position_at(workspace, 0U, &position) == UMI_STATUS_OK);
    REQUIRE_EXECUTION(position.quantity == (publishes ? requested : requested / 2.0));
    if (publishes) {
        before = after;
        REQUIRE_EXECUTION(umi_trading_workspace_record_execution(workspace, &report) == UMI_STATUS_OK);
        REQUIRE_EXECUTION(umi_trading_workspace_snapshot(workspace, &after) == UMI_STATUS_OK);
        REQUIRE_EXECUTION(after.revision == before.revision && after.execution_count == 2U);
    }
    printf("Scenario %s retained the expected revision, evidence and position.\n", mode);
finish:
    umi_trading_workspace_destroy(workspace);
    if (result == 0) puts("Local demonstration complete; no broker transport or settlement was used.");
    return result;
}
