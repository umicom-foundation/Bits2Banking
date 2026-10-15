# Stage 9 practical workbook — three small investigations

**Instructions:** Work on a computer you own or have explicit permission to use. The Notes systems below are fictional. Never collect passwords, secret keys, customer data, patient data or private remote logs.

## Lab A — Which computer am I using? (Chapters 109–110)

1. Open PowerShell 7 or your Linux terminal. Use `Get-Location` or `pwd` to check your current directory.
2. Use `hostname` and an appropriate OS-version command from Chapter 110. Record the command exactly.
3. Copy the time with an offset using `Get-Date -Format o` or `date -Is`.
4. Write one row: `host | purpose | OS | processor architecture | evidence source | time | status`.
5. Create a second fictional row for `notes-storage`. Mark the OS and version **Not observed**.

**Marking points:** The student distinguishes current observations from fictional input, avoids credentials and does not infer a remote host's version from their own computer.

## Lab B — The gateway responds but Notes cannot save (Chapters 111–118)

You are given: a gateway process reports Running; HTTP health responds; the Notes save check fails; storage is reported read-only. One gateway log is at 14:03 UTC, and a storage log at 14:02 UTC. Their clocks differ by three minutes.

1. Put each fact on a separate line; add a **source and confidence** field.
2. Explain why the process and HTTP observations cannot overrule the failed save.
3. Make a list of questions for the storage owner. Do not propose restarting services without checking impact.
4. State why apparent timestamp order does not establish cause until clock uncertainty is reviewed.

**Suggested interpretation:** Business readiness is blocked. Filesystem authority should be investigated. The exact order of events is uncertain. Support can escalate rather than claim a fix.

## Lab C — Recovery is not release qualification (Chapters 117–120)

Policy: permitted RPO is **15 minutes** and RTO is **30 minutes**. A fictional drill recorded estimated data loss **20 minutes** and elapsed recovery **24 minutes**. A proposed application update failed and a previous revision was restored.

1. Identify which objective failed. **Answer:** RPO failed; RTO met.
2. State whether checksum equality alone proves database consistency. **Answer:** no.
3. Label the proposed update. **Answer:** Failed.
4. Label the previous revision after independent functionality checks. **Answer:** Restored to previous state.
5. Write a seven-column incident report: `time | host | observation | source | release | status | next owner`.

## Optional developer extension

Compile `labs/native/fleet-readiness`. Record the outcomes of the named CTest cases and explain why four result states exist. Do not use this offline policy model to monitor a real host. If the program compiles on Linux but not Windows, the Windows acceptance criterion is still open.

## Submission checklist

- Commands can be repeated by another learner.
- All observations have a time and source.
- Permission boundaries are respected.
- Unverified fields are **not** recorded as Passed.
- No live system changes were made.
- Original files and logs remain intact.
