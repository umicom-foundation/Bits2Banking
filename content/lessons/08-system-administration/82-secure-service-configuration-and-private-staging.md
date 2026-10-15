# Chapter 82 — Configure a service safely in a private staging environment

**Bits to Banking · System Administration From Zero · Stage 6 · Umicom Foundation**  
**Prerequisite:** Chapter 68 (private staging), 70 (readiness) and 77 (least privilege).  
**Safety:** No registry edits, service installation, firewall changes, real passwords or production deployment.

## Why application files and configuration are different

A compiled program contains operations the developer built into it. **Configuration** tells an installation which permitted options to use—for example, a listening address, a local notes directory or a log level. Two installations can run the same executable with different configuration. But configuration is not automatically safe: a single wildcard listener or database URL could expose sensitive functionality.

Umicom Framework provides reusable native configuration, security and application lifecycle contracts. A thin Umicom application should consume those services instead of creating its own configuration parser or introducing a PowerShell/Python setup script. This chapter is about the administrator's responsibilities: examining a configuration change, staging it privately, preserving the last known-good version, and testing the new state.

![Build, test, private stage, readiness and rollback](../../assets/diagrams/sysadmin-admin-change-gates-update43.svg)

## Separate five pieces of a release

| Item | Why it exists | Good practice |
|---|---|---|
| Program binary | Executable implementation. | Hash and identify the tested revision. |
| Configuration file | Deployment-specific settings. | Validate schema and retain approved history. |
| Secret reference | Points to credential storage. | Do not store the secret directly in the repository. |
| Service definition | Describes process start, account and restart policy. | Review privileges and dependencies. |
| Verification evidence | Shows what was actually tested and observed. | Tie results to the exact staged revision. |

## Windows PowerShell — read-only plan and private directory

Start with a check of your current location and a safe candidate prefix:

```powershell
Get-Location
$Stage = Join-Path $HOME "UmicomLearning\private-stage"
Test-Path -LiteralPath $Stage
```

If `True`, examine the existing contents before any writing:

```powershell
Get-ChildItem -LiteralPath $Stage -ErrorAction SilentlyContinue
```

For a harmless Markdown configuration sketch, create a separate text file under a **new** training folder using Notepad:

```powershell
New-Item -ItemType Directory -Path "$HOME\UmicomLearning\service-config-training" -Force
notepad "$HOME\UmicomLearning\service-config-training\notes-configuration-review.md"
```

Write a short *proposal*, not a production configuration: `listen address = 127.0.0.1`, `purpose = read-only Notes demonstration`, `owner = training`, and `secrets = none`. Save and inspect it:

```powershell
Get-Content "$HOME\UmicomLearning\service-config-training\notes-configuration-review.md"
```

This is training documentation. It is **not** a valid `.ini`, `.yaml` or Umicom application manifest, and nobody should use it as operational input.

## Linux terminal — equivalent review

```bash
pwd
ls -la "$HOME/UmicomLearning"
```

If appropriate, create a new personal course folder and open its Markdown review document with your chosen text editor. An editor may be absent; do not install one as root merely to finish this lesson. Keep the simulated configuration outside production locations such as `/etc`.

## How to review a genuine service definition (read-only)

On a Linux system with systemd and an authorised practice service, use a name actually provided by the instructor:

```bash
systemctl --user cat APPROVED_PRACTICE_SERVICE.service
```

This displays user-service unit content without enabling it. The name is a placeholder. If no approved unit exists, record *not available*. On Windows, `Get-Service` displays status but does **not** show the complete executable command or protected credentials; additional inspections must follow authorised procedures.

## A staged change can still be blocked

Suppose the Notes executable was built and tested, but its new configuration points to a database that is unavailable. The process might start and show a PID while failing its actual work. A reviewer should separate process existence, dependency connection, application readiness and a successful Notes transaction. A **restored previous configuration** is a recovery outcome, not evidence that the new configuration deployed successfully.

## Practical worksheet

Record the proposed listener binding, what will change, who approves it, which dependencies may be affected, how the change is tested, and how the previous configuration can be restored. For a first exercise, write **no real secrets** and make **no operating-system service changes**.

## Review questions

1. Why separate configuration from program binaries? **The same tested program can be deployed with different controlled settings.**
2. Is a successful process start proof of service readiness? **No.**
3. Should secrets be committed to Git? **No.**
4. What should a failed change report? **Failure plus any independently observed recovery, not false success.**

**Next:** Chapter 83 — collecting an incident timeline without collecting unnecessary private information.
