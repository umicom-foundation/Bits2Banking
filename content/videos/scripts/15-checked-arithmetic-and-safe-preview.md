# Episode 15 — Check before changing: exact money and website previews

**Duration:** 17–22 minutes  
**Companion lessons:** [Checked arithmetic](../../lessons/03-native-code/59-checked-arithmetic-and-money.md) and [Build and preview the website](../../lessons/05-engineering/62-build-and-preview-the-education-site.md)

## 00:00–03:00 — An apparently simple transfer

**On screen:** Show two fictional balances: education £150.00 and materials £40.00. Place a proposed transfer of £25.00 between them.

**Narration:**

> We want our training application to move twenty-five pounds from one fictional budget to another. The expected result is easy to calculate: one hundred and twenty-five pounds remains in education, and sixty-five pounds is now in materials.
>
> The computer stores these amounts as integer pence. Why? Because an integer gives us exact units. It also gives us a new question: what if the amount we try to calculate cannot fit in the integer type?

## 03:00–08:00 — Checked unsigned arithmetic

**On screen:** Open `checked-money/account.c`, then show the arithmetic check and the accompanying diagram.

**Narration:**

> An unsigned 64-bit integer has a largest possible value. If we add beyond that value, the arithmetic wraps around to a smaller result. C defines that wraparound, but our account model must not accept it.
>
> We therefore compare the starting value with the maximum minus the proposed addition. Only when it is safe do we perform the addition. The key principle is that we check **before** using the calculation.

**Demonstration:** Open `test_account.c` and show a rejected addition of one to `UINT64_MAX`. Run the test. Explain that the output value remains unchanged on refusal.

## 08:00–12:00 — Prepare the whole fictional transfer

**On screen:** Show `checked-money-before-commit.svg`, highlighting each of the four checks.

**Narration:**

> Our transfer has more than one number. We must subtract from the source, add to the recipient and advance two revision values. If the recipient cannot accept the amount, we cannot change the source and claim the transfer succeeded.
>
> The teaching implementation prepares all four values in temporary storage. It changes both records only after every check passes. This is useful reasoning for financial systems and for non-financial software too. But it is not a banking transaction engine; there is no durable database transaction, security policy or audit trail in this exercise.

**Demonstration:** Build the checked-money project in PowerShell, run CTest and then run the demonstration. Read the balances and compare them to the opening prediction.

## 12:00–17:00 — Build and preview the learning website

**On screen:** Switch to `education-build-serve.svg`. Show `content/`, `mkdocs.yml` and generated `site/index.html`.

**Narration:**

> The same idea of checking before acting is useful in our education tools. The native server cannot serve a page that has not been generated. The `doctor` command checks prerequisites, but it does not create HTML pages.
>
> First we run `umicom-education build`. That uses MkDocs to convert Markdown into the website. We confirm that `site/index.html` exists, then run `umicom-education serve`. The new `serve --build` option makes both steps available as one explicit operation. If the build fails, the server does not start.

**Demonstration:**

```powershell
Set-Location "C:\umicom\Umicom-Applications"
$Education = ".\build\umicom-education\bin\umicom-education.exe"
$Books = "C:\umicom\Umicom-Bits2Banking"
$Python = "$Books\.venv\Scripts\python.exe"

& $Education serve --repo $Books --build --python $Python --port 8765
```

Open the local address, show a lesson and navigate to the original Islam volume. Stop the server with Ctrl+C. If MkDocs reports a content error, show the actual diagnostic instead of ignoring it.

## 17:00–20:00 — Practise and share

**Narration:**

> For the first exercise, change the fictional transfer from twenty-five pounds to twelve pounds fifty pence and predict the result. For the second, add a sentence to a lesson, rebuild the website and see it appear in your browser.
>
> These are small steps, but the skills accumulate: write a contract, check inputs, test the result and share what you learn with the next contributor.

**End screen:** Links to Bits2Banking lessons, owned-notes and checked-money sources, Umicom Framework, and instructions for a first documentation contribution.
