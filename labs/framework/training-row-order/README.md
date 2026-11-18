![Umicom](../../../content/assets/branding/umicom-wordmark.svg)

# Visit training rows once

This C23 program calls Framework's row-order service. It keeps seven training records and two held-out records separate, checks a deterministic permutation, and visits batches containing three, three and one record. It does not allocate a model or train weights.

1. Install CMake, Ninja and a C23-capable compiler as described in the development setup course.
2. Select matching Bits2Banking and Framework source checkouts. Framework must include `sample_order.h` and `sample_order.c`.
3. From Bits2Banking, run these commands separately. Stop on any error.

```powershell
cmake -S labs/framework/training-row-order -B build/learning-row-order -G Ninja -DCMAKE_C_COMPILER=C:/msys64/ucrt64/bin/gcc.exe -DUMICOM_FRAMEWORK_SOURCE=C:/umicom/Umicom-Applications/framework
cmake --build build/learning-row-order
ctest --test-dir build/learning-row-order --output-on-failure
& ".\build\learning-row-order\umicom-training-row-order.exe"
```

Expected training IDs: `30 10 70`, then `40 50 60`, then `20`. The service's temporary index payload is 28 bytes for this example, released before return. That figure excludes the caller's arrays, allocator bookkeeping and process overhead. No source row is moved or changed.

This is a narrow source-based learning composition, not an installed-SDK qualification. The full [step-by-step lesson](../../../content/courses/preparing-llm-training-data/lessons/25-shuffle-an-epoch-without-changing-the-split.html) explains indices, partitions, replacement sampling, batches and resume state.
