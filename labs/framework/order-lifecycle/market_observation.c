/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/framework/order-lifecycle/market_observation.c
 *
 * PURPOSE:
 *   Demonstrate market observations and protective controls through public Framework owners without external trading.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/


#include <math.h>
#include <stdio.h>
#include <string.h>
#include "umicom/trading/trading.h"
#include "umicom/trading_ui/action_controller.h"

/* These checks remain active in optimized builds. One cleanup path releases
 * the workspace; the client never reads private owner memory or resets counters. */
#define OBSERVE_CHECK(x) do { if (!(x)) { fprintf(stderr, "%s:%d: %s\n", __FILE__, __LINE__, #x); result=1; goto done; } } while(0)

static UmiInstrument SyntheticInstrument(void)
{
    UmiInstrument instrument={0};
    strcpy(instrument.instrument_id.value,"LAB.MARKET");
    strcpy(instrument.symbol,"LAB");
    strcpy(instrument.venue,"SYNTHETIC");
    strcpy(instrument.currency.code,"USD");
    instrument.multiplier=1.0;
    return instrument;
}
static UmiStatus PublicPrint(UmiTradingWorkspace *workspace, UmiInstrument instrument,
    uint64_t sequence, double price)
{
    UmiTradeTick tick={0};tick.instrument=instrument;tick.price=price;tick.size=2.0;tick.event_time_ms=1000;
    UmiTradingTradeTapeRecord record;
    UmiStatus status=umi_trading_trade_tape_record_init(&record,sequence,&tick,
        UMI_TRADING_TRADE_DIRECTION_BUYER_INITIATED,"synthetic");
    return status==UMI_STATUS_OK?umi_trading_workspace_update_trade(workspace,&record):status;
}
int main(int argc,char **argv)
{
    static const char *scenarios[]={"depth","invalid-depth","metadata","tape","alerts","remove","protect","draft"};
    if(argc!=2){fputs("Usage: btb-market-observation depth|invalid-depth|metadata|tape|alerts|remove|protect|draft\n",stderr);return 2;}
    int known=0;for(size_t i=0;i<sizeof(scenarios)/sizeof(scenarios[0]);++i)if(!strcmp(argv[1],scenarios[i]))known=1;
    if(!known)return 2;
    const char *scenario=argv[1];int result=0;
    UmiTradingWorkspace *workspace=NULL;
    UmiTradingWorkspaceConfig config=umi_trading_workspace_config_default();
    config.risk_limit=(UmiRiskLimit){1000.0,1.0e12,5000.0,1.0e12};
    UmiInstrument instrument=SyntheticInstrument();
    OBSERVE_CHECK(umi_trading_workspace_create(&config,&workspace)==UMI_STATUS_OK);
    OBSERVE_CHECK(umi_trading_workspace_add_instrument(workspace,&instrument)==UMI_STATUS_OK);
    OBSERVE_CHECK(umi_trading_workspace_set_health(workspace,1,0,1)==UMI_STATUS_OK);
    UmiQuote quote={0};quote.instrument=instrument;quote.bid=99;quote.ask=101;quote.event_time_ms=1000;
    OBSERVE_CHECK(umi_trading_workspace_update_quote(workspace,&quote)==UMI_STATUS_OK);
    UmiTradingWorkspaceSnapshot before,after;
    OBSERVE_CHECK(umi_trading_workspace_snapshot(workspace,&before)==UMI_STATUS_OK);
    if(!strcmp(scenario,"depth")||!strcmp(scenario,"invalid-depth")||!strcmp(scenario,"metadata")) {
        UmiMarketDepth depth={0};depth.instrument=instrument;depth.bid_count=1;depth.ask_count=1;
        depth.bids[0]=(UmiDepthLevel){99,4};depth.asks[0]=(UmiDepthLevel){101,3};depth.event_time_ms=1000;
        if(!strcmp(scenario,"invalid-depth"))depth.bids[0].size=NAN;
        if(!strcmp(scenario,"metadata"))depth.instrument.multiplier=2.0;
        int accepted=!strcmp(scenario,"depth");
        OBSERVE_CHECK(umi_market_depth_valid(&depth)==(strcmp(scenario,"invalid-depth")!=0));
        UmiStatus status=umi_trading_workspace_update_depth(workspace,&depth);
        OBSERVE_CHECK(status==(accepted?UMI_STATUS_OK:UMI_STATUS_INVALID_ARGUMENT));
        OBSERVE_CHECK(umi_trading_workspace_snapshot(workspace,&after)==UMI_STATUS_OK);
        OBSERVE_CHECK(after.revision==before.revision+(accepted?1U:0U));
        OBSERVE_CHECK(after.has_depth==accepted);
    } else if(!strcmp(scenario,"tape")) {
        OBSERVE_CHECK(PublicPrint(workspace,instrument,1,100)==UMI_STATUS_OK);
        OBSERVE_CHECK(umi_trading_workspace_set_trade_tape_paused(workspace,1)==UMI_STATUS_OK);
        OBSERVE_CHECK(PublicPrint(workspace,instrument,3,102)==UMI_STATUS_OK);
        OBSERVE_CHECK(umi_trading_workspace_snapshot(workspace,&after)==UMI_STATUS_OK);
        OBSERVE_CHECK(after.trade_tape.retained_count==2U && after.trade_tape.missing_sequence_count==1U);
        OBSERVE_CHECK(after.selected_trade_count==1U && after.selected_latest_trade.sequence==1U);
        OBSERVE_CHECK(after.execution_count==0U && after.position_count==0U);
        OBSERVE_CHECK(umi_trading_workspace_set_trade_tape_paused(workspace,0)==UMI_STATUS_OK);
        OBSERVE_CHECK(umi_trading_workspace_snapshot(workspace,&after)==UMI_STATUS_OK);
        OBSERVE_CHECK(after.selected_trade_count==2U && after.selected_latest_trade.sequence==3U);
    } else if(!strcmp(scenario,"alerts")||!strcmp(scenario,"remove")) {
        OBSERVE_CHECK(umi_trading_workspace_add_price_alert(workspace,"price-crossing",instrument.instrument_id.value,
            UMI_TRADING_PRICE_ALERT_CROSSES_ABOVE,101,1000)==UMI_STATUS_OK);
        quote.bid=101;quote.ask=103;quote.event_time_ms=2000;
        OBSERVE_CHECK(umi_trading_workspace_update_quote(workspace,&quote)==UMI_STATUS_OK);
        OBSERVE_CHECK(umi_trading_workspace_snapshot(workspace,&after)==UMI_STATUS_OK);
        OBSERVE_CHECK(after.active_alert_count==1U && after.unacknowledged_alert_count==1U);
        if(!strcmp(scenario,"alerts")) {
            OBSERVE_CHECK(umi_trading_workspace_acknowledge_price_alert(workspace,"price-crossing")==UMI_STATUS_OK);
            OBSERVE_CHECK(umi_trading_workspace_snapshot(workspace,&after)==UMI_STATUS_OK);
            OBSERVE_CHECK(after.alert_count==1U && after.active_alert_count==0U);
        } else {
            OBSERVE_CHECK(PublicPrint(workspace,instrument,1,102)==UMI_STATUS_OK);
            OBSERVE_CHECK(umi_trading_workspace_remove_instrument(workspace,instrument.instrument_id.value)==UMI_STATUS_OK);
            OBSERVE_CHECK(umi_trading_workspace_snapshot(workspace,&after)==UMI_STATUS_OK);
            OBSERVE_CHECK(after.market_count==0U && after.alert_count==0U && after.trade_tape.retained_count==0U);
        }
    } else if(!strcmp(scenario,"protect")) {
        UmiTradingUiController controller;
        OBSERVE_CHECK(umi_trading_ui_controller_init(&controller,workspace,NULL)==UMI_STATUS_OK);
        OBSERVE_CHECK(umi_trading_ui_controller_engage_kill_switch(&controller,"Synthetic course exercise")==UMI_STATUS_OK);
        OBSERVE_CHECK(umi_trading_workspace_snapshot(workspace,&after)==UMI_STATUS_OK);
        OBSERVE_CHECK(after.kill_switch_engaged && !after.can_submit_order);
        OBSERVE_CHECK(umi_trading_ui_controller_reset_kill_switch(&controller)==UMI_STATUS_OK);
        OBSERVE_CHECK(controller.state.last_status==UMI_STATUS_OK);
        OBSERVE_CHECK(umi_trading_workspace_snapshot(workspace,&after)==UMI_STATUS_OK);
        OBSERVE_CHECK(!after.kill_switch_engaged);
    } else {
        UmiRiskDecision decision;UmiPretradeRiskEvidence evidence;
        OBSERVE_CHECK(UmiTradingWorkspacePreviewOrderAt(workspace,1000,&decision)==UMI_STATUS_OK && decision.allowed);
        OBSERVE_CHECK(UmiTradingWorkspaceRiskEvidence(workspace,&evidence)==UMI_STATUS_OK);
        OBSERVE_CHECK(umi_trading_workspace_set_draft_quantity(workspace,2.0)==UMI_STATUS_OK);
        OBSERVE_CHECK(UmiTradingWorkspaceRiskEvidence(workspace,&evidence)==UMI_STATUS_NOT_FOUND);
        OBSERVE_CHECK(umi_trading_workspace_snapshot(workspace,&after)==UMI_STATUS_OK);
        OBSERVE_CHECK(after.draft_order.quantity==2.0 && !after.has_draft_risk);
    }
    printf("Completed synthetic %s scenario through Framework.\n",scenario);
done:
    if(workspace!=NULL)umi_trading_workspace_destroy(workspace);
    return result;
}
