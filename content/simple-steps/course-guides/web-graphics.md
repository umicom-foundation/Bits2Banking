<!--
Umicom Bits2Banking
File: content/simple-steps/course-guides/web-graphics.md

PURPOSE:
  Guide learners through a local SVG, Canvas and icon practice session.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check a report's web graphics

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

1. Open the [monthly deposits example](../../labs/web/web-graphics/monthly-deposits.html). Read January, February and March in the table. Write down which deposit was largest.
2. Locate February's bar in the SVG. Choose **Draw canvas** and check that February is the tallest in both drawings.
3. In a working copy, change March's table value from `50` to `80`. Keep the HTML and JavaScript files together in their original folders. Reload and draw again. The canvas should now show March as tallest.
4. Update the SVG's March rectangle to `y="32"` and `height="80"`. Change the SVG description to say March is tallest. Reload and confirm that the table, both drawings and the description all agree.
5. Use **Tab** and **Enter** to follow **Read the deposit table**. Check the name of the link in the browser's accessibility inspector. Its words should tell you where it goes.

If the canvas is missing, check whether the script loaded. If the two charts disagree, compare their heights against the table one row at a time. If a reader cannot use the drawing, they should still be able to get the numbers and their month names from the table.

[Read the Web Graphics course](../../lessons/04-web/web-graphics/index.md) · [Learning in Simple Steps](../index.md)
