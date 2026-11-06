# Live bars and confirmed values

[Course contents](index.md) · [Previous: A chart and a price series](01-a-chart-and-a-price-series.md)

## Why the last point can move

The previous lesson used completed sample bars. During an open market interval, new observations can change the current bar's price. An indicator can therefore show a different value later in the same bar. Historical bars and an unfinished real-time bar are not equivalent evidence.

Pine's execution model determines when the script runs and which state is retained. Read the official execution-model guide after tracing this small example. Here we concentrate on a simple rule: calculate the mean on every update, but publish a point only when the current bar is confirmed.

## Make confirmation visible

Save a separate copy of the previous indicator and replace it with:

```pine
//@version=6
indicator("Learning: confirmed mean", overlay=true)
average = ta.sma(close, 3)
confirmedAverage = barstate.isconfirmed ? average : na
plot(confirmedAverage, title="Confirmed three-bar mean", color=color.blue,
     style=plot.style_linebr)
```

The conditional expression `condition ? first : second` chooses its first result when the condition is true and its second result otherwise. `barstate.isconfirmed` supplies that condition. `na` means no available value. `plot.style_linebr` leaves a break where values are missing rather than deliberately joining across the missing sample.

The moving-average function is called on every calculation. We choose whether to display its result afterward. This keeps the time-series calculation separate from display policy.

## Trace the same interval twice

```text
Previous completed closes: 10, 12
Current bar, still open:   close 15 → mean 37 / 3 → hidden
Current bar, now complete: close 18 → mean 40 / 3 → displayed
```

The expected confirmed mean is about 13.33. Waiting for confirmation delays the information. It does not guarantee a successful trade or prevent every source of changing historical data. Provider corrections, other timeframes and different script logic need separate consideration. This introductory indicator does not request other timeframes or submit orders.

On a closed market, all visible bars may already be confirmed, so both indicators can look alike. That is not proof that the rule is unused. Compare their logic and use the paper trace when live observations are unavailable. A platform's replay and alert facilities are later topics, with their own behaviour to verify.

## Connect to the native chart model

Framework's candle-study contract requires increasing candle times and finite price and volume inputs. It also tells consumers to recompute after corrections or timeframe changes. This is a useful design lesson: a chart should explain which observations its values came from. It must not silently label provisional or simulated data as final market evidence.

This comparison teaches data handling. It does not claim that Umicom executes the Pine script or that the two implementations have matching indicators.

## Exercise

The last completed closes are 6 and 9. An unfinished bar first shows 12 and later closes at 15. Calculate both means. Which value does the confirmed-only script publish for that bar? Why should an automated action not assume that the earlier display was final?

## Answer and explanation

The early mean is (6 + 9 + 12) / 3 = 9. The confirmed mean is (6 + 9 + 15) / 3 = 10. The script hides the early point and publishes 10 after confirmation. Acting on the unfinished point uses information that can change before the interval ends. A future alert or trading lesson must specify its observation timing explicitly.

## Continue learning

Practise inputs, history references and missing values before alerts. Then study simulation assumptions, costs and data quality before any strategy experiment. Keep those exercises separate from connecting a broker account.

[Review the prerequisite course](../../../courses/learning-c/index.html).


## Source and further reading

[Read the related Umicom example](https://github.com/umicom-foundation/umicom-framework/blob/f00aa3eb0c165ab0ac0107f81e84e4602d79c170/include/umicom/chart/candle_study.h). Path: `Umicom-Applications/framework/include/umicom/chart/candle_study.h`. This reference connects the topic to the codebase; it does not imply a language runtime or adapter is implemented in Umicom.

[Technical reference](https://www.tradingview.com/pine-script-docs/primer/first-indicator/). Check the version requirements in the lesson before practical work.

[Official Pine execution model](https://www.tradingview.com/pine-script-docs/language/execution-model/).

[Read this lesson as HTML](../../../courses/learning-pinescript/lessons/02-live-bars-and-confirmed-values.html).

[Course contents](index.md) · [Previous: A chart and a price series](01-a-chart-and-a-price-series.md)

Sammy Hegab · Umicom Foundation · Original learning material.
