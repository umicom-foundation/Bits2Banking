# Episode 29 — Protect Executable Memory and Model a Process Lifecycle

**Duration:** approximately 17–21 minutes  
**Lessons:** [94. Review executable-memory protection](../../lessons/05-engineering/94-review-executable-memory-protection.md) and [95. Model a process lifecycle](../../lessons/05-engineering/95-model-a-process-lifecycle-in-c23.md)  
**Reference:** [Umicom Kernel](https://github.com/umicom-foundation/umicom-kernel)

## Opening: two separate concerns (0:00–2:00)

**On screen:** Split screen: an executable-file diagram and a process-state diagram.

**Narration:**

“An operating system needs to answer two questions about every application. First, what memory may this program read, change or execute? Second, is this process ready to run, currently running, waiting or finished? Those are different responsibilities, but they must work together.

“Today, we will examine a subtle executable-file permission problem and then write a simple C23 process-state machine. Both examples use real engineering practices: explicit limits, testable contracts and safe refusal when a request is not permitted.”

## Demonstration: a hidden page conflict (2:00–6:15)

**On screen:** `elf-page-protection.svg`, then `memory_audit.c`.

**Narration:**

“Here are two parts of a fictional ELF program. The code bytes occupy the addresses from 1000 to 15FF. We want to read and execute them. Our data begins at 1600 and ends at 18FF. We want to read and write it.

“The ranges do not overlap as bytes, but both fit into the same page from 1000 through 1FFF. A processor does not normally store separate permissions for every single byte. The mapping applies to a complete page. If we combine the requested permissions, we would need write and execute on the same page, which deserves careful review.

“This is why a secure loader must reason about *pages*, not just about segments. The new `umicom-education memory-audit` command does exactly that as a read-only inspection.”

**Presenter:** Point to the `writeExecutePages` field and the calculation of rounded page boundaries. Explain that a high-level check must not allocate a 4 KiB object for every virtual page of an untrusted file. The native implementation sweeps a bounded collection of boundaries instead.

## Demonstration: the new Framework command (6:15–9:45)

**On screen:** PowerShell in `C:\umicom\Umicom-Applications`.

```powershell
Set-Location "C:\umicom\Umicom-Applications"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\framework\tools\umicom-education" -B ".\build\umicom-education" -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" -DBUILD_TESTING=ON
cmake --build ".\build\umicom-education" --parallel 2
ctest --test-dir ".\build\umicom-education" --output-on-failure
$Education = ".\build\umicom-education\bin\umicom-education.exe"
$Fixture = ".\build\umicom-education\education-load-plan-test\fixture with spaces\umicom kernel.elf"
& $Education memory-audit --file $Fixture
```

**Narration:**

“The Framework tests generate a harmless ELF fixture, even when the host computer is running Windows. We inspect its declared mappings without attempting to execute RISC-V instructions.

“The fixture should have two mapped pages and no page that requires both write and execute. That is a useful narrow result, but it is not proof that an operating system would safely load or run arbitrary code.”

**Presenter:** Show the direct unit test in `test_memory_audit.c` that deliberately creates two byte-disjoint segments sharing one virtual page. The expected report has one W+X page and one shared page. Highlight why returning a nonzero status for a review finding is useful in build qualification.

## A process is a state machine (9:45–13:30)

**On screen:** Table of five states: New, Ready, Running, Waiting, Terminated.

**Narration:**

“Now consider what happens after a program has been admitted for execution. A scheduler may give it the processor, or a process may wait for input or another event. We can model these changes as a state machine.

“Our classroom process starts at NEW. After admission it becomes READY. Dispatch selects RUNNING. From RUNNING the process can yield, wait or exit. A waiting process becomes ready only after a wake event. A terminated process cannot be restarted by changing an old record.

“The advantage of writing down transitions is that invalid changes become testable. For example, NEW cannot jump directly to TERMINATED, and a failed state change should not partially overwrite process information.”

**On screen:** Open `labs/native/process-lifecycle/process.c`; identify `BtbProcessApply`, revision checks and the local copy used for publication.

## Run the process laboratory (13:30–17:20)

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
cmake -S ".\labs\native\process-lifecycle" -B ".\output\learning-build\process-lifecycle" -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe"
cmake --build ".\output\learning-build\process-lifecycle" --parallel 2
ctest --test-dir ".\output\learning-build\process-lifecycle" --output-on-failure
& ".\output\learning-build\process-lifecycle\btb-process-demo.exe"
```

**Narration:**

“The tests show the legal path from new to terminated and several invalid operations. Notice that the revision number changes only after an accepted transition. When a revision reaches its maximum supported value, the function refuses to wrap it. It does not pretend the old state is new again.

“This is an educational model, not a real process or task scheduler. The actual Umicom Kernel source owns the process registry, thread and scheduling services. We link to that source so you can progress from a few understandable lines of C23 to the genuine implementation.”

## Connect to privileged execution (17:20–19:30)

**On screen:** `arch/riscv64/boot.S` and the lesson on supervisor and user privilege.

**Narration:**

“The kernel must connect those process states to saved registers, address spaces, interrupts and privilege changes. RISC-V starts the original Umicom Kernel boot in machine mode. Its bootstrap establishes the environment required to enter C23. Later subsystems prepare page tables and test hardware translation. The architecture is built piece by piece, with each step examined and tested before the next one.

“Follow Lessons 94 through 96 for the complete explanations. Make one small change in each laboratory, predict its effect, then run the tests. Finally, open the related source in the Umicom Kernel repository and identify which responsibilities are controlled by the processor and the kernel rather than by the application.”

**End card:** Bits2Banking · Umicom Foundation · “We Value Each Other and Together Everyone Achieves More.”
