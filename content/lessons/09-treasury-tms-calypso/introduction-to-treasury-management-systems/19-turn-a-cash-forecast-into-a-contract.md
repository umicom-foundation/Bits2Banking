# Turn a cash forecast into a data contract

## From a business question to a program

Treasury asks whether cash will be available when obligations fall due. A program needs a more precise question: which account or scope, currency, date horizon, statuses and data cutoff? Without those fields, a number may be arithmetically correct but operationally misleading.

The supplied Treasury guide teaches the connection between front-office trades and downstream processing. Here we narrow that idea to one classroom forecast. We do not infer settlement or available funds from a trade's existence.

## Worked contract

Use one agreed GBP horizon with expected receipts of 125000 and payments of 140000 minor units. The net movement is -15000. If the opening available balance is 50000 and no other movements exist, the projected closing balance is 35000. The native lab computes only net movement; opening balance and availability policy are separate.

Umicom Framework's UmiTreasuryCashForecast stores an identifier, horizon and nonnegative inflow/outflow totals. It does not store currency. The caller must partition by currency before constructing it. The classroom executable uses a fixed identifier and zero horizon sentinel; do not mistake those values for a complete production forecast record.

## Follow the reusable service

~~~c
UmiTreasuryCashForecast forecast;
if (umi_treasury_cash_forecast_init(
        &forecast, "classroom", 0, 125000, 140000) != UMI_STATUS_OK)
    return 3;
~~~

The [native lab](https://github.com/umicom-foundation/Bits2Banking/tree/main/labs/native/treasury-framework-bridge) then calls the existing net-minor operation. Neither the C++ nor JVM examples introduce a second finance engine.

## Exercise and answer

A second receipt of 10000 USD arrives. Can you add it to GBP inflow? Answer: no. First separate currencies. Conversion requires an explicit rate, timestamp and rounding policy; the simple forecast contract does not perform it.

## Check before proceeding

Write down units, cutoff, horizon and included statuses beside every fixture. Preserve rejected records and missing-data indicators. The expected result -15000 validates a narrow arithmetic case, not a bank balance, funding recommendation or payment authorization.

[Course contents](index.md)
