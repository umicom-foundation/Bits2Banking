# Stage 7 — Security operations, configuration and recovery

**System Administration From Zero · Bits2Banking · Umicom Foundation**  
**Chapters:** 85–96 of the cumulative course. **Audience:** newcomers, returning professionals and supervised younger learners.

## What you will be able to explain

Stage 7 develops the habits of a reliable junior system administrator: observe before acting, identify the authoritative owner, distinguish a configured value from a running service's effective state, protect private information and verify recovery independently. No lesson requires an administrator password, a production server, a GitHub account or the installation of new application code.

| Lesson | Practical question | Safe learning exercise |
| --- | --- | --- |
| [85. Everyday security operations](85-security-operations-in-everyday-administration.md) | Is a running app necessarily secure? | Evidence status card |
| [86. Account lifecycle](86-user-account-lifecycle-and-offboarding.md) | What happens when someone changes roles? | Joiner–mover–leaver matrix |
| [87. Groups and ACLs](87-groups-acls-and-safe-permission-review.md) | Who may read or edit a file? | Read-only permissions review |
| [88. Configuration and secrets](88-service-configuration-overrides-and-secrets.md) | Why does the same program behave differently? | Fictional local configuration |
| [89. Baselines and drift](89-configuration-baselines-drift-and-sha256.md) | How can we detect a changed file? | SHA-256 comparison |
| [90. Updates and maintenance](90-updates-patches-and-maintenance-windows.md) | How should updates be approved? | Fictional change plan |
| [91. Endpoint and firewall evidence](91-firewalls-endpoint-security-and-control-evidence.md) | What does a green security icon prove? | Read-only status checks |
| [92. Credential rotation](92-credentials-rotation-and-secrets-hygiene.md) | How are secrets replaced safely? | No-secret rotation runbook |
| [93. Certificates and trust](93-certificate-expiry-trust-and-clock-checks.md) | Why does HTTPS fail on some computers? | Read-only clock/cert review |
| [94. Audit and logs](94-logs-audit-alerts-retention-and-privacy.md) | How should an incident be recorded? | Redacted event timeline |
| [95. Recovery](95-rollback-restoration-and-independent-recovery.md) | What proves a rollback really helped? | Harmless practice restore |
| [96. Capstone](96-capstone-safe-umicom-security-operations-review.md) | Can a trainee report missing evidence? | C23 evidence-gate verification |

## Recommended reading path

For an absolute beginner, read Chapters 85–87 before writing any practice file. Then follow 88–89 in order because the SHA-256 exercise uses the file made in Chapter 88. Chapters 90–94 introduce operational controls independently, while Chapter 95 reuses the harmless file from Chapter 89. Chapter 96 combines all concepts. Learners who do not have GCC or CMake can complete the written capstone first and mark the executable component Not Run.

## Companion material

The [Stage 7 workbook](stage-7-workbook.md) contains guided tasks and an assessment. The [command reference](stage-7-safe-command-reference.md) distinguishes read-only checks from practice-file writes. The [glossary](stage-7-glossary.md) defines every new term. The [instructor guide](stage-7-instructor-guide.md) explains marking and safe classroom demonstrations.

**Important:** Educational review statuses never confer permission to administer a real service. A class may inspect only owned or explicitly authorised practice systems. Never use another person's credentials, disable protective software, create an actual public listener or collect patient/banking information for a demonstration.
