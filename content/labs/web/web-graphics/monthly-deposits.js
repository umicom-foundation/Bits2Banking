/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: content/labs/web/web-graphics/monthly-deposits.js
 *
 * PURPOSE:
 *   Draw the example's three table values with the browser's Canvas 2D API.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
const canvas = document.getElementById("deposits-canvas");
const button = document.getElementById("draw-canvas");
const result = document.getElementById("canvas-result");
const rows = document.getElementById("deposit-values").rows;
const context = canvas.getContext("2d");

if (context) {
  button.hidden = false;
  button.addEventListener("click", () => {
    // Keep the table as both the text equivalent and the input to the drawing.
    const deposits = Array.from(rows, (row) => {
      const text = row.cells[1].textContent.trim();
      return { month: row.cells[0].textContent.trim(), amount: text === "" ? NaN : Number(text) };
    });
    const baseline = 112;
    if (deposits.length !== 3 ||
        deposits.some(({ amount }) => !Number.isInteger(amount) || amount < 0 || amount > 100)) {
      canvas.hidden = true;
      result.textContent = "Use three whole-pound deposits between 0 and 100.";
      return;
    }

    // Redraw the surface on each click so a new value cannot leave a stale bar.
    context.fillStyle = "#fff";
    context.fillRect(0, 0, canvas.width, canvas.height);
    context.fillStyle = "#292f36";
    context.fillRect(12, baseline, 228, 1);
    context.font = "12px Segoe UI, sans-serif";
    context.textAlign = "center";
    deposits.forEach(({ month, amount }, index) => {
      const x = 27 + index * 78;
      context.fillStyle = "#1f5e99";
      context.fillRect(x, baseline - amount, 42, amount);
      context.fillStyle = "#292f36";
      context.fillText(month.slice(0, 3), x + 21, 130);
    });
    canvas.hidden = false;
    result.textContent = "Canvas drawn from 3 deposits.";
  });
}
