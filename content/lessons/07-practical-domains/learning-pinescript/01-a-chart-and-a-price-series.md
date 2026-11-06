# A chart and a price series

[Course contents](index.md) · [Next: Live bars and confirmed values](02-live-bars-and-confirmed-values.md)

## Begin with a picture of data

A price chart places time along the horizontal axis and price along the vertical axis. One candle summarises an interval, such as a minute or a day. Its open is the first recorded price, high and low are the interval's extremes, and close is the last recorded price. A series is a sequence of values indexed by bars, rather than one value for the whole chart.

You can trace this lesson on paper. To run the script, use TradingView's Pine Editor with an account and a chart you are entitled to view. The practical example targets Pine Script version 6. Pine Script is a separate charting language; it is not C and this lesson does not add a Pine interpreter to Umicom Trader.

## Draw a short moving average

An average adds several values and divides by how many there are. A moving average repeats that calculation over a window that moves along the series.

```text
Closing prices: 10, 12, 14, 16
Three-bar average at bar 3: (10 + 12 + 14) / 3 = 12
Three-bar average at bar 4: (12 + 14 + 16) / 3 = 14
```

Create a new indicator in the Pine Editor. Replace its example text with the following original script, save it under a name of your choice and use Add to chart. Menu placement can vary; the official Pine first-indicator guide explains the editor workflow.

```pine
//@version=6
indicator("Learning: three closing prices", overlay=true)
average = ta.sma(close, 3)
plot(average, title="Three-bar mean", color=color.blue)
```

`//@version=6` selects the language version. `indicator` declares a study; `overlay=true` puts it in the price pane. `close` supplies each bar's closing-price value. `ta.sma` calculates a simple moving average. The assignment gives that result the name `average`. `plot` draws the values using a blue line and a readable title.

At the start of a short series there may not yet be three available values. Do not invent zeros to fill that gap: zero would change the calculation. On an ordinary chart with enough history, expect a line that follows the prices more smoothly than the individual closes. Its actual numbers depend on the chart, not on the invented four-number example above.

## Connect the idea to Umicom

Framework's `include/umicom/chart/candle_study.h` defines native candle-study inputs and results. It describes volume-weighted averages, Bollinger bands and Donchian bands. Those are not all the same calculation as this simple mean. The reusable idea is to compute from an ordered series and then render the result; chart appearance must not decide the mathematics.

Read that header as a map, not as a requirement to understand every C declaration today. In particular, its `valid` flag describes whether a result can be used. Later native exercises can compare input candles and calculated samples without pretending that a visual resemblance proves numerical parity.

## Exercise

Use closing prices 8, 10, 12 and 18. Find the three-bar mean at the third and fourth bars. Change the script's window from 3 to 2 and calculate the final two-bar mean on paper.

## Answer and explanation

The third bar gives (8 + 10 + 12) / 3 = 10. The fourth gives (10 + 12 + 18) / 3 = 40 / 3, about 13.33. The final two-bar mean is (12 + 18) / 2 = 15. A shorter window reacts more strongly to the recent rise. That is a numerical property, not evidence of profitable trading.

## If the result is unexpected

Check the version line, spelling and whether you created an indicator. Check that the chart has enough bars. A line drawn behind candles can be difficult to see; inspect the indicator's displayed values too. Do not place orders for this exercise. Next, distinguish an unfinished bar from a completed one.

[Review the prerequisite course](../../../courses/learning-c/index.html).


## Source and further reading

[Read the related Umicom example](https://github.com/umicom-foundation/umicom-framework/blob/f00aa3eb0c165ab0ac0107f81e84e4602d79c170/include/umicom/chart/candle_study.h). Path: `Umicom-Applications/framework/include/umicom/chart/candle_study.h`. This reference connects the topic to the codebase; it does not imply a language runtime or adapter is implemented in Umicom.

[Technical reference](https://www.tradingview.com/pine-script-docs/primer/first-indicator/). Check the version requirements in the lesson before practical work.

[Read this lesson as HTML](../../../courses/learning-pinescript/lessons/01-a-chart-and-a-price-series.html).

[Course contents](index.md) · [Next: Live bars and confirmed values](02-live-bars-and-confirmed-values.md)

Sammy Hegab · Umicom Foundation · Original learning material.
