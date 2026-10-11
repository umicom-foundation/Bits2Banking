# Process lifecycle — C23 laboratory

A process state machine is a way to reason about work that is ready, running, waiting or finished. This example models those transitions without launching a real program or scheduling a real CPU.

From `C:\umicom\Umicom-Bits2Banking`:

```powershell
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\process-lifecycle" -B ".\output\learning-build\process-lifecycle" -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe"
cmake --build ".\output\learning-build\process-lifecycle" --parallel 2
ctest --test-dir ".\output\learning-build\process-lifecycle" --output-on-failure
& ".\output\learning-build\process-lifecycle\btb-process-demo.exe"
```

Follow the `NEW → READY → RUNNING → WAITING → READY → RUNNING → TERMINATED` transitions. Unsupported transitions preserve the complete previous state. A revision counter detects when a caller is using older state, and refuses overflow rather than wrapping to zero.

For a real kernel implementation, follow [Umicom Kernel's process registry and supervisor](https://github.com/umicom-foundation/umicom-kernel/tree/main/kernel). A real operating-system scheduler requires interrupts, separate address spaces, CPU state and privilege transitions that the teaching model deliberately does not implement.
