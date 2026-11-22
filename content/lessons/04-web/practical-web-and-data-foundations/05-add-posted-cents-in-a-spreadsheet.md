<!--
Umicom Bits2Banking
File: content/lessons/04-web/practical-web-and-data-foundations/05-add-posted-cents-in-a-spreadsheet.md

PURPOSE:
Add posted cents in a spreadsheet in the Bits2Banking web and data course.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original learning material. Linked references retain their own terms.
-->

<picture>
  <source srcset="../../../assets/branding/umicom-wordmark-on-dark.svg" media="(prefers-color-scheme: dark)">
  <img src="../../../assets/branding/umicom-wordmark.svg" width="220" alt="Umicom Foundation">
</picture>

# Add posted cents in a spreadsheet

[Course contents](index.md) · [Previous lesson · Read a local statement with Node.js](04-read-the-file-with-node.md) · [Next lesson · Compare SQL database dialects](06-compare-sql-database-dialects.md)

Read a range of spreadsheet cells and use one formula to add only the posted amounts.

## Draw a small grid

A spreadsheet is a grid of boxes called cells. Columns use letters, and rows use numbers. `C2` means the box at column C, row 2. `C2:C4` means the boxes from C2 down to C4. You can draw the grid on paper first. If you already have a spreadsheet app, copy these entries into cells A1 through C4.

```text
       A            B           C
1      ID           Status      Cents
2      1            posted       2600
3      2            posted       -850
4      3            pending       500
```

Enter the amount in C3 as a negative number using a minus sign before 850. The heading `Cents` explains the unit. Keep the amount cells as numbers so formulas can add them.

## Ask for a conditional total

A formula tells the spreadsheet to calculate something. `SUMIF` checks a condition on each row and adds the matching numbers. In cell C6, enter the following formula. It checks column B for `posted`, and takes the amount from the same row in column C.

```text
=SUMIF(B2:B4,"posted",C2:C4)
```

Check these pairs with your finger before looking at the answer. B2 says `posted`, so add C2. B3 says `posted`, so add the negative value in C3. B4 says `pending`, so leave C4 alone. The result is `1750`. The same formula structure is used in Excel and Google Sheets. Regional settings can require different punctuation between the three arguments.

## Try an easy change

Change B4 to `posted` in the practice workbook. Predict the total before pressing Enter. Check for `2250`, then change it back to `pending`. If you get an unexpected total, inspect the status text and confirm the two ranges start and end on matching rows. If the formula appears as text, check that it starts with `=` and that the formula cell is not set to store text.

## Connect to Umicom

A treasury developer can use a small spreadsheet as an independent check of an Umicom TMS practice calculation. Copy a few fictional records into a grid, compute the expected amount, and compare it with the application. A recorded result is more useful when it also includes the three conditions and the units.

- [Introduction to Treasury Management Systems](../../../courses/introduction-to-treasury-management-systems/index.html)
- [Excel SUMIF help](https://support.microsoft.com/en-us/excel/functions/sumif-function)
- [Google Sheets SUMIF help](https://support.google.com/docs/answer/3093583)

[Open the HTML edition](../../../courses/practical-web-and-data-foundations/lessons/05-add-posted-cents-in-a-spreadsheet.html)
