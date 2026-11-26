<!--
Umicom Bits2Banking
File: content/lessons/04-web/web-graphics/02-draw-a-canvas-from-a-table.md

PURPOSE:
  Teach Canvas drawing from real HTML table cells and show the text equivalent.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# 2. Draw a canvas from a table

![Umicom Foundation](../../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A canvas is a drawing surface. JavaScript is used here to call the browser's Canvas 2D API. The three amounts come from the HTML table, and the script draws their heights into the surface when you choose **Draw canvas**.

1. Open the [monthly deposits example](../../../labs/web/web-graphics/monthly-deposits.html). Choose **Draw canvas**. Expect three bars with February tallest and a message saying that three deposits were drawn.
2. Open the [drawing script](../../../labs/web/web-graphics/monthly-deposits.js). Find `canvas.getContext("2d")`. This gets the objects and operations needed to draw lines, rectangles and text. Find `fillRect(x, baseline - amount, 42, amount)`. It takes the left position, top position, width and height.
3. In a working copy of the HTML, change March to `80` in the table only. Reload and choose **Draw canvas** again. March should become the tallest bar in the canvas. The SVG stays at its earlier value until you edit its corresponding rectangle. A live report should render each view from the same data instead of keeping two sets of manually edited values.
4. Change March to `101` and try again. The exercise limits amounts to 0–100 because of its chosen drawing space. It should explain that range and hide the canvas. Restore a valid amount to draw again.
5. In your copy, change the HTML script's `src="monthly-deposits.js"` to `src="missing-script.js"` and reload. The drawing button should stay hidden. You should still see every amount in the table. Restore the original script name and reload again.

A bar drawn with `fillRect` is a group of pixels. The browser can expose the table's header and cell relationships to assistive tools, so this example keeps the table as the complete source of the values. If the draw button is missing, confirm that the script is next to the HTML file and your browser permits local scripts.

[Give an icon link a clear name](03-label-an-icon-link.md) · [Course contents](index.md) · [Canvas element reference](https://html.spec.whatwg.org/multipage/canvas.html#the-canvas-element)
