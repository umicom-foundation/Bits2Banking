# Separate cash forecasts from valuations

Trace a fictional foreign-exchange obligation through dates, valuation, cash and settlement.

Lesson 2 of 2. Read [Start here](../../../../courses/framework-and-finance/start.html) first. No banking account or live connection is needed.

A **cash position** describes money observed at a particular time. A **cash forecast** estimates future receipts and payments. A **valuation** estimates what a contract is worth under stated assumptions. These answer different questions and should not share an unexplained “balance” label.

Suppose an account holds 1,000 units today, expects 300 tomorrow and must pay 800 tomorrow. The simple forecast ending balance is 500. If the receipt is delayed, the balance becomes 200. A forecast should retain its assumptions so both scenarios can be explained.

```text
opening 1,000 + expected receipt 300 − due payment 800 = forecast 500
opening 1,000 + delayed receipt   0 − due payment 800 = forecast 200
```

A **market snapshot** is the set of prices and rates observed for an evaluation. A model may use that snapshot to discount a future amount. For a simple teaching example, a future 100 multiplied by a discount factor of 0.98 gives a present value of 98. The factor and date convention must be explicit; 98 is not an observed bank balance.

## Build an evidence table

1. Use columns for amount, currency, expected date, source and confidence.
2. Enter the opening cash separately from future flows.
3. Create the delayed-receipt scenario without replacing the original forecast.
4. Record which market snapshot a valuation used.
5. Compare predicted and actual flows after the date passes.

More advanced models require calendars, day counts, curves and calibration. A calendar decides which days count as business days; a day-count convention measures a time interval for a calculation. Neither should be guessed from the computer's current date.

The source-reading task introduces Framework's cash-forecast contract. It is a starting point for inspecting what the current implementation represents, not a claim that a complete production pricing engine is qualified.

## Read a real Umicom source contract

In a local checkout, open `C:\umicom\Umicom-Applications\framework\include\umicom\finance\treasury\cash_forecast.h`. A **contract** states what an operation accepts, returns and promises. Read its comments before its implementation.

The following excerpt comes from that source file. The surrounding declarations and comments are part of the contract too.

```text
typedef struct UmiTreasuryCashForecast {
    char id[UMI_TREASURY_ID_CAPACITY];
    int64_t horizon_end_epoch_millis;
    int64_t inflow_minor;
    int64_t outflow_minor;
} UmiTreasuryCashForecast;
/**
 * Initialise treasury cash forecast from caller-provided values so later operations
 * receive a known state.
 */
UmiStatus umi_treasury_cash_forecast_init(UmiTreasuryCashForecast *value,
    const char *id,
    int64_t horizon_end_epoch_millis,
    int64_t inflow_minor,
```

1. Locate the file in your editor. You are reading it; do not edit your working product to complete this exercise.
2. Inspect cash_forecast.h and cash_position.h side by side. List the inputs each requires and identify any dates or currencies the caller must supply.
3. Write the input, expected result and a possible failure in your own words.

The source reference identifies an existing implementation or contract. It does not establish that an application has wired every operation, or that its build has passed. If your checkout differs, compare the current declarations and record the difference.

## Check your understanding

A valuation increased by 20. Must the bank account have received 20?

### Worked answer

No. A valuation can change because prices or assumptions changed. Cash changes need cash-flow or settlement evidence. The two may be connected by later events but are not interchangeable.

## Keep a learning checkpoint

Write one observation, one unanswered question and the result of the exercise. In Studio you may record a private checkpoint as explained in [Start here](../../../../courses/framework-and-finance/start.html#progress). Opening the page alone is not completion.

---

[Read this lesson in HTML](../../../../courses/framework-and-finance/treasury-operations/lessons/cash-and-valuations.html) · [Learning sequence](../../../../start/learning-sequence.md)
