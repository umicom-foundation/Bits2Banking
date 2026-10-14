# Stage 4 Instructor Guide — Managed Services and Recovery

**Umicom Foundation · Bits to Banking · Chapters 49–60**

## Audience and teaching standard

This stage is suitable for a school technology club, adult beginners, a community workshop or a technical refresher group. Explanations are professional but assume no prior administration vocabulary. Define each term before using it and demonstrate a command in a normal user shell before discussing privileges or exceptions.

## Four 90-minute teaching sessions

| Session | Chapters | Shared practical activity | Evidence to retain |
|---|---|---|---|
| 1 — What starts and who owns it? | 49–52 | Read service states, identities, unit files and scheduled tasks | Distinguish service name, owner, scheduler and readiness |
| 2 — What configuration is effective? | 53–54 | Use one harmless temporary variable; record installed tool versions | Explain scope, precedence and a reviewed maintenance plan |
| 3 — Is the service healthy and recoverable? | 55–58 | Observe metrics/listeners; restore a practice note to a separate directory | Separate observation, network exposure and recovery verification |
| 4 — How should we respond to change failure? | 59–60 | Incident timeline and C23 maintenance simulation | Full CTest transcript, fictional recovery outcome and escalation note |

Allow additional time for keyboard practice. Students should not be penalised for slow typing. Encourage them to repeat the *meaning* of a command before pressing Enter.

## Safety requirements

Use a non-elevated Windows PowerShell 7 session or an authorised Linux account. A young learner should use a supervised device and practise only inside an explicitly named private directory. Do not use production service accounts, customer records, bank data, patient data, live trading environments, package upgrades, firewall changes or system-wide scheduled tasks for demonstrations. For Linux-only systemd activities, a tutor may show a recorded walkthrough where a student's machine lacks systemd.

The two practice-write exercises are explicitly confined to the student's own `UmicomLearning` folders. Check destination filenames before creating or copying text. Do not use wildcards, force overwrites or deletion as teaching shortcuts.

## Explain failed commands correctly

A missing `systemctl` in a container, a restricted Windows Event Log query or no task returned by `crontab -l` is not evidence that the student has failed. Teach how to identify environmental prerequisites and record **not performed**, **not available**, **restricted**, **passed** and **failed** separately.

## Guide the C23 lab

The new `maintenance-review` project composes the unchanged Update 40 `service-readiness` library, which composes unchanged Update 39 `sysadmin-evidence`. Compile it with CMake + Ninja and require an actual CTest report. Discuss the difference between a test *passing when it rejects bad input* and a real service *failing verification*. Show the demo's `ROLLBACK_REQUIRED` and `RESTORED` outputs; explain why the second does not mean the upgrade succeeded.

## Sample mentoring questions

Ask learners to explain why `0.0.0.0` is a bind wildcard rather than a secure destination; why a scheduled report is not proof of execution; why a service account should have fewer rights than a local administrator; why a copied file is not a tested backup; and what evidence a real Umicom OS operator would need before updating a Framework gitlink.

## Source and publication standards

Preserve the original guide and all earlier chapters. New C23 teaching source must not become a duplicate of Umicom Framework's security, VCS, service or deployment implementation. PowerShell is for interactive commands only; no new `.ps1` or `.py` implementation files. Peer-review the standalone HTML course, Markdown and MkDocs navigation before publication. The Windows build and the hosted site require independent verification.
