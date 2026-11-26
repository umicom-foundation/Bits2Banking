<!--
Umicom Bits2Banking
File: content/lessons/04-web/web-graphics/01-scale-an-svg-chart.md

PURPOSE:
  Teach the SVG coordinate system using a small monthly deposits chart.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# 1. Scale an SVG chart

![Umicom Foundation](../../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

SVG stores a picture as shapes with positions and sizes. In this report, a blue rectangle stands for one month's deposits. The height is the amount in pounds, and all three bars start from the same baseline.

1. Open the [monthly deposits example](../../../labs/web/web-graphics/monthly-deposits.html). Read the table before looking at the bars. It gives £40 in January, £60 in February and £50 in March.
2. Open the HTML source in your editor and find the chart's `viewBox="0 0 252 140"`. Its first two numbers mark the drawing's origin. Its last two numbers give the width and height of the drawing space. The browser can display the same drawing at a different size.
3. Find February's rectangle. The `x` coordinate places it along the chart. Its top is at `y="52"` and its height is `60`, so its bottom is at `52 + 60 = 112`. SVG's y coordinate grows downward from the top.

~~~html
<rect x="105" y="52" width="42" height="60" />
~~~

4. In a working copy, change February to £70 in the table. Change that rectangle to `y="42"` and `height="70"`. Reload the example. The February bar should grow toward the top and its bottom should still meet the baseline.
5. Change the chart's HTML `width` and `height` from `252` and `140` to `126` and `70`. Keep the `viewBox` values. All three bars should shrink together and February should still be tallest.

Keep the actual numbers in the table and the SVG's `title` and `desc` accurate. If only the top of a bar moves, check that `y + height` still equals `112`. If the chart is squeezed, restore dimensions in the same ratio as the drawing space.

[Draw the same values on a canvas](02-draw-a-canvas-from-a-table.md) · [Course contents](index.md) · [W3Schools SVG tutorial](https://www.w3schools.com/graphics/svg_intro.asp)
