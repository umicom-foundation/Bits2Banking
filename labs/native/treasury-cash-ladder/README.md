# Treasury cash ladder — native C23 teaching laboratory

Purpose: provide a *standalone classroom model* for exact minor-unit receipts/payments by currency, value date, and confidence level (forecast, confirmed, settled). It cannot transfer funds, read bank accounts, open Calypso, connect to a network, or persist anything. The fixed-capacity, copied `BtbCashFlow` records are owned by the `BtbCashLadder` value. No heap allocation is needed. The unchanged-output-on-error contract is important when a cash forecast cannot be trusted.

**Source of truth:** Before promoting reusable functions into production, investigate `Umicom Framework` finance decimal, cash planning and TMS APIs. The educational lab intentionally avoids creating a second production data store or FX service. It does not use a real bank feed or vendor binary.

From PowerShell, in your Bits2Banking checkout:

```powershell
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\treasury-cash-ladder" -B ".\output\learning-build\treasury-cash-ladder" -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" -DBUILD_TESTING=ON
cmake --build ".\output\learning-build\treasury-cash-ladder" --parallel 2
ctest --test-dir ".\output\learning-build\treasury-cash-ladder" --no-tests=error --output-on-failure
& ".\output\learning-build\treasury-cash-ladder\btb-treasury-cash-demo.exe"
```

Try changing a forecast receipt to `BTB_CASH_SETTLED`, observe the difference in totals, and explain why neither state can be inferred from process uptime. The demo does not make a real payment.
