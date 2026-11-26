<!--
Umicom Bits2Banking
File: content/lessons/04-web/web-graphics/03-label-an-icon-link.md

PURPOSE:
  Teach clear HTML link names when a small SVG illustration accompanies the text.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# 3. Give an icon link a clear name

![Umicom Foundation](../../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

An icon is a small image associated with a control or piece of information. A picture of three bars might suggest a chart, statistics or a report. Use words that tell the reader what will actually happen.

1. In the [monthly deposits example](../../../labs/web/web-graphics/monthly-deposits.html), press **Tab** to reach **Read the deposit table**. Press **Enter**. The link moves to the heading above the table.
2. Open the source and find `href="#deposit-data"`. The text after `#` identifies the heading. The link's readable text tells the user the destination.
3. Find `aria-hidden="true"` on the little SVG inside the link. The drawing adds no information beyond the text, so it is hidden from assistive tools. `focusable="false"` leaves the enclosing link as the only keyboard stop for that control.
4. Change the visible link text in a working copy to **Compare monthly deposits**, and reload. The icon stays the same, but the link's words still explain its purpose. Use your browser's accessibility inspector to check that the link name is the text you wrote.
5. In your copy, add `aria-label="Compare monthly deposits"` to the `<a>` element, then remove its visible text. Keep the SVG and the destination. The page shows an icon-only link. Press **Tab**, use **Enter** and check that the accessibility inspector still names the link **Compare monthly deposits**. Restore the visible wording and remove `aria-label` to give the link its name from the text again.
6. If a meaningful image stands on its own, give readers the meaning in words. In this example the larger SVG has a title and description, and the table provides the full values. The icon inside the link accompanies the link's name.

For navigation, use a link with a destination. For an action, use a button with a clear text name, as the example does for **Draw canvas**. If pressing **Tab** never reaches a control, first check that it is a real HTML link or button and still has a visible focus indicator.

[Practise all three checks](../../../simple-steps/course-guides/web-graphics.md) · [Course contents](index.md) · [W3C guide to image text alternatives](https://www.w3.org/WAI/tutorials/images/decision-tree/)
