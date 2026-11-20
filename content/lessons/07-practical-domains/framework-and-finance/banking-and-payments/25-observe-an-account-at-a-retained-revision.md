![Umicom](../../../../assets/branding/umicom-wordmark.svg)

# Observe a bank account at a retained revision

Two revisions of a practice ledger can show the same amount available to spend for different reasons. A **revision** counts accepted operations in one selected database. Write that number beside each balance you quote.

## Calculate the three amounts

**Booked** is the amount recorded by completed postings. **Reserved** is the part set aside for an outstanding operation. In this practice ledger, **available** equals booked minus reserved. With GBP at scale 2, one minor unit is one penny.

| Revision | Operation | Booked pence | Reserved pence | Available pence |
| --- | --- | ---: | ---: | ---: |
| 6 | Funding already posted | 100,000 | 0 | 100,000 |
| 7 | Transfer submitted | 100,000 | 15,000 | 85,000 |
| 8 | Transfer approved | 100,000 | 15,000 | 85,000 |
| 9 | Transfer posted | 85,000 | 0 | 85,000 |
| 10 | Transfer reversed | 100,000 | 0 | 100,000 |

Calculate the available amount yourself. GBP 150.00 is reserved at revisions 7 and 8. At revision 9, the booked amount drops to GBP 850.00 and no reservation remains.

## Run the practice checks

1. Open the Umicom Framework source directory. Have CMake, Ninja, a C23 compiler and SQLite development files available.
2. Configure and build the standalone Bank review. It uses synthetic accounts.
3. Run the selected tests. Expect five passes. The SQLite case closes and reopens a practice file before checking the older reserved balance and the balance after posting.

```powershell
cmake -S examples/bank_review -B build/bank-history -G Ninja -DUMICOM_BANK_REVIEW_SQLITE=ON
cmake --build build/bank-history
ctest --test-dir build/bank-history --no-tests=error --output-on-failure -R 'account-observation'
```

If CMake cannot find SQLite, use the development files for the compiler selected in that terminal. Use a fresh build directory when changing compilers. Keep the tests on disposable practice data.

## Read an existing practice database

When your Umicom Bank installation includes the historical account command, supply an existing practice path, the account ID and a retained decimal revision. Adjust the path and ID for your practice ledger.

```powershell
.\umicom-bank-console.exe --observe-account 'C:/practice/bank.sqlite' a1 7
```

**Observed revision** identifies the snapshot. **Loaded revision** identifies how far the ledger had advanced when you opened it. The command refuses revisions beyond the loaded ledger and cannot return an account that opened after the requested revision. If the command is unavailable, check that the installed console and Framework SDK support historical account observations.

Framework's `UmiBankOperationsObserveAccountAtRevision` applies the retained ledger operations in order to an isolated copy. The returned values include exact minor units and the requested revision. A refused query preserves the earlier value in the caller's output.

## Practice

Explain why the available balance stays at 85,000 pence from revision 7 to revision 9. Name the revision where the booked balance changes. Predict the result for an account opened at revision 3 when you ask for revision 2.

[Framework banking operations header](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/bank_operations/operations.h) · [Offline lesson](../../../../courses/framework-and-finance/banking-and-payments/lessons/25-observe-an-account-at-a-retained-revision.html) · [Umicom icon](../../../../assets/branding/umicom.ico)
