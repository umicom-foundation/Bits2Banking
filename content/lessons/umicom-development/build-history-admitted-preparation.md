<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/build-history-admitted-preparation.md

PURPOSE:
Record an admitted failure before a child starts

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
![Umicom](../../assets/branding/umicom-logo.svg)

# Record an admitted failure before a child starts

## Start with a failed attempt

A build command does more than start a compiler. It first resolves the project root, prepares the tool arguments, selects a working directory and owns the environment and diagnostic parser. Any of those steps can fail. A useful development tool must show that refusal as the latest attempt, even when the previous attempt succeeded. Otherwise the interface can present a reassuring result that belongs to older work.



The shared runner distinguishes admission from execution. Admission reserves an operation identity and creates the caller result. Execution begins only after preparation succeeds. A null runner is not admitted. A valid runner whose Run program is missing is admitted, then refused during preparation. Those cases both return an error, but they have different history consequences.



| Boundary | Identity | History |
| --- | --- | --- |
| Invalid caller argument | None | Unchanged |
| Admitted preparation refusal | Reserved ID | Completed failure offered to history |
| Child completion | Same reserved ID | Completed observation offered once |
| Exhausted identity space | No new ID | Unchanged |



## Use the actual Framework boundary

~~~c
UmiStatus status = umi_build_runner_run(runner, UMI_BUILD_PHASE_RUN, result);
if (status == UMI_STATUS_INVALID_STATE) {
    /* Inspect result->operation_id and state before updating presentation. */
}
~~~



The laboratory creates a valid profile with an absolute illustrative root and leaves its Run program empty. The launch-plan contract rejects the missing program before a child can start. The client checks INVALID_STATE, failed state, exit code -1, zero duration and empty child output. It then reads the configured history and compares the retained value with the returned result. This is a real API observation, not a manually invented history entry.



## Exercise: trace single

- Read main.c and locate profile initialisation, runner creation and ObserveRefusal.
- Build the client against an installed SDK using its README. Run the single scenario only after that build succeeds.
- Explain why operation 1 can be retained even though no program ran.
- Identify which checks would fail with an older SDK that omitted preparation failures from history.



## Interpret the laboratory result

The client exits zero when the expected refusal and history are observed. That exit code belongs to the laboratory, while INVALID_STATE belongs to its attempted Run operation. Keep those two layers separate in reports. A successful laboratory result would not establish that a compiler, CTest, an application or Studio launched. Current source and checker expectations are authored; execution still needs owner evidence.



## Recovery and next step

If history is empty, first compare the installed SDK identity with the source containing the shared completion change. Do not change the expected history count to hide an older implementation. Preserve the failed observation and rebuild the correct producer through its normal workflow. Next, examine how history can retain a value after the caller reuses its own buffer.



## Source and practice

<!-- Previous source-tree links are retained for review; public repository routes
     below remain usable after the lesson is published.
[Build-history laboratory and owner commands](../../../labs/native/framework-build-history/README.md) · [HTML edition](../../courses/umicom-development/lessons/build-history-admitted-preparation.html)
-->
[Build-history laboratory and owner commands](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-build-history/README.md) · [HTML edition](../../courses/umicom-development/lessons/build-history-admitted-preparation.html)

[Previous lesson](native-project-qualification-evidence.md) · [Next lesson](build-history-copy-and-lifetime.md) · [Course index](index.md)
