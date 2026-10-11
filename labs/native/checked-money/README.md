# Checked money — an exact C23 arithmetic laboratory

This program simulates a transfer between two fictional education budgets. Both balances are stored as an **integer number of pence**: `15000` represents £150.00. It uses no floating-point monetary calculation.

It is not a bank, payment rail, accounting engine or transaction service. The example runs in one process, does not persist state and is not safe for concurrent modification. Real financial applications require Framework-owned monetary contracts, database transactions, authorisation, audit and reconciliation.

## Build and test on Windows

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\checked-money" -B ".\output\learning-build\checked-money" -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe"
cmake --build ".\output\learning-build\checked-money" --parallel 2
ctest --test-dir ".\output\learning-build\checked-money" --output-on-failure
& ".\output\learning-build\checked-money\bits2banking-checked-money.exe"
```

## Build and test on Linux

```bash
cmake -S labs/native/checked-money -B output/learning-build/checked-money -G Ninja
cmake --build output/learning-build/checked-money --parallel 2
ctest --test-dir output/learning-build/checked-money --output-on-failure
./output/learning-build/checked-money/bits2banking-checked-money
```

## Inspect the implementation

`BtbCheckedAdd` checks `left > UINT64_MAX - right` **before adding**. `BtbCheckedMultiply` checks `left > UINT64_MAX / right` only when `right` is non-zero. `BtbAccountTransfer` calculates two new balances and two new revision numbers before changing either account.

The tests try an overflowing credit, a debit larger than the fictional balance and a revision that cannot be incremented. Each refused operation preserves both account records.

## Extend the exercise

Change the demonstration transfer to £12.50 (1,250 pence). Predict both final balances and revisions before running the program. Add a test where the destination revision is `UINT64_MAX`, then verify that neither account changes.

See [Checked arithmetic in C23](../../../content/lessons/03-native-code/59-checked-arithmetic-and-money.md).
